//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanRenderer.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_vulkan.h>

VISRCBEG

CVulkanRenderer::CVulkanRenderer(const SRendererCreateInfo &createInfo)
	: m_Window(createInfo.WindowPtr), m_SubPasses(2)
{
	m_Context = CGraphicsContext::Create(m_Window);
	RecreateSwapchain(m_Window->GetExtent());
	CreateDescriptorSetLayout();
	CreateDescriptors();
}

void CVulkanRenderer::Setup()
{
	m_CmdBufferSolver = CCmdBufferSolver::Create(m_Swapchain, m_Context);

	m_SubPasses[0] = CRenderSubrender::CreateDefaultSubrender(m_Context, m_Swapchain, m_GlobalDescriptorSetLayout);
	m_SubPasses[1] = CRenderSubrender::CreatePointLightSubrender(m_Context, m_Swapchain, m_GlobalDescriptorSetLayout);

	DefaultVertexBuffer = CVertexBuffer::Create(m_Context, DefaultVertices);
	DefaultIndexBuffer  = CIndexBuffer ::Create(m_Context, DefaultIndices);

}

PVertexBuffer CVulkanRenderer::CreateVertexBuffer(const CList<SVertex> &vertices)
{
	return CVertexBuffer::Create(m_Context, vertices);
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

	SCommandBuffer commandBuffer = m_CmdBufferSolver->Begin(world, m_ImageIndex);

	return { commandBuffer,
			 m_GlobalDescriptorSets[m_Swapchain->GetFrameIndex()],
			 m_ImageIndex,
			 m_Swapchain->GetFrameIndex(),
			 m_Swapchain->GetExtentAspectRatio() };
}

void CVulkanRenderer::DrawFrame(SFrameInfo& frameInfo, const PWorld& world)
{
	for (auto& subpass : m_SubPasses) {
		subpass->Compute(frameInfo, world);
	}

	// end computations
	auto& constantBuffer = world->GetConstantsBuffer(frameInfo.FrameIndex);
	constantBuffer->SubmitToGPU(frameInfo.Constants);

	m_Swapchain->BeginRenderPass(frameInfo.CommandBuffer, frameInfo.ImageIndex);

	for (auto& subpass : m_SubPasses) {
		subpass->Pass(frameInfo, world);
	}

	m_Swapchain->EndRenderPass(frameInfo.CommandBuffer);
}

void CVulkanRenderer::EndFrame(const SFrameInfo& frameInfo)
{
	m_CmdBufferSolver->End(frameInfo.CommandBuffer);
	Accessors::Swapchain::SubmitCommandBuffers(m_Swapchain, CCast<VkCommandBuffer*>(&frameInfo.CommandBuffer), &m_ImageIndex);
}

void CVulkanRenderer::Shutdown(const PWorld& world)
{
	m_Context->WaitReleaseResources();

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
		{
			m_SubPasses[0] = CRenderSubrender::CreateDefaultSubrender(m_Context, m_Swapchain,
			                                                          m_GlobalDescriptorSetLayout);
			m_SubPasses[1] = CRenderSubrender::CreatePointLightSubrender(m_Context, m_Swapchain,
			                                                             m_GlobalDescriptorSetLayout);
		}
}


PIndexBuffer CVulkanRenderer::CreateIndexBuffer(const CList<UInt32> &indices) {
	return CIndexBuffer::Create(m_Context, indices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const CList<SVertex> &vertices) {
	return CGeometryData::Create(m_Context, vertices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const CList<SVertex> &vertices, const CList<UInt32> &indices) {
	return CGeometryData::Create(m_Context, vertices, indices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const SGeometryDataCreateInfo &createInfo)
{
	if (!createInfo.Indices.empty())
		return CGeometryData::Create(m_Context, createInfo.Vertices, createInfo.Indices);
	else
		return CGeometryData::Create(m_Context, createInfo.Vertices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const PVertexBuffer &vertexBuffer) {
	return CGeometryData::Create(vertexBuffer);
}

CGeometryData
CVulkanRenderer::CreateGeometryData(const PVertexBuffer &vertexBuffer, const PIndexBuffer &indexBuffer) {
	return CGeometryData::Create(vertexBuffer, indexBuffer);
}

void CVulkanRenderer::BeginUIFrame()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void CVulkanRenderer::EndUIFrame(SCommandBuffer commandBuffer)
{
	ImGuiIO& io = ImGui::GetIO();

	auto extent = m_Window->GetExtent();
	io.DisplaySize = {CCast<Float32>(extent.Width), CCast<Float32>(extent.Height)};
	io.DisplayFramebufferScale = { 1.0F, 1.0F };

	ImGui::Render();
	ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), CCast<VkCommandBuffer>(commandBuffer));

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

}

PUniformBuffer CVulkanRenderer::CreateUniformBuffer() {
	 return CUniformBuffer::Create(m_Context, 1);
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
			.AddBinding(0, DescriptorTypeUniformBuffer, ShaderStageAllStages);

	m_GlobalDescriptorSetLayout = CDescriptorSetLayout::Create(m_Context, layoutCreateInfo);
}

void CVulkanRenderer::CreateDescriptors(const PWorld &world) {
	m_GlobalDescriptorSets.resize(m_Swapchain->GetMaxFramesInFlight());
	for (UInt32 i = 0; i < m_GlobalDescriptorSets.size(); i++)
	{
		auto& rcb = world->GetConstantsBuffer(i);
		auto bufferInfo = Accessors::UniformBuffer::GetDescriptorBufferInfo(rcb);
		PDescriptorWriter writer = CDescriptorWriter::Create(m_GlobalPool, m_GlobalDescriptorSetLayout);
		Accessors::DescriptorWriter::WriteBuffer(writer, 0, &bufferInfo);
		writer->Build(m_GlobalDescriptorSets[i]);
	}
}

VISRCEND
