//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanRenderer.hpp"

VISRCBEG

CVulkanRenderer::CVulkanRenderer(const SRendererCreateInfo &createInfo)
	: m_Window(createInfo.WindowPtr)
{
	m_Device = CDevice::Create(m_Window);
	RecreateSwapchain(m_Window->GetExtent());
	CreatePipeline();
}

void CVulkanRenderer::Setup()
{
	m_DrawCommandBuffer = CDrawCommandBuffer::Create(m_Swapchain, m_Device, m_Pipeline);
}

PVertexBuffer CVulkanRenderer::CreateVertexBuffer(const List<SVertex> &vertices)
{
	return CVertexBuffer::Create(m_Device, vertices);
}

	CVulkanRenderer::~CVulkanRenderer() = default;

void CVulkanRenderer::DrawFrame(const PWorld& world)
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

	m_DrawCommandBuffer->RecordCommandBuffer(world, imageIndex);
	Accessors::Swapchain::SubmitCommandBuffers(m_Swapchain, &Accessors::DrawCommandBuffer::GetCommandBufferList(m_DrawCommandBuffer).at(imageIndex), &imageIndex);

}

void CVulkanRenderer::BeginFrame()
{

}

void CVulkanRenderer::EndFrame()
{

}

void CVulkanRenderer::Shutdown(const PWorld& world) {

	vkDeviceWaitIdle(Accessors::Device::GetDevice(m_Device));

	auto renderable_objs = world->FindGameObjectsWithComponent<SComponentRenderable>(); // all renderables MUST have a transform component!!!
	for (auto renderable_obj : renderable_objs)
	{
		auto& rrc = renderable_obj->GetComponent<SComponentRenderable>();
		rrc.VertexBuffer.reset();
	}

	world->Clear();
}

void CVulkanRenderer::OnWindowResize(const SWindowExtent &extent) {
	RecreateSwapchain(extent);
}

void CVulkanRenderer::RecreateSwapchain(const SWindowExtent &newExtent) {
	if (!newExtent.Width || !newExtent.Height) {
		m_Window->WaitForEvents();
		return;
	}

	vkDeviceWaitIdle(Accessors::Device::GetDevice(m_Device));

	if (!m_Swapchain)
		m_Swapchain = CSwapchain::Create(m_Device, newExtent);
	else
	{
		m_Swapchain = CSwapchain::Create(m_Device, newExtent, std::move(m_Swapchain).get());
		if (m_Swapchain->GetImageCount() != Accessors::DrawCommandBuffer::GetCommandBufferList(m_DrawCommandBuffer).size())
		{
			m_DrawCommandBuffer = nullptr;
			m_DrawCommandBuffer = CDrawCommandBuffer::Create(m_Swapchain, m_Device, m_Pipeline);
		}
	}
	CreatePipeline();
}

void CVulkanRenderer::CreatePipeline()
{
	m_Pipeline = CPipeline::Create("Default", m_Device, m_Swapchain);
}

VISRCEND
