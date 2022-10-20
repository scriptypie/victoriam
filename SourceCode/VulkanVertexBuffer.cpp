//
// Created by Вячеслав Кривенко on 20.10.2022.
//

#include "VulkanVertexBuffer.hpp"


VISRCBEG

cVulkanVertexBuffer::cVulkanVertexBuffer(pDevice &device, const List<sVertex> &vertices)
	: m_Device(device)
{
	CreateVertexBuffer(vertices);
}

cVulkanVertexBuffer::~cVulkanVertexBuffer()
{
	vkDestroyBuffer(Accessors::Device::GetDevice(m_Device), m_VertexBuffer, nullptr);
	vkFreeMemory(Accessors::Device::GetDevice(m_Device), m_VertexBufferMemory, nullptr);
}

void cVulkanVertexBuffer::Bind(const sCommandBuffer& buffer) {
	VkBuffer buffers[] = { m_VertexBuffer };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(CCast<VkCommandBuffer>(buffer), 0, 1, buffers, offsets);
}

void cVulkanVertexBuffer::Draw(const sCommandBuffer& buffer) const {
	vkCmdDraw(CCast<VkCommandBuffer>(buffer), m_VertexCount, 1, 0, 0);
}

void cVulkanVertexBuffer::CreateVertexBuffer(const List<sVertex> &vertices) {
	m_VertexCount = vertices.size();
	assert(m_VertexCount >= 3 && "There MUST be at least 3 vertices!");

	VkDeviceSize bufferSize = sizeof(vertices.front()) * m_VertexCount;
	Accessors::Device::CreateBuffer(m_Device, bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_VertexBuffer, m_VertexBufferMemory);

	void* data = nullptr;
	vkMapMemory(Accessors::Device::GetDevice(m_Device), m_VertexBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, vertices.data(), CCast<size_t>(bufferSize));
	vkUnmapMemory(Accessors::Device::GetDevice(m_Device), m_VertexBufferMemory);
}

VISRCEND
