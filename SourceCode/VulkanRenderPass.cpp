//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#include "VulkanRenderPass.hpp"

VISRCBEG

CVulkanRenderPass::CVulkanRenderPass(PGraphicsContext &context, PSwapchain &swapchain,
                                         const SRenderPassCreateInfo &createInfo)
										 : m_Context(context), m_Swapchain(swapchain)
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
}

void CVulkanRenderPass::Begin(SCommandBuffer const &commandBuffer) {
	VkRenderPassBeginInfo renderPassBeginInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
	renderPassBeginInfo.renderPass = m_RenderPass;
	renderPassBeginInfo.framebuffer = nullptr; // TODO: framebuffers

	renderPassBeginInfo.renderArea.extent = Cast<VkExtent2D>(&m_Extent);

	CArray<VkClearValue, 2> clearValues = {};
	clearValues.At(0).color = Cast<VkClearColorValue>(&m_ClearColor);
	clearValues.At(1).depthStencil = { m_Depth, m_Stencil };

	renderPassBeginInfo.clearValueCount = CCast<UInt32>(clearValues.Size());
	renderPassBeginInfo.pClearValues = clearValues.Data();

	vkCmdBeginRenderPass(CCast<VkCommandBuffer>(commandBuffer), &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

	auto extent = VkExtent2D{m_Swapchain->GetWidth(), m_Swapchain->GetHeight()};
	VkViewport viewport = {};
	viewport.width = CCast<Float32>(extent.width);
	viewport.height = CCast<Float32>(extent.height);
	viewport.maxDepth = 1.0F;
	VkRect2D scissor = {};
	scissor.extent = extent;
	vkCmdSetViewport(CCast<VkCommandBuffer>(commandBuffer), 0, 1, &viewport);
	vkCmdSetScissor(CCast<VkCommandBuffer>(commandBuffer), 0, 1, &scissor);
}

void CVulkanRenderPass::End(SCommandBuffer const &commandBuffer) {
	vkCmdEndRenderPass(CCast<VkCommandBuffer>(commandBuffer));
}

void CVulkanRenderPass::CreateRenderPass() {
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

	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = Accessors::Swapchain::GetSwapchainImageFormat(m_Swapchain);
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef = {};
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;
	subpass.pDepthStencilAttachment = &depthAttachmentRef;

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

	CArray<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};
	VkRenderPassCreateInfo renderPassInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
	renderPassInfo.attachmentCount = CCast<UInt32>(attachments.Size());
	renderPassInfo.pAttachments = attachments.Data();
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;

	if (vkCreateRenderPass(Accessors::GraphicsContext::GetDevice(m_Context), &renderPassInfo, nullptr, &m_RenderPass) != VK_SUCCESS)
	ViAbort("Failed to create render pass!");
}

VISRCEND
