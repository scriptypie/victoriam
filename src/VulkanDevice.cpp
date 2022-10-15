//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <set>
#include <iostream>
#include <unordered_set>

#include "VulkanDevice.hpp"

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
		std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;
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

cVulkanDevice::cVulkanDevice(const SPtr<cWindow> &window)
	: m_Window(window)
{
	CreateGraphicsInstance();
	SetupDebugMessenger();
	CreateSurface();
	ChoosePhysicalDevice();
	CreateLogicalDevice();
	CreateCommandPool();
}

cVulkanDevice::~cVulkanDevice()
{
	vkDestroyCommandPool(m_Device, m_CmdPool, nullptr);
	vkDestroyDevice(m_Device, nullptr);

	if (m_EnableValidation)
		DestroyDebugMessengerEXT(m_Instance, m_DebugMessenger);

	vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
	vkDestroyInstance(m_Instance, nullptr);
}

void cVulkanDevice::CreateGraphicsInstance()
{
	if (m_EnableValidation && !CheckValidationLayerSupport())
		throw std::runtime_error("Validation layers requested, but not available!");

	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	VkApplicationInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info.pApplicationName = "VIsualEditor";
	info.pEngineName = "Victoriam Engine";
	info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	info.apiVersion = VK_API_VERSION_1_0;
	instanceCreateInfo.pApplicationInfo = &info;
	auto extensions = GetRequiredExtensions();
#ifdef __APPLE__
	instanceCreateInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
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
		throw std::runtime_error("Failed to create instance!");
	HasGLFWRequiredInstanceExtensions();
}

void cVulkanDevice::SetupDebugMessenger()
{
	if (!m_EnableValidation) return;
	VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
	PopulateDebugMessengerCreateInfo(createInfo);
	if (CreateDebugMessengerEXT(m_Instance, &createInfo, &m_DebugMessenger) != VK_SUCCESS)
		throw std::runtime_error("Failed to set up debug messenger!");
}

void cVulkanDevice::CreateSurface()
{
	CreateWindowSurface(m_Window, m_Instance, &m_Surface);
}

void cVulkanDevice::ChoosePhysicalDevice()
{
	UInt32 deviceCount = {};
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);
	if (!deviceCount) throw std::runtime_error("There no supported GPU!");
	List<VkPhysicalDevice> physicalDevices(deviceCount);
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, physicalDevices.data());

	for (auto& device : physicalDevices)
		if (IsPhysicalDeviceSuitable(device))
		{
			m_PhysicalDevice = device;
			break;
		}

	if (m_PhysicalDevice == nullptr)
		throw std::runtime_error("Failed to find a suitable GPU!");
	vkGetPhysicalDeviceProperties(m_PhysicalDevice, &m_Properties);
	// log here
}

void cVulkanDevice::CreateLogicalDevice()
{
	sQueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);
	List<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<UInt32> uniqueQueueFamilies = { indices.GraphicsFamily, indices.PresentFamily };
	Float32 queuePriority = 1.0F;
	for (UInt32 queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}
	VkPhysicalDeviceFeatures features = {};
	features.samplerAnisotropy = VK_TRUE;

	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
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
		throw std::runtime_error("Failed to create logical device!");

	vkGetDeviceQueue(m_Device, indices.GraphicsFamily, 0, &m_GraphicsQueue);
	vkGetDeviceQueue(m_Device, indices.PresentFamily, 0, &m_PresentQueue);
}

void cVulkanDevice::CreateCommandPool()
{
	sQueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);

	VkCommandPoolCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	createInfo.queueFamilyIndex = indices.GraphicsFamily;
	createInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	if (vkCreateCommandPool(m_Device, &createInfo, nullptr, &m_CmdPool) != VK_SUCCESS)
		throw std::runtime_error("Failed to create command pool!");
}

Bool cVulkanDevice::IsPhysicalDeviceSuitable(VkPhysicalDevice device)
{
	sQueueFamilyIndices indices = FindQueueFamilies(device);
	Bool extensionsSupported = CheckDeviceExtensionSupport(device);
	Bool swapchainIsOkay = false;
	if (extensionsSupported)
	{
		sSwapchainSupportDetails* swapchainSupportDetails = QuerySwapchainSupport(device);
		swapchainIsOkay = !swapchainSupportDetails->formats.empty() && !swapchainSupportDetails->presentModes.empty();
		delete swapchainSupportDetails; // for memory safety
	}
	VkPhysicalDeviceFeatures supportedFeatures;
	vkGetPhysicalDeviceFeatures(m_PhysicalDevice, &supportedFeatures);

	return indices.IsCompleted() && extensionsSupported && swapchainIsOkay && supportedFeatures.samplerAnisotropy;
}

List<CString> cVulkanDevice::GetRequiredExtensions() const {
	UInt32 glfwExtensionCount = {};
	CString* glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	List<CString> requiredExtensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
	if (m_EnableValidation)
		requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	return requiredExtensions;
}

Bool cVulkanDevice::CheckValidationLayerSupport()
{
	UInt32 layerCount = {};
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	List<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (CString layerName : VALIDATION_LAYERS)
	{
		Bool layerFound = false;

		for (const auto& layerProperties : availableLayers)
		{
			if (!strcmp(layerName, layerProperties.layerName))
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound) return false;
	}
	return true;
}

sQueueFamilyIndices cVulkanDevice::FindQueueFamilies(VkPhysicalDevice device)
{
	sQueueFamilyIndices indices;

	UInt32 queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	List<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	UInt32 i = {};
	for (const auto &queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
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

void cVulkanDevice::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &info)
{
	info = {};
	info.sType              = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	info.messageSeverity    = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
	                             VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	info.messageType        = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
	                         VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
	                         VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	info.pfnUserCallback = DebugCallback;
	info.pUserData = nullptr;  // Optional
}

void cVulkanDevice::HasGLFWRequiredInstanceExtensions()
{
	UInt32 extensionCount = {};
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	List<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	std::unordered_set<String> available;
	for (const auto &extension : extensions)
		available.insert(extension.extensionName);

	auto requiredExtensions = GetRequiredExtensions();
	for (const auto &required : requiredExtensions)
		if (available.find(required) == available.end())
			throw std::runtime_error("Missing required glfw extension");
}

Bool cVulkanDevice::CheckDeviceExtensionSupport(VkPhysicalDevice device)
{
	UInt32 extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	List<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<String> requiredExtensions(DEVICE_EXTENSIONS.begin(), DEVICE_EXTENSIONS.end());

	for (const auto &extension : availableExtensions)
		requiredExtensions.erase(extension.extensionName);

	return requiredExtensions.empty();
}

sSwapchainSupportDetails* cVulkanDevice::QuerySwapchainSupport(VkPhysicalDevice device)
{
	auto* details = new sSwapchainSupportDetails;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_Surface, &details->capabilities);
	UInt32 formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, nullptr);

	if (formatCount) {
		details->formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, details->formats.data());
	}

	UInt32 presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details->presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR( device, m_Surface, &presentModeCount, details->presentModes.data());
	}

	return details;
}

VISRCEND
