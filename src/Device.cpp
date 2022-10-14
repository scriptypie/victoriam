//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <Victoriam/Graphics/Device.hpp>

#include "VulkanDevice.hpp"

VISRCBEG

UPtr<cDevice> cDevice::Create(const SPtr<cWindow> &window) {
	return CreateUPtr<cVulkanDevice>(window);
}

VISRCEND

