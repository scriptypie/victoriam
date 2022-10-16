//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_ADEVICE_HPP
#define VICTORIAM_ADEVICE_HPP

#include "Victoriam/Graphics/Basics.hpp"

#include "../VulkanDevice.hpp"

VISRCBEG

namespace Accessors {

	class VIDECL Device {
	public:
		VIDECL static VkDevice GetDevice(const pDevice &device) {
			return ((cVulkanDevice *) device.get())->GetDevice();
		}

		VIDECL static VkSurfaceKHR DeviceGetSurface(const pDevice &device) {
			return ((cVulkanDevice *) device.get())->GetSurface();
		}

		VIDECL static VkCommandPool GetCommandPool(const pDevice &device) {
			return ((cVulkanDevice *) device.get())->GetCommandPool();
		}

		VIDECL static sSwapchainSupportDetails GetSwapchainSupport(const pDevice &device) {
			return ((cVulkanDevice *) device.get())->GetSwapchainSupport();
		}

		VIDECL static VkQueue GetGraphicsQueue(const pDevice &device) {
			return ((cVulkanDevice *) device.get())->GetGraphicsQueue();
		}

		VIDECL static VkQueue GetPresentQueue(const pDevice &device) {
			return ((cVulkanDevice *) device.get())->GetPresentQueue();
		}
	};

}

VISRCEND

#endif //VICTORIAM_ADEVICE_HPP
