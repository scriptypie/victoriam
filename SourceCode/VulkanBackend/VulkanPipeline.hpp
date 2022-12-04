//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_VULKANPIPELINE_HPP
#define VICTORIAM_VULKANPIPELINE_HPP

#include "Victoriam/Utils/UShaderCooker.hpp"
#include "Victoriam/Graphics/GPipeline.hpp"

#include "VulkanVertex.hpp"

VISRCBEG

namespace Accessors { class Pipeline; }

struct VIDECL SVulkanPipelineCreateInfo : SPipelineCreateInfo
{
	VIDECL CSet<VkVertexInputBindingDescription> BindingDescriptions = {};
	VIDECL CSet<VkVertexInputAttributeDescription> AttributeDescriptions = {};
	VIDECL VkPipelineInputAssemblyStateCreateInfo InputAssemblyStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
	VIDECL VkPipelineRasterizationStateCreateInfo RasterizationStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
	VIDECL VkPipelineMultisampleStateCreateInfo MultisampleStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
	VIDECL VkPipelineColorBlendAttachmentState ColorBlendAttachmentState = {};
	VIDECL VkPipelineColorBlendStateCreateInfo ColorBlendStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
	VIDECL VkPipelineDepthStencilStateCreateInfo DepthStencilStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
	VIDECL VkPipelineViewportStateCreateInfo ViewportStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
	VIDECL VkPipelineDynamicStateCreateInfo DynamicStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
	VIDECL CSet<VkDynamicState> DynamicStateEnables = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
	VIDECL VkPipelineLayout PipelineLayout = VK_NULL_HANDLE;
	VIDECL VkRenderPass RenderPass = VK_NULL_HANDLE;
	VIDECL UInt32 Subpass = {};

	VIDECL inline explicit SVulkanPipelineCreateInfo(const VkRenderPass& renderPass)
	{
		// RenderPass
		RenderPass = renderPass;
	}

	VIDECL inline explicit SVulkanPipelineCreateInfo(const SPipelineCreateInfo& createInfo, const VkRenderPass& renderPass)
	{
		RenderPass = renderPass;
		Name = createInfo.Name;
		Width = createInfo.Width;
		Height = createInfo.Height;
		bProvideBindings = createInfo.bProvideBindings;
		bProvideAttributes = createInfo.bProvideAttributes;

		if (!bProvideBindings)
		{
			BindingDescriptions.Clear();
		}
		if (!bProvideAttributes)
		{
			AttributeDescriptions.Clear();
		}
	}

	VIDECL inline SVulkanPipelineCreateInfo()
	{
		// InputAssembly
		InputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		// ViewportStateCreateInfo
		ViewportStateCreateInfo.viewportCount = 1; // Only one viewport will be used
		ViewportStateCreateInfo.pViewports = nullptr;
		ViewportStateCreateInfo.scissorCount = 1; // ...as well as scissor
		ViewportStateCreateInfo.pScissors = nullptr;
		// RasterizationState
		RasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL; // // VK_POLYGON_MODE_FILL or VK_POLYGON_MODE_LINE TODO: Maybe add a wireframe mode?
		RasterizationStateCreateInfo.lineWidth = 1.0f;                   // LINE_WIDTH FOR WIREFRAME MODE
		RasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;   // VK_CULL_MODE_NONE or VK_CULL_MODE_BACK_BIT
		RasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
		// MultisampleStateCreateInfo
		MultisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		MultisampleStateCreateInfo.minSampleShading = 1.0f;
		// ColorBlendAttachmentState
		ColorBlendAttachmentState.colorWriteMask = 0x0000000F; /* RGBA */
		ColorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional
		ColorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
		ColorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;             // Optional
		ColorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional
		ColorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
		ColorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;             // Optional
		// ColorBlendStateCreateInfo
		ColorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_COPY;
		ColorBlendStateCreateInfo.attachmentCount = 1;
		ColorBlendStateCreateInfo.pAttachments = &ColorBlendAttachmentState;
		// DepthStencilStateCreateInfo
		DepthStencilStateCreateInfo.depthTestEnable = true;
		DepthStencilStateCreateInfo.depthWriteEnable = true;
		DepthStencilStateCreateInfo.depthCompareOp = VK_COMPARE_OP_LESS;
		DepthStencilStateCreateInfo.maxDepthBounds = 1.0f;
		// DynamicStateCreateInfo
		DynamicStateCreateInfo.dynamicStateCount = CCast<UInt32>(DynamicStateEnables.Size());
		DynamicStateCreateInfo.pDynamicStates = DynamicStateEnables.Data();

		BindingDescriptions = FGetVertexBindingDescriptions();
		AttributeDescriptions = FGetVertexAttributeDescriptions();

	}
};

class VIDECL CVulkanPipeline : public CPipeline
{
	friend class Accessors::Pipeline;
	friend class CVulkanRenderer;

	VIDECL CShaderCooker m_ShaderCooker = {};
	VIDECL PGraphicsContext& m_Context;
	VIDECL VkPipeline m_GraphicsPipeline = {};
	VIDECL VkShaderModule m_VertexShaderModule = {};
	VIDECL VkShaderModule m_FragmentShaderModule = {};
	VIDECL SVulkanPipelineCreateInfo m_Info = {};
public:
	VIDECL CVulkanPipeline(PGraphicsContext& context, PRenderPass& renderPass, const PDescriptorSetLayout& setLayout, const SPipelineCreateInfo& createInfo, const UInt32& pushDataSize);
	VIDECL ~CVulkanPipeline() override;

	VIDECL void BindCommandBuffer(const SCommandBuffer& buffer) const override;
	VIDECL void PushSimpleData(const SCommandBuffer& buffer, const UInt32& offset, const void* data, const UInt32& dataSize) const override;
	VIDECL void BindConstantsDescriptorSet(const Signal& bindPoint, const SFrameInfo& frameInfo) const override;
private:
	VIDECL void CreateShaderModule(const CBinaryData& sourceData, VkShaderModule* shaderModule);
	VIDECL void CreateGraphicsPipeline();
	VIDECL void CreatePipelineLayout(const PDescriptorSetLayout& setLayout, const UInt32& pushDataSize);
};

VISRCEND

#endif //VICTORIAM_VULKANPIPELINE_HPP
