//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#include "VulkanIndexBuffer.hpp"

VISRCBEG

CVulkanIndexBuffer::CVulkanIndexBuffer(PGraphicsContext &context, const CSet<UInt32> &indices)
	: m_Context(context)
{
	CreateIndexBuffer(indices);
}

void CVulkanIndexBuffer::Bind(SCommandBuffer const &buffer) {
	vkCmdBindIndexBuffer(CCast<VkCommandBuffer>(buffer), m_MemoryBuffer->GetBuffer(), 0, VK_INDEX_TYPE_UINT32);
}

void CVulkanIndexBuffer::Draw(SCommandBuffer const &buffer) const {
	vkCmdDrawIndexed(CCast<VkCommandBuffer>(buffer), m_IndexCount, 1, 0, 0, 0);
}

void CVulkanIndexBuffer::CreateIndexBuffer(const CSet<UInt32> &indices) {
	m_IndexCount = indices.Size();
	if (!m_IndexCount) return;

	PVulkanMemoryBuffer stagingBuffer = CVulkanMemoryBuffer::Create(
			m_Context,
			sizeof(indices[0]),
			m_IndexCount,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	stagingBuffer->Map();
	stagingBuffer->WriteToBuffer(indices.Data());
	m_MemoryBuffer = CVulkanMemoryBuffer::Create(
			m_Context,
			sizeof(indices[0]),
			m_IndexCount,
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	Accessors::GraphicsContext::CopyBuffer(m_Context, stagingBuffer->GetBuffer(), m_MemoryBuffer->GetBuffer(), sizeof(UInt32) * m_IndexCount);
}

VISRCEND
