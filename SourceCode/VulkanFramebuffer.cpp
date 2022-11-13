//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#include "VulkanFramebuffer.hpp"

#include "Accessors/AGraphicsContext.hpp"
#include "Accessors/ARenderPass.hpp"

VISRCBEG

CVulkanFramebuffer::CVulkanFramebuffer(PGraphicsContext& context, PRenderPass& renderPass, const SFramebufferCreateInfo& createInfo)
	: m_Context(context), m_RenderPass(renderPass)
{
	if (!createInfo.Attachments.empty())
		for (auto& attachment : createInfo.Attachments)
			m_Attachments.push_back(CCast<VkImageView>(attachment));
	CreateFramebuffer();
}

CVulkanFramebuffer::~CVulkanFramebuffer() {
	vkDestroyFramebuffer(Accessors::GraphicsContext::GetDevice(m_Context), m_Framebuffer, nullptr);
}

void CVulkanFramebuffer::CreateFramebuffer() {
	SExtent2D extent = Accessors::RenderPass::GetExtent(m_RenderPass);
	VkFramebufferCreateInfo framebufferInfo = { VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO };
	framebufferInfo.renderPass = Accessors::RenderPass::GetRenderPass(m_RenderPass);
	framebufferInfo.attachmentCount = CCast<UInt32>(m_Attachments.size());
	framebufferInfo.pAttachments = m_Attachments.data();
	framebufferInfo.width = extent.Width;
	framebufferInfo.height = extent.Height;
	framebufferInfo.layers = 1;

	if (vkCreateFramebuffer(Accessors::GraphicsContext::GetDevice(m_Context), &framebufferInfo, nullptr, &m_Framebuffer) != VK_SUCCESS)
		ViAbort("Failed to create framebuffer!");
}

VISRCEND
