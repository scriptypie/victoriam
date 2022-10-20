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

class cVulkanDrawCommandBuffer : public cDrawCommandBuffer {
	friend class Accessors::DrawCommandBuffer;

	List<VkCommandBuffer> m_CommandBuffers = {};
	pSwapchain& m_Swapchain;
	pDevice& m_Device;
	pPipeline& m_Pipeline;
	List<pVertexBuffer> m_VertexBuffers = {};
public:
	cVulkanDrawCommandBuffer(pSwapchain& swapchain, pDevice& device, pPipeline& pipeline, const List<pVertexBuffer>& vertexBuffers);
	~cVulkanDrawCommandBuffer() override;

	void RecordCommandBuffer(UInt32 imageIndex) override;

private:
	void CreateCommandBuffers();
private:
	VIDECL VIREQOUT inline List<VkCommandBuffer> GetCommandBufferList() const { return m_CommandBuffers; }
};

VISRCEND

#endif //VICTORIAM_VULKANDRAWCOMMANDBUFFER_HPP
