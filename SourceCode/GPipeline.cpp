//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <Victoriam/Graphics/GPipeline.hpp>

#include "VulkanPipeline.hpp"

VISRCBEG

PPipeline CPipeline::Create(const String& name, PDevice& device, PSwapchain& swapchain) {
	return CreateUPtr<CVulkanPipeline>(name, device, swapchain);
}

VISRCEND

