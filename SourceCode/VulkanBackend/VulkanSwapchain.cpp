//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#include <cstdlib>
#include <limits>
#include <set>
#include <stdexcept>

#include "VulkanSwapchain.hpp"

#include "../Accessors/AGraphicsContext.hpp"
#include "../Accessors/AImage.hpp"

VISRCBEG

CVulkanSwapchain::CVulkanSwapchain(PGraphicsContext &context, const SExtent2D &extent)
	: m_Context(context), m_WindowExtent(extent)
{
	Init();
}

CVulkanSwapchain::CVulkanSwapchain(PGraphicsContext &context, const SExtent2D &extent, CSwapchain* prev)
	: m_Context(context), m_WindowExtent(extent)
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
	SetupSynchronization();
}

CVulkanSwapchain::~CVulkanSwapchain() {
	auto device = Accessors::GraphicsContext::GetDevice(m_Context);

	for (auto& imageView : m_SwapchainImageViews) {
		vkDestroyImageView(device, imageView, nullptr);
		imageView = nullptr;
	}
	m_SwapchainImageViews.clear();

	if (m_Swapchain != nullptr) {
		vkDestroySwapchainKHR(device, m_Swapchain, nullptr);
		m_Swapchain = nullptr;
	}

	// cleanup synchronization objects
	for (UInt32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroySemaphore(device, m_RenderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(device, m_ImageAvailableSemaphores[i], nullptr);
		vkDestroyFence(device, m_InFlightFences[i], nullptr);
	}
}

void CVulkanSwapchain::CreateSwapchain()
{
	SSwapchainSupportDetails swapChainSupport = Accessors::GraphicsContext::GetSwapchainSupport(m_Context);

	VkSurfaceFormatKHR surfaceFormat = ChooseSwapchainSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = ChooseSwapchainPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = ChooseSwapchainExtent(swapChainSupport.capabilities);

	UInt32 imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 &&
	    imageCount > swapChainSupport.capabilities.maxImageCount) {
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo = { VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
	createInfo.surface = Accessors::GraphicsContext::GetSurface(m_Context);
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	SQueueFamilyIndices indices = Accessors::GraphicsContext::FindQueueFamilies(m_Context);
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

	auto device = Accessors::GraphicsContext::GetDevice(m_Context);

	if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &m_Swapchain) != VK_SUCCESS)
		ViAbort("failed to create swap chain!");

	vkGetSwapchainImagesKHR(device, m_Swapchain, &imageCount, nullptr);
	m_SwapchainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device, m_Swapchain, &imageCount, m_SwapchainImages.data());

	m_SwapchainImageFormat = surfaceFormat.format;
	m_SwapchainExtent = extent;
}

void CVulkanSwapchain::CreateImageViews()
{
	auto device = Accessors::GraphicsContext::GetDevice(m_Context);
	m_SwapchainImageViews.resize(m_SwapchainImages.size());
	for (size_t i = 0; i < m_SwapchainImages.size(); i++) {
		VkImageViewCreateInfo viewInfo = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
		viewInfo.image = m_SwapchainImages[i];
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = m_SwapchainImageFormat;
		viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(device, &viewInfo, nullptr, &m_SwapchainImageViews[i]) != VK_SUCCESS)
			ViAbort("Failed to create texture image view!");
	}
}

void CVulkanSwapchain::CreateDepthResources()
{
	VkFormat depthFormat = FindDepthFormat();
	m_SwapchainDepthFormat = depthFormat;
	VkExtent2D swapChainExtent = GetSwapchainExtent();

	m_DepthImages.resize(GetImageCount());
	for (auto & m_DepthImage : m_DepthImages) {
		SImageCreateInfo imageCreateInfo = {};
		imageCreateInfo.Type = ImageType2D;
		imageCreateInfo.Extent.Width = swapChainExtent.width;
		imageCreateInfo.Extent.Height = swapChainExtent.height;
		imageCreateInfo.Extent.Depth = 1;
		imageCreateInfo.Format = CCast<Signal>(m_SwapchainDepthFormat);
		imageCreateInfo.Usage = ImageUsageDepthStencilAttachment;
		imageCreateInfo.MemoryType = ImageMemoryGPUOnly;
		imageCreateInfo.Aspect = ImageAspectDepth;
		imageCreateInfo.bCreateView = true;

		m_DepthImage = CImage::Create2D(m_Context, imageCreateInfo);
	}
}

