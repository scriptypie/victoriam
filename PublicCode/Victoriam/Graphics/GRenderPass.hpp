//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_GRENDERPASS_HPP
#define VICTORIAM_GRENDERPASS_HPP

#include <Victoriam/Graphics/Structs/GRenderPassCreateInfo.hpp>
#include <Victoriam/Graphics/GSwapchain.hpp>

VISRCBEG

class VIDECL CRenderPass {
public:
	VIDECL virtual ~CRenderPass() = default;

	VIDECL virtual void Begin(const SCommandBuffer& commandBuffer) = 0;
	VIDECL virtual void End(const SCommandBuffer& commandBuffer) = 0;

	VIDECL VIREQOUT static UPtr<CRenderPass> Create(PGraphicsContext& context, PSwapchain& swapchain, const SRenderPassCreateInfo& createInfo);
};

VIDECL typedef UPtr<CRenderPass> PRenderPass;

VISRCEND

#endif //VICTORIAM_GRENDERPASS_HPP
