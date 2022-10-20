//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanRenderer.hpp"

VISRCBEG

cVulkanRenderer::cVulkanRenderer(const sRendererCreateInfo &createInfo)
	: m_Window(createInfo.WindowPtr)
{
	m_Device = cDevice::Create(m_Window);
	m_Swapchain = cSwapchain::Create(m_Device, m_Window->GetExtent());
	m_Pipeline = cPipeline::Create("Default", m_Device, m_Swapchain, sPipelineCreateInfo(m_Window->GetWidth(), m_Window->GetHeight()));
}

void cVulkanRenderer::Setup()
{
	m_DrawCommandBuffer = cDrawCommandBuffer::Create(m_Swapchain, m_Device, m_Pipeline, m_VertexBuffers);
}

void cVulkanRenderer::PushVertexBuffer(const List<sVertex>& vertices)
{
	m_VertexBuffers.push_back(cVertexBuffer::Create(m_Device, vertices));
}

cVulkanRenderer::~cVulkanRenderer() = default;

void cVulkanRenderer::DrawFrame()
{
	UInt32 imageIndex;
	auto result = Accessors::Swapchain::AcquiredNextImage(m_Swapchain, &imageIndex);
	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		throw std::runtime_error("Failed to acquire next image!");

	Accessors::Swapchain::SubmitCommandBuffers(m_Swapchain, &Accessors::DrawCommandBuffer::GetCommandBufferList(m_DrawCommandBuffer).at(imageIndex), &imageIndex);


}

void cVulkanRenderer::BeginFrame()
{

}

void cVulkanRenderer::EndFrame()
{

}

void cVulkanRenderer::Shutdown() {
	vkDeviceWaitIdle(Accessors::Device::GetDevice(m_Device));
}

void cVulkanRenderer::OnWindowResize(const sWindowExtent &extent) {
	m_Swapchain->RecreateSwapchain(extent);
}

VISRCEND
