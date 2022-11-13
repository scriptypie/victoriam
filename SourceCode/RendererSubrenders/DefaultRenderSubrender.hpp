//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_DEFAULTRENDERSUBRENDER_HPP
#define VICTORIAM_DEFAULTRENDERSUBRENDER_HPP

#include <Victoriam/Graphics/GRenderSubrender.hpp>

VISRCBEG

class VIDECL CDefaultRenderSubrender : public CRenderSubrender
{
	PGraphicsContext& m_Context;
	PPipeline m_Pipeline = {};
public:
	VIDECL CDefaultRenderSubrender(PGraphicsContext& context, PSwapchain& swapchain, const PDescriptorSetLayout& setLayout);
	VIDECL ~CDefaultRenderSubrender() override = default;

	VIDECL void Compute(SFrameInfo& frameInfo, const PWorld& world) override;
	VIDECL void Pass(const SFrameInfo& frameInfo, const PWorld& world) override;

private:
	VIDECL void CreateUniquePipeline(PSwapchain& swapchain, const PDescriptorSetLayout& setLayout);
};

VISRCEND

#endif //VICTORIAM_DEFAULTRENDERSUBRENDER_HPP
