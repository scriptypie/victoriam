//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanRenderer.hpp"

VISRCBEG

Vi::cVulkanRenderer::cVulkanRenderer(const Vi::sRendererCreateInfo &createInfo)
{
	auto window = createInfo.WindowPtr;
	m_Device = cDevice::Create(window);
	m_Swapchain = cSwapchain::Create(m_Device, window->GetExtent());
	m_Pipeline = cPipeline::Create("Default", m_Device, m_Swapchain, sPipelineCreateInfo(window->GetWidth(), window->GetHeight()));
	m_DrawCommandBuffer = cDrawCommandBuffer::Create(m_Swapchain, m_Device, m_Pipeline);

}

Vi::cVulkanRenderer::~cVulkanRenderer() = default;

void Vi::cVulkanRenderer::DrawFrame()
{
	UInt32 imageIndex;
	auto result = Accessors::Swapchain::AcquiredNextImage(m_Swapchain, &imageIndex);
	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		throw std::runtime_error("Failed to acquire next image!");

	result = Accessors::Swapchain::SubmitCommandBuffers(m_Swapchain, &Accessors::DrawCommandBuffer::GetCommandBufferList(m_DrawCommandBuffer).at(imageIndex), &imageIndex);
	if (result != VK_SUCCESS)
		throw std::runtime_error("Failed to present swapchain image!");

}

void Vi::cVulkanRenderer::BeginFrame()
{

}

void Vi::cVulkanRenderer::EndFrame()
{

}

void cVulkanRenderer::Shutdown() {
	vkDeviceWaitIdle(Accessors::Device::GetDevice(m_Device));
}

VISRCEND
