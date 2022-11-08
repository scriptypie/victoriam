//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_VULKANCOMMANDBUFFERDRAWER_HPP
#define VICTORIAM_VULKANCOMMANDBUFFERDRAWER_HPP

#include<Victoriam/Graphics/GCommandBufferDrawer.hpp>

#include"Accessors/ASwapchain.hpp"
#include"Accessors/AGraphicsContext.hpp"
#include"Accessors/APipeline.hpp"

VISRCBEG

namespace Accessors { class CommandBufferDrawer; }

class VIDECL CVulkanCommandBufferDrawer : public CCommandBufferDrawer {
	friend class Accessors::CommandBufferDrawer;

	List<VkCommandBuffer> m_CommandBuffers = {};
	PSwapchain& m_Swapchain;
	PGraphicsContext& m_Context;
	PPipeline& m_Pipeline;
public:
	VIDECL CVulkanCommandBufferDrawer(PSwapchain& swapchain, PGraphicsContext& device, PPipeline& pipeline);
	VIDECL ~CVulkanCommandBufferDrawer() override;

	VIDECL VIREQOUT SCommandBuffer Begin(const PWorld& world, const UInt32& imageIndex) override;
	VIDECL          void SubmitDraw(const PWorld& world, const SFrameInfo& frameInfo) const override;
	VIDECL          void End(const SCommandBuffer& commandBuffer) const override;

private:
	VIDECL void CreateCommandBuffers();
private:
	VIDECL VIREQOUT inline List<VkCommandBuffer> GetCommandBufferList() const { return m_CommandBuffers; }
};

VISRCEND

#endif //VICTORIAM_VULKANCOMMANDBUFFERDRAWER_HPP
