//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_DEFAULTRENDERSUBPASS_HPP
#define VICTORIAM_DEFAULTRENDERSUBPASS_HPP

#include <Victoriam/Graphics/GRenderSubPass.hpp>

VISRCBEG

class VIDECL CDefaultRenderSubPass : public CRenderSubPass
{
	PGraphicsContext& m_Context;
	PPipeline m_Pipeline = {};
public:
	VIDECL CDefaultRenderSubPass(PGraphicsContext& context, PSwapchain& swapchain, const PDescriptorSetLayout& setLayout);
	VIDECL ~CDefaultRenderSubPass() override = default;

	VIDECL void Pass(const SFrameInfo& frameInfo, const PWorld& world) override;

private:
	VIDECL void CreateSubPass(PSwapchain& swapchain, const PDescriptorSetLayout& setLayout);
};

VISRCEND

#endif //VICTORIAM_DEFAULTRENDERSUBPASS_HPP
