//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#include <Victoriam/Graphics/GRenderPass.hpp>

#include "VulkanRenderPass.hpp"

VISRCBEG

PRenderPass CRenderPass::Create(Vi::PGraphicsContext &context, Vi::PSwapchain &swapchain,
                                const Vi::SRenderPassCreateInfo &createInfo)
{
	return CreateUPtr<CVulkanRenderPass>(context, swapchain, createInfo);
}

VISRCEND
