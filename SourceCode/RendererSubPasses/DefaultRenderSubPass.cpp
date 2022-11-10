//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#include "DefaultRenderSubPass.hpp"

VISRCBEG

CDefaultRenderSubPass::CDefaultRenderSubPass(PGraphicsContext &context, PSwapchain &swapchain, const PDescriptorSetLayout &setLayout)
	: m_Context(context)
{
	CreateSubPass(swapchain, setLayout);
}

void CDefaultRenderSubPass::Pass(const SFrameInfo &frameInfo, const PWorld &world)
{
	m_Pipeline->BindCommandBuffer(frameInfo.CommandBuffer);
	m_Pipeline->BindConstantsDescriptorSet(BindPointGraphics, frameInfo);

	auto renderable_objs = world->AllWith<SComponentRenderable, SComponentTransform>(); // all renderables MUST have a transform component!!!
	for (auto renderable_obj: renderable_objs) {
		auto [rrc, rtc] = renderable_obj->Group<SComponentRenderable, SComponentTransform>();

		if (!rrc->Geometry.Empty()) {
			SMaterialData materialData = {};
			materialData.ModelMatrix = rtc->Transform();
			m_Pipeline->PushMaterialData(CCast<SCommandBuffer>(frameInfo.CommandBuffer), 0, &materialData);
			rrc->Geometry.SubmitDraw(CCast<SCommandBuffer>(frameInfo.CommandBuffer));
		}
	}
}

void CDefaultRenderSubPass::CreateSubPass(PSwapchain &swapchain, const PDescriptorSetLayout &setLayout) {
	m_Pipeline = CPipeline::Create("Default", m_Context, swapchain, setLayout);
}

VISRCEND
