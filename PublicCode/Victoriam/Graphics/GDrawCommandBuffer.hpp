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

VISRCBEG

class cDrawCommandBuffer
{
public:
	virtual ~cDrawCommandBuffer() = default;

	VIDECL VIREQOUT static SPtr<cDrawCommandBuffer> Create(pSwapchain& swapchain, pDevice& device, pPipeline& pipeline, const List<pVertexBuffer>& vertexBuffers);
};

VIDECL typedef SPtr<cDrawCommandBuffer> pDrawCommandBuffer;

VISRCEND

#endif //VICTORIAM_GDRAWCOMMANDBUFFER_HPP
