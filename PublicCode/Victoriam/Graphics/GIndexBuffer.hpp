//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_GINDEXBUFFER_HPP
#define VICTORIAM_GINDEXBUFFER_HPP

#include <Victoriam/Graphics/GBuffer.hpp>

VISRCBEG

class VIDECL CIndexBuffer : public CBuffer
{
public:
	VIDECL ~CIndexBuffer() override = default;

	VIDECL VIREQOUT static PIndexBuffer Create(PGraphicsContext& context, const CSet<UInt32>& indices);
};

VIDECL static PIndexBuffer DefaultIndexBuffer;

VISRCEND

#endif //VICTORIAM_GINDEXBUFFER_HPP
