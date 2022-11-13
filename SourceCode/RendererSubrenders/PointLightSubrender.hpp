//
// Created by Вячеслав Кривенко on 11.11.2022.
//

#ifndef VICTORIAM_POINTLIGHTSUBRENDER_HPP
#define VICTORIAM_POINTLIGHTSUBRENDER_HPP

#include <Victoriam/Graphics/GRenderSubrender.hpp>

VISRCBEG

class VIDECL CPointLightSubrender : public CRenderSubrender
{
	PGraphicsContext& m_Context;
	PPipeline m_Pipeline = {};
public:
	VIDECL CPointLightSubrender(PGraphicsContext& context, PSwapchain& swapchain, const PDescriptorSetLayout& setLayout);
	VIDECL ~CPointLightSubrender() override = default;

	VIDECL void Compute(SFrameInfo& frameInfo, const PWorld& world) override;
	VIDECL void Pass(const SFrameInfo& frameInfo, const PWorld& world) override;

private:
	VIDECL void CreateUniquePipeline(PSwapchain& swapchain, const PDescriptorSetLayout& setLayout);
};

VISRCEND

#endif //VICTORIAM_POINTLIGHTSUBRENDER_HPP