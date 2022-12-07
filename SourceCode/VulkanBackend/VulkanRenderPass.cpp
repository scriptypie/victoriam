//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#include "VulkanRenderPass.hpp"

#include "../Accessors/AGraphicsContext.hpp"
#include "../Accessors/ASwapchain.hpp"
#include "../Accessors/AFramebuffer.hpp"

VISRCBEG

CVulkanRenderPass::CVulkanRenderPass(PGraphicsContext &context, PSwapchain &swapchain,
                                         const SRenderPassCreateInfo &createInfo)
										 : m_Swapchain(swapchain), m_Context(context)
{
	m_ClearColor = createInfo.ClearColor;
	m_Depth = createInfo.Depth;
	m_Extent = createInfo.Extent;
	m_Offset = createInfo.Offset;
	m_Stencil = createInfo.Stencil;

	CreateRenderPass();
}

CVulkanRenderPass::~CVulkanRenderPass() {
	vkDestroyRenderPass(Accessors::GraphicsContext::GetDevice(m_Context), m_RenderPass, nullptr);
	m_RenderPass = nullptr;
}

void CVulkanRenderPass::Begin(const SFrameInfo& frameInfo) {
	VkRenderPassBeginInfo renderPassBeginInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
	renderPassBeginInfo.renderPass = m_RenderPass;
	renderPassBeginInfo.framebuffer = Accessors::Framebuffer::GetFramebuffer(frameInfo.Framebuffer);
	renderPassBeginInfo.renderArea.extent.width = m_Extent.Width;
	renderPassBeginInfo.renderArea.extent.height = m_Extent.Height;
	renderPassBeginInfo.renderArea.offset.x = CCast<Int32>(m_Offset.x);
	renderPassBeginInfo.renderArea.offset.y = CCast<Int32>(m_Offset.y);

	VkClearValue colorClearValue = {};
	colorClearValue.color.float32[0] = m_ClearColor.r;
	colorClearValue.color.float32[1] = m_ClearColor.g;
	colorClearValue.color.float32[2] = m_ClearColor.b;
	colorClearValue.color.float32[3] = m_ClearColor.a;

	VkClearValue depthClearValue = {};
	depthClearValue.depthStencil = { m_Depth, m_Stencil };

	VkClearValue clearValues[] = {colorClearValue, depthClearValue};

	renderPassBeginInfo.clearValueCount = FSize(clearValues);
	renderPassBeginInfo.pClearValues = clearValues;

	vkCmdBeginRenderPass(CCast<VkCommandBuffer>(frameInfo.CommandBuffer), &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

	auto extent = VkExtent2D{m_Swapchain->GetWidth(), m_Swapchain->GetHeight()};
	VkViewport viewport = {};
	viewport.width = CCast<Float32>(extent.width);
	viewport.height = CCast<Float32>(extent.height);
	viewport.maxDepth = 1.0F;

	VkRect2D scissor = {};
	scissor.offset = {};
	scissor.extent = extent;

	vkCmdSetViewport(CCast<VkCommandBuffer>(frameInfo.CommandBuffer), 0, 1, &viewport);
	vkCmdSetScissor(CCast<VkCommandBuffer>(frameInfo.CommandBuffer), 0, 1, &scissor);
}

void CVulkanRenderPass::End(const SFrameInfo& frameInfo) {
	vkCmdEndRenderPass(CCast<VkCommandBuffer>(frameInfo.CommandBuffer));
}

void CVulkanRenderPass::CreateRenderPass() {
	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = Accessors::Swapchain::GetSwapchainImageFormat(m_Swapchain);
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;


	VkAttachmentDescription depthAttachment = {};
	depthAttachment.format = Accessors::Swapchain::FindDepthFormat(m_Swapchain);
	depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthAttachmentRef = {};
	depthAttachmentRef.attachment = 1;
	depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	// TODO: other attachments...(input, resolve, preserve)

	VkSubpassDescription subpass = {};
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;
	subpass.pDepthStencilAttachment = &depthAttachmentRef;

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkAttachmentDescription attachments[] = {colorAttachment, depthAttachment};
	VkSubpassDescription subpasses[] = {subpass};
	VkSubpassDependency dependencies[] = {dependency};

	VkRenderPassCreateInfo renderPassInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
	renderPassInfo.attachmentCount = FSize(attachments);
	renderPassInfo.pAttachments = attachments;
	renderPassInfo.subpassCount = FSize(subpasses);
	renderPassInfo.pSubpasses = subpasses;
	renderPassInfo.dependencyCount = FSize(dependencies);
	renderPassInfo.pDependencies = dependencies;

	if (vkCreateRenderPass(Accessors::GraphicsContext::GetDevice(m_Context), &renderPassInfo, nullptr, &m_RenderPass) != VK_SUCCESS)
	ViAbort("Failed to create render pass!");
}

VISRCEND
