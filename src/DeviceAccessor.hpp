//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_DEVICEACCESSOR_HPP
#define VICTORIAM_DEVICEACCESSOR_HPP

#include <Victoriam/Graphics/Basics.hpp>

#include "VulkanDevice.hpp"

VISRCBEG

class cDeviceAccessor
{
public:
	static VkDevice GetDevice(const pDevice& device)
	{
		return ((cVulkanDevice*)device.get())->m_Device;
	}
	static VkSurfaceKHR GetSurface(const pDevice& device)
	{
		return ((cVulkanDevice*)device.get())->m_Surface;
	}
};

VISRCEND

#endif //VICTORIAM_DEVICEACCESSOR_HPP
