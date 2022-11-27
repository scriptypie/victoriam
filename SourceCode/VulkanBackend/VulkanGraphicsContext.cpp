//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <set>
#include <unordered_set>

#include "VulkanGraphicsContext.hpp"
#include <vulkan/vulkan_beta.h>

VISRCBEG

namespace
{

	VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback
	(
			VkDebugUtilsMessageSeverityFlagBitsEXT,
			VkDebugUtilsMessageTypeFlagsEXT,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void*
	)
	{
		ViLog("%s\n", pCallbackData->pMessage);
		return VK_FALSE;
	}

	VkResult CreateDebugMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
	                                 VkDebugUtilsMessengerEXT *pDebugMessenger)
	{
		auto func = CCast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
		if (func == nullptr)
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		return func(instance, pCreateInfo, nullptr, pDebugMessenger);
	}

	void DestroyDebugMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT DebugMessenger)
	{
		auto func = CCast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
		if (func) func(instance, DebugMessenger, nullptr);
	}

}

CVulkanGraphicsContext::CVulkanGraphicsContext(const SShared<CWindow> &window)
	: m_Window(window)
{
	CreateGraphicsInstance();
	SetupDebugMessenger();
	CreateSurface();
	ChoosePhysicalDevice();
	CreateLogicalDevice();
	CreateCommandPool();
}

CVulkanGraphicsContext::~CVulkanGraphicsContext()
{
	vkFreeCommandBuffers(m_Device, m_CmdPool, CCast<UInt32>(m_CmdBuffers.size()), m_CmdBuffers.data());
	m_CmdBuffers.clear();

	vkDestroyCommandPool(m_Device, m_CmdPool, nullptr);
	m_CmdPool = nullptr;

	vkDestroyDevice(m_Device, nullptr);
	m_Device = nullptr;

	if (m_EnableValidation)
		DestroyDebugMessengerEXT(m_Instance, m_DebugMessenger);
	m_DebugMessenger = nullptr;

	vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
	m_Surface = nullptr;
	vkDestroyInstance(m_Instance, nullptr);
	m_Instance = nullptr;
}

void CVulkanGraphicsContext::CreateGraphicsInstance()
{
	if (m_EnableValidation && !CheckValidationLayerSupport())
	{
		ViAbort("Validation layers requested, but not available!");
	}

	VkInstanceCreateInfo instanceCreateInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
	VkApplicationInfo info = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
	info.pApplicationName = "VIsualEditor";
	info.pEngineName = "Victoriam Engine";
	info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	info.apiVersion = VK_API_VERSION_1_0;
	instanceCreateInfo.pApplicationInfo = &info;
	auto extensions = GetRequiredExtensions();
#ifdef __APPLE__
	instanceCreateInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
	extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif
	instanceCreateInfo.enabledExtensionCount = CCast<UInt32>(extensions.size());
	instanceCreateInfo.ppEnabledExtensionNames = extensions.data();
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
	if (m_EnableValidation)
	{
		instanceCreateInfo.enabledLayerCount = CCast<UInt32>(VALIDATION_LAYERS.size());
		instanceCreateInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();
		PopulateDebugMessengerCreateInfo(debugCreateInfo);
		instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
	}
	else
	{
		instanceCreateInfo.enabledLayerCount = 0;
		instanceCreateInfo.pNext = nullptr;
	}
	if (vkCreateInstance(&instanceCreateInfo, nullptr, &m_Instance) != VK_SUCCESS)
	{
		ViAbort("Failed to create graphics engine instance!");
	}
	HasGLFWRequiredInstanceExtensions();
}

void CVulkanGraphicsContext::SetupDebugMessenger()
{
	if (!m_EnableValidation) return;
	VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
	PopulateDebugMessengerCreateInfo(createInfo);
	if (CreateDebugMessengerEXT(m_Instance, &createInfo, &m_DebugMessenger) != VK_SUCCESS)
	{
		ViAbort("Failed to set up debug messenger!");
	}
}

void CVulkanGraphicsContext::CreateSurface()
{
	Accessors::Window::CreateWindowSurface(m_Window, m_Instance, &m_Surface);
}

void CVulkanGraphicsContext::ChoosePhysicalDevice()
{
	UInt32 deviceCount = {};
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);
	if (!deviceCount) { ViAbort("There's no supported GPU!"); }
	CList<VkPhysicalDevice> physicalDevices(deviceCount);
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, physicalDevices.data());

	VIGNORE std::find_if(physicalDevices.begin(), physicalDevices.end(), [&](const auto& device) -> Bool
	{
		if (IsPhysicalDeviceSuitable(device))
		{
			m_PhysicalDevice = device;
			return true;
		}
		return false;
	});

	if (m_PhysicalDevice == nullptr)
	{
		ViAbort("Failed to find a suitable GPU!");
	}
	vkGetPhysicalDeviceProperties(m_PhysicalDevice, &m_Properties);
	// log here
}

