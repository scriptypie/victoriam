//
// Created by Вячеслав Кривенко on 27.10.2022.
//

#ifndef VICTORIAM_GINDEXBUFFER_HPP
#define VICTORIAM_GINDEXBUFFER_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/GDevice.hpp>

VISRCBEG

class CIndexBuffer
{
public:
	virtual ~CIndexBuffer() = default;

	virtual void Bind(const SCommandBuffer& buffer) = 0;
	virtual void Draw(const SCommandBuffer& buffer) const = 0;
	virtual void Recreated() = 0;

	static SPtr<CIndexBuffer> Create(PDevice& device, const List<UInt32>& indices);
};

VIDECL typedef SPtr<CIndexBuffer> PIndexBuffer;

VIDECL static PIndexBuffer DefaultIndexBuffer;

VISRCEND

#endif //VICTORIAM_GINDEXBUFFER_HPP
