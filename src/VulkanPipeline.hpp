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

class cVulkanPipeline : public cPipeline
{
	VIDECL cShaderCooker m_ShaderCooker = {};
	VIDECL pDevice& m_Device;
	VIDECL VkPipeline m_GraphicsPipeline = {};
	VIDECL VkShaderModule m_VertexShaderModule = {};
	VIDECL VkShaderModule m_FragmentShaderModule = {};
	VIDECL sPipelineCreateInfo m_Info = {0, 0};
public:
	cVulkanPipeline(pDevice& device, const sPipelineCreateInfo& info);
	cVulkanPipeline(const String& name, pDevice& device, const sPipelineCreateInfo& info);

	void SetShader(const String& name) override;

private:
	VIDECL void CreateShaderModule(const BinaryData& sourceData, VkShaderModule* shaderModule);
};

VISRCEND

#endif //VICTORIAM_VULKANPIPELINE_HPP
