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
	m_Context = CGraphicsContext::Create(m_Window);
	RecreateSwapchain(m_Window->GetExtent());
	CreateDescriptorSetLayout();
	CreateDescriptors();
	CreatePipeline("Default");
}

void CVulkanRenderer::Setup()
{
	m_CommandBufferDrawer = CCommandBufferDrawer::Create(m_Swapchain, m_Context, m_Pipeline);

	DefaultVertexBuffer = CBuffer::CreateVertexBuffer(m_Context, DefaultVertices);
	DefaultIndexBuffer  = CBuffer ::CreateIndexBuffer(m_Context, DefaultIndices);

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
	createInfo.Instance = Accessors::GraphicsContext::GetInstance(m_Context);
	createInfo.PhysicalDevice = Accessors::GraphicsContext::GetPhysicalDevice(m_Context);
	createInfo.GraphicsContext = Accessors::GraphicsContext::GetContext(m_Context);
	createInfo.QueueFamily = Accessors::GraphicsContext::FindQueueFamilies(m_Context).GraphicsFamily;
	createInfo.Queue = Accessors::GraphicsContext::GetGraphicsQueue(m_Context);
	createInfo.PipelineCache = VK_NULL_HANDLE;
	createInfo.MinImageCount = 2;
	createInfo.ImageCount = m_Swapchain->GetImageCount();

	ImGui_ImplVulkan_Init(&createInfo, Accessors::Swapchain::GetRenderPass(m_Swapchain));
	*/
}

PBuffer CVulkanRenderer::CreateVertexBuffer(const List<SVertex> &vertices)
{
	return CBuffer::CreateVertexBuffer(m_Context, vertices);
}

SFrameInfo CVulkanRenderer::BeginFrame(const PWorld& world)
{
	auto result = CCast<VkResult>(m_Swapchain->AcquireNextImage(&m_ImageIndex));
	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		RecreateSwapchain(m_Window->GetExtent());
		return {  };
	}
	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		ViAbort("Failed to acquire next image!");

	SCommandBuffer commandBuffer = m_CommandBufferDrawer->Begin(world, m_ImageIndex);

	return { commandBuffer, m_GlobalDescriptorSets[m_Swapchain->GetFrameIndex()], m_ImageIndex };
}

void CVulkanRenderer::DrawFrame(const SFrameInfo& frameInfo, const PWorld& world)
{
	m_CommandBufferDrawer->SubmitDraw(world, frameInfo);
}

void CVulkanRenderer::EndFrame(const SFrameInfo& frameInfo)
{
	m_Swapchain->EndRenderPass(frameInfo.CommandBuffer);
	m_CommandBufferDrawer->End(frameInfo.CommandBuffer);
	Accessors::Swapchain::SubmitCommandBuffers(m_Swapchain, CCast<VkCommandBuffer*>(&frameInfo.CommandBuffer), &m_ImageIndex);
}

void CVulkanRenderer::Shutdown(const PWorld& world)
{
	m_Context->WaitReleaseResources();
	/*
	ImGui_ImplVulkan_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	*/
	auto renderable_objs = world->AllWith<SComponentRenderable>(); // all renderables MUST have a transform component!!!
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

	vkDeviceWaitIdle(Accessors::GraphicsContext::GetDevice(m_Context));

	if (!m_Swapchain)
		m_Swapchain = CSwapchain::Create(m_Context, newExtent);
	else
	{
		PSwapchain oldSwapchain = std::move(m_Swapchain);
		m_Swapchain = CSwapchain::Create(m_Context, newExtent, oldSwapchain.get());
		if (!oldSwapchain->CompareFormats(m_Swapchain))
			ViAbort("Swapchain image or depth format is changed!!!");
	}
	if (m_GlobalDescriptorSetLayout)
		CreatePipeline("Default"); // only if descriptor set layout is exists!!!
}

void CVulkanRenderer::CreatePipeline(const String& name)
{
	m_Pipeline = CPipeline::Create(name, m_Context, m_Swapchain, m_GlobalDescriptorSetLayout);
}

PBuffer CVulkanRenderer::CreateIndexBuffer(const List<UInt32> &indices) {
	return CBuffer::CreateIndexBuffer(m_Context, indices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const List<SVertex> &vertices) {
	return CGeometryData::Create(m_Context, vertices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const List<SVertex> &vertices, const List<UInt32> &indices) {
	return CGeometryData::Create(m_Context, vertices, indices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const SGeometryDataCreateInfo &createInfo)
{
	if (!createInfo.Indices.empty())
		return CGeometryData::Create(m_Context, createInfo.Vertices, createInfo.Indices);
	else
		return CGeometryData::Create(m_Context, createInfo.Vertices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const PBuffer &vertexBuffer) {
	return CGeometryData::Create(vertexBuffer);
}

CGeometryData
CVulkanRenderer::CreateGeometryData(const PBuffer &vertexBuffer, const PBuffer &indexBuffer) {
	return CGeometryData::Create(vertexBuffer, indexBuffer);
}

void CVulkanRenderer::BeginUIFrame()
{

}

void CVulkanRenderer::EndUIFrame()
{

}

PUniformBuffer CVulkanRenderer::CreateUniformBuffer() {
	 return CBuffer::CreateUniformBuffer(m_Context, 1);
}

void CVulkanRenderer::CreateDescriptors() {
	SDescriptorPoolCreateInfo poolCreateInfo =
			 SDescriptorPoolCreateInfo()
			.SetMaxSets(m_Swapchain->GetMaxFramesInFlight())
			.AddPoolSize(SDescriptorPoolSize(DescriptorTypeUniformBuffer, m_Swapchain->GetMaxFramesInFlight()));

	m_GlobalPool = CDescriptorPool::Create(m_Context, poolCreateInfo);
}

void CVulkanRenderer::CreateDescriptorSetLayout() {
	auto layoutCreateInfo =
			 SDescriptorSetLayoutCreateInfo()
			.AddBinding(0, DescriptorTypeUniformBuffer, ShaderStageVertex);

	m_GlobalDescriptorSetLayout = CDescriptorSetLayout::Create(m_Context, layoutCreateInfo);
}

void CVulkanRenderer::CreateDescriptors(const PWorld &world) {
	m_GlobalDescriptorSets.resize(m_Swapchain->GetMaxFramesInFlight());
	for (UInt32 i = 0; i < m_GlobalDescriptorSets.size(); i++)
	{
		auto& rcb = world->GetConstantsBuffer(i);
		auto bufferInfo = Accessors::Buffer::GetDescriptorBufferInfo(rcb);
		PDescriptorWriter writer = CDescriptorWriter::Create(m_GlobalPool, m_GlobalDescriptorSetLayout);
		Accessors::DescriptorWriter::WriteBuffer(writer, 0, &bufferInfo);
		writer->Build(m_GlobalDescriptorSets[i]);
	}
}

VISRCEND
