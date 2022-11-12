//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <Victoriam/Graphics/GPipeline.hpp>

#include "VulkanPipeline.hpp"

VISRCBEG

PPipeline CPipeline::Create(PGraphicsContext& context, PSwapchain& swapchain, const PDescriptorSetLayout& setLayout, const SPipelineCreateInfo& createInfo, const UInt32& pushDataSize) {
	return CreateUPtr<CVulkanPipeline>(context, swapchain, setLayout, createInfo, pushDataSize);
}

VISRCEND

