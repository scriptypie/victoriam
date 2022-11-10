//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <Victoriam/Graphics/GPipeline.hpp>

#include "VulkanPipeline.hpp"

VISRCBEG

PPipeline CPipeline::Create(const String& name, PGraphicsContext& context, PSwapchain& swapchain, const PDescriptorSetLayout& setLayout, Bool createConstantRanges) {
	return CreateUPtr<CVulkanPipeline>(name, context, swapchain, setLayout, createConstantRanges);
}

VISRCEND

