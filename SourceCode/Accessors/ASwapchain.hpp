//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAGetASWAPCHAIN_HPP
#define VICTORIAGetASWAPCHAIN_HPP

#include "../VulkanBackend/VulkanSwapchain.hpp"

VISRCBEG

namespace Accessors
{

	class Swapchain
	{
	public:
		VIDECL VIREQOUT static CList<PFramebuffer> GetFramebuffers(const PSwapchain& swapchain)
		{
			return CCast<CVulkanSwapchain*>(swapchain.get())->GetFramebuffers();
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
	};

}

VISRCEND

#endif //VICTORIAGetASWAPCHAIN_HPP
