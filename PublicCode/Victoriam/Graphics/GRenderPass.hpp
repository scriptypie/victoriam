//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_GRENDERPASS_HPP
#define VICTORIAM_GRENDERPASS_HPP

#include <Victoriam/Graphics/Structs/GRenderPassCreateInfo.hpp>
#include <Victoriam/Graphics/GSwapchain.hpp>
#include <Victoriam/Graphics/Structs/GFrameInfo.hpp>

VISRCBEG

class VIDECL CRenderPass {
public:
	VIDECL virtual ~CRenderPass() = default;

	VIDECL virtual void Begin(const SFrameInfo& frameInfo) = 0;
	VIDECL virtual void End(const SFrameInfo& frameInfo) = 0;

	VIDECL VIREQOUT static SUnique<CRenderPass> Create(PGraphicsContext& context, PSwapchain& swapchain, const SRenderPassCreateInfo& createInfo);
};

VIDECL typedef SUnique<CRenderPass> PRenderPass;

VISRCEND

#endif //VICTORIAM_GRENDERPASS_HPP
