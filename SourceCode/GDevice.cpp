//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <Victoriam/Graphics/GDevice.hpp>

#include "VulkanDevice.hpp"

VISRCBEG

PDevice CDevice::Create(const SPtr<CWindow> &window) {
	return CreateSPtr<CVulkanDevice>(window);
}

VISRCEND

