//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanCmdBufferSolver.hpp"

#include "Victoriam/Graphics/Structs/GRendererConstants.hpp"
#include "Victoriam/Graphics/GCamera.hpp"

VISRCBEG

CVulkanCmdBufferSolver::CVulkanCmdBufferSolver(PSwapchain &swapchain, PGraphicsContext& context)
	: m_Swapchain(swapchain), m_Context(context)
{
	CreateCmdBuffers();
}

CVulkanCmdBufferSolver::~CVulkanCmdBufferSolver()
{
	vkFreeCommandBuffers(
			Accessors::GraphicsContext::GetDevice(m_Context),
			Accessors::GraphicsContext::GetCommandPool(m_Context),
			CCast<UInt32>(m_CmdBuffers.size()),
			m_CmdBuffers.data());

	m_CmdBuffers.clear();
}

void CVulkanCmdBufferSolver::CreateCmdBuffers()
{
	m_CmdBuffers.resize(m_Swapchain->GetImageCount());

	VkCommandBufferAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocateInfo.commandPool = Accessors::GraphicsContext::GetCommandPool(m_Context);
	allocateInfo.commandBufferCount = CCast<UInt32>(m_CmdBuffers.size());

	if (vkAllocateCommandBuffers(Accessors::GraphicsContext::GetDevice(m_Context), &allocateInfo, m_CmdBuffers.data()) != VK_SUCCESS)
		ViAbort("Failed to allocate command buffers!");
}

SCommandBuffer CVulkanCmdBufferSolver::Begin(const PWorld& world, const UInt32& imageIndex)
{
	VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
	if (vkBeginCommandBuffer(m_CmdBuffers.at(imageIndex), &beginInfo) != VK_SUCCESS)
		ViAbort("Failed to call vkBeginCommandBuffer()");

	return CCast<SCommandBuffer>(m_CmdBuffers.at(imageIndex));
}

void CVulkanCmdBufferSolver::End(const SCommandBuffer& commandBuffer) const
{
	if (vkEndCommandBuffer(CCast<VkCommandBuffer>(commandBuffer)) != VK_SUCCESS)
		ViAbort("Failed to record command buffer!");
}

VISRCEND