void CVulkanGraphicsContext::CreateLogicalDevice()
{
	SQueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);
	CList<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<UInt32> uniqueQueueFamilies = { indices.GraphicsFamily, indices.PresentFamily };
	Float32 queuePriority = 1.0F;
	for (UInt32 queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo = { VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO };
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}
	VkPhysicalDeviceFeatures features = {};
	features.samplerAnisotropy = VK_TRUE;

	VkDeviceCreateInfo createInfo = { VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };
	createInfo.queueCreateInfoCount = CCast<UInt32>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.pEnabledFeatures = &features;
	createInfo.enabledExtensionCount = CCast<UInt32>(DEVICE_EXTENSIONS.size());
	createInfo.ppEnabledExtensionNames = DEVICE_EXTENSIONS.data();

	if (m_EnableValidation)
	{
		createInfo.enabledLayerCount = CCast<UInt32>(VALIDATION_LAYERS.size());
		createInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();
	}
	else
		createInfo.enabledLayerCount = 0;

	if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device) != VK_SUCCESS)
	{
		ViAbort("Failed to create logical device!");
	}

	vkGetDeviceQueue(m_Device, indices.GraphicsFamily, 0, &m_GraphicsQueue);
	vkGetDeviceQueue(m_Device, indices.PresentFamily, 0, &m_PresentQueue);
}

void CVulkanGraphicsContext::CreateCommandPool()
{
	SQueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);

	VkCommandPoolCreateInfo createInfo = { VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
	createInfo.queueFamilyIndex = indices.GraphicsFamily;
	createInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	if (vkCreateCommandPool(m_Device, &createInfo, nullptr, &m_CmdPool) != VK_SUCCESS)
	{
		ViAbort("Failed to create command pool!");
	}
}

Bool CVulkanGraphicsContext::IsPhysicalDeviceSuitable(VkPhysicalDevice device)
{
	SQueueFamilyIndices indices = FindQueueFamilies(device);
	Bool extensionsSupported = CheckDeviceExtensionSupport(device);
	Bool swapchainIsOkay;
	if (extensionsSupported)
	{
		SSwapchainSupportDetails swapchainSupportDetails = QuerySwapchainSupport(device);
		swapchainIsOkay = !swapchainSupportDetails.formats.empty() && !swapchainSupportDetails.presentModes.empty();
	}
	VkPhysicalDeviceFeatures supportedFeatures;
	vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

	return indices.IsCompleted() && extensionsSupported && swapchainIsOkay && supportedFeatures.samplerAnisotropy;
}

CList<CString> CVulkanGraphicsContext::GetRequiredExtensions() const {
	UInt32 glfwExtensionCount = {};
	CString* glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	CList<CString> requiredExtensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
	if (m_EnableValidation)
		requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	return requiredExtensions;
}

Bool CVulkanGraphicsContext::CheckValidationLayerSupport()
{
	UInt32 layerCount = {};
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	CList<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (CString layerName : VALIDATION_LAYERS)
	{
		Bool layerFound = false;

		for (const auto& layerProperties : availableLayers)
			if (!strcmp(layerName, layerProperties.layerName))
			{
				layerFound = true;
				break;
			}

		if (!layerFound) return false;
	}
	return true;
}

SQueueFamilyIndices CVulkanGraphicsContext::FindQueueFamilies(VkPhysicalDevice device)
{
	SQueueFamilyIndices indices;

	UInt32 queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	CList<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	UInt32 i = {};
	for (const auto &queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) ) {
			indices.GraphicsFamily = i;
			indices.GraphicsFamilyHasValue = true;
		}
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_Surface, &presentSupport);
		if (queueFamily.queueCount > 0 && presentSupport) {
			indices.PresentFamily = i;
			indices.PresentFamilyHasValue = true;
		}
		if (indices.IsCompleted()) {
			break;
		}

		i++;
	}

	return indices;
}

void CVulkanGraphicsContext::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &info)
{
	info                    = { VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT };
	info.messageSeverity    =   VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			                    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	info.messageType        =   VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			                    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
							    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	info.pfnUserCallback = DebugCallback;
	info.pUserData = nullptr;  // Optional
}

void CVulkanGraphicsContext::HasGLFWRequiredInstanceExtensions()
{
	UInt32 extensionCount = {};
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	CList<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	std::unordered_set<String> available;
	for (const auto &extension : extensions)
		available.insert(extension.extensionName);

	auto requiredExtensions = GetRequiredExtensions();
	for (const auto &required : requiredExtensions)
		if (available.find(required) == available.end())
			throw std::runtime_error("Missing required glfw extension");
}

Bool CVulkanGraphicsContext::CheckDeviceExtensionSupport(VkPhysicalDevice device)
{
	UInt32 extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	CList<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<String> requiredExtensions(DEVICE_EXTENSIONS.begin(), DEVICE_EXTENSIONS.end());

	for (const auto &extension : availableExtensions)
		requiredExtensions.erase(extension.extensionName);

	return requiredExtensions.empty();
}

SSwapchainSupportDetails CVulkanGraphicsContext::QuerySwapchainSupport(VkPhysicalDevice device)
{
	auto details = SSwapchainSupportDetails();

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_Surface, &details.capabilities);
	UInt32 formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, nullptr);

	if (formatCount) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, details.formats.data());
	}

	UInt32 presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR( device, m_Surface, &presentModeCount, details.presentModes.data());
	}

	return details;
}

