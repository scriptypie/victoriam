//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#include <Victoriam/Graphics/GBuffer.hpp>

#include "VulkanBuffer.hpp"

VISRCBEG

PBuffer CBuffer::CreateVertexBuffer(PGraphicsContext &context, const List<SVertex> &vertices) {
	return CreateSPtr<CVulkanBuffer>(context, vertices);
}

PBuffer CBuffer::CreateIndexBuffer(PGraphicsContext &context, const List<UInt32> &indices) {
	return CreateSPtr<CVulkanBuffer>(context, indices);
}

PUniformBuffer CBuffer::CreateUniformBuffer(PGraphicsContext& context, const UInt32& count) {
	return CreateUPtr<CVulkanBuffer>(context, count);
}

VISRCEND
