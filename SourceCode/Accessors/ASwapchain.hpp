//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAGetASWAPCHAIN_HPP
#define VICTORIAGetASWAPCHAIN_HPP

#include "../VulkanBackend/VulkanSwapchain.hpp"

VISRCBEG

namespace Accessors
{

	class Swapchain {
	public:
		VIDECL VIREQOUT static CList<PFramebuffer> GetFramebuffers(const PSwapchain& swapchain) {
			return CCast<CVulkanSwapchain*>(swapchain.Get())->GetFramebuffers();
		}
		VIDECL VIREQOUT static VkImageView GetImageView(const PSwapchain& swapchain, const UInt32& index) {
			return CCast<CVulkanSwapchain*>(swapchain.Get())->GetImageView(index);
		}
		VIDECL VIREQOUT static VkFormat GetSwapchainImageFormat(const PSwapchain& swapchain) {
			return CCast<CVulkanSwapchain*>(swapchain.Get())->GetSwapchainImageFormat();
		}
		VIDECL VIREQOUT static VkExtent2D GetSwapchainExtent(const PSwapchain& swapchain) {
			return CCast<CVulkanSwapchain*>(swapchain.Get())->GetSwapchainExtent();
		}
		VIDECL VIREQOUT static VkFormat FindDepthFormat(const PSwapchain& swapchain) {
			return CCast<CVulkanSwapchain*>(swapchain.Get())->FindDepthFormat();
		}
	};

}

VISRCEND

#endif //VICTORIAGetASWAPCHAIN_HPP
