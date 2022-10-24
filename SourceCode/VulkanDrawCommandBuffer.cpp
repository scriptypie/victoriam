//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanDrawCommandBuffer.hpp"

VISRCBEG

CVulkanDrawCommandBuffer::CVulkanDrawCommandBuffer(PSwapchain &swapchain, PDevice& device, PPipeline& pipeline, const List<PVertexBuffer>& vertexBuffers)
	: m_Swapchain(swapchain), m_Device(device), m_Pipeline(pipeline)
{
	m_VertexBuffers = vertexBuffers;
	CreateCommandBuffers();
}

CVulkanDrawCommandBuffer::~CVulkanDrawCommandBuffer()
{
	vkFreeCommandBuffers(Accessors::Device::GetDevice(m_Device), Accessors::Device::GetCommandPool(m_Device), CCast<UInt32>(m_CommandBuffers.size()), m_CommandBuffers.data());
	m_CommandBuffers.clear();
}

void CVulkanDrawCommandBuffer::CreateCommandBuffers()
{
	m_CommandBuffers.resize(m_Swapchain->GetImageCount());

	VkCommandBufferAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocateInfo.commandPool = Accessors::Device::GetCommandPool(m_Device);
	allocateInfo.commandBufferCount = CCast<UInt32>(m_CommandBuffers.size());

	if (vkAllocateCommandBuffers(Accessors::Device::GetDevice(m_Device), &allocateInfo, m_CommandBuffers.data()) != VK_SUCCESS)
		throw std::runtime_error("Failed to allocate command buffers!");
}

void CVulkanDrawCommandBuffer::RecordCommandBuffer(UInt32 imageIndex)
{
	VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
	if (vkBeginCommandBuffer(m_CommandBuffers.at(imageIndex), &beginInfo) != VK_SUCCESS)
		throw std::runtime_error("Failed to call vkBeginCommandBuffer()");

	VkRenderPassBeginInfo renderPassBeginInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
	renderPassBeginInfo.renderPass = Accessors::Swapchain::GetRenderPass(m_Swapchain);
	renderPassBeginInfo.framebuffer = Accessors::Swapchain::GetFramebuffer(m_Swapchain, imageIndex);

	renderPassBeginInfo.renderArea.offset = {0, 0};
	renderPassBeginInfo.renderArea.extent = Accessors::Swapchain::GetSwapchainExtent(m_Swapchain);

	Array<VkClearValue, 2> clearValues = {};
	clearValues.at(0).color = { 0.01F, 0.01F, 0.01F, 1.0F };
	clearValues.at(1).depthStencil = { 1.0F, 0 };

	renderPassBeginInfo.clearValueCount = CCast<UInt32>(clearValues.size());
	renderPassBeginInfo.pClearValues = clearValues.data();

	vkCmdBeginRenderPass(m_CommandBuffers.at(imageIndex), &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

	auto extent = Accessors::Swapchain::GetSwapchainExtent(m_Swapchain);
	VkViewport viewport = {};
	viewport.width = CCast<Float32>(extent.width);
	viewport.height = CCast<Float32>(extent.height);
	viewport.maxDepth = 1.0F;
	VkRect2D scissor = {};
	scissor.extent = extent;
	vkCmdSetViewport(m_CommandBuffers.at(imageIndex), 0, 1, &viewport);
	vkCmdSetScissor(m_CommandBuffers.at(imageIndex), 0, 1, &scissor);

	m_Pipeline->BindDrawCommandBuffer(CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex)));
	for (const auto& m_VertexBuffer : m_VertexBuffers)
	{
		m_VertexBuffer->Bind(CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex)));
		m_VertexBuffer->Draw(CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex)));
	}

	vkCmdEndRenderPass(m_CommandBuffers.at(imageIndex));

	if (vkEndCommandBuffer(m_CommandBuffers.at(imageIndex)) != VK_SUCCESS)
		throw std::runtime_error("Failed to record command buffer!");
}

VISRCEND
