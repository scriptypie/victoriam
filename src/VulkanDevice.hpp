//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_VULKANDEVICE_HPP
#define VICTORIAM_VULKANDEVICE_HPP

#include <Victoriam/Graphics/Device.hpp>

#include "WindowGlfwImpl.hpp"

VISRCBEG

class cVulkanDevice : public cDevice
{
	VkDevice m_Device;
	cWindowGLFWImpl* m_Window;
public:
	explicit cVulkanDevice(const SPtr<cWindow> &window);
	virtual ~cVulkanDevice();
};

VISRCEND

#endif //VICTORIAM_VULKANDEVICE_HPP
