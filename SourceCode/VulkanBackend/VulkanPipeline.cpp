//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include "VulkanPipeline.hpp"

#include "Victoriam/Graphics/Structs/GMaterialData.hpp"

#include "../Accessors/AWindow.hpp"
#include "../Accessors/AGraphicsContext.hpp"
#include "../Accessors/ASwapchain.hpp"
#include "../Accessors/ADescriptorSetLayout.hpp"
#include "../Accessors/ARenderPass.hpp"

VISRCBEG

CVulkanPipeline::CVulkanPipeline(PGraphicsContext& context, PRenderPass& renderPass, const PDescriptorSetLayout& setLayout, const SPipelineCreateInfo& createInfo, const UInt32& pushDataSize)
		: m_Context(context)
{

	m_Info.RenderPass = Accessors::RenderPass::GetRenderPass(renderPass);
	m_Info.bProvideAttributes = createInfo.bProvideAttributes;
	m_Info.bProvideBindings = createInfo.bProvideBindings;
	m_Info.bCreateConstantRanges = createInfo.bCreateConstantRanges;
	m_Info.Name = createInfo.Name;

	if (!m_Info.bProvideBindings)
		m_Info.BindingDescriptions.Clear();
	if (!m_Info.bProvideAttributes)
		m_Info.AttributeDescriptions.Clear();

	// I know, it's wrong, but in this case it's okay 'cause our virtual function will be existed
	CreateShaderModule(m_ShaderCooker.LoadVertexShader(m_Info.Name), &m_VertexShaderModule);
	CreateShaderModule(m_ShaderCooker.LoadFragmentShader(m_Info.Name), &m_FragmentShaderModule);
	CreatePipelineLayout(setLayout, pushDataSize);
	CreateGraphicsPipeline();
}

CVulkanPipeline::~CVulkanPipeline()
{
	vkDestroyShaderModule(Accessors::GraphicsContext::GetDevice(m_Context), m_VertexShaderModule, nullptr);
	m_VertexShaderModule = nullptr;
	vkDestroyShaderModule(Accessors::GraphicsContext::GetDevice(m_Context), m_FragmentShaderModule, nullptr);
	m_FragmentShaderModule = nullptr;
	vkDestroyPipelineLayout(Accessors::GraphicsContext::GetDevice(m_Context), m_Info.PipelineLayout, nullptr);
	m_Info.PipelineLayout = nullptr;
	vkDestroyPipeline(Accessors::GraphicsContext::GetDevice(m_Context), m_GraphicsPipeline, nullptr);
	m_GraphicsPipeline = nullptr;
}

void CVulkanPipeline::CreateShaderModule(const CBinaryData &sourceData, VkShaderModule *shaderModule)
{
	VkShaderModuleCreateInfo createInfo = { VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
	createInfo.codeSize = sourceData.Size();
	createInfo.pCode = CCast<const UInt32*>(sourceData.Data());

	if (vkCreateShaderModule(Accessors::GraphicsContext::GetDevice(m_Context), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
		 ViAbort("Failed to create shader module!");
}

void CVulkanPipeline::CreateGraphicsPipeline()
{
	ViAssert(m_Info.RenderPass, "Cannot create graphics pipeline, cause RenderPass object is nullptr!");
	ViAssert(m_Info.PipelineLayout, "Cannot create graphics pipeline, cause PipelineLayout object is nullptr!");

	VkPipelineShaderStageCreateInfo shaderStagesCreateInfo[2] = {};
	for (UInt32 i = 0; i < 2; i++)
	{
		shaderStagesCreateInfo[i] = { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO };
		shaderStagesCreateInfo[i].stage = CCast<VkShaderStageFlagBits>(1 << i * 4);
		shaderStagesCreateInfo[i].pName = "main";
	}
	shaderStagesCreateInfo[0].module = m_VertexShaderModule;
	shaderStagesCreateInfo[1].module = m_FragmentShaderModule;

	VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };

	if (m_Info.bProvideAttributes) {
		vertexInputStateCreateInfo.pVertexAttributeDescriptions = m_Info.AttributeDescriptions.Data();
		vertexInputStateCreateInfo.vertexAttributeDescriptionCount = CCast<UInt32>(m_Info.AttributeDescriptions.Size());
	}
	if (m_Info.bProvideBindings) {
		vertexInputStateCreateInfo.pVertexBindingDescriptions = m_Info.BindingDescriptions.Data();
		vertexInputStateCreateInfo.vertexBindingDescriptionCount = CCast<UInt32>(m_Info.BindingDescriptions.Size());
	}

	VkGraphicsPipelineCreateInfo pipelineCreateInfo = { VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
	pipelineCreateInfo.pColorBlendState = &m_Info.ColorBlendStateCreateInfo;
	pipelineCreateInfo.pDepthStencilState = &m_Info.DepthStencilStateCreateInfo;
	pipelineCreateInfo.pInputAssemblyState = &m_Info.InputAssemblyStateCreateInfo;
	pipelineCreateInfo.pMultisampleState = &m_Info.MultisampleStateCreateInfo;
	pipelineCreateInfo.pRasterizationState = &m_Info.RasterizationStateCreateInfo;
	pipelineCreateInfo.pStages = shaderStagesCreateInfo;
	pipelineCreateInfo.stageCount = FSize(shaderStagesCreateInfo);
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

void CVulkanPipeline::CreatePipelineLayout(const PDescriptorSetLayout& setLayout, const UInt32& pushDataSize)
{
	VkPipelineLayoutCreateInfo createInfo = { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
	VkPushConstantRange pushConstantRange = {};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
	pushConstantRange.size = pushDataSize;

	if (m_Info.bCreateConstantRanges) {
		createInfo.pushConstantRangeCount = 1;
		createInfo.pPushConstantRanges = &pushConstantRange;
	}

	CSet<VkDescriptorSetLayout> setLayouts = {Accessors::DescriptorSetLayout::GetDescriptorSetLayout(setLayout)};

	createInfo.pSetLayouts = setLayouts.Data();
	createInfo.setLayoutCount = CCast<UInt32>(setLayouts.Size());

	if (vkCreatePipelineLayout(Accessors::GraphicsContext::GetDevice(m_Context), &createInfo, nullptr, &m_Info.PipelineLayout) != VK_SUCCESS)
		ViAbort("Failed to create pipeline layout!");
}

void CVulkanPipeline::BindCommandBuffer(const SCommandBuffer &commandBuffer) const {
	if (m_GraphicsPipeline)
		vkCmdBindPipeline(CCast<VkCommandBuffer>(commandBuffer),
				        VK_PIPELINE_BIND_POINT_GRAPHICS,
						m_GraphicsPipeline);
	else
		ViAbort("Failed to bind command buffer because graphics pipeline is null!");
}

void CVulkanPipeline::PushSimpleData(const SCommandBuffer& buffer, const UInt32& offset, const void* data, const UInt32& dataSize) const {
	vkCmdPushConstants(
			CCast<VkCommandBuffer>(buffer),
	        m_Info.PipelineLayout,
			VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
			offset,
			dataSize,
			data);
}

void CVulkanPipeline::BindConstantsDescriptorSet(const Signal& bindPoint, const SFrameInfo& frameInfo) const {
	vkCmdBindDescriptorSets(CCast<VkCommandBuffer>(frameInfo.CommandBuffer),
			                CCast<VkPipelineBindPoint>(bindPoint),
							m_Info.PipelineLayout, 0, 1,
							CCast<VkDescriptorSet*>(&frameInfo.ConstantsDescriptorSet),
					        0, nullptr);
}

VISRCEND
