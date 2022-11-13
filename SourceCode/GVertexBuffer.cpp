//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#include <Victoriam/Graphics/GVertexBuffer.hpp>

#include "VulkanVertexBuffer.hpp"

VISRCBEG

PVertexBuffer CVertexBuffer::Create(PGraphicsContext &context, const CList<SVertex> &vertices) {
	return CreateSPtr<CVulkanVertexBuffer>(context, vertices);
}

VISRCEND
