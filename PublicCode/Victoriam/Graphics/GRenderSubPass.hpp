//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_GRENDERSUBPASS_HPP
#define VICTORIAM_GRENDERSUBPASS_HPP

#include <Victoriam/Graphics/GSwapchain.hpp>
#include <Victoriam/Graphics/GPipeline.hpp>
#include <Victoriam/Graphics/GGraphicsContext.hpp>
#include <Victoriam/Graphics/GDescriptorSetLayout.hpp>
#include <Victoriam/World/WWorld.hpp>

VISRCBEG

class VIDECL CRenderSubPass
{
public:
	VIDECL virtual ~CRenderSubPass() = default;
	VIDECL virtual void Pass(const SFrameInfo& frameInfo, const PWorld& world) = 0;

	VIDECL VIREQOUT static UPtr<CRenderSubPass> CreateDefaultSubPass(PGraphicsContext& context, PSwapchain& swapchain, const PDescriptorSetLayout& setLayout);
	VIDECL VIREQOUT static UPtr<CRenderSubPass> CreatePointLightBillboardSubPass(PGraphicsContext& context, PSwapchain& swapchain, const PDescriptorSetLayout& setLayout);
};

VIDECL typedef UPtr<CRenderSubPass> PRenderSubPass;

VISRCEND

#endif //VICTORIAM_GRENDERSUBPASS_HPP
