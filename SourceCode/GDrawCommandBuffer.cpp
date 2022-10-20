//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include <Victoriam/Graphics/GDrawCommandBuffer.hpp>

#include "VulkanDrawCommandBuffer.hpp"

VISRCBEG

pDrawCommandBuffer cDrawCommandBuffer::Create(pSwapchain &swapchain, pDevice& device, pPipeline& pipeline, const List<pVertexBuffer>& vertexBuffers)
{
	return CreateSPtr<cVulkanDrawCommandBuffer>(swapchain, device, pipeline, vertexBuffers);
}

VISRCEND
