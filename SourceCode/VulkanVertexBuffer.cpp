//
// Created by Вячеслав Кривенко on 20.10.2022.
//

#include "VulkanVertexBuffer.hpp"


VISRCBEG

CVulkanVertexBuffer::CVulkanVertexBuffer(PDevice &device, const List<SVertex> &vertices)
	: m_Device(device), m_Recreated(false)
{
	CreateVertexBuffer(vertices);
}

CVulkanVertexBuffer::~CVulkanVertexBuffer()
{
	vkDestroyBuffer(Accessors::Device::GetDevice(m_Device), m_VertexBuffer, nullptr);
	vkFreeMemory(Accessors::Device::GetDevice(m_Device), m_VertexBufferMemory, nullptr);
}

void CVulkanVertexBuffer::Bind(const SCommandBuffer& buffer) {
	VkBuffer buffers[] = { m_VertexBuffer };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(CCast<VkCommandBuffer>(buffer), 0, 1, buffers, offsets);
}

void CVulkanVertexBuffer::Draw(const SCommandBuffer& buffer) const {
	vkCmdDraw(CCast<VkCommandBuffer>(buffer), m_VertexCount, 1, 0, 0);
}

void CVulkanVertexBuffer::CreateVertexBuffer(const List<SVertex> &vertices) {
	m_VertexCount = vertices.size();
	assert(m_VertexCount >= 3 && "There MUST be at least 3 vertices!");

	VkDeviceSize bufferSize = sizeof(vertices.front()) * m_VertexCount;

	VkBuffer stagingBuffer = nullptr;
	VkDeviceMemory stagingBufferMemory = nullptr;
	Accessors::Device::CreateBuffer(m_Device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data = nullptr;
	vkMapMemory(Accessors::Device::GetDevice(m_Device), stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, vertices.data(), CCast<size_t>(bufferSize));
	vkUnmapMemory(Accessors::Device::GetDevice(m_Device), stagingBufferMemory);

	Accessors::Device::CreateBuffer(m_Device, bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_VertexBuffer, m_VertexBufferMemory);
	Accessors::Device::CopyBuffer(m_Device, stagingBuffer, m_VertexBuffer, bufferSize);

	vkDestroyBuffer(Accessors::Device::GetDevice(m_Device), stagingBuffer, nullptr);
	vkFreeMemory(Accessors::Device::GetDevice(m_Device), stagingBufferMemory, nullptr);

}

VISRCEND
