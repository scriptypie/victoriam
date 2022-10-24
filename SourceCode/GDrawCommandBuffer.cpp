//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include <Victoriam/Graphics/GDrawCommandBuffer.hpp>

#include "VulkanDrawCommandBuffer.hpp"

VISRCBEG

PDrawCommandBuffer CDrawCommandBuffer::Create(PSwapchain &swapchain, PDevice& device, PPipeline& pipeline, const List<PVertexBuffer>& vertexBuffers)
{
	return CreateSPtr<CVulkanDrawCommandBuffer>(swapchain, device, pipeline, vertexBuffers);
}

VISRCEND
