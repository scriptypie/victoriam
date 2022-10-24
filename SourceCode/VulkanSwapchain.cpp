//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#include <array>
#include <cstdlib>
#include <limits>
#include <set>
#include <stdexcept>

#include "VulkanSwapchain.hpp"

VISRCBEG

CVulkanSwapchain::CVulkanSwapchain(PDevice &device, const SWindowExtent &extent)
	: m_Device(device), m_WindowExtent(extent)
{
	Init();
}

CVulkanSwapchain::CVulkanSwapchain(PDevice &device, const SWindowExtent &extent, CSwapchain* prev)
	: m_Device(device), m_WindowExtent(extent)
{
	m_OldSwapchain = prev;
	Init();
	m_OldSwapchain = nullptr;
}

void CVulkanSwapchain::Init()
{
	CreateSwapchain();
	CreateImageViews();
	CreateDepthResources();
	CreateRenderPass();
	CreateFramebuffers();
	SetupSynchronization();
}

CVulkanSwapchain::~CVulkanSwapchain() {
	for (auto imageView : m_SwapchainImageViews) {
		vkDestroyImageView(Accessors::Device::GetDevice(m_Device), imageView, nullptr);
	}
	m_SwapchainImageViews.clear();

	if (m_Swapchain != nullptr) {
		vkDestroySwapchainKHR(Accessors::Device::GetDevice(m_Device), m_Swapchain, nullptr);
		m_Swapchain = nullptr;
	}

	for (int i = 0; i < m_DepthImages.size(); i++) {
		vkDestroyImageView(Accessors::Device::GetDevice(m_Device), m_DepthImageViews[i], nullptr);
		vkDestroyImage(Accessors::Device::GetDevice(m_Device), m_DepthImages[i], nullptr);
		vkFreeMemory(Accessors::Device::GetDevice(m_Device), m_DepthImageMemories[i], nullptr);
	}

	for (auto framebuffer : m_SwapchainFramebuffers) {
		vkDestroyFramebuffer(Accessors::Device::GetDevice(m_Device), framebuffer, nullptr);
	}

	vkDestroyRenderPass(Accessors::Device::GetDevice(m_Device), m_RenderPass, nullptr);

	// cleanup synchronization objects
	for (UInt32 i = 0; i < MAX_FRAMES_PER_STEP; i++) {
		vkDestroySemaphore(Accessors::Device::GetDevice(m_Device), m_RenderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(Accessors::Device::GetDevice(m_Device), m_ImageAvailableSemaphores[i], nullptr);
		vkDestroyFence(Accessors::Device::GetDevice(m_Device), m_InFlightFences[i], nullptr);
	}
}

void CVulkanSwapchain::CreateSwapchain()
{
	SSwapchainSupportDetails swapChainSupport = Accessors::Device::GetSwapchainSupport(m_Device);

	VkSurfaceFormatKHR surfaceFormat = ChooseSwapchainSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = ChooseSwapchainPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = ChooseSwapchainExtent(swapChainSupport.capabilities);

	UInt32 imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 &&
	    imageCount > swapChainSupport.capabilities.maxImageCount) {
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo = { VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
	createInfo.surface = Accessors::Device::GetSurface(m_Device);
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	SQueueFamilyIndices indices = Accessors::Device::FindQueueFamilies(m_Device);
	UInt32 queueFamilyIndices[] = { indices.GraphicsFamily, indices.PresentFamily };

	if (indices.GraphicsFamily != indices.PresentFamily) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}

	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = true;
	if (m_OldSwapchain)
		createInfo.oldSwapchain = CCast<CVulkanSwapchain*>(m_OldSwapchain)->m_Swapchain;

	if (vkCreateSwapchainKHR(Accessors::Device::GetDevice(m_Device), &createInfo, nullptr, &m_Swapchain) != VK_SUCCESS)
		throw std::runtime_error("failed to create swap chain!");

	// we only specified a minimum number of images in the swap chain, so the implementation is
	// allowed to create a swap chain with more. That's why we'll first query the final number of
	// images with vkGetSwapchainImagesKHR, then resize the container and finally call it again to
	// retrieve the handles.
	vkGetSwapchainImagesKHR(Accessors::Device::GetDevice(m_Device), m_Swapchain, &imageCount, nullptr);
	m_SwapchainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(Accessors::Device::GetDevice(m_Device), m_Swapchain, &imageCount, m_SwapchainImages.data());

	m_SwapchainImageFormat = surfaceFormat.format;
	m_SwapchainExtent = extent;
}

void CVulkanSwapchain::CreateImageViews()
{
	m_SwapchainImageViews.resize(m_SwapchainImages.size());
	for (size_t i = 0; i < m_SwapchainImages.size(); i++) {
		VkImageViewCreateInfo viewInfo = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
		viewInfo.image = m_SwapchainImages[i];
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = m_SwapchainImageFormat;
		viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(Accessors::Device::GetDevice(m_Device), &viewInfo, nullptr, &m_SwapchainImageViews[i]) != VK_SUCCESS)
			throw std::runtime_error("Failed to create texture image view!");
	}
}

