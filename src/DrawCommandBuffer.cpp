//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include <Victoriam/Graphics/DrawCommandBuffer.hpp>

#include "VulkanDrawCommandBuffer.hpp"

VISRCBEG

pDrawCommandBuffer cDrawCommandBuffer::Create(pSwapchain &swapchain, pDevice& device, pPipeline& pipeline)
{
	return CreateSPtr<cVulkanDrawCommandBuffer>(swapchain, device, pipeline);
}

VISRCEND
