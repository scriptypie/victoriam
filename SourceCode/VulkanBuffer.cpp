//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#include "VulkanBuffer.hpp"

VISRCBEG

CVulkanBuffer::CVulkanBuffer(PGraphicsContext &context, const List<SVertex> &vertices) : m_Context(context), m_Type(ECType::VertexBuffer)
{
	CreateVertexBuffer(vertices);
}

CVulkanBuffer::CVulkanBuffer(PGraphicsContext &context, const List<UInt32> &indices) : m_Context(context), m_Type(ECType::IndexBuffer)
{
	CreateIndexBuffer(indices);
}

void CVulkanBuffer::Bind(SCommandBuffer const &buffer) {
	switch (m_Type)
	{
		case ECType::VertexBuffer:
		{
			VkBuffer buffers[] = { m_MemoryBuffer->GetBuffer() };
			VkDeviceSize offsets[] = { 0 };
			vkCmdBindVertexBuffers(CCast<VkCommandBuffer>(buffer), 0, 1, buffers, offsets);
			return;
		}
		case ECType::IndexBuffer:
		{
			vkCmdBindIndexBuffer(CCast<VkCommandBuffer>(buffer), m_MemoryBuffer->GetBuffer(), 0, VK_INDEX_TYPE_UINT32);
			return;
		}
		case ECType::UniformBuffer:
		{
			m_MemoryBuffer->Map();
			return;
		}
		default:
		{
			ViAbort("Buffer type not implemented!!!");
		}
	}
}

void CVulkanBuffer::Draw(SCommandBuffer const &buffer) const {
	switch (m_Type)
	{
		case ECType::VertexBuffer:
		{
			vkCmdDraw(CCast<VkCommandBuffer>(buffer), m_Count, 1, 0, 0);
			return;
		}
		case ECType::IndexBuffer:
		{
			vkCmdDrawIndexed(CCast<VkCommandBuffer>(buffer), m_Count, 1, 0, 0, 0);
			return;
		}
		default:
		{
			ViAbort("Buffer type not implemented!!!");
		}
	}
}

void CVulkanBuffer::CreateVertexBuffer(const List<SVertex> &vertices) {
	m_Count = vertices.size();
	ViAssert(m_Count >= 3, "There MUST be at least 3 vertices!");

	PVulkanMemoryBuffer stagingBuffer = CVulkanMemoryBuffer::Create(
			m_Context,
			sizeof(vertices[0]),
			m_Count,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	stagingBuffer->Map();
	stagingBuffer->WriteToBuffer(vertices.data());

	m_MemoryBuffer = CVulkanMemoryBuffer::Create(
			m_Context,
			sizeof(vertices[0]),
			m_Count,
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	Accessors::GraphicsContext::CopyBuffer(m_Context, stagingBuffer->GetBuffer(), m_MemoryBuffer->GetBuffer(), sizeof(vertices[0]) * m_Count);
}

void CVulkanBuffer::CreateIndexBuffer(const List<UInt32> &indices) {
	m_Count = indices.size();
	if (!m_Count) return;

	PVulkanMemoryBuffer stagingBuffer = CVulkanMemoryBuffer::Create(
			m_Context,
			sizeof(indices[0]),
			m_Count,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	stagingBuffer->Map();
	stagingBuffer->WriteToBuffer(indices.data());
	m_MemoryBuffer = CVulkanMemoryBuffer::Create(
			m_Context,
			sizeof(indices[0]),
			m_Count,
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	Accessors::GraphicsContext::CopyBuffer(m_Context, stagingBuffer->GetBuffer(), m_MemoryBuffer->GetBuffer(), sizeof(UInt32) * m_Count);
}

CVulkanBuffer::CVulkanBuffer(PGraphicsContext &device, const UInt32& maxFramesInFlight) : m_Context(device), m_Type(ECType::UniformBuffer)
{
	CreateUniformBuffer(maxFramesInFlight);
}

void CVulkanBuffer::CreateUniformBuffer(const UInt32 &maxFramesInFlight) {
	m_MemoryBuffer = CVulkanMemoryBuffer::Create(
			m_Context, sizeof(SRendererConstants),
			maxFramesInFlight,
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT/* | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT*/);
}

void CVulkanBuffer::SubmitUniformBuffer(const SRendererConstants &constants)
{
	m_MemoryBuffer->WriteToBuffer(&constants);
	m_MemoryBuffer->Flush();
}

VISRCEND
