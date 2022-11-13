//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#ifndef VICTORIAM_VULKANMEMORYBUFFER_HPP
#define VICTORIAM_VULKANMEMORYBUFFER_HPP

#include "Victoriam/Graphics/Basics.hpp"
#include "../Accessors/AGraphicsContext.hpp"

VISRCBEG

class VIDECL CVulkanMemoryBuffer {
	VIDECL PGraphicsContext& m_Context;
	VIDECL VkBuffer m_Buffer = nullptr;
	VIDECL VkDeviceMemory m_Memory = nullptr;
	VIDECL void* m_MappedMemory = nullptr;
	VIDECL VkDeviceSize m_BufferSize = {};
	VIDECL UInt64 m_InstanceCount = {};
	VIDECL VkDeviceSize m_InstanceSize = {};
	VIDECL VkDeviceSize m_AlignmentSize = {};
	VIDECL VkBufferUsageFlags m_UsageFlags = {};
	VIDECL VkMemoryPropertyFlags m_MemoryPropertyFlags = {};
public:

	VIDECL CVulkanMemoryBuffer(PGraphicsContext& device, const VkDeviceSize& instanceSize, const UInt64& instanceCount, const VkBufferUsageFlags& usageFlags, const VkMemoryPropertyFlags& memoryPropertyFlags, const VkDeviceSize& minOffsetAlignment);
	VIDECL virtual ~CVulkanMemoryBuffer();

	VIDECL CVulkanMemoryBuffer(const CVulkanMemoryBuffer&) = delete;
	VIDECL CVulkanMemoryBuffer& operator=(const CVulkanMemoryBuffer&) = delete;

	VIDECL VkResult Map(const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {});
	VIDECL void Unmap();

	VIDECL void WriteToBuffer(void* data, const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {});
	template<class T>
	VIDECL void WriteToBuffer(T* data, const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {})
	{
		WriteToBuffer(CCast<void*>(data), size, offset);
	}
	VIDECL          VkResult Flush(const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {});
	VIDECL VIREQOUT VkDescriptorBufferInfo GetDescriptorInfo(const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {});
	VIDECL          VkResult Invalidate(const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {});

	VIDECL          void WriteToIndex(void* data, const Int64& index);
	VIDECL          VkResult FlushIndex(const Int64& index);
	VIDECL VIREQOUT VkDescriptorBufferInfo GetDescriptorInfoForIndex(const Int64& index);
	VIDECL          VkResult InvalidateIndex(const Int64& index);

	VIDECL VIREQOUT inline VkBuffer GetBuffer() { return m_Buffer; }
	VIDECL VIREQOUT inline void* GetMappedMemory() { return m_MappedMemory; }
	VIDECL VIREQOUT inline VkDeviceSize GetBufferSize() const { return m_BufferSize; }
	VIDECL VIREQOUT inline UInt64 GetInstanceCount() const { return m_InstanceCount; }
	VIDECL VIREQOUT inline VkDeviceSize GetInstanceSize() const { return m_InstanceSize; }
	VIDECL VIREQOUT inline VkDeviceSize GetAlignmentSize() const { return m_AlignmentSize; }
	VIDECL VIREQOUT inline VkBufferUsageFlags GetBufferUsageFlags() const { return m_UsageFlags; }
	VIDECL VIREQOUT inline VkMemoryPropertyFlags GetMemoryPropertyFlags() const { return m_MemoryPropertyFlags; }

	VIDECL static UPtr<CVulkanMemoryBuffer> Create(PGraphicsContext&            context,
												   const VkDeviceSize&          instanceSize,
												   const UInt64&                instanceCount,
												   const VkBufferUsageFlags&    usageFlags,
												   const VkMemoryPropertyFlags& memoryPropertyFlags,
												   const VkDeviceSize&          minOffsetAlignment = 1);
private:
	VIDECL VIREQOUT static VkDeviceSize GetAlignment(const VkDeviceSize& instanceSize,
													 const VkDeviceSize& minOffsetAlignment);
};

VIDECL typedef UPtr<CVulkanMemoryBuffer> PVulkanMemoryBuffer;

VISRCEND

#endif //VICTORIAM_VULKANMEMORYBUFFER_HPP
