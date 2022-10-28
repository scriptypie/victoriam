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

	DefaultVertexBuffer = CVertexBuffer::Create(m_Device, DefaultVertices);
	DefaultIndexBuffer  = CIndexBuffer ::Create(m_Device, DefaultIndices);
}

PVertexBuffer CVulkanRenderer::CreateVertexBuffer(const List<SVertex> &vertices)
{
	return CVertexBuffer::Create(m_Device, vertices);
}

CVulkanRenderer::~CVulkanRenderer() = default;

SCommandBuffer CVulkanRenderer::BeginFrame()
{
	auto result = m_Swapchain->AcquireNextImage(&m_ImageIndex);
	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		RecreateSwapchain(m_Window->GetExtent());
		return nullptr;
	}
	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		throw std::runtime_error("Failed to acquire next image!");

	return m_DrawCommandBuffer->Begin(m_ImageIndex);
}

void CVulkanRenderer::DrawFrame(const SCommandBuffer& commandBuffer, const PWorld& world)
{
	m_DrawCommandBuffer->SubmitDraw(world, m_ImageIndex);
}

void CVulkanRenderer::EndFrame(const SCommandBuffer& commandBuffer)
{
	m_Swapchain->EndRenderPass(commandBuffer);
	m_DrawCommandBuffer->End(m_ImageIndex);
	Accessors::Swapchain::SubmitCommandBuffers(m_Swapchain, CCast<VkCommandBuffer*>(&commandBuffer), &m_ImageIndex);
}

void CVulkanRenderer::Shutdown(const PWorld& world)
{
	m_Device->WaitReleaseResources();

	auto renderable_objs = world->FindGameObjectsWithComponent<SComponentRenderable>(); // all renderables MUST have a transform component!!!
	for (auto renderable_obj : renderable_objs)
	{
		auto rrc = renderable_obj->GetComponent<SComponentRenderable>();
		rrc->Geometry.Release();
	}

	DefaultVertexBuffer.reset();
	DefaultIndexBuffer.reset();

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
		PSwapchain oldSwapchain = std::move(m_Swapchain);
		m_Swapchain = CSwapchain::Create(m_Device, newExtent, oldSwapchain.get());
		if (!oldSwapchain->CompareFormats(m_Swapchain))
			throw std::runtime_error("Swapchain image or depth format is changed!!!");
	}
	CreatePipeline();
}

void CVulkanRenderer::CreatePipeline()
{
	m_Pipeline = CPipeline::Create("Default", m_Device, m_Swapchain);
}

PIndexBuffer CVulkanRenderer::CreateIndexBuffer(const List<UInt32> &indices) {
	return CIndexBuffer::Create(m_Device, indices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const List<SVertex> &vertices) {
	return CGeometryData::Create(m_Device, vertices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const List<SVertex> &vertices, const List<UInt32> &indices) {
	return CGeometryData::Create(m_Device, vertices, indices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const SGeometryDataCreateInfo &createInfo)
{
	if (createInfo.pIndices)
		return CGeometryData::Create(m_Device, *createInfo.pVertices, *createInfo.pIndices);
	else
		return CGeometryData::Create(m_Device, *createInfo.pVertices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const PVertexBuffer &vertexBuffer) {
	return CGeometryData::Create(m_Device, vertexBuffer);
}

CGeometryData
CVulkanRenderer::CreateGeometryData(const PVertexBuffer &vertexBuffer, const PIndexBuffer &indexBuffer) {
	return CGeometryData::Create(m_Device, vertexBuffer, indexBuffer);
}

VISRCEND
