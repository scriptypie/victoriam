//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_VULKANUNIFORMBUFFER_HPP
#define VICTORIAM_VULKANUNIFORMBUFFER_HPP

#include "Victoriam/Graphics/GUniformBuffer.hpp"

#include "VulkanMemoryBuffer.hpp"

VISRCBEG

namespace Accessors { class UniformBuffer; }

class CVulkanUniformBuffer : public CUniformBuffer
{
	friend class Accessors::UniformBuffer;
	PGraphicsContext& m_Context;
	PVulkanMemoryBuffer m_MemoryBuffer = nullptr;
	UInt64 m_Count = {};
public:
	VIDECL CVulkanUniformBuffer(PGraphicsContext &context, const UInt32& maxFramesInFlight);
	VIDECL ~CVulkanUniformBuffer() override = default;

	VIDECL void Bind(const SCommandBuffer& buffer) override;
	VIDECL void SubmitToGPU(const SRendererConstants& constants) override;

private:
	VIDECL VIREQOUT inline VkDescriptorBufferInfo GetDescriptorBufferInfo(const VkDeviceSize& size = VK_WHOLE_SIZE, const VkDeviceSize& offset = {})
	{
		return m_MemoryBuffer->GetDescriptorInfo(size, offset);
	}

private:
	VIDECL void CreateUniformBuffer(const UInt32& maxFramesInFlight);
};

VISRCEND

#endif //VICTORIAM_VULKANUNIFORMBUFFER_HPP
