//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_GCOMMANDBUFFERDRAWER_HPP
#define VICTORIAM_GCOMMANDBUFFERDRAWER_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/GSwapchain.hpp>
#include <Victoriam/Graphics/GDevice.hpp>
#include <Victoriam/Graphics/GPipeline.hpp>
#include <Victoriam/Graphics/GBuffer.hpp>
#include <Victoriam/World/WWorld.hpp>

VISRCBEG

class CCommandBufferDrawer
{
public:
	virtual ~CCommandBufferDrawer() = default;

	virtual SCommandBuffer Begin(const PWorld& world, UInt32 imageIndex) = 0;
	virtual void End(UInt32 imageIndex) = 0;
	virtual void SubmitDraw(const PWorld& world, UInt32 imageIndex) = 0;

	VIDECL VIREQOUT static SPtr<CCommandBufferDrawer> Create(PSwapchain& swapchain, PDevice& device, PPipeline& pipeline);
};

VIDECL typedef SPtr<CCommandBufferDrawer> PDrawCommandBuffer;

VISRCEND

#endif //VICTORIAM_GCOMMANDBUFFERDRAWER_HPP
