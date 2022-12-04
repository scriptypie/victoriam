//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_VULKANFRAMEBUFFER_HPP
#define VICTORIAM_VULKANFRAMEBUFFER_HPP

#include "Victoriam/Graphics/GFramebuffer.hpp"

#include <vulkan/vulkan.h>

VISRCBEG

namespace Accessors { class Framebuffer; }

class VIDECL CVulkanFramebuffer : public CFramebuffer {
	friend class Accessors::Framebuffer;
	PGraphicsContext& m_Context;
	PRenderPass& m_RenderPass;
	VkFramebuffer m_Framebuffer = {};
	CSet<VkImageView> m_Attachments = {};
public:
	VIDECL CVulkanFramebuffer(PGraphicsContext& context, PRenderPass& renderPass, const SFramebufferCreateInfo& createInfo);
	VIDECL ~CVulkanFramebuffer() override;
private:
	VIDECL void CreateFramebuffer();
private:
	VIDECL VIREQOUT VkFramebuffer GetFramebuffer() { return m_Framebuffer; }
};

VISRCEND

#endif //VICTORIAM_VULKANFRAMEBUFFER_HPP
