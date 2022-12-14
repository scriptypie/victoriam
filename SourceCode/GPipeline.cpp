//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <Victoriam/Graphics/GPipeline.hpp>

#include "VulkanBackend/VulkanPipeline.hpp"

VISRCBEG

PPipeline CPipeline::Create(PGraphicsContext& context, PRenderPass& renderPass, const PDescriptorSetLayout& setLayout, const SPipelineCreateInfo& createInfo, const UInt32& pushDataSize) {
	return FMakeUnique<CVulkanPipeline>(context, renderPass, setLayout, createInfo, pushDataSize);
}

VISRCEND

