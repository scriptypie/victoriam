//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_VULKANCOMMANDBUFFERDRAWER_HPP
#define VICTORIAM_VULKANCOMMANDBUFFERDRAWER_HPP

#include<Victoriam/Graphics/GCommandBufferDrawer.hpp>

#include"Accessors/ASwapchain.hpp"
#include"Accessors/ADevice.hpp"
#include"Accessors/APipeline.hpp"

VISRCBEG

namespace Accessors { class CommandBufferDrawer; }

class CVulkanCommandBufferDrawer : public CCommandBufferDrawer {
	friend class Accessors::CommandBufferDrawer;

	List<VkCommandBuffer> m_CommandBuffers = {};
	PSwapchain& m_Swapchain;
	PDevice& m_Device;
	PPipeline& m_Pipeline;
public:
	CVulkanCommandBufferDrawer(PSwapchain& swapchain, PDevice& device, PPipeline& pipeline);
	~CVulkanCommandBufferDrawer() override;

	SCommandBuffer Begin(const PWorld& world, UInt32 imageIndex) override;
	void End(UInt32 imageIndex) override;
	void SubmitDraw(const PWorld& world, UInt32 imageIndex) override;

private:
	void CreateCommandBuffers();
private:
	VIDECL VIREQOUT inline List<VkCommandBuffer> GetCommandBufferList() const { return m_CommandBuffers; }
};

VISRCEND

#endif //VICTORIAM_VULKANCOMMANDBUFFERDRAWER_HPP
