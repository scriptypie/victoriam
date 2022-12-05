//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_DEFAULTRENDERSUBRENDER_HPP
#define VICTORIAM_DEFAULTRENDERSUBRENDER_HPP

#include <Victoriam/Graphics/GPipeline.hpp>
#include <Victoriam/Graphics/GFramebuffer.hpp>

#include <Victoriam/Graphics/GRenderSubrender.hpp>

VISRCBEG

class VIDECL CDefaultRenderSubrender : public CRenderSubrender
{
	PGraphicsContext& m_Context;
	PPipeline m_Pipeline = {};
public:
	VIDECL CDefaultRenderSubrender(PGraphicsContext& context, PRenderPass& renderPass, const PDescriptorSetLayout& setLayout);
	VIDECL ~CDefaultRenderSubrender() override = default;

	VIDECL void Compute(SFrameInfo& frameInfo, const PWorld& world) override;
	VIDECL void Pass(SFrameInfo& frameInfo, const PWorld& world) override;

private:
	VIDECL void CreateUniquePipeline(PRenderPass& renderPass, const PDescriptorSetLayout& setLayout);
};

VISRCEND

#endif //VICTORIAM_DEFAULTRENDERSUBRENDER_HPP
