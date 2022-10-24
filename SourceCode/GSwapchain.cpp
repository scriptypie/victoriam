//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#include <Victoriam/Graphics/GSwapchain.hpp>

#include "VulkanSwapchain.hpp"

VISRCBEG


PSwapchain CSwapchain::Create(PDevice &device, const SWindowExtent &extent) {
	return CreateUPtr<CVulkanSwapchain>(device, extent);
}

PSwapchain CSwapchain::Create(PDevice &device, const SWindowExtent &extent, CSwapchain* prev)
{
	return CreateUPtr<CVulkanSwapchain>(device, extent, prev);
}

VISRCEND
