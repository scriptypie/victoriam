//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAGetASWAPCHAIN_HPP
#define VICTORIAGetASWAPCHAIN_HPP

#include "../VulkanSwapchain.hpp"

VISRCBEG

namespace Accessors
{

	class Swapchain
	{
	public:
		VIDECL VIREQOUT static VkFramebuffer GetFramebuffer(const pSwapchain& swapchain, const UInt32& index)
		{
			return CCast<cVulkanSwapchain*>(swapchain.get())->GetFramebuffer(index);
		}
		VIDECL VIREQOUT static VkRenderPass GetRenderPass(const pSwapchain& swapchain)
		{
			return CCast<cVulkanSwapchain*>(swapchain.get())->GetRenderPass();
		}
		VIDECL VIREQOUT static VkImageView GetImageView(const pSwapchain& swapchain, const UInt32& index)
		{
			return CCast<cVulkanSwapchain*>(swapchain.get())->GetImageView(index);
		}
		VIDECL VIREQOUT static UInt32 GetImageCount(const pSwapchain& swapchain)
		{
			return CCast<cVulkanSwapchain*>(swapchain.get())->GetImageCount();
		}
		VIDECL VIREQOUT static VkFormat GetSwapchainImageFormat(const pSwapchain& swapchain)
		{
			return CCast<cVulkanSwapchain*>(swapchain.get())->GetSwapchainImageFormat();
		}
		VIDECL VIREQOUT static VkExtent2D GetSwapchainExtent(const pSwapchain& swapchain)
		{
			return CCast<cVulkanSwapchain*>(swapchain.get())->GetSwapchainExtent();
		}
		VIDECL VIREQOUT static UInt32 GetWidth(const pSwapchain& swapchain)
		{
			return CCast<cVulkanSwapchain*>(swapchain.get())->GetWidth();
		}
		VIDECL VIREQOUT static UInt32 GetHeight(const pSwapchain& swapchain)
		{
			return CCast<cVulkanSwapchain*>(swapchain.get())->GetHeight();
		}
		VIDECL VIREQOUT static Float32 GetExtentAspectRatio(const pSwapchain& swapchain)
		{
			return CCast<cVulkanSwapchain*>(swapchain.get())->GetExtentAspectRatio();
		}
		VIDECL VIREQOUT static VkFormat FindDepthFormat(const pSwapchain& swapchain)
		{
			return CCast<cVulkanSwapchain*>(swapchain.get())->FindDepthFormat();
		}
		VIDECL VIREQOUT static VkResult AcquiredNextImage(const pSwapchain& swapchain, UInt32* imageIndex)
		{
			return CCast<cVulkanSwapchain*>(swapchain.get())->AcquireNextImage(imageIndex);
		}
		VIDECL static VkResult SubmitCommandBuffers(const pSwapchain& swapchain, const VkCommandBuffer* buffers, UInt32* imageIndex)
		{
			return CCast<cVulkanSwapchain*>(swapchain.get())->SubmitCommandBuffers(buffers, imageIndex);
		}
	};

}

VISRCEND

#endif //VICTORIAGetASWAPCHAIN_HPP
