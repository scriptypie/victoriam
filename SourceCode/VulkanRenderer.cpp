//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanRenderer.hpp"

VISRCBEG

cVulkanRenderer::cVulkanRenderer(const sRendererCreateInfo &createInfo)
	: m_Window(createInfo.WindowPtr)
{
	m_Device = cDevice::Create(m_Window);
	RecreateSwapchain(m_Window->GetExtent());
	CreatePipeline();
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
	auto result = m_Swapchain->AcquireNextImage(&imageIndex);
	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		RecreateSwapchain(m_Window->GetExtent());
		return;
	}
	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		throw std::runtime_error("Failed to acquire next image!");

	m_DrawCommandBuffer->RecordCommandBuffer(imageIndex);
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
	RecreateSwapchain(extent);
}

void cVulkanRenderer::RecreateSwapchain(const sWindowExtent &newExtent) {
	if (!newExtent.Width || !newExtent.Height) {
		m_Window->WaitForEvents();
		return;
	}

	vkDeviceWaitIdle(Accessors::Device::GetDevice(m_Device));

	if (!m_Swapchain)
		m_Swapchain = cSwapchain::Create(m_Device, newExtent);
	else
	{
		m_Swapchain = cSwapchain::Create(m_Device, newExtent, std::move(m_Swapchain).get());
		if (m_Swapchain->GetImageCount() != Accessors::DrawCommandBuffer::GetCommandBufferList(m_DrawCommandBuffer).size())
		{
			m_DrawCommandBuffer = nullptr;
			m_DrawCommandBuffer = cDrawCommandBuffer::Create(m_Swapchain, m_Device, m_Pipeline, m_VertexBuffers);
		}
	}
	CreatePipeline();
}

void cVulkanRenderer::CreatePipeline()
{
	m_Pipeline = cPipeline::Create("Default", m_Device, m_Swapchain);
}

VISRCEND
