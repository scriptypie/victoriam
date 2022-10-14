//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <Victoriam/Graphics/Pipeline.hpp>

#include "VulkanPipeline.hpp"

VISRCBEG

pPipeline cPipeline::Create(pDevice &device, const sPipelineCreateInfo &info) {
	return CreateSPtr<cVulkanPipeline>(device, info);
}

pPipeline cPipeline::Create(const String& name, pDevice& device, const sPipelineCreateInfo& info) {
	return CreateSPtr<cVulkanPipeline>(name, device, info);
}

VISRCEND

