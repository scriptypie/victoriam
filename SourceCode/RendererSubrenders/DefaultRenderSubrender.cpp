//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#include "DefaultRenderSubrender.hpp"

VISRCBEG

CDefaultRenderSubrender::CDefaultRenderSubrender(PGraphicsContext &context, PRenderPass& renderPass, const PDescriptorSetLayout &setLayout)
	: m_Context(context)
{
	CreateUniquePipeline(renderPass, setLayout);
}



void CDefaultRenderSubrender::Compute(SFrameInfo &frameInfo, const PWorld &world) {

	auto sunobj = world->OneWith<SComponentSun>(); // There CAN be single one on a scene
	auto rendererSettings = world->GetRendererSettings(); // as well as renderer settings

	CCamera* mainCamera = nullptr;
	{
		auto cam_obj = world->OneWith<SComponentCamera, SComponentTransform>();
		auto [componentCamera, componentTransform] = cam_obj->Group<SComponentCamera, SComponentTransform>();
		if (componentCamera->Primary) {
			componentCamera->Camera.SetPerspective(frameInfo.AspectRatio);
			componentCamera->Camera.SetViewMatrix(FLookAt(componentTransform->Translation,
			                                                  componentTransform->Translation +
			                                                  componentCamera->Camera.Front(),
			                                                  componentCamera->Camera.Up()));
			mainCamera = &componentCamera->Camera;
		}
	}

	// submit constants buffer
	auto& constants = frameInfo.Constants;
	constants.SunDirection = sunobj ? SVector4(-sunobj->GetComponent<SComponentSun>()->Direction, 1.0F) : SVector4();
	constants.Ambient = rendererSettings.Ambient;
	constants.Brightness = rendererSettings.Brightness;
	constants.Projection = mainCamera->GetProjection();
	constants.View = mainCamera->GetView();

}


void CDefaultRenderSubrender::Pass(const SFrameInfo &frameInfo, const PWorld &world)
{
	m_Pipeline->BindCommandBuffer(frameInfo.CommandBuffer);
	m_Pipeline->BindConstantsDescriptorSet(BindPointGraphics, frameInfo);

	auto renderable_objs = world->AllWith<SComponentRenderable, SComponentTransform>(); // all renderables MUST have a transform component!!!
	for (auto renderable_obj: renderable_objs) {
		auto [rrc, rtc] = renderable_obj->Group<SComponentRenderable, SComponentTransform>();

		if (!rrc->Geometry.Empty()) {
			SMaterialData materialData = {};
			materialData.ModelMatrix = rtc->Transform();
			m_Pipeline->PushSimpleData(frameInfo.CommandBuffer, 0, &materialData);
			rrc->Geometry.SubmitDraw(frameInfo.CommandBuffer);
		}
	}
}

void CDefaultRenderSubrender::CreateUniquePipeline(PRenderPass& renderPass, const PDescriptorSetLayout &setLayout) {
	SPipelineCreateInfo createInfo = {};
	createInfo.Name = "Default";
	m_Pipeline = CPipeline::CreateFor<SMaterialData>(m_Context, renderPass, setLayout, createInfo);
}

VISRCEND
