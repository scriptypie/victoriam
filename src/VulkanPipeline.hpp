//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_VULKANPIPELINE_HPP
#define VICTORIAM_VULKANPIPELINE_HPP

#include "Accessors/AWindow.hpp"
#include "Accessors/ADevice.hpp"
#include <Victoriam/Utils/ShaderCooker.hpp>
#include <Victoriam/Graphics/Pipeline.hpp>

VISRCBEG

struct VIDECL sVulkanPipelineCreateInfo : sPipelineCreateInfo
{
	VIDECL VkViewport Viewport = {};
	VIDECL VkRect2D Scissor = {};
	VIDECL VkPipelineViewportStateCreateInfo ViewportStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
	VIDECL VkPipelineInputAssemblyStateCreateInfo InputAssemblyStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
	VIDECL VkPipelineRasterizationStateCreateInfo RasterizationStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
	VIDECL VkPipelineMultisampleStateCreateInfo MultisampleStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
	VIDECL VkPipelineColorBlendAttachmentState ColorBlendAttachmentState = {};
	VIDECL VkPipelineColorBlendStateCreateInfo ColorBlendStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
	VIDECL VkPipelineDepthStencilStateCreateInfo DepthStencilStateCreateInfo = { VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO };
	VIDECL VkPipelineLayout PipelineLayout = nullptr;
	VIDECL VkRenderPass RenderPass = nullptr;
	VIDECL UInt32 Subpass = {};

	VIDECL inline sVulkanPipelineCreateInfo(const UInt32& width, const UInt32& height)
		: sPipelineCreateInfo(width, height)
	{
		
	}
};

class cVulkanPipeline : public cPipeline
{
	VIDECL cShaderCooker m_ShaderCooker = {};
	VIDECL pDevice& m_Device;
	VIDECL VkPipeline m_GraphicsPipeline = {};
	VIDECL VkShaderModule m_VertexShaderModule = {};
	VIDECL VkShaderModule m_FragmentShaderModule = {};
	VIDECL sVulkanPipelineCreateInfo m_Info = {0, 0};
public:
	cVulkanPipeline(pDevice& device, const sPipelineCreateInfo& info);
	cVulkanPipeline(const String& name, pDevice& device, const sPipelineCreateInfo& info);

	void SetShader(const String& name) override;

private:
	VIDECL void CreateShaderModule(const BinaryData& sourceData, VkShaderModule* shaderModule);
};

VISRCEND

#endif //VICTORIAM_VULKANPIPELINE_HPP