void CVulkanSwapchain::SetupSynchronization()
{
	m_ImageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	m_RenderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	m_InFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
	m_ImagesInFlight.resize(GetImageCount(), nullptr);

	VkSemaphoreCreateInfo semaphoreInfo = { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
	VkFenceCreateInfo fenceInfo = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	auto device = Accessors::GraphicsContext::GetDevice(m_Context);

	for (UInt32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &m_ImageAvailableSemaphores[i]) != VK_SUCCESS ||
		    vkCreateSemaphore(device, &semaphoreInfo, nullptr, &m_RenderFinishedSemaphores[i]) != VK_SUCCESS ||
		        vkCreateFence(device, &fenceInfo,     nullptr, &m_InFlightFences[i])           != VK_SUCCESS)
			ViAbort("Failed to create synchronization objects for a frame!");
	}
}

VkSurfaceFormatKHR CVulkanSwapchain::ChooseSwapchainSurfaceFormat(const CList<VkSurfaceFormatKHR> &available)
{
	for (const auto &availableFormat : available) if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		return availableFormat;
	return available[0];
}

VkPresentModeKHR CVulkanSwapchain::ChooseSwapchainPresentMode(const CList<VkPresentModeKHR> &available)
{
	for (const auto &availablePresentMode : available)
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			return availablePresentMode;
	/*
	for (const auto &availablePresentMode : available) {
	  if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
	    return availablePresentMode;
	  }
	}
	*/

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D CVulkanSwapchain::ChooseSwapchainExtent(const VkSurfaceCapabilitiesKHR &capabilities)
{
	return Cast<VkExtent2D>(&m_WindowExtent);
}

VkFormat CVulkanSwapchain::FindDepthFormat()
{
	return Accessors::GraphicsContext::FindSupportedFormat(m_Context, {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT}, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

UInt32 CVulkanSwapchain::AcquireNextImage(UInt32 *imageIndex)
{
	auto device = Accessors::GraphicsContext::GetDevice(m_Context);
	vkWaitForFences(device, 1, &m_InFlightFences[m_CurrentFrame], true, std::numeric_limits<uint64_t>::max());
	return vkAcquireNextImageKHR(device, m_Swapchain, std::numeric_limits<uint64_t>::max(), m_ImageAvailableSemaphores[m_CurrentFrame],  /* must be a not signaled semaphore */ nullptr, imageIndex);
}

VkResult CVulkanSwapchain::SubmitCommandBuffers(const VkCommandBuffer *buffers, const UInt32 *imageIndex)
{
	auto device = Accessors::GraphicsContext::GetDevice(m_Context);
	if (m_ImagesInFlight[*imageIndex] != nullptr)
		vkWaitForFences(device, 1, &m_ImagesInFlight[*imageIndex], true, std::numeric_limits<uint64_t>::max());

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

	vkResetFences(device, 1, &m_InFlightFences[m_CurrentFrame]);
	if (vkQueueSubmit(Accessors::GraphicsContext::GetGraphicsQueue(m_Context), 1, &submitInfo, m_InFlightFences[m_CurrentFrame]) != VK_SUCCESS)
		ViAbort("Failed to submit draw command buffer!");

	VkPresentInfoKHR presentInfo = { VK_STRUCTURE_TYPE_PRESENT_INFO_KHR };
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = {m_Swapchain};
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = imageIndex;

	auto result = vkQueuePresentKHR(Accessors::GraphicsContext::GetPresentQueue(m_Context), &presentInfo);

	m_CurrentFrame = (m_CurrentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

	return result;
}

Bool CVulkanSwapchain::CompareFormats(const PSwapchain& swapchain) const
{
	if (!swapchain) return false;
	return  m_SwapchainImageFormat == CCast<CVulkanSwapchain*>(swapchain.get())->m_SwapchainImageFormat &&
			m_SwapchainDepthFormat == CCast<CVulkanSwapchain*>(swapchain.get())->m_SwapchainDepthFormat;
}

void CVulkanSwapchain::CreateFramebuffers(PRenderPass &renderPass) {
	m_Framebuffers.resize(GetImageCount());
	for (UInt32 i = 0; i < GetImageCount(); i++)
	{
		SFramebufferCreateInfo createInfo = {};
		createInfo.Attachments = {
				CCast<SImageViewObject>(m_SwapchainImageViews[i]),
				CCast<SImageViewObject>(Accessors::Image::GetImageView(m_DepthImages[i])) };
		m_Framebuffers[i] = CFramebuffer::Create(m_Context, renderPass, createInfo);
	}
}

void CVulkanSwapchain::CmdSubmit(const SCommandBuffer *buffers, const UInt32 *imageIndex) {
	SubmitCommandBuffers(CCast<VkCommandBuffer*>(buffers), imageIndex);
}

VISRCEND
