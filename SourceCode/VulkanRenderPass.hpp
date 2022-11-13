//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_VULKANRENDERPASS_HPP
#define VICTORIAM_VULKANRENDERPASS_HPP

#include <Victoriam/Graphics/GRenderPass.hpp>

#include "Accessors/AGraphicsContext.hpp"
#include "Accessors/ASwapchain.hpp"

VISRCBEG

namespace Accessors { class RenderPass; }

class VIDECL CVulkanRenderPass : public CRenderPass {
	friend class Accessors::RenderPass;
	VkRenderPass m_RenderPass = {};
	PSwapchain& m_Swapchain;
	PGraphicsContext& m_Context;
	SVector2 m_Offset = {};
	SWindowExtent m_Extent = {};
	SVector4 m_ClearColor = {0.01F, 0.01F, 0.01F, 1.0F};
	Float32 m_Depth = {};
	UInt32 m_Stencil = {};
public:
	VIDECL CVulkanRenderPass(PGraphicsContext& context, PSwapchain& swapchain, const SRenderPassCreateInfo& createInfo);
	VIDECL ~CVulkanRenderPass() override;

	VIDECL void Begin(const SCommandBuffer& commandBuffer) override;
	VIDECL void End(const SCommandBuffer& commandBuffer) override;

private:
	VIDECL void CreateRenderPass();
private:
	VIDECL VIREQOUT inline VkRenderPass GetRenderPass() { return m_RenderPass; }
};

VISRCEND

#endif //VICTORIAM_VULKANRENDERPASS_HPP
