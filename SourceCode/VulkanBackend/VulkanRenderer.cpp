//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanRenderer.hpp"

#include "../Accessors/ADescriptorWriter.hpp"
#include "../Accessors/AVertexBuffer.hpp"
#include "../Accessors/AUniformBuffer.hpp"

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
	m_Context->CmdCreate(m_Swapchain->GetImageCount());

	m_SubPasses[0] = RenderSubrender::CreateDefaultSubrender(m_Context, m_MainRenderPass, m_GlobalDescriptorSetLayout);
	m_SubPasses[1] = RenderSubrender::CreatePointLightSubrender(m_Context, m_MainRenderPass, m_GlobalDescriptorSetLayout);

	DefaultVertexBuffer = VertexBuffer::Create(m_Context, DefaultVertices);
	DefaultIndexBuffer  = IndexBuffer ::Create(m_Context, DefaultIndices);
}

PVertexBuffer CVulkanRenderer::CreateVertexBuffer(const CSet<SVertex> &vertices)
{
	return VertexBuffer::Create(m_Context, vertices);
}

SFrameInfo CVulkanRenderer::BeginFrame()
{
	auto result = CCast<VkResult>(m_Swapchain->AcquireNextImage(&m_ImageIndex));
	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		RecreateSwapchain(m_Window->GetExtent());
		return {};
	}
	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		ViAbort("Failed to acquire next image!");

	SCommandBuffer commandBuffer = m_Context->CmdBegin(m_ImageIndex);

	return { commandBuffer,
			 m_GlobalDescriptorSets[m_Swapchain->GetFrameIndex()],
			 m_ImageIndex,
			 m_Swapchain->GetFrameIndex(),
			 m_Swapchain->GetExtentAspectRatio(),
			 m_Swapchain->GetFramebuffers()[m_ImageIndex] };
}

void CVulkanRenderer::DrawFrame(SFrameInfo& frameInfo, const PWorld& world)
{
	for (auto& subpass : m_SubPasses) {
		subpass->Compute(frameInfo, world);
	}
	// end computations
	auto& constantBuffer = world->GetConstantsBuffer(frameInfo.FrameIndex);
	constantBuffer->SubmitToGPU(frameInfo.Constants);


	m_MainRenderPass->Begin(frameInfo);

	for (auto& subpass : m_SubPasses) {
		subpass->Pass(frameInfo, world);
	}

	m_MainRenderPass->End(frameInfo);
}

void CVulkanRenderer::EndFrame(const SFrameInfo& frameInfo)
{
	m_Context->CmdEnd(frameInfo.CommandBuffer);
	m_Swapchain->CmdSubmit(&frameInfo.CommandBuffer, &m_ImageIndex);
}

void CVulkanRenderer::Shutdown(const PWorld& world)
{
	m_Context->WaitGPUReady();

	auto rrls = world->AllWith<SComponentRenderable>();
	for (auto rrl : rrls)
	{
		auto rrc = rrl->GetComponent<SComponentRenderable>();
		rrc->Geometry.Release();
	}

	DefaultVertexBuffer.Reset();
	DefaultIndexBuffer.Reset();

	world->Clear();
}

void CVulkanRenderer::OnWindowResize(const SExtent2D &extent) {
	RecreateSwapchain(extent);
}

void CVulkanRenderer::RecreateSwapchain(const SExtent2D &newExtent) {
	if (!newExtent.Width || !newExtent.Height) {
		m_Window->WaitForEvents();
		return;
	}

	m_Context->WaitGPUReady();

	if (!m_Swapchain)
		m_Swapchain = CSwapchain::Create(m_Context, newExtent);
	else
	{
		auto oldSwapchain = FMove(m_Swapchain);
		m_Swapchain = Swapchain::Create(m_Context, newExtent, oldSwapchain.Get());
		if (!oldSwapchain->CompareFormats(m_Swapchain))
			ViAbort("Swapchain image or depth format is changed!!!");
	}

	// main renderpass is depends on swapchain, in this case recreate this too.
	SRenderPassCreateInfo renderPassCreateInfo = {};
	renderPassCreateInfo.Extent = newExtent;
	renderPassCreateInfo.ClearColor = {0.005F, 0.005F, 0.005F, 1.0F};
	renderPassCreateInfo.Depth = 1.0F;
	renderPassCreateInfo.Stencil = 0;

	m_MainRenderPass = RenderPass::Create(m_Context, m_Swapchain, renderPassCreateInfo);

	// then recreate framebuffers

	m_Swapchain->CreateFramebuffers(m_MainRenderPass);

	if (m_GlobalDescriptorSetLayout)
	{
		m_SubPasses[0] = RenderSubrender::CreateDefaultSubrender(m_Context, m_MainRenderPass,
		                                                          m_GlobalDescriptorSetLayout);
		m_SubPasses[1] = RenderSubrender::CreatePointLightSubrender(m_Context, m_MainRenderPass,
		                                                             m_GlobalDescriptorSetLayout);
	}
}


PIndexBuffer CVulkanRenderer::CreateIndexBuffer(const CSet<UInt32> &indices) {
	return IndexBuffer::Create(m_Context, indices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const CSet<SVertex> &vertices) {
	return CGeometryData::Create(m_Context, vertices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const CSet<SVertex> &vertices, const CSet<UInt32> &indices) {
	return CGeometryData::Create(m_Context, vertices, indices);
}

CGeometryData CVulkanRenderer::CreateGeometryData(const SGeometryDataCreateInfo &createInfo)
{
	if (!createInfo.Indices.Empty())
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

void CVulkanRenderer::BeginUIFrame() {}

void CVulkanRenderer::EndUIFrame(SCommandBuffer commandBuffer) {}

PUniformBuffer CVulkanRenderer::CreateUniformBuffer() {
	 return UniformBuffer::Create(m_Context, 1);
}

void CVulkanRenderer::CreateDescriptors() {
	SDescriptorPoolCreateInfo poolCreateInfo =
			 SDescriptorPoolCreateInfo()
			.SetMaxSets(m_Swapchain->GetMaxFramesInFlight())
			.AddPoolSize(SDescriptorPoolSize(DescriptorTypeUniformBuffer, m_Swapchain->GetMaxFramesInFlight()));

	m_GlobalPool = DescriptorPool::Create(m_Context, poolCreateInfo);
}

void CVulkanRenderer::CreateDescriptorSetLayout() {
	auto layoutCreateInfo =
			 SDescriptorSetLayoutCreateInfo()
			.AddBinding(0, DescriptorTypeUniformBuffer, ShaderStageAllStages);

	m_GlobalDescriptorSetLayout = DescriptorSetLayout::Create(m_Context, layoutCreateInfo);
}

void CVulkanRenderer::CreateDescriptors(const PWorld &world) {
	m_GlobalDescriptorSets.Resize(m_Swapchain->GetMaxFramesInFlight());
	for (UInt32 i = 0; i < m_GlobalDescriptorSets.Size(); i++)
	{
		auto& rcb = world->GetConstantsBuffer(i);
		auto bufferInfo = Accessors::UniformBuffer::GetDescriptorBufferInfo(rcb);
		PDescriptorWriter writer = DescriptorWriter::Create(m_GlobalPool, m_GlobalDescriptorSetLayout);
		Accessors::DescriptorWriter::WriteBuffer(writer, 0, &bufferInfo);
		writer->Build(m_GlobalDescriptorSets[i]);
	}
}

VISRCEND
