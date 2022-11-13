//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_GINDEXBUFFER_HPP
#define VICTORIAM_GINDEXBUFFER_HPP

#include <Victoriam/Graphics/GBuffer.hpp>
#include <Victoriam/Graphics/GGraphicsContext.hpp>

VISRCBEG

class VIDECL CIndexBuffer : public CBuffer
{
public:
	VIDECL ~CIndexBuffer() override = default;

	VIDECL VIREQOUT static SPtr<CIndexBuffer> Create(PGraphicsContext& context, const CList<UInt32>& indices);
};

VIDECL typedef SPtr<CIndexBuffer> PIndexBuffer;

VIDECL static PIndexBuffer DefaultIndexBuffer;

VISRCEND

#endif //VICTORIAM_GINDEXBUFFER_HPP
