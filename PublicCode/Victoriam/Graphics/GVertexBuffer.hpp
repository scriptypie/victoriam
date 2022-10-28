//
// Created by Вячеслав Кривенко on 20.10.2022.
//

#ifndef VICTORIAM_GVERTEXBUFFER_HPP
#define VICTORIAM_GVERTEXBUFFER_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/Structs/GVertex.hpp>
#include <Victoriam/Graphics/GDevice.hpp>

VISRCBEG

class VIDECL CVertexBuffer
{
public:
	virtual ~CVertexBuffer() = default;

	virtual void Bind(const SCommandBuffer& buffer) = 0;
	virtual void Draw(const SCommandBuffer& buffer) const = 0;

	VIDECL VIREQOUT static SPtr<CVertexBuffer> Create(PDevice& device, const List<SVertex>& vertices);
};

VIDECL typedef SPtr<CVertexBuffer> PVertexBuffer;

VIDECL static PVertexBuffer DefaultVertexBuffer;

VISRCEND

#endif //VICTORIAM_GVERTEXBUFFER_HPP
