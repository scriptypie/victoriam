//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_GRENDERPASS_HPP
#define VICTORIAM_GRENDERPASS_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/Structs/GRenderPassCreateInfo.hpp>
#include <Victoriam/Graphics/Structs/GFrameInfo.hpp>

VISRCBEG

class VIDECL CRenderPass {
public:
	VIDECL virtual ~CRenderPass() = default;

	VIDECL virtual void Begin(const SFrameInfo& frameInfo) = 0;
	VIDECL virtual void End(const SFrameInfo& frameInfo) = 0;

	VIDECL VIREQOUT static PRenderPass Create(PGraphicsContext& context, PSwapchain& swapchain, const SRenderPassCreateInfo& createInfo);
};

VISRCEND

#endif //VICTORIAM_GRENDERPASS_HPP
