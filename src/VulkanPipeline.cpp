//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include "VulkanPipeline.hpp"

VISRCBEG

cVulkanPipeline::cVulkanPipeline(pDevice &device, const sPipelineCreateInfo &info)
		: m_Device(device), m_Info(info)
{

}

cVulkanPipeline::cVulkanPipeline(const String& name, pDevice &device, const sPipelineCreateInfo &info)
		: cVulkanPipeline(device, info)
{
	// I know, it's wrong, but in this case its okay 'cause our virtual function will be existed
	SetShader(name);
}

void cVulkanPipeline::SetShader(const String &name) {

}

void cVulkanPipeline::CreateShaderModule(const BinaryData &sourceData, VkShaderModule *shaderModule) {
	VkShaderModuleCreateInfo createInfo = { VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
	createInfo.codeSize = sourceData.size();
	createInfo.pCode = sourceData.data();

	if (vkCreateShaderModule(Accessors::Device::GetDevice(m_Device), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
		 throw std::runtime_error("Failed to create shader module!");
}

VISRCEND
