//
// Created by Вячеслав Кривенко on 11.11.2022.
//

#include "PointLightBillboardSubPass.hpp"

#include <vulkan/vulkan.h>

VISRCBEG

CPointLightBillboardSubPass::CPointLightBillboardSubPass(PGraphicsContext &context, PSwapchain &swapchain,
                                                         const PDescriptorSetLayout &setLayout)
	: m_Context(context)
{
	CreateSubPass(swapchain, setLayout);
}

void CPointLightBillboardSubPass::Pass(const SFrameInfo &frameInfo, const PWorld &world) {
	m_Pipeline->BindCommandBuffer(frameInfo.CommandBuffer);
	m_Pipeline->BindConstantsDescriptorSet(BindPointGraphics, frameInfo);

	vkCmdDraw(CCast<VkCommandBuffer>(frameInfo.CommandBuffer), 6, 1, 0, 0);
}

void
CPointLightBillboardSubPass::CreateSubPass(PSwapchain &swapchain, const PDescriptorSetLayout &setLayout) {
	m_Pipeline = CPipeline::Create("PLBillboard", m_Context, swapchain, setLayout, false);
}

VISRCEND
