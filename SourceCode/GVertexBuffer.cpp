//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#include <Victoriam/Graphics/GVertexBuffer.hpp>

#include "VulkanBackend/VulkanVertexBuffer.hpp"

VISRCBEG

PVertexBuffer CVertexBuffer::Create(PGraphicsContext &context, const CList<SVertex> &vertices) {
	return FCreateShared<CVulkanVertexBuffer>(context, vertices);
}

VISRCEND
