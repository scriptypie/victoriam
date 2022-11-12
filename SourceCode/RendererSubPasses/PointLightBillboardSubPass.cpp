//
// Created by Вячеслав Кривенко on 11.11.2022.
//

#include "PointLightBillboardSubPass.hpp"

#include <Victoriam/Graphics/Structs/GPointLightsData.hpp>

#include <vulkan/vulkan.h>

VISRCBEG

CPointLightBillboardSubPass::CPointLightBillboardSubPass(PGraphicsContext &context, PSwapchain &swapchain,
                                                         const PDescriptorSetLayout &setLayout)
	: m_Context(context)
{
	CreateSubPass(swapchain, setLayout);
}

void CPointLightBillboardSubPass::Compute(SFrameInfo &frameInfo, const PWorld &world) {

	auto plObjects = world->AllWith<SComponentTransform, SComponentPointLight>();
	auto camObject = world->OneWith<SComponentTransform, SComponentCamera>();
	auto [camTransform, camCamera] = camObject->Group<SComponentTransform, SComponentCamera>();

	Int32 index = 0;
	auto& constants = frameInfo.Constants;

	for (auto plObj : plObjects)
	{
		auto [componentTransform, componentPointLight] = plObj->Group<SComponentTransform, SComponentPointLight>();
		auto& pointLight = constants.PointLights[index];
		Float32 distance = glm::distance(camTransform->Translation, componentTransform->Translation);
		if (distance > world->GetRendererSettings().IlluminationDistance) continue;

		pointLight.Position = SVector4(
				componentTransform->Translation,
				componentPointLight->Radius
				);
		pointLight.Color = componentPointLight->LightColor;
		index += 1;
	}
	constants.ActiveLightsCount = index;
}

void CPointLightBillboardSubPass::Pass(const SFrameInfo &frameInfo, const PWorld &world) {
	m_Pipeline->BindCommandBuffer(frameInfo.CommandBuffer);
	m_Pipeline->BindConstantsDescriptorSet(BindPointGraphics, frameInfo);

	auto plObjects = world->AllWith<SComponentTransform, SComponentPointLight>();
	for (auto plObj : plObjects)
	{
		auto [componentTransform, componentPointLight] = plObj->Group<SComponentTransform, SComponentPointLight>();

		SPointLightData plData = {};
		plData.Position = SVector4(
				componentTransform->Translation,
				componentPointLight->Radius
		);
		plData.Color = componentPointLight->LightColor;

		m_Pipeline->PushSimpleData(frameInfo.CommandBuffer, 0, &plData);
		vkCmdDraw(CCast<VkCommandBuffer>(frameInfo.CommandBuffer), 6, 1, 0, 0);
	}

}

void
CPointLightBillboardSubPass::CreateSubPass(PSwapchain &swapchain, const PDescriptorSetLayout &setLayout) {
	SPipelineCreateInfo createInfo = {};
	createInfo.Name = "PLDefault";
	createInfo.bProvideBindings = createInfo.bProvideAttributes = false;
	m_Pipeline = CPipeline::CreateFor<SPointLightData>(m_Context, swapchain, setLayout, createInfo);
}

VISRCEND
