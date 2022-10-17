//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_VULKANSWAPCHAIN_HPP
#define VICTORIAM_VULKANSWAPCHAIN_HPP

#include <Victoriam/Graphics/Swapchain.hpp>
#include "Accessors/ADevice.hpp"

VISRCBEG

namespace Accessors { class VIDECL Swapchain; }

class VIDECL cVulkanSwapchain : public cSwapchain
{
	friend class Accessors::Swapchain;

	VIDECL inline static constexpr UInt32 MAX_FRAMES_PER_STEP = 2; // TODO: configurable MAX_FRAMES_PER_STEP
	VIDECL VkFormat m_SwapchainImageFormat = {};
	VIDECL VkExtent2D m_SwapchainExtent = {};
	VIDECL List<VkFramebuffer> m_SwapchainFramebuffers = {};
	VIDECL VkRenderPass m_RenderPass = {};
	VIDECL List<VkImage> m_DepthImages = {};
	VIDECL List<VkDeviceMemory> m_DepthImageMemories = {};
	VIDECL List<VkImageView> m_DepthImageViews = {};
	VIDECL List<VkImage> m_SwapchainImages = {};
	VIDECL List<VkImageView> m_SwapchainImageViews = {};
	VIDECL pDevice& m_Device;
	VIDECL sWindowExtent m_WindowExtent = {};
	VIDECL VkSwapchainKHR m_Swapchain = {};
	VIDECL List<VkSemaphore> m_ImageAvailableSemaphores = {};
	VIDECL List<VkSemaphore> m_RenderFinishedSemaphores = {};
	VIDECL List<VkFence> m_InFlightFences = {};
	VIDECL List<VkFence> m_ImagesInFlight = {};
	VIDECL UInt32 m_CurrentFrame = {};

public:
	explicit cVulkanSwapchain(pDevice& device, const sWindowExtent& extent);
	~cVulkanSwapchain() override;


private:
	VIDECL void CreateSwapchain();
	VIDECL void CreateImageViews();
	VIDECL void CreateDepthResources();
	VIDECL void CreateRenderPass();
	VIDECL void CreateFramebuffers();
	VIDECL void SetupSynchronization();

	VIDECL static VkSurfaceFormatKHR ChooseSwapchainSurfaceFormat(const List<VkSurfaceFormatKHR>& available);
	VIDECL static VkPresentModeKHR ChooseSwapchainPresentMode(const List<VkPresentModeKHR>& available);
	VIDECL VkExtent2D ChooseSwapchainExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	VIDECL VkFormat FindDepthFormat();
	VIDECL VkResult AcquireNextImage(UInt32* imageIndex);
	VIDECL VkResult SubmitCommandBuffers(const VkCommandBuffer* buffers, const UInt32* imageIndex);
private:
	VIDECL VIREQOUT inline VkFramebuffer GetFramebuffer(const UInt32& index) const { return m_SwapchainFramebuffers[index]; }
	VIDECL VIREQOUT inline VkRenderPass GetRenderPass() const { return m_RenderPass; }
	VIDECL VIREQOUT inline VkImageView GetImageView(const UInt32& index) const { return m_SwapchainImageViews[index]; }
	VIDECL VIREQOUT inline UInt32 GetImageCount() const { return m_SwapchainImages.size(); }
	VIDECL VIREQOUT inline VkFormat GetSwapchainImageFormat() const { return m_SwapchainImageFormat; }
	VIDECL VIREQOUT inline VkExtent2D GetSwapchainExtent() const { return m_SwapchainExtent; }
	VIDECL VIREQOUT inline UInt32 GetWidth() const { return m_SwapchainExtent.width; }
	VIDECL VIREQOUT inline UInt32 GetHeight() const { return m_SwapchainExtent.height; }
	VIDECL VIREQOUT inline Float32 GetExtentAspectRatio() const { return CCast<Float32>(m_SwapchainExtent.width) / CCast<Float32>(m_SwapchainExtent.height); }
};

VISRCEND

#endif //VICTORIAM_VULKANSWAPCHAIN_HPP
