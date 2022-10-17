//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <Victoriam/Graphics/Pipeline.hpp>

#include "VulkanPipeline.hpp"

VISRCBEG

pPipeline cPipeline::Create(const String& name, pDevice& device, pSwapchain& swapchain, const sPipelineCreateInfo& info) {
	return CreateUPtr<cVulkanPipeline>(name, device, swapchain, info);
}

VISRCEND

