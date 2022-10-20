//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#include <Victoriam/Graphics/GSwapchain.hpp>

#include "VulkanSwapchain.hpp"

VISRCBEG


pSwapchain cSwapchain::Create(pDevice &device, const sWindowExtent &extent) {
	return CreateUPtr<cVulkanSwapchain>(device, extent);
}

pSwapchain cSwapchain::Create(pDevice &device, const sWindowExtent &extent, cSwapchain* prev)
{
	return CreateUPtr<cVulkanSwapchain>(device, extent, prev);
}

VISRCEND
