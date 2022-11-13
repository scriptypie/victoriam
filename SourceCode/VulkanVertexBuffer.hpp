//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#ifndef VICTORIAM_VULKANVERTEXBUFFER_HPP
#define VICTORIAM_VULKANVERTEXBUFFER_HPP

#include <Victoriam/Graphics/GVertexBuffer.hpp>

#include "VulkanMemoryBuffer.hpp"

VISRCBEG

namespace Accessors { class VertexBuffer; }

class VIDECL CVulkanVertexBuffer : public CVertexBuffer
{
	friend class Accessors::VertexBuffer;
	PGraphicsContext& m_Context;
	PVulkanMemoryBuffer m_MemoryBuffer = nullptr;
	UInt64 m_VertexCount = {};
public:
	VIDECL CVulkanVertexBuffer(PGraphicsContext &context, const CList<SVertex> &vertices);
	VIDECL ~CVulkanVertexBuffer() override = default;

	VIDECL void Bind(const SCommandBuffer& buffer) override;
	VIDECL void Draw(const SCommandBuffer& buffer) const override;

private:
	VIDECL VIREQOUT inline VkDescriptorBufferInfo GetDescriptorBufferInfo(const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {})
	{
		return m_MemoryBuffer->GetDescriptorInfo(size, offset);
	}

private:
	VIDECL void CreateVertexBuffer(const CList<SVertex>& vertices);
};

VISRCEND

#endif //VICTORIAM_VULKANVERTEXBUFFER_HPP
