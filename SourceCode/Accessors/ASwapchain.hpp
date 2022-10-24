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
		VIDECL VIREQOUT static VkFramebuffer GetFramebuffer(const PSwapchain& swapchain, const UInt32& index)
		{
			return CCast<CVulkanSwapchain*>(swapchain.get())->GetFramebuffer(index);
		}
		VIDECL VIREQOUT static VkRenderPass GetRenderPass(const PSwapchain& swapchain)
		{
			return CCast<CVulkanSwapchain*>(swapchain.get())->GetRenderPass();
		}
		VIDECL VIREQOUT static VkImageView GetImageView(const PSwapchain& swapchain, const UInt32& index)
		{
			return CCast<CVulkanSwapchain*>(swapchain.get())->GetImageView(index);
		}
		VIDECL VIREQOUT static VkFormat GetSwapchainImageFormat(const PSwapchain& swapchain)
		{
			return CCast<CVulkanSwapchain*>(swapchain.get())->GetSwapchainImageFormat();
		}
		VIDECL VIREQOUT static VkExtent2D GetSwapchainExtent(const PSwapchain& swapchain)
		{
			return CCast<CVulkanSwapchain*>(swapchain.get())->GetSwapchainExtent();
		}
		VIDECL VIREQOUT static VkFormat FindDepthFormat(const PSwapchain& swapchain)
		{
			return CCast<CVulkanSwapchain*>(swapchain.get())->FindDepthFormat();
		}
		VIDECL static VkResult SubmitCommandBuffers(const PSwapchain& swapchain, const VkCommandBuffer* buffers, UInt32* imageIndex)
		{
			return CCast<CVulkanSwapchain*>(swapchain.get())->SubmitCommandBuffers(buffers, imageIndex);
		}
	};

}

VISRCEND

#endif //VICTORIAGetASWAPCHAIN_HPP
