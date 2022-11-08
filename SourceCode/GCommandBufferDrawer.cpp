//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include <Victoriam/Graphics/GCommandBufferDrawer.hpp>

#include "VulkanCommandBufferDrawer.hpp"

VISRCBEG

PCommandBufferDrawer CCommandBufferDrawer::Create(PSwapchain &swapchain, PGraphicsContext& context, PPipeline& pipeline)
{
	return CreateSPtr<CVulkanCommandBufferDrawer>(swapchain, context, pipeline);
}

VISRCEND
