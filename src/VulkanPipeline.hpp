//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_VULKANPIPELINE_HPP
#define VICTORIAM_VULKANPIPELINE_HPP

#include "WindowAccessor.hpp"
#include "DeviceAccessor.hpp"
#include <Victoriam/Utils/ShaderCooker.hpp>
#include <Victoriam/Graphics/Pipeline.hpp>

VISRCBEG

class cVulkanPipeline : public cPipeline, public cDeviceAccessor
{
	cShaderCooker m_ShaderCooker = {};
	pDevice& m_Device;
	VkPipeline m_GraphicsPipeline = {};
	VkShaderModule m_VertexShaderModule = {};
	VkShaderModule m_FragmentShaderModule = {};
public:
	cVulkanPipeline(pDevice& device, const sPipelineCreateInfo& info);
	cVulkanPipeline(const String& name, pDevice& device, const sPipelineCreateInfo& info);

	void SetShader(const String& name) override;

private:
	void CreateShaderModule(const BinaryData& sourceData, VkShaderModule* shaderModule);
};

VISRCEND

#endif //VICTORIAM_VULKANPIPELINE_HPP