void CVulkanSwapchain::CreateDepthResources()
{
	VkFormat depthFormat = FindDepthFormat();
	VkExtent2D swapChainExtent = GetSwapchainExtent();

	m_DepthImages.resize(GetImageCount());
	m_DepthImageMemories.resize(GetImageCount());
	m_DepthImageViews.resize(GetImageCount());

	for (int i = 0; i < m_DepthImages.size(); i++) {
		VkImageCreateInfo imageInfo = { VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
		imageInfo.imageType = VK_IMAGE_TYPE_2D;
		imageInfo.extent.width = swapChainExtent.width;
		imageInfo.extent.height = swapChainExtent.height;
		imageInfo.extent.depth = 1;
		imageInfo.mipLevels = 1;
		imageInfo.arrayLayers = 1;
		imageInfo.format = depthFormat;
		imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
		imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;

		Accessors::Device::CreateImageWithInfo(m_Device,
				imageInfo,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
				m_DepthImages[i],
				m_DepthImageMemories[i]);

		VkImageViewCreateInfo viewInfo = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
		viewInfo.image = m_DepthImages[i];
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = depthFormat;
		viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(Accessors::Device::GetDevice(m_Device), &viewInfo, nullptr, &m_DepthImageViews[i]) != VK_SUCCESS)
			throw std::runtime_error("Failed to create texture image view!");
	}
}

void CVulkanSwapchain::CreateRenderPass()
{
	VkAttachmentDescription depthAttachment = {};
	depthAttachment.format = FindDepthFormat();
	depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthAttachmentRef = {};
	depthAttachmentRef.attachment = 1;
	depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = GetSwapchainImageFormat();
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;
	subpass.pDepthStencilAttachment = &depthAttachmentRef;

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

	std::array<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};
	VkRenderPassCreateInfo renderPassInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
	renderPassInfo.attachmentCount = CCast<UInt32>(attachments.size());
	renderPassInfo.pAttachments = attachments.data();
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;

	if (vkCreateRenderPass(Accessors::Device::GetDevice(m_Device), &renderPassInfo, nullptr, &m_RenderPass) != VK_SUCCESS)
		throw std::runtime_error("Failed to create render pass!");
}

void CVulkanSwapchain::CreateFramebuffers()
{
	m_SwapchainFramebuffers.resize(GetImageCount());
	for (size_t i = 0; i < GetImageCount(); i++) {
		std::array<VkImageView, 2> attachments = {m_SwapchainImageViews[i], m_DepthImageViews[i]};

		VkExtent2D swapChainExtent = GetSwapchainExtent();
		VkFramebufferCreateInfo framebufferInfo = { VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO };
		framebufferInfo.renderPass = m_RenderPass;
		framebufferInfo.attachmentCount = CCast<UInt32>(attachments.size());
		framebufferInfo.pAttachments = attachments.data();
		framebufferInfo.width = swapChainExtent.width;
		framebufferInfo.height = swapChainExtent.height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(Accessors::Device::GetDevice(m_Device), &framebufferInfo, nullptr, &m_SwapchainFramebuffers[i]) != VK_SUCCESS)
			throw std::runtime_error("Failed to create framebuffer!");
	}
}

