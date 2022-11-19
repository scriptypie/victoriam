//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_VULKANSWAPCHAIN_HPP
#define VICTORIAM_VULKANSWAPCHAIN_HPP

#include <Victoriam/Graphics/GSwapchain.hpp>
#include <Victoriam/Graphics/GFramebuffer.hpp>
#include <Victoriam/Graphics/GRenderPass.hpp>
#include <Victoriam/Graphics/GImage.hpp>

#include <vulkan/vulkan.h>

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
	VIDECL CList<PImage> m_DepthImages = {};
	VIDECL CList<VkImageView> m_SwapchainImageViews = {};
	VIDECL CList<VkImage> m_SwapchainImages = {};
	VIDECL PGraphicsContext& m_Context;
	VIDECL CList<PFramebuffer> m_Framebuffers = {};
	VIDECL SExtent2D m_WindowExtent = {};
	VIDECL VkSwapchainKHR m_Swapchain = {};
	VIDECL CList<VkSemaphore> m_ImageAvailableSemaphores = {};
	VIDECL CList<VkSemaphore> m_RenderFinishedSemaphores = {};
	VIDECL CList<VkFence> m_InFlightFences = {};
	VIDECL CList<VkFence> m_ImagesInFlight = {};
	VIDECL UInt32 m_CurrentFrame = {};
	VIDECL CSwapchain* m_OldSwapchain = {};

public:
	VIDECL explicit CVulkanSwapchain(PGraphicsContext& device, const SExtent2D& extent);
	VIDECL explicit CVulkanSwapchain(PGraphicsContext& device, const SExtent2D& extent, CSwapchain* prev);
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
private:
	VIDECL          void Init();
	VIDECL          void CreateSwapchain();
	VIDECL          void CreateImageViews();
	VIDECL          void CreateDepthResources();
	VIDECL          void SetupSynchronization();

	VIDECL VIREQOUT static VkSurfaceFormatKHR ChooseSwapchainSurfaceFormat(const CList<VkSurfaceFormatKHR>& available);
	VIDECL VIREQOUT static VkPresentModeKHR ChooseSwapchainPresentMode(const CList<VkPresentModeKHR>& available);
	VIDECL VIREQOUT VkExtent2D ChooseSwapchainExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	VIDECL VIREQOUT VkFormat FindDepthFormat();
	VIDECL          VkResult SubmitCommandBuffers(const VkCommandBuffer* buffers, const UInt32* imageIndex);
private:
	VIDECL VIREQOUT inline CList<PFramebuffer>& GetFramebuffers() override { return m_Framebuffers; }
	VIDECL void CreateFramebuffers(PRenderPass& renderPass) override;
	VIDECL VIREQOUT inline VkImageView GetImageView(const UInt32& index) const { return m_SwapchainImageViews[index]; }
	VIDECL VIREQOUT inline VkFormat GetSwapchainImageFormat() const { return m_SwapchainImageFormat; }
	VIDECL VIREQOUT inline VkExtent2D GetSwapchainExtent() const { return m_SwapchainExtent; }
};

VISRCEND

#endif //VICTORIAM_VULKANSWAPCHAIN_HPP
