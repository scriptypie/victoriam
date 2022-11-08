//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#ifndef VICTORIAM_VULKANBUFFER_HPP
#define VICTORIAM_VULKANBUFFER_HPP

#include <Victoriam/Graphics/GBuffer.hpp>

#include "VulkanMemoryBuffer.hpp"

VISRCBEG

namespace Accessors { class Buffer; }

class VIDECL CVulkanBuffer : public CBuffer
{
	friend class Accessors::Buffer;
	enum class ECType : UInt32 { None = 0U, VertexBuffer, IndexBuffer, UniformBuffer };
	ECType m_Type = ECType::None;
	PGraphicsContext& m_Context;
	PVulkanMemoryBuffer m_MemoryBuffer = nullptr;
	UInt64 m_Count = {};
public:
	VIDECL CVulkanBuffer(PGraphicsContext &context, const List<SVertex> &vertices);
	VIDECL CVulkanBuffer(PGraphicsContext &context, const List<UInt32> &indices);
	VIDECL CVulkanBuffer(PGraphicsContext &context, const UInt32& maxFramesInFlight);
	VIDECL ~CVulkanBuffer() override = default;

	VIDECL void Bind(const SCommandBuffer& buffer) override;
	VIDECL void SubmitUniformBuffer(const SRendererConstants& constants) override;
	VIDECL void Draw(const SCommandBuffer& buffer) const override;

private:
	VIDECL VIREQOUT inline VkDescriptorBufferInfo GetDescriptorBufferInfo(const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {})
	{
		return m_MemoryBuffer->GetDescriptorInfo(size, offset);
	}

private:
	VIDECL void CreateVertexBuffer(const List<SVertex>& vertices);
	VIDECL void CreateIndexBuffer(const List<UInt32>& indices);
	VIDECL void CreateUniformBuffer(const UInt32& maxFramesInFlight);
};

VISRCEND

#endif //VICTORIAM_VULKANBUFFER_HPP
