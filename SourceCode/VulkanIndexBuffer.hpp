//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_VULKANINDEXBUFFER_HPP
#define VICTORIAM_VULKANINDEXBUFFER_HPP

#include <Victoriam/Graphics/GIndexBuffer.hpp>

#include "VulkanMemoryBuffer.hpp"

VISRCBEG

namespace Accessors { class IndexBuffer; }

class CVulkanIndexBuffer : public CIndexBuffer
{
	friend class Accessors::IndexBuffer;
	PGraphicsContext& m_Context;
	PVulkanMemoryBuffer m_MemoryBuffer = nullptr;
	UInt64 m_IndexCount = {};
public:
	VIDECL CVulkanIndexBuffer(PGraphicsContext &context, const CList<UInt32> &indices);
	VIDECL ~CVulkanIndexBuffer() override = default;

	VIDECL void Bind(const SCommandBuffer& buffer) override;
	VIDECL void Draw(const SCommandBuffer& buffer) const override;

private:
	VIDECL VIREQOUT inline VkDescriptorBufferInfo GetDescriptorBufferInfo(const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {})
	{
		return m_MemoryBuffer->GetDescriptorInfo(size, offset);
	}

private:
	VIDECL void CreateIndexBuffer(const CList<UInt32>& indices);
};

VISRCEND

#endif //VICTORIAM_VULKANINDEXBUFFER_HPP
