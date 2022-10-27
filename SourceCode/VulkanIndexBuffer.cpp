//
// Created by Вячеслав Кривенко on 27.10.2022.
//

#include "VulkanIndexBuffer.hpp"

VISRCBEG

CVulkanIndexBuffer::CVulkanIndexBuffer(PDevice &device, const List<UInt32> &indices) : m_Device(device)
{
	CreateIndexBuffer(indices);
}

CVulkanIndexBuffer::~CVulkanIndexBuffer()
{
	vkDestroyBuffer(Accessors::Device::GetDevice(m_Device), m_IndexBuffer, nullptr);
	vkFreeMemory(Accessors::Device::GetDevice(m_Device), m_IndexBufferMemory, nullptr);
}

void CVulkanIndexBuffer::Bind(SCommandBuffer const &buffer) {
	vkCmdBindIndexBuffer(CCast<VkCommandBuffer>(buffer), m_IndexBuffer, 0, VK_INDEX_TYPE_UINT32);
}

void CVulkanIndexBuffer::Draw(SCommandBuffer const &buffer) const {
	if (m_IndexBuffer)
		vkCmdDrawIndexed(CCast<VkCommandBuffer>(buffer), m_IndexCount, 1, 0, 0, 0);
}

void CVulkanIndexBuffer::CreateIndexBuffer(const List<UInt32> &indices) {
	m_IndexCount = indices.size();
	VkDeviceSize bufferSize = sizeof(UInt32) * m_IndexCount;

	if (!m_IndexCount) return;

	VkBuffer stagingBuffer = nullptr;
	VkDeviceMemory stagingBufferMemory = nullptr;
	Accessors::Device::CreateBuffer(m_Device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data = nullptr;
	vkMapMemory(Accessors::Device::GetDevice(m_Device), stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, indices.data(), CCast<size_t>(bufferSize));
	vkUnmapMemory(Accessors::Device::GetDevice(m_Device), stagingBufferMemory);

	Accessors::Device::CreateBuffer(m_Device, bufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_IndexBuffer, m_IndexBufferMemory);
	Accessors::Device::CopyBuffer(m_Device, stagingBuffer, m_IndexBuffer, bufferSize);

	vkDestroyBuffer(Accessors::Device::GetDevice(m_Device), stagingBuffer, nullptr);
	vkFreeMemory(Accessors::Device::GetDevice(m_Device), stagingBufferMemory, nullptr);
}

VISRCEND
