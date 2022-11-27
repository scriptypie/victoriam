//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#include "VulkanMemoryBuffer.hpp"

VISRCBEG

CVulkanMemoryBuffer::CVulkanMemoryBuffer(PGraphicsContext&              context,
										 const VkDeviceSize&            instanceSize,
                                         const UInt64&                  instanceCount,
										 const VkBufferUsageFlags&      usageFlags,
                                         const VkMemoryPropertyFlags&   memoryPropertyFlags,
                                         const VkDeviceSize&            minOffsetAlignment)
											 : m_Context(context), m_InstanceSize(instanceSize), m_InstanceCount(instanceCount),
											   m_UsageFlags(usageFlags), m_MemoryPropertyFlags(memoryPropertyFlags)
{
	m_AlignmentSize = GetAlignment(m_InstanceSize, minOffsetAlignment);
	m_BufferSize = m_AlignmentSize * m_InstanceCount;
	Accessors::GraphicsContext::CreateBuffer(m_Context, m_BufferSize, m_UsageFlags, m_MemoryPropertyFlags, m_Buffer, m_Memory);
}

CVulkanMemoryBuffer::~CVulkanMemoryBuffer() {
	Unmap();
	vkDestroyBuffer(Accessors::GraphicsContext::GetDevice(m_Context), m_Buffer, nullptr);
	m_Buffer = nullptr;
	vkFreeMemory(Accessors::GraphicsContext::GetDevice(m_Context), m_Memory, nullptr);
	m_Memory = nullptr;
}

VkResult CVulkanMemoryBuffer::Map(const VkDeviceSize &size, const VkDeviceSize &offset) {
	ViAssert(m_Buffer && m_Memory, "Called Map() on buffer before creating!\n");
	return vkMapMemory(Accessors::GraphicsContext::GetDevice(m_Context), m_Memory, offset, size, 0, &m_MappedMemory);
}

void CVulkanMemoryBuffer::Unmap() {
	if (m_MappedMemory)
	{
		vkUnmapMemory(Accessors::GraphicsContext::GetDevice(m_Context), m_Memory);
		m_MappedMemory = nullptr;
	}
}

void CVulkanMemoryBuffer::WriteToBuffer(void *data, const VkDeviceSize &size, const VkDeviceSize &offset) {
	ViAssert(m_MappedMemory, "Cannot write to unmapped buffer!\n");
	if (size == VK_WHOLE_SIZE)
		memcpy(m_MappedMemory, data, m_BufferSize);
	else
	{
		Int8* memoryOffset = CCast<Int8*>(m_MappedMemory);
		memoryOffset += offset;
		memcpy(memoryOffset, data, size);
	}
}

VkResult CVulkanMemoryBuffer::Flush(const VkDeviceSize &size, const VkDeviceSize &offset) {
	VkMappedMemoryRange mappedMemoryRange = { VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE };
	mappedMemoryRange.memory = m_Memory;
	mappedMemoryRange.size = size;
	mappedMemoryRange.offset = offset;
	return vkFlushMappedMemoryRanges(Accessors::GraphicsContext::GetDevice(m_Context), 1, &mappedMemoryRange);
}

VkDescriptorBufferInfo
CVulkanMemoryBuffer::GetDescriptorInfo(const VkDeviceSize &size, const VkDeviceSize &offset) {
	return VkDescriptorBufferInfo{ m_Buffer, offset, size };
}

VkResult CVulkanMemoryBuffer::Invalidate(const VkDeviceSize &size, const VkDeviceSize &offset) {
	VkMappedMemoryRange mappedMemoryRange = { VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE };
	mappedMemoryRange.memory = m_Memory;
	mappedMemoryRange.offset = offset;
	mappedMemoryRange.size = size;
	return vkInvalidateMappedMemoryRanges(Accessors::GraphicsContext::GetDevice(m_Context), 1, &mappedMemoryRange);
}

void CVulkanMemoryBuffer::WriteToIndex(void *data, const Int64 &index) {
	WriteToBuffer(data, m_InstanceSize, index * m_AlignmentSize);
}

VkResult CVulkanMemoryBuffer::FlushIndex(const Int64 &index) {
	return Flush(m_AlignmentSize, index * m_AlignmentSize);
}

VkDescriptorBufferInfo CVulkanMemoryBuffer::GetDescriptorInfoForIndex(const Int64 &index) {
	return GetDescriptorInfo(m_AlignmentSize, index * m_AlignmentSize);
}

VkResult CVulkanMemoryBuffer::InvalidateIndex(const Int64 &index) {
	return Invalidate(m_AlignmentSize, index * m_AlignmentSize);
}

VkDeviceSize
CVulkanMemoryBuffer::GetAlignment(const VkDeviceSize &instanceSize, const VkDeviceSize &minOffsetAlignment) {
	if (minOffsetAlignment > 0)
		return (instanceSize + minOffsetAlignment - 1) & ~(minOffsetAlignment - 1);
	return instanceSize;
}

PVulkanMemoryBuffer
CVulkanMemoryBuffer::Create(PGraphicsContext &context,
							const VkDeviceSize &instanceSize,
							const UInt64 &instanceCount,
                            const VkBufferUsageFlags &usageFlags,
							const VkMemoryPropertyFlags &memoryPropertyFlags,
                            const VkDeviceSize &minOffsetAlignment) {
	return FCreateUnique<CVulkanMemoryBuffer>(context, instanceSize, instanceCount, usageFlags, memoryPropertyFlags,
	                                          minOffsetAlignment);
}

VISRCEND
