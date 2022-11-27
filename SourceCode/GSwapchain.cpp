//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#include <Victoriam/Graphics/GSwapchain.hpp>

#include "VulkanBackend/VulkanSwapchain.hpp"

VISRCBEG

PSwapchain CSwapchain::Create(PGraphicsContext &context, const SExtent2D &extent) {
	return FCreateUnique<CVulkanSwapchain>(context, extent);
}

PSwapchain CSwapchain::Create(PGraphicsContext &context, const SExtent2D &extent, CSwapchain* prev)
{
	return FCreateUnique<CVulkanSwapchain>(context, extent, prev);
}

VISRCEND
