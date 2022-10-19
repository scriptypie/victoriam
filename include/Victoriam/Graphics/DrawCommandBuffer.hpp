//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_DRAWCOMMANDBUFFER_HPP
#define VICTORIAM_DRAWCOMMANDBUFFER_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/Swapchain.hpp>
#include <Victoriam/Graphics/Device.hpp>
#include <Victoriam/Graphics/Pipeline.hpp>

VISRCBEG

class cDrawCommandBuffer
{
public:
	virtual ~cDrawCommandBuffer() = default;

	VIDECL VIREQOUT static SPtr<cDrawCommandBuffer> Create(pSwapchain& swapchain, pDevice& device, pPipeline& pipeline);
};

VIDECL typedef SPtr<cDrawCommandBuffer> pDrawCommandBuffer;

VISRCEND

#endif //VICTORIAM_DRAWCOMMANDBUFFER_HPP
