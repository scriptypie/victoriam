//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_GCOMMANDBUFFERDRAWER_HPP
#define VICTORIAM_GCOMMANDBUFFERDRAWER_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/GSwapchain.hpp>
#include <Victoriam/Graphics/GGraphicsContext.hpp>
#include <Victoriam/Graphics/GPipeline.hpp>
#include <Victoriam/Graphics/GBuffer.hpp>
#include <Victoriam/World/WWorld.hpp>
#include <Victoriam/Graphics/Structs/GFrameInfo.hpp>

VISRCBEG

class VIDECL CCommandBufferDrawer
{
public:
	VIDECL virtual ~CCommandBufferDrawer() = default;

	VIDECL VIREQOUT virtual SCommandBuffer Begin(const PWorld& world, const UInt32& imageIndex) = 0;
	VIDECL virtual void SubmitDraw(const PWorld& world, const SFrameInfo& frameInfo) const = 0;
	VIDECL virtual void End(const SCommandBuffer& commandBuffer) const = 0;

	VIDECL VIREQOUT static SPtr<CCommandBufferDrawer> Create(PSwapchain& swapchain, PGraphicsContext& context, PPipeline& pipeline);
};

VIDECL typedef SPtr<CCommandBufferDrawer> PCommandBufferDrawer;

VISRCEND

#endif //VICTORIAM_GCOMMANDBUFFERDRAWER_HPP
