//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include "VulkanDevice.hpp"

VISRCBEG

cVulkanDevice::cVulkanDevice(const SPtr<cWindow> &window) {
	m_Window = (cWindowGLFWImpl*)window.get();

}

cVulkanDevice::~cVulkanDevice() {

}

VISRCEND
