//
// Created by Вячеслав Кривенко on 11.11.2022.
//

#ifndef VICTORIAM_POINTLIGHTBILLBOARDSUBPASS_HPP
#define VICTORIAM_POINTLIGHTBILLBOARDSUBPASS_HPP

#include <Victoriam/Graphics/GRenderSubPass.hpp>

VISRCBEG

class VIDECL CPointLightBillboardSubPass : public CRenderSubPass
{
	PGraphicsContext& m_Context;
	PPipeline m_Pipeline = {};
public:
	VIDECL CPointLightBillboardSubPass(PGraphicsContext& context, PSwapchain& swapchain, const PDescriptorSetLayout& setLayout);
	VIDECL ~CPointLightBillboardSubPass() override = default;

	VIDECL void Pass(const SFrameInfo& frameInfo, const PWorld& world) override;

private:
	VIDECL void CreateSubPass(PSwapchain& swapchain, const PDescriptorSetLayout& setLayout);
};

VISRCEND

#endif //VICTORIAM_POINTLIGHTBILLBOARDSUBPASS_HPP
