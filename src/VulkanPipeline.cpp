//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include "VulkanPipeline.hpp"

VISRCBEG

cVulkanPipeline::cVulkanPipeline(const String& name, pDevice &device, const sPipelineCreateInfo &info)
		: m_Device(device), m_Info(info.Width, info.Height)
{
	// I know, it's wrong, but in this case it's okay 'cause our virtual function will be existed
	CreateShaderModule(m_ShaderCooker.LoadVertexShader(name), &m_VertexShaderModule);
	CreateShaderModule(m_ShaderCooker.LoadFragmentShader(name), &m_FragmentShaderModule);
	CreateGraphicsPipeline();
}

cVulkanPipeline::~cVulkanPipeline() {
	vkDestroyShaderModule(Accessors::Device::GetDevice(m_Device), m_VertexShaderModule, nullptr);
	vkDestroyShaderModule(Accessors::Device::GetDevice(m_Device), m_FragmentShaderModule, nullptr);
	vkDestroyPipeline(Accessors::Device::GetDevice(m_Device), m_GraphicsPipeline, nullptr);
}

void cVulkanPipeline::CreateShaderModule(const BinaryData &sourceData, VkShaderModule *shaderModule) {
	VkShaderModuleCreateInfo createInfo = { VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
	createInfo.codeSize = sourceData.size();
	createInfo.pCode = CCast<const UInt32*>(sourceData.data());

	if (vkCreateShaderModule(Accessors::Device::GetDevice(m_Device), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
		 throw std::runtime_error("Failed to create shader module!");
}

void cVulkanPipeline::CreateGraphicsPipeline() {
	assert(m_Info.RenderPass != nullptr && "Cannot create graphics pipeline, cause RenderPass object is nullptr!");
	assert(m_Info.PipelineLayout != nullptr && "Cannot create graphics pipeline, cause PipelineLayout object is nullptr!");

	VkPipelineShaderStageCreateInfo shaderStagesCreateInfo[2] = {{VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO }, {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO } };
	shaderStagesCreateInfo[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	shaderStagesCreateInfo[0].module = m_VertexShaderModule;
	shaderStagesCreateInfo[0].pName = "main";
	shaderStagesCreateInfo[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	shaderStagesCreateInfo[1].module = m_FragmentShaderModule;
	shaderStagesCreateInfo[1].pName = "main";

	VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };

	VkGraphicsPipelineCreateInfo pipelineCreateInfo = { VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
	pipelineCreateInfo.pColorBlendState = &m_Info.ColorBlendStateCreateInfo;
	pipelineCreateInfo.pDepthStencilState = &m_Info.DepthStencilStateCreateInfo;
	pipelineCreateInfo.pInputAssemblyState = &m_Info.InputAssemblyStateCreateInfo;
	pipelineCreateInfo.pMultisampleState = &m_Info.MultisampleStateCreateInfo;
	pipelineCreateInfo.pRasterizationState = &m_Info.RasterizationStateCreateInfo;
	pipelineCreateInfo.pStages = shaderStagesCreateInfo;
	pipelineCreateInfo.stageCount = StaticSize(shaderStagesCreateInfo);
	pipelineCreateInfo.pVertexInputState = &vertexInputStateCreateInfo;
	pipelineCreateInfo.pViewportState = &m_Info.ViewportStateCreateInfo;
	pipelineCreateInfo.layout = m_Info.PipelineLayout;
	pipelineCreateInfo.renderPass = m_Info.RenderPass;
	pipelineCreateInfo.subpass = m_Info.Subpass;
	pipelineCreateInfo.basePipelineIndex = -1;

	if (vkCreateGraphicsPipelines(Accessors::Device::GetDevice(m_Device), nullptr, 1, &pipelineCreateInfo, nullptr, &m_GraphicsPipeline) != VK_SUCCESS)
		throw std::runtime_error("Failed to create graphics pipeline!");
}


VISRCEND
