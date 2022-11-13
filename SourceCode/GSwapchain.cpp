//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#include <Victoriam/Graphics/GSwapchain.hpp>

#include "VulkanBackend/VulkanSwapchain.hpp"

VISRCBEG

PSwapchain CSwapchain::Create(PGraphicsContext &context, const SExtent2D &extent) {
	return CreateUPtr<CVulkanSwapchain>(context, extent);
}

PSwapchain CSwapchain::Create(PGraphicsContext &context, const SExtent2D &extent, CSwapchain* prev)
{
	return CreateUPtr<CVulkanSwapchain>(context, extent, prev);
}

VISRCEND