void CVulkanGraphicsContext::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                                          VkBuffer &buffer, VkDeviceMemory &bufferMemory)
 {
	 VkBufferCreateInfo bufferInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
	 bufferInfo.size = size;
	 bufferInfo.usage = usage;

	 if (vkCreateBuffer(m_Device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
	 {
		 ViAbort("Failed to create buffer!!!\n");
	 }

	 VkMemoryRequirements memRequirements;
	 vkGetBufferMemoryRequirements(m_Device, buffer, &memRequirements);

	 VkMemoryAllocateInfo allocInfo = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
	 allocInfo.allocationSize = memRequirements.size;
	 allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

	 if (vkAllocateMemory(m_Device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
	 {
		 ViAbort("Failed to allocate buffer memory!\n");
	 }

	 vkBindBufferMemory(m_Device, buffer, bufferMemory, 0);
}

VkCommandBuffer CVulkanGraphicsContext::BeginSingleTimeCommands()
{
	VkCommandBufferAllocateInfo allocInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
	allocInfo.commandPool = m_CmdPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(m_Device, &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);
	return commandBuffer;
}

void CVulkanGraphicsContext::EndSingleTimeCommands(VkCommandBuffer commandBuffer) {
	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(m_GraphicsQueue, 1, &submitInfo, nullptr);
	vkQueueWaitIdle(m_GraphicsQueue);

	vkFreeCommandBuffers(m_Device, m_CmdPool, 1, &commandBuffer);
}

void CVulkanGraphicsContext::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
	VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

	VkBufferCopy copyRegion = {};
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

	EndSingleTimeCommands(commandBuffer);
}

void CVulkanGraphicsContext::CopyBufferToImage(VkBuffer buffer, VkImage image, UInt32 width, UInt32 height, UInt32 layerCount)
{
	VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

	VkBufferImageCopy region = {};
	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.layerCount = layerCount;
	region.imageExtent = {width, height, 1};

	vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
	EndSingleTimeCommands(commandBuffer);
}

void CVulkanGraphicsContext::CreateImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkDeviceSize memoryOffset, VkImage &image, VkDeviceMemory &imageMemory)
{
	if (vkCreateImage(m_Device, &imageInfo, nullptr, &image) != VK_SUCCESS)
		ViAbort("Failed to create image!");

	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(m_Device, image, &memRequirements);

	VkMemoryAllocateInfo allocInfo = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(m_Device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
		ViAbort("Failed to allocate image memory!");

	if (vkBindImageMemory(m_Device, image, imageMemory, memoryOffset) != VK_SUCCESS)
		ViAbort("Failed to bind image memory!");
}

UInt32 CVulkanGraphicsContext::FindMemoryType(UInt32 typeFilter, VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties memProperties = {};
	vkGetPhysicalDeviceMemoryProperties(m_PhysicalDevice, &memProperties);
	for (UInt32 i = 0; i < memProperties.memoryTypeCount; i++) if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
		return i;

	ViAbort("Failed to find suitable memory type!");
}

VkFormat CVulkanGraphicsContext::FindSupportedFormat(const CList<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
{
	for (VkFormat format : candidates) {
		VkFormatProperties props = {};
		vkGetPhysicalDeviceFormatProperties(m_PhysicalDevice, format, &props);
		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features ||
			tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
			return format;
	}
	ViAbort("Failed to find supported format!");
}

void CVulkanGraphicsContext::WaitReleaseResources()
{
	vkDeviceWaitIdle(m_Device);
}

void CVulkanGraphicsContext::Execute(ImmediateGraphicsActionFN fn) {
	auto commandBuffer = CCast<SCommandBuffer>(BeginSingleTimeCommands());
	fn(commandBuffer);
	EndSingleTimeCommands(CCast<VkCommandBuffer>(commandBuffer));
}

void CVulkanGraphicsContext::CmdCreate(const UInt32 &imageCount) {
	m_CmdBuffers.resize(imageCount);

	VkCommandBufferAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocateInfo.commandPool = m_CmdPool;
	allocateInfo.commandBufferCount = CCast<UInt32>(m_CmdBuffers.size());

	if (vkAllocateCommandBuffers(m_Device, &allocateInfo, m_CmdBuffers.data()) != VK_SUCCESS)
	ViAbort("Failed to allocate command buffers!");
}

SCommandBuffer CVulkanGraphicsContext::CmdBegin(const UInt32 &imageIndex) const {
	VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
	if (vkBeginCommandBuffer(m_CmdBuffers.at(imageIndex), &beginInfo) != VK_SUCCESS)
	ViAbort("Failed to call vkBeginCommandBuffer()");

	return CCast<SCommandBuffer>(m_CmdBuffers.at(imageIndex));
}

void CVulkanGraphicsContext::CmdEnd(SCommandBuffer const &cmdBuffer) const {
	if (vkEndCommandBuffer(CCast<VkCommandBuffer>(cmdBuffer)) != VK_SUCCESS)
	ViAbort("Failed to record command buffer!");
}

VISRCEND