void CVulkanSwapchain::SetupSynchronization()
{
	m_ImageAvailableSemaphores.resize(MAX_FRAMES_PER_STEP);
	m_RenderFinishedSemaphores.resize(MAX_FRAMES_PER_STEP);
	m_InFlightFences.resize(MAX_FRAMES_PER_STEP);
	m_ImagesInFlight.resize(GetImageCount(), nullptr);

	VkSemaphoreCreateInfo semaphoreInfo = { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
	VkFenceCreateInfo fenceInfo = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (UInt32 i = 0; i < MAX_FRAMES_PER_STEP; i++) {
		if (vkCreateSemaphore(Accessors::Device::GetDevice(m_Device), &semaphoreInfo, nullptr, &m_ImageAvailableSemaphores[i]) != VK_SUCCESS ||
		    vkCreateSemaphore(Accessors::Device::GetDevice(m_Device), &semaphoreInfo, nullptr, &m_RenderFinishedSemaphores[i]) != VK_SUCCESS ||
		    vkCreateFence(Accessors::Device::GetDevice(m_Device), &fenceInfo, nullptr, &m_InFlightFences[i])                   != VK_SUCCESS)
			throw std::runtime_error("Failed to create synchronization objects for a frame!");
	}
}

VkSurfaceFormatKHR CVulkanSwapchain::ChooseSwapchainSurfaceFormat(const List<VkSurfaceFormatKHR> &available)
{
	for (const auto &availableFormat : available)
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
		    availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			return availableFormat;

	return available[0];
}

VkPresentModeKHR CVulkanSwapchain::ChooseSwapchainPresentMode(const List<VkPresentModeKHR> &available)
{
	for (const auto &availablePresentMode : available)
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			return availablePresentMode;

	// for (const auto &availablePresentMode : availablePresentModes) {
	//   if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
	//     std::cout << "Present mode: Immediate" << std::endl;
	//     return availablePresentMode;
	//   }
	// }

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D CVulkanSwapchain::ChooseSwapchainExtent(const VkSurfaceCapabilitiesKHR &capabilities)
{
	return Cast<VkExtent2D>(&m_WindowExtent);
}

VkFormat CVulkanSwapchain::FindDepthFormat()
{
	return Accessors::Device::FindSupportedFormat(m_Device,
			{VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT}, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

UInt32 CVulkanSwapchain::AcquireNextImage(UInt32 *imageIndex)
{
	vkWaitForFences(Accessors::Device::GetDevice(m_Device), 1, &m_InFlightFences[m_CurrentFrame], true, std::numeric_limits<uint64_t>::max());
	return vkAcquireNextImageKHR(Accessors::Device::GetDevice(m_Device), m_Swapchain, std::numeric_limits<uint64_t>::max(), m_ImageAvailableSemaphores[m_CurrentFrame],  /* must be a not signaled semaphore */ nullptr, imageIndex);
}

VkResult CVulkanSwapchain::SubmitCommandBuffers(const VkCommandBuffer *buffers, const UInt32 *imageIndex)
{
	if (m_ImagesInFlight[*imageIndex] != nullptr)
		vkWaitForFences(Accessors::Device::GetDevice(m_Device), 1, &m_ImagesInFlight[*imageIndex], true, std::numeric_limits<uint64_t>::max());

	m_ImagesInFlight[*imageIndex] = m_InFlightFences[m_CurrentFrame];

	VkSubmitInfo submitInfo = { VK_STRUCTURE_TYPE_SUBMIT_INFO };

	VkSemaphore waitSemaphores[] = {m_ImageAvailableSemaphores[m_CurrentFrame]};
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = buffers;

	VkSemaphore signalSemaphores[] = {m_RenderFinishedSemaphores[m_CurrentFrame]};
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(Accessors::Device::GetDevice(m_Device), 1, &m_InFlightFences[m_CurrentFrame]);
	if (vkQueueSubmit(Accessors::Device::GetGraphicsQueue(m_Device), 1, &submitInfo, m_InFlightFences[m_CurrentFrame]) != VK_SUCCESS)
		throw std::runtime_error("Failed to submit draw command buffer!");

	VkPresentInfoKHR presentInfo = { VK_STRUCTURE_TYPE_PRESENT_INFO_KHR };
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = {m_Swapchain};
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = imageIndex;

	auto result = vkQueuePresentKHR(Accessors::Device::GetPresentQueue(m_Device), &presentInfo);

	m_CurrentFrame = (m_CurrentFrame + 1) % MAX_FRAMES_PER_STEP;

	return result;
}

VISRCEND
