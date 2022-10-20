//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include "VulkanPipeline.hpp"

#include "VulkanVertex.hpp"

VISRCBEG

cVulkanPipeline::cVulkanPipeline(const String& name, pDevice &device, pSwapchain& swapchain)
		: m_Device(device), m_Info(Accessors::Swapchain::GetRenderPass(swapchain))
{
	// I know, it's wrong, but in this case it's okay 'cause our virtual function will be existed
	CreateShaderModule(m_ShaderCooker.LoadVertexShader(name), &m_VertexShaderModule);
	CreateShaderModule(m_ShaderCooker.LoadFragmentShader(name), &m_FragmentShaderModule);
	CreatePipelineLayout();
	CreateGraphicsPipeline();
}

cVulkanPipeline::~cVulkanPipeline()
{
	vkDestroyShaderModule(Accessors::Device::GetDevice(m_Device), m_VertexShaderModule, nullptr);
	vkDestroyShaderModule(Accessors::Device::GetDevice(m_Device), m_FragmentShaderModule, nullptr);
	vkDestroyPipelineLayout(Accessors::Device::GetDevice(m_Device), m_Info.PipelineLayout, nullptr);
	vkDestroyPipeline(Accessors::Device::GetDevice(m_Device), m_GraphicsPipeline, nullptr);
}

void cVulkanPipeline::CreateShaderModule(const BinaryData &sourceData, VkShaderModule *shaderModule)
{
	VkShaderModuleCreateInfo createInfo = { VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
	createInfo.codeSize = sourceData.size();
	createInfo.pCode = CCast<const UInt32*>(sourceData.data());

	if (vkCreateShaderModule(Accessors::Device::GetDevice(m_Device), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
		 throw std::runtime_error("Failed to create shader module!");
}

void cVulkanPipeline::CreateGraphicsPipeline()
{
	assert(m_Info.RenderPass && "Cannot create graphics pipeline, cause RenderPass object is nullptr!");
	assert(m_Info.PipelineLayout && "Cannot create graphics pipeline, cause PipelineLayout object is nullptr!");

	VkPipelineShaderStageCreateInfo shaderStagesCreateInfo[2] = {{VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO }, {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO } };
	shaderStagesCreateInfo[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	shaderStagesCreateInfo[0].module = m_VertexShaderModule;
	shaderStagesCreateInfo[0].pName = "main";
	shaderStagesCreateInfo[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	shaderStagesCreateInfo[1].module = m_FragmentShaderModule;
	shaderStagesCreateInfo[1].pName = "main";

	auto bindingDescriptions = GetVertexBindingDesctiptions();
	auto attributeDescriptions = GetVertexAttributeDescriptions();

	VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };
	vertexInputStateCreateInfo.vertexAttributeDescriptionCount = CCast<UInt32>(attributeDescriptions.size());
	vertexInputStateCreateInfo.vertexBindingDescriptionCount = CCast<UInt32>(bindingDescriptions.size());
	vertexInputStateCreateInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
	vertexInputStateCreateInfo.pVertexBindingDescriptions = bindingDescriptions.data();

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
	pipelineCreateInfo.pDynamicState = &m_Info.DynamicStateCreateInfo;
	pipelineCreateInfo.layout = m_Info.PipelineLayout;
	pipelineCreateInfo.renderPass = m_Info.RenderPass;
	pipelineCreateInfo.subpass = m_Info.Subpass;
	pipelineCreateInfo.basePipelineIndex = -1;

	if (vkCreateGraphicsPipelines(Accessors::Device::GetDevice(m_Device), nullptr, 1, &pipelineCreateInfo, nullptr, &m_GraphicsPipeline) != VK_SUCCESS)
		throw std::runtime_error("Failed to create graphics pipeline!");
}

void cVulkanPipeline::CreatePipelineLayout()
{
	VkPipelineLayoutCreateInfo createInfo = { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
	if (vkCreatePipelineLayout(Accessors::Device::GetDevice(m_Device), &createInfo, nullptr, &m_Info.PipelineLayout) != VK_SUCCESS)
		throw std::runtime_error("Failed to create pipeline layout!");
}

void cVulkanPipeline::BindDrawCommandBuffer(const sCommandBuffer &commandBuffer) {
	if (m_GraphicsPipeline != VK_NULL_HANDLE)
		vkCmdBindPipeline(CCast<VkCommandBuffer>(commandBuffer), VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicsPipeline);
	else
		throw std::runtime_error("Failed to bind command buffer because graphics pipeline is null!");
}

VISRCEND
