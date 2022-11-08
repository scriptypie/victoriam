//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_VULKANSWAPCHAIN_HPP
#define VICTORIAM_VULKANSWAPCHAIN_HPP

#include <Victoriam/Graphics/GSwapchain.hpp>
#include "Accessors/AGraphicsContext.hpp"

VISRCBEG

namespace Accessors { class VIDECL Swapchain; }

class VIDECL CVulkanSwapchain : public CSwapchain
{
	friend class Accessors::Swapchain;
	friend class CVulkanRenderer;
VIDECL
	VIDECL inline static constexpr UInt32 MAX_FRAMES_IN_FLIGHT = 2; // TODO: configurable MAX_FRAMES_IN_FLIGHT
	VIDECL VkFormat m_SwapchainImageFormat = {};
	VIDECL VkFormat m_SwapchainDepthFormat = {};
	VIDECL VkExtent2D m_SwapchainExtent = {};
	VIDECL List<VkFramebuffer> m_SwapchainFramebuffers = {};
	VIDECL VkRenderPass m_RenderPass = {};
	VIDECL List<VkImage> m_DepthImages = {};
	VIDECL List<VkDeviceMemory> m_DepthImageMemories = {};
	VIDECL List<VkImageView> m_DepthImageViews = {};
	VIDECL List<VkImage> m_SwapchainImages = {};
	VIDECL List<VkImageView> m_SwapchainImageViews = {};
	VIDECL PGraphicsContext& m_Context;
	VIDECL SWindowExtent m_WindowExtent = {};
	VIDECL VkSwapchainKHR m_Swapchain = {};
	VIDECL List<VkSemaphore> m_ImageAvailableSemaphores = {};
	VIDECL List<VkSemaphore> m_RenderFinishedSemaphores = {};
	VIDECL List<VkFence> m_InFlightFences = {};
	VIDECL List<VkFence> m_ImagesInFlight = {};
	VIDECL UInt32 m_CurrentFrame = {};
	VIDECL CSwapchain* m_OldSwapchain = {};

public:
	VIDECL explicit CVulkanSwapchain(PGraphicsContext& device, const SWindowExtent& extent);
	VIDECL explicit CVulkanSwapchain(PGraphicsContext& device, const SWindowExtent& extent, CSwapchain* prev);
	VIDECL ~CVulkanSwapchain() override;

	VIDECL VIREQOUT UInt32 AcquireNextImage(UInt32* imageIndex) override;
	VIDECL VIREQOUT inline UInt32 GetImageCount() const override { return m_SwapchainImages.size(); }
	VIDECL VIREQOUT inline UInt32 GetFrameIndex() const override { return m_CurrentFrame; }
	VIDECL VIREQOUT inline UInt32 GetMaxFramesInFlight() const override { return MAX_FRAMES_IN_FLIGHT; }
	VIDECL VIREQOUT inline UInt32 GetWidth() const override { return m_SwapchainExtent.width; }
	VIDECL VIREQOUT inline UInt32 GetHeight() const override { return m_SwapchainExtent.height; }
	VIDECL VIREQOUT inline Float32 GetExtentAspectRatio() const override
	{
		return CCast<Float32>(m_SwapchainExtent.width)
				/ CCast<Float32>(m_SwapchainExtent.height);
	}
	VIDECL VIREQOUT Bool CompareFormats(const PSwapchain& swapchain) const override;
	VIDECL          void BeginRenderPass(const SCommandBuffer& commandBuffer, UInt32 imageIndex) override;
	VIDECL          void EndRenderPass(const SCommandBuffer& commandBuffer) override;
private:
	VIDECL          void Init();
	VIDECL          void CreateSwapchain();
	VIDECL          void CreateImageViews();
	VIDECL          void CreateDepthResources();
	VIDECL          void CreateRenderPass();
	VIDECL          void CreateFramebuffers();
	VIDECL          void SetupSynchronization();

	VIDECL VIREQOUT static VkSurfaceFormatKHR ChooseSwapchainSurfaceFormat(const List<VkSurfaceFormatKHR>& available);
	VIDECL VIREQOUT static VkPresentModeKHR ChooseSwapchainPresentMode(const List<VkPresentModeKHR>& available);
	VIDECL VIREQOUT VkExtent2D ChooseSwapchainExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	VIDECL VIREQOUT VkFormat FindDepthFormat();
	VIDECL          VkResult SubmitCommandBuffers(const VkCommandBuffer* buffers, const UInt32* imageIndex);
private:
	VIDECL VIREQOUT inline VkFramebuffer GetFramebuffer(const UInt32& index) const { return m_SwapchainFramebuffers[index]; }
	VIDECL VIREQOUT inline VkRenderPass GetRenderPass() const { return m_RenderPass; }
	VIDECL VIREQOUT inline VkImageView GetImageView(const UInt32& index) const { return m_SwapchainImageViews[index]; }
	VIDECL VIREQOUT inline VkFormat GetSwapchainImageFormat() const { return m_SwapchainImageFormat; }
	VIDECL VIREQOUT inline VkExtent2D GetSwapchainExtent() const { return m_SwapchainExtent; }
};

VISRCEND

#endif //VICTORIAM_VULKANSWAPCHAIN_HPP
