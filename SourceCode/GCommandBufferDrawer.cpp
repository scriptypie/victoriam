//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include <Victoriam/Graphics/GCommandBufferDrawer.hpp>

#include "VulkanCommandBufferDrawer.hpp"

VISRCBEG

PDrawCommandBuffer CCommandBufferDrawer::Create(PSwapchain &swapchain, PDevice& device, PPipeline& pipeline)
{
	return CreateSPtr<CVulkanCommandBufferDrawer>(swapchain, device, pipeline);
}

VISRCEND
