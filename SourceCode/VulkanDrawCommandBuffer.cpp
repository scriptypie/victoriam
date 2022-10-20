//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanDrawCommandBuffer.hpp"

VISRCBEG

cVulkanDrawCommandBuffer::cVulkanDrawCommandBuffer(pSwapchain &swapchain, pDevice& device, pPipeline& pipeline, const List<pVertexBuffer>& vertexBuffers)
	: m_Swapchain(swapchain), m_Device(device), m_Pipeline(pipeline)
{
	m_VertexBuffers = vertexBuffers;
	CreateCommandBuffers();
}

cVulkanDrawCommandBuffer::~cVulkanDrawCommandBuffer()
{

}

void cVulkanDrawCommandBuffer::CreateCommandBuffers()
{
	m_CommandBuffers.resize(Accessors::Swapchain::GetImageCount(m_Swapchain));

	VkCommandBufferAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocateInfo.commandPool = Accessors::Device::GetCommandPool(m_Device);
	allocateInfo.commandBufferCount = CCast<UInt32>(m_CommandBuffers.size());

	if (vkAllocateCommandBuffers(Accessors::Device::GetDevice(m_Device), &allocateInfo, m_CommandBuffers.data()) != VK_SUCCESS)
		throw std::runtime_error("Failed to allocate command buffers!");

	for (UInt32 i = 0; i < m_CommandBuffers.size(); i++)
	{
		VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
		if (vkBeginCommandBuffer(m_CommandBuffers.at(i), &beginInfo) != VK_SUCCESS)
			throw std::runtime_error("Failed to call vkBeginCommandBuffer()");

		VkRenderPassBeginInfo renderPassBeginInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
		renderPassBeginInfo.renderPass = Accessors::Swapchain::GetRenderPass(m_Swapchain);
		renderPassBeginInfo.framebuffer = Accessors::Swapchain::GetFramebuffer(m_Swapchain, i);

		renderPassBeginInfo.renderArea.offset = {0, 0};
		renderPassBeginInfo.renderArea.extent = Accessors::Swapchain::GetSwapchainExtent(m_Swapchain);

		Array<VkClearValue, 2> clearValues = {};
		clearValues.at(0).color = { 0.1F, 0.1F, 0.1F, 1.0F };
		clearValues.at(1).depthStencil = { 1.0F, 0 };

		renderPassBeginInfo.clearValueCount = CCast<UInt32>(clearValues.size());
		renderPassBeginInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(m_CommandBuffers.at(i), &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);


		Accessors::Pipeline::BindDrawCommandBuffer(m_Pipeline, m_CommandBuffers.at(i));
		for (UInt32 j = 0; j < m_VertexBuffers.size(); j++)
		{
			Accessors::VertexBuffer::Bind(m_VertexBuffers.at(j), m_CommandBuffers.at(i));
			Accessors::VertexBuffer::Draw(m_VertexBuffers.at(j), m_CommandBuffers.at(i));
		}

		vkCmdEndRenderPass(m_CommandBuffers.at(i));

		if (vkEndCommandBuffer(m_CommandBuffers.at(i)) != VK_SUCCESS)
			throw std::runtime_error("Failed to record command buffer!");
	}

}

VISRCEND
