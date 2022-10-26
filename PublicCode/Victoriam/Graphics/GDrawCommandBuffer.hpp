//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_GDRAWCOMMANDBUFFER_HPP
#define VICTORIAM_GDRAWCOMMANDBUFFER_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/GSwapchain.hpp>
#include <Victoriam/Graphics/GDevice.hpp>
#include <Victoriam/Graphics/GPipeline.hpp>
#include <Victoriam/Graphics/GVertexBuffer.hpp>
#include <Victoriam/World/WWorld.hpp>

VISRCBEG

class CDrawCommandBuffer
{
public:
	virtual ~CDrawCommandBuffer() = default;

	virtual SCommandBuffer Begin(UInt32 imageIndex) = 0;
	virtual void End(UInt32 imageIndex) = 0;
	virtual void SubmitDraw(const PWorld& world, UInt32 imageIndex) = 0;

	VIDECL VIREQOUT static SPtr<CDrawCommandBuffer> Create(PSwapchain& swapchain, PDevice& device, PPipeline& pipeline);
};

VIDECL typedef SPtr<CDrawCommandBuffer> PDrawCommandBuffer;

VISRCEND

#endif //VICTORIAM_GDRAWCOMMANDBUFFER_HPP
