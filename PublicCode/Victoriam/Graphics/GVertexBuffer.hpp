//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_GVERTEXBUFFER_HPP
#define VICTORIAM_GVERTEXBUFFER_HPP

#include <Victoriam/Graphics/GBuffer.hpp>
#include <Victoriam/Graphics/Structs/GVertex.hpp>
#include <Victoriam/Graphics/GGraphicsContext.hpp>

VISRCBEG

class VIDECL CVertexBuffer : public CBuffer
{
public:
	VIDECL virtual ~CVertexBuffer() override = default;

	VIDECL VIREQOUT static SPtr<CVertexBuffer> Create(PGraphicsContext& context, const CList<SVertex>& vertices);
};

VIDECL typedef SPtr<CVertexBuffer> PVertexBuffer;

VIDECL static PVertexBuffer DefaultVertexBuffer;

VISRCEND

#endif //VICTORIAM_GVERTEXBUFFER_HPP
