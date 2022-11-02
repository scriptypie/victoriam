//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#ifndef VICTORIAM_GBUFFER_HPP
#define VICTORIAM_GBUFFER_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/Structs/GVertex.hpp>
#include <Victoriam/Graphics/Structs/GRendererConstants.hpp>
#include <Victoriam/Graphics/GDevice.hpp>
#include <Victoriam/Graphics/GSwapchain.hpp>

VISRCBEG

class VIDECL CBuffer
{
public:
	virtual void Bind(const SCommandBuffer& buffer) = 0;
	virtual void Draw(const SCommandBuffer& buffer) const = 0;
	virtual void SubmitUniformBuffer(const SRendererConstants* constants, const UInt32& imageIndex) = 0;

	VIDECL VIREQOUT static SPtr<CBuffer> CreateVertexBuffer(PDevice& device, const List<SVertex>& vertices);
	VIDECL VIREQOUT static SPtr<CBuffer> CreateIndexBuffer(PDevice& device, const List<UInt32>& indices);
	VIDECL VIREQOUT static SPtr<CBuffer> CreateUniformBuffer(PDevice& device, const PSwapchain& swaphain);
};

VIDECL typedef SPtr<CBuffer> PBuffer;

VIDECL static PBuffer DefaultVertexBuffer;
VIDECL static PBuffer DefaultIndexBuffer;

VISRCEND

#endif //VICTORIAM_GBUFFER_HPP
