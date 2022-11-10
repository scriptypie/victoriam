//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include "VulkanPipeline.hpp"

#include "VulkanVertex.hpp"

#include <Victoriam/Graphics/Structs/GMaterialData.hpp>

VISRCBEG

CVulkanPipeline::CVulkanPipeline(const String& name, PGraphicsContext& context, PSwapchain& swapchain, const PDescriptorSetLayout& setLayout)
		: m_Context(context), m_Info(Accessors::Swapchain::GetRenderPass(swapchain))
{
	// I know, it's wrong, but in this case it's okay 'cause our virtual function will be existed
	CreateShaderModule(m_ShaderCooker.LoadVertexShader(name), &m_VertexShaderModule);
	CreateShaderModule(m_ShaderCooker.LoadFragmentShader(name), &m_FragmentShaderModule);
	CreatePipelineLayout(setLayout);
	CreateGraphicsPipeline();
}

CVulkanPipeline::~CVulkanPipeline()
{
	vkDestroyShaderModule(Accessors::GraphicsContext::GetDevice(m_Context), m_VertexShaderModule, nullptr);
	vkDestroyShaderModule(Accessors::GraphicsContext::GetDevice(m_Context), m_FragmentShaderModule, nullptr);
	vkDestroyPipelineLayout(Accessors::GraphicsContext::GetDevice(m_Context), m_Info.PipelineLayout, nullptr);
	vkDestroyPipeline(Accessors::GraphicsContext::GetDevice(m_Context), m_GraphicsPipeline, nullptr);
}

void CVulkanPipeline::CreateShaderModule(const BinaryData &sourceData, VkShaderModule *shaderModule)
{
	VkShaderModuleCreateInfo createInfo = { VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
	createInfo.codeSize = sourceData.size();
	createInfo.pCode = CCast<const UInt32*>(sourceData.data());

	if (vkCreateShaderModule(Accessors::GraphicsContext::GetDevice(m_Context), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
		 throw std::runtime_error("Failed to create shader module!");
}

void CVulkanPipeline::CreateGraphicsPipeline()
{
	ViAssert(m_Info.RenderPass, "Cannot create graphics pipeline, cause RenderPass object is nullptr!");
	ViAssert(m_Info.PipelineLayout, "Cannot create graphics pipeline, cause PipelineLayout object is nullptr!");

	VkPipelineShaderStageCreateInfo shaderStagesCreateInfo[2] = {{VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO }, {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO } };
	shaderStagesCreateInfo[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	shaderStagesCreateInfo[0].module = m_VertexShaderModule;
	shaderStagesCreateInfo[0].pName = "main";
	shaderStagesCreateInfo[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	shaderStagesCreateInfo[1].module = m_FragmentShaderModule;
	shaderStagesCreateInfo[1].pName = "main";

	auto bindingDescriptions = FGetVertexBindingDescriptions();
	auto attributeDescriptions = FGetVertexAttributeDescriptions();

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

	if (vkCreateGraphicsPipelines(Accessors::GraphicsContext::GetDevice(m_Context), nullptr, 1, &pipelineCreateInfo, nullptr, &m_GraphicsPipeline) != VK_SUCCESS)
		ViAbort("Failed to create graphics pipeline!");
}

void CVulkanPipeline::CreatePipelineLayout(const PDescriptorSetLayout& setLayout)
{
	VkPushConstantRange pushConstantRange = {};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
	pushConstantRange.size = sizeof(SMaterialData);

	VkPipelineLayoutCreateInfo createInfo = { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
	createInfo.pushConstantRangeCount = 1;
	createInfo.pPushConstantRanges = &pushConstantRange;

	VkDescriptorSetLayout vkSetLayoutObject = Accessors::DescriptorSetLayout::GetDescriptorSetLayout(setLayout);
	List<VkDescriptorSetLayout> setLayouts = {vkSetLayoutObject};

	createInfo.pSetLayouts = setLayouts.data();
	createInfo.setLayoutCount = CCast<UInt32>(setLayouts.size());

	if (vkCreatePipelineLayout(Accessors::GraphicsContext::GetDevice(m_Context), &createInfo, nullptr, &m_Info.PipelineLayout) != VK_SUCCESS)
		ViAbort("Failed to create pipeline layout!");
}

void CVulkanPipeline::BindCommandBuffer(const SCommandBuffer &commandBuffer) const {
	if (m_GraphicsPipeline != VK_NULL_HANDLE)
		vkCmdBindPipeline(CCast<VkCommandBuffer>(commandBuffer), VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicsPipeline);
	else
		ViAbort("Failed to bind command buffer because graphics pipeline is null!");
}

void CVulkanPipeline::PushMaterialData(SCommandBuffer const &buffer, const UInt32 &offset, const SMaterialData *materialData) const
{
	vkCmdPushConstants(CCast<VkCommandBuffer>(buffer), m_Info.PipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, offset, sizeof(SMaterialData), materialData);
}

void CVulkanPipeline::BindConstantsDescriptorSet(const Signal& bindPoint, const SFrameInfo& frameInfo) const {
	vkCmdBindDescriptorSets(CCast<VkCommandBuffer>(frameInfo.CommandBuffer), CCast<VkPipelineBindPoint>(bindPoint), m_Info.PipelineLayout, 0, 1, CCast<VkDescriptorSet*>(&frameInfo.ConstantsDescriptorSet), 0, nullptr);
}

VISRCEND
