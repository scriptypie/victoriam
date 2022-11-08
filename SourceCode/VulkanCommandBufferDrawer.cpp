//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanCommandBufferDrawer.hpp"

#include <Victoriam/Graphics/Structs/GMaterialData.hpp>
#include <Victoriam/Graphics/GCamera.hpp>

VISRCBEG

CVulkanCommandBufferDrawer::CVulkanCommandBufferDrawer(PSwapchain &swapchain, PGraphicsContext& context, PPipeline& pipeline)
	: m_Swapchain(swapchain), m_Context(context), m_Pipeline(pipeline)
{
	CreateCommandBuffers();
}

CVulkanCommandBufferDrawer::~CVulkanCommandBufferDrawer()
{
	vkFreeCommandBuffers(
			Accessors::GraphicsContext::GetDevice(m_Context),
			Accessors::GraphicsContext::GetCommandPool(m_Context),
			CCast<UInt32>(m_CommandBuffers.size()),
	        m_CommandBuffers.data());

	m_CommandBuffers.clear();
}

void CVulkanCommandBufferDrawer::CreateCommandBuffers()
{
	m_CommandBuffers.resize(m_Swapchain->GetImageCount());

	VkCommandBufferAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocateInfo.commandPool = Accessors::GraphicsContext::GetCommandPool(m_Context);
	allocateInfo.commandBufferCount = CCast<UInt32>(m_CommandBuffers.size());

	if (vkAllocateCommandBuffers(Accessors::GraphicsContext::GetDevice(m_Context), &allocateInfo, m_CommandBuffers.data()) != VK_SUCCESS)
		ViAbort("Failed to allocate command buffers!");
}

SCommandBuffer CVulkanCommandBufferDrawer::Begin(const PWorld& world, const UInt32& imageIndex)
{
	VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
	if (vkBeginCommandBuffer(m_CommandBuffers.at(imageIndex), &beginInfo) != VK_SUCCESS)
		ViAbort("Failed to call vkBeginCommandBuffer()");

	auto sunobj = world->OneWith<SComponentSun>(); // There CAN be single one on a scene
	auto rendererSettings = world->GetRendererSettings(); // as well as renderer settings

	CCamera* mainCamera = nullptr;
	auto cam_obj = world->OneWith<SComponentCamera, SComponentTransform>();
	auto [componentCamera, componentTransform] = cam_obj->Group<SComponentCamera, SComponentTransform>();
	if (componentCamera->Primary) {
		componentCamera->Camera.SetPerspective(m_Swapchain->GetExtentAspectRatio());
		componentCamera->Camera.SetViewMatrix(glm::lookAt(componentTransform->Translation,
		                                                  componentTransform->Translation + componentCamera->Camera.Front(),
		                                                  componentCamera->Camera.Up()));
		mainCamera = &componentCamera->Camera;
	}

	// submit constants buffer
	SRendererConstants constants = {};
	constants.SunDirection = sunobj ? SVector4(-sunobj->GetComponent<SComponentSun>()->Direction, 1.0F) : SVector4();
	constants.Ambient = rendererSettings.Ambient;
	constants.Brightness = rendererSettings.Brightness;
	constants.ProjectionView = mainCamera->GetViewProjection();

	auto& constantBuffer = world->GetConstantsBuffer(m_Swapchain->GetFrameIndex());
	constantBuffer->SubmitUniformBuffer(constants);

	m_Swapchain->BeginRenderPass(CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex)), imageIndex);

	return CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex));
}

void CVulkanCommandBufferDrawer::End(const SCommandBuffer& commandBuffer) const
{
	if (vkEndCommandBuffer(CCast<VkCommandBuffer>(commandBuffer)) != VK_SUCCESS)
		ViAbort("Failed to record command buffer!");
}

void CVulkanCommandBufferDrawer::SubmitDraw(const PWorld& world, const SFrameInfo& frameInfo) const
{
	m_Pipeline->BindCommandBuffer(frameInfo.CommandBuffer);
	m_Pipeline->BindConstantsDescriptorSet(BindPointGraphics, frameInfo);

	auto renderable_objs = world->AllWith<SComponentRenderable, SComponentTransform>(); // all renderables MUST have a transform component!!!
	for (auto renderable_obj: renderable_objs) {
		auto [rrc, rtc] = renderable_obj->Group<SComponentRenderable, SComponentTransform>();

		if (!rrc->Geometry.Empty()) {
			SMaterialData materialData = {};
			materialData.ModelMatrix = rtc->Transform();
			m_Pipeline->PushMaterialData(CCast<SCommandBuffer>(frameInfo.CommandBuffer), 0, &materialData);
			rrc->Geometry.SubmitDraw(CCast<SCommandBuffer>(frameInfo.CommandBuffer));
		}
	}
}

VISRCEND
