//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#include "VulkanUniformBuffer.hpp"

VISRCBEG

CVulkanUniformBuffer::CVulkanUniformBuffer(PGraphicsContext &context, const UInt32 &maxFramesInFlight)
	: m_Context(context)
{
	CreateUniformBuffer(maxFramesInFlight);
}

void CVulkanUniformBuffer::Bind(SCommandBuffer const &buffer) {
	m_MemoryBuffer->Map();
}

void CVulkanUniformBuffer::SubmitToGPU(const SRendererConstants &constants) {
	m_MemoryBuffer->WriteToBuffer(&constants);
	m_MemoryBuffer->Flush();
}

void CVulkanUniformBuffer::CreateUniformBuffer(const UInt32 &maxFramesInFlight) {
	m_MemoryBuffer = CVulkanMemoryBuffer::Create(
			m_Context, sizeof(SRendererConstants),
			maxFramesInFlight,
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT/* | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT*/);
}

VISRCEND
