//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_VULKANPIPELINE_HPP
#define VICTORIAM_VULKANPIPELINE_HPP

#include "Accessors/AWindow.hpp"
#include "Accessors/ADevice.hpp"
#include "Accessors/ASwapchain.hpp"
#include <Victoriam/Utils/UShaderCooker.hpp>
#include <Victoriam/Graphics/GPipeline.hpp>

VISRCBEG

namespace Accessors { class Pipeline; }

struct VIDECL sVulkanPipelineCreateInfo : sPipelineCreateInfo
{
	VIDECL VkPipelineInputAssemblyStateCreateInfo InputAssemblyStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
	VIDECL VkPipelineRasterizationStateCreateInfo RasterizationStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
	VIDECL VkPipelineMultisampleStateCreateInfo MultisampleStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
	VIDECL VkPipelineColorBlendAttachmentState ColorBlendAttachmentState = {};
	VIDECL VkPipelineColorBlendStateCreateInfo ColorBlendStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
	VIDECL VkPipelineDepthStencilStateCreateInfo DepthStencilStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
	VIDECL VkPipelineViewportStateCreateInfo ViewportStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
	VIDECL VkPipelineDynamicStateCreateInfo DynamicStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
	VIDECL List<VkDynamicState> DynamicStateEnables = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
	VIDECL VkPipelineLayout PipelineLayout = VK_NULL_HANDLE;
	VIDECL VkRenderPass RenderPass = VK_NULL_HANDLE;
	VIDECL UInt32 Subpass = {};

	VIDECL inline explicit sVulkanPipelineCreateInfo(const VkRenderPass& renderPass)
		: sVulkanPipelineCreateInfo()
	{
		// RenderPass
		RenderPass = renderPass;
	}

	VIDECL inline sVulkanPipelineCreateInfo()
	{
		// InputAssembly
		InputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		// ViewportStateCreateInfo
		ViewportStateCreateInfo.viewportCount = 1; // Only one viewport will be used
		ViewportStateCreateInfo.pViewports = nullptr;
		ViewportStateCreateInfo.scissorCount = 1; // ...as well as scissor
		ViewportStateCreateInfo.pScissors = nullptr;
		// RasterizationState
		RasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL; // TODO: Maybe add a wireframe mode?
		RasterizationStateCreateInfo.lineWidth = 1.0f;                   // LINE_WIDTH FOR WIREFRAME MODE
		RasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;   // VK_CULL_MODE_NONE
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
		DynamicStateCreateInfo.dynamicStateCount = CCast<UInt32>(DynamicStateEnables.size());
		DynamicStateCreateInfo.pDynamicStates = DynamicStateEnables.data();
	}
};

class cVulkanPipeline : public cPipeline
{
	friend class Accessors::Pipeline;
	friend class cVulkanRenderer;

	VIDECL cShaderCooker m_ShaderCooker = {};
	VIDECL pDevice& m_Device;
	VIDECL VkPipeline m_GraphicsPipeline = {};
	VIDECL VkShaderModule m_VertexShaderModule = {};
	VIDECL VkShaderModule m_FragmentShaderModule = {};
	VIDECL sVulkanPipelineCreateInfo m_Info = {};
public:
	cVulkanPipeline(const String& name, pDevice& device, pSwapchain& swapchain);
	~cVulkanPipeline() override;

	void BindDrawCommandBuffer(const sCommandBuffer& buffer) override;
private:
	VIDECL void CreateShaderModule(const BinaryData& sourceData, VkShaderModule* shaderModule);
	VIDECL void CreateGraphicsPipeline();
	VIDECL void CreatePipelineLayout();
};

VISRCEND

#endif //VICTORIAM_VULKANPIPELINE_HPP
