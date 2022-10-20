//
// Created by Вячеслав Кривенко on 20.10.2022.
//

#ifndef VICTORIAM_GVERTEXBUFFER_HPP
#define VICTORIAM_GVERTEXBUFFER_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/Structs/GVertex.hpp>
#include <Victoriam/Graphics/GDevice.hpp>

VISRCBEG

class VIDECL cVertexBuffer
{
public:
	virtual ~cVertexBuffer() = default;

	virtual void Bind(const sCommandBuffer& buffer) = 0;
	virtual void Draw(const sCommandBuffer& buffer) const = 0;

	VIDECL VIREQOUT static SPtr<cVertexBuffer> Create(pDevice& device, const List<sVertex>& vertices);
};

VIDECL typedef SPtr<cVertexBuffer> pVertexBuffer;

VISRCEND

#endif //VICTORIAM_GVERTEXBUFFER_HPP
