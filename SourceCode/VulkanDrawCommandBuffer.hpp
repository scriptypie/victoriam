//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_VULKANDRAWCOMMANDBUFFER_HPP
#define VICTORIAM_VULKANDRAWCOMMANDBUFFER_HPP

#include<Victoriam/Graphics/GDrawCommandBuffer.hpp>

#include"Accessors/ASwapchain.hpp"
#include"Accessors/ADevice.hpp"
#include"Accessors/APipeline.hpp"
#include"Accessors/AVertexBuffer.hpp"

VISRCBEG

namespace Accessors { class DrawCommandBuffer; }

class CVulkanDrawCommandBuffer : public CDrawCommandBuffer {
	friend class Accessors::DrawCommandBuffer;

	List<VkCommandBuffer> m_CommandBuffers = {};
	PSwapchain& m_Swapchain;
	PDevice& m_Device;
	PPipeline& m_Pipeline;
public:
	CVulkanDrawCommandBuffer(PSwapchain& swapchain, PDevice& device, PPipeline& pipeline);
	~CVulkanDrawCommandBuffer() override;

	SCommandBuffer Begin(UInt32 imageIndex) override;
	void End(UInt32 imageIndex) override;
	void SubmitDraw(const PWorld& world, UInt32 imageIndex) override;

private:
	void CreateCommandBuffers();
private:
	VIDECL VIREQOUT inline List<VkCommandBuffer> GetCommandBufferList() const { return m_CommandBuffers; }
};

VISRCEND

#endif //VICTORIAM_VULKANDRAWCOMMANDBUFFER_HPP
