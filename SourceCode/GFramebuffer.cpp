//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#include <Victoriam/Graphics/GFramebuffer.hpp>

#include "VulkanBackend/VulkanFramebuffer.hpp"

VISRCBEG

PFramebuffer CFramebuffer::Create(PGraphicsContext& context, PRenderPass& renderPass, const SFramebufferCreateInfo& createInfo)
{
	return FCreateShared<CVulkanFramebuffer>(context, renderPass, createInfo);
}

VISRCEND
