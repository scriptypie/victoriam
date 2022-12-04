//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#include "VulkanVertexBuffer.hpp"

VISRCBEG

CVulkanVertexBuffer::CVulkanVertexBuffer(PGraphicsContext &context, const CSet<SVertex> &vertices) : m_Context(context)
{
	CreateVertexBuffer(vertices);
}

void CVulkanVertexBuffer::Bind(SCommandBuffer const &buffer) {
	VkBuffer buffers[] = { m_MemoryBuffer->GetBuffer() };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(CCast<VkCommandBuffer>(buffer), 0, 1, buffers, offsets);
}

void CVulkanVertexBuffer::Draw(SCommandBuffer const &buffer) const {
	vkCmdDraw(CCast<VkCommandBuffer>(buffer), m_VertexCount, 1, 0, 0);
}

void CVulkanVertexBuffer::CreateVertexBuffer(const CSet<SVertex> &vertices) {
	m_VertexCount = vertices.Size();
	ViAssert(m_VertexCount >= 3, "There MUST be at least 3 vertices!");

	PVulkanMemoryBuffer stagingBuffer = CVulkanMemoryBuffer::Create(
			m_Context,
			sizeof(vertices[0]),
			m_VertexCount,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	stagingBuffer->Map();
	stagingBuffer->WriteToBuffer(vertices.Data());

	m_MemoryBuffer = CVulkanMemoryBuffer::Create(
			m_Context,
			sizeof(vertices[0]),
			m_VertexCount,
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	Accessors::GraphicsContext::CopyBuffer(m_Context, stagingBuffer->GetBuffer(), m_MemoryBuffer->GetBuffer(), sizeof(vertices[0]) * m_VertexCount);
}

VISRCEND
