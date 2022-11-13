//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_GRENDERSUBRENDER_HPP
#define VICTORIAM_GRENDERSUBRENDER_HPP

#include <Victoriam/Graphics/GSwapchain.hpp>
#include <Victoriam/Graphics/GPipeline.hpp>
#include <Victoriam/Graphics/GGraphicsContext.hpp>
#include <Victoriam/Graphics/GDescriptorSetLayout.hpp>
#include <Victoriam/World/WWorld.hpp>

VISRCBEG

class VIDECL CRenderSubrender
{
public:
	VIDECL virtual ~CRenderSubrender() = default;

	VIDECL virtual void Compute(SFrameInfo& frameInfo, const PWorld& world) {}
	VIDECL virtual void Pass(const SFrameInfo& frameInfo, const PWorld& world) = 0;

	VIDECL VIREQOUT static UPtr<CRenderSubrender> CreateDefaultSubrender(PGraphicsContext& context, PSwapchain& swapchain, const PDescriptorSetLayout& setLayout);
	VIDECL VIREQOUT static UPtr<CRenderSubrender> CreatePointLightSubrender(PGraphicsContext& context, PSwapchain& swapchain, const PDescriptorSetLayout& setLayout);
};

VIDECL typedef UPtr<CRenderSubrender> PRenderSubrender;

VISRCEND

#endif //VICTORIAM_GRENDERSUBRENDER_HPP
