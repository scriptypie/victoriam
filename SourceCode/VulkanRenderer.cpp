//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanRenderer.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_vulkan.h>

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
	m_CommandBufferDrawer = CCommandBufferDrawer::Create(m_Swapchain, m_Device, m_Pipeline);

	DefaultVertexBuffer = CBuffer::CreateVertexBuffer(m_Device, DefaultVertices);
	DefaultIndexBuffer  = CBuffer ::CreateIndexBuffer(m_Device, DefaultIndices);

	/*
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	VIGNORE io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	ImGui_ImplGlfw_InitForVulkan(Accessors::Window::GetGLFWWindow(m_Window), true);
	ImGui_ImplVulkan_InitInfo createInfo = {};
	createInfo.Instance = Accessors::Device::GetInstance(m_Device);
	createInfo.PhysicalDevice = Accessors::Device::GetPhysicalDevice(m_Device);
	createInfo.Device = Accessors::Device::GetDevice(m_Device);
	createInfo.QueueFamily = Accessors::Device::FindQueueFamilies(m_Device).GraphicsFamily;
	createInfo.Queue = Accessors::Device::GetGraphicsQueue(m_Device);
	createInfo.PipelineCache = VK_NULL_HANDLE;
	createInfo.MinImageCount = 2;
	createInfo.ImageCount = m_Swapchain->GetImageCount();

	ImGui_ImplVulkan_Init(&createInfo, Accessors::Swapchain::GetRenderPass(m_Swapchain));
	*/
}

PBuffer CVulkanRenderer::CreateVertexBuffer(const List<SVertex> &vertices)
{
	return CBuffer::CreateVertexBuffer(m_Device, vertices);
}

CVulkanRenderer::~CVulkanRenderer() = default;

SFrameInfo CVulkanRenderer::BeginFrame(const PWorld& world)
{
	auto result = CCast<VkResult>(m_Swapchain->AcquireNextImage(&m_ImageIndex));
	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		RecreateSwapchain(m_Window->GetExtent());
		return { nullptr };
	}
	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		throw std::runtime_error("Failed to acquire next image!");

	return {m_CommandBufferDrawer->Begin(world, m_ImageIndex)};
}

void CVulkanRenderer::DrawFrame(const SFrameInfo& frameInfo, const PWorld& world)
{
	m_CommandBufferDrawer->SubmitDraw(world, m_ImageIndex);
}

void CVulkanRenderer::EndFrame(const SFrameInfo& frameInfo)
{
	m_Swapchain->EndRenderPass(frameInfo.CommandBuffer);
	m_CommandBufferDrawer->End(m_ImageIndex);
	Accessors::Swapchain::SubmitCommandBuffers(m_Swapchain, CCast<VkCommandBuffer*>(&frameInfo.CommandBuffer), &m_ImageIndex);
}

void CVulkanRenderer::Shutdown(const PWorld& world)
{
	m_Device->WaitReleaseResources();
	/*
	ImGui_ImplVulkan_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	*/
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

PBuffer CVulkanRenderer::CreateIndexBuffer(const List<UInt32> &indices) {
	return CBuffer::CreateIndexBuffer(m_Device, indices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const List<SVertex> &vertices) {
	return CGeometryData::Create(m_Device, vertices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const List<SVertex> &vertices, const List<UInt32> &indices) {
	return CGeometryData::Create(m_Device, vertices, indices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const SGeometryDataCreateInfo &createInfo)
{
	if (!createInfo.Indices.empty())
		return CGeometryData::Create(m_Device, createInfo.Vertices, createInfo.Indices);
	else
		return CGeometryData::Create(m_Device, createInfo.Vertices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const PBuffer &vertexBuffer) {
	return CGeometryData::Create(m_Device, vertexBuffer);
}

CGeometryData
CVulkanRenderer::CreateGeometryData(const PBuffer &vertexBuffer, const PBuffer &indexBuffer) {
	return CGeometryData::Create(m_Device, vertexBuffer, indexBuffer);
}

void CVulkanRenderer::BeginUIFrame()
{

}

void CVulkanRenderer::EndUIFrame()
{

}

PBuffer CVulkanRenderer::CreateUniformBuffer() {
	return CBuffer::CreateUniformBuffer(m_Device, m_Swapchain);
}

VISRCEND
