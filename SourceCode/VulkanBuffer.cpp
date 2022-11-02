//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#include "VulkanBuffer.hpp"

VISRCBEG

CVulkanBuffer::CVulkanBuffer(PDevice &device, const List<SVertex> &vertices) : m_Device(device), m_Type(ECType::VertexBuffer)
{
	CreateVertexBuffer(vertices);
}

CVulkanBuffer::CVulkanBuffer(PDevice &device, const List<UInt32> &indices) : m_Device(device), m_Type(ECType::IndexBuffer)
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
	VkDeviceSize bufferSize = sizeof(vertices.front()) * m_Count;
	UInt32 vertexSize = sizeof(vertices[0]);
	PVulkanMemoryBuffer stagingBuffer = CVulkanMemoryBuffer::Create(m_Device, vertexSize, m_Count, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	stagingBuffer->Map();
	stagingBuffer->WriteToBuffer(vertices.data());
	m_MemoryBuffer = CVulkanMemoryBuffer::Create(m_Device, vertexSize, m_Count, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	Accessors::Device::CopyBuffer(m_Device, stagingBuffer->GetBuffer(), m_MemoryBuffer->GetBuffer(), bufferSize);
}

void CVulkanBuffer::CreateIndexBuffer(const List<UInt32> &indices) {
	m_Count = indices.size();
	if (!m_Count) return;

	VkDeviceSize bufferSize = sizeof(UInt32) * m_Count;
	UInt32 indexSize = sizeof(indices[0]);
	PVulkanMemoryBuffer stagingBuffer = CVulkanMemoryBuffer::Create(m_Device, indexSize, m_Count, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	stagingBuffer->Map();
	stagingBuffer->WriteToBuffer(indices.data());
	m_MemoryBuffer = CVulkanMemoryBuffer::Create(m_Device, indexSize, m_Count, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	Accessors::Device::CopyBuffer(m_Device, stagingBuffer->GetBuffer(), m_MemoryBuffer->GetBuffer(), bufferSize);
}

CVulkanBuffer::CVulkanBuffer(PDevice &device, const UInt32& maxFramesInFlight) : m_Device(device), m_Type(ECType::UniformBuffer)
{
	CreateUniformBuffer(maxFramesInFlight);
}

void CVulkanBuffer::CreateUniformBuffer(const UInt32 &maxFramesInFlight) {
	auto properties = Accessors::Device::GetPhysicalDeviceProperties(m_Device);
	const VkDeviceSize minOffsetAlignment = std::lcm(properties.limits.minUniformBufferOffsetAlignment, properties.limits.nonCoherentAtomSize);
	m_MemoryBuffer = CVulkanMemoryBuffer::Create(m_Device, sizeof(SRendererConstants), maxFramesInFlight, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, minOffsetAlignment);
	m_MemoryBuffer->Map();
}

void CVulkanBuffer::SubmitUniformBuffer(const SRendererConstants *constants, const UInt32 &imageIndex)
{
	m_MemoryBuffer->WriteToIndex(&constants, imageIndex);
	m_MemoryBuffer->FlushIndex(imageIndex);
}

VISRCEND
