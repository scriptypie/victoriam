//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#ifndef VICTORIAM_GBUFFER_HPP
#define VICTORIAM_GBUFFER_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/Structs/GVertex.hpp>
#include <Victoriam/Graphics/Structs/GRendererConstants.hpp>
#include <Victoriam/Graphics/GGraphicsContext.hpp>
#include <Victoriam/Graphics/GSwapchain.hpp>

VISRCBEG

class VIDECL CBuffer
{
public:
	VIDECL virtual ~CBuffer() = default;

	VIDECL virtual void Bind(const SCommandBuffer& buffer) = 0;
	VIDECL virtual void Draw(const SCommandBuffer& buffer) const = 0;
	VIDECL virtual void SubmitUniformBuffer(const SRendererConstants& constants) = 0;

	VIDECL VIREQOUT static SPtr<CBuffer> CreateVertexBuffer(PGraphicsContext& context, const List<SVertex>& vertices);
	VIDECL VIREQOUT static SPtr<CBuffer> CreateIndexBuffer(PGraphicsContext& context, const List<UInt32>& indices);
	VIDECL VIREQOUT static UPtr<CBuffer> CreateUniformBuffer(PGraphicsContext& context, const UInt32& count);
};

VIDECL typedef SPtr<CBuffer> PBuffer;
VIDECL typedef UPtr<CBuffer> PUniformBuffer;

VIDECL static PBuffer DefaultVertexBuffer;
VIDECL static PBuffer DefaultIndexBuffer;

VISRCEND

#endif //VICTORIAM_GBUFFER_HPP
