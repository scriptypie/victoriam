//
// Created by Вячеслав Кривенко on 11.11.2022.
//

#include "PointLightSubrender.hpp"

#include <Victoriam/Graphics/Structs/GPointLightsData.hpp>

#include <vulkan/vulkan.h>

VISRCBEG

CPointLightSubrender::CPointLightSubrender(PGraphicsContext &context, PRenderPass& renderPass,
                                           const PDescriptorSetLayout &setLayout)
	: m_Context(context)
{
	CreateUniquePipeline(renderPass, setLayout);
}

void CPointLightSubrender::Compute(SFrameInfo &frameInfo, const PWorld &world) {

	auto plObjects = world->AllWith<SComponentTransform, SComponentPointLight>();
	auto camObject = world->OneWith<SComponentTransform, SComponentCamera>();
	auto [camTransform, camCamera] = camObject->Group<SComponentTransform, SComponentCamera>();

	CStream css;
	css << camTransform->Translation;
	ViLog("%s\n", css.Str().c_str());

	Int32 index = 0;
	auto& constants = frameInfo.Constants;

	for (auto plObj : plObjects)
	{
		auto [componentTransform, componentPointLight] = plObj->Group<SComponentTransform, SComponentPointLight>();
		auto& pointLight = constants.PointLights[index];
		Float32 distance = FDistance(camTransform->Translation, componentTransform->Translation);
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

void CPointLightSubrender::Pass(SFrameInfo &frameInfo, const PWorld &world) {
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
CPointLightSubrender::CreateUniquePipeline(PRenderPass& renderPass, const PDescriptorSetLayout &setLayout) {
	SPipelineCreateInfo createInfo = {};
	createInfo.Name = "PLDefault";
	createInfo.bProvideBindings = createInfo.bProvideAttributes = false;
	m_Pipeline = CPipeline::CreateFor<SPointLightData>(m_Context, renderPass, setLayout, createInfo);
}

VISRCEND
