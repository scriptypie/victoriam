//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanCommandBufferDrawer.hpp"

#include <Victoriam/Graphics/Structs/GMaterialData.hpp>
#include <Victoriam/Graphics/GCamera.hpp>

VISRCBEG

CVulkanCommandBufferDrawer::CVulkanCommandBufferDrawer(PSwapchain &swapchain, PDevice& device, PPipeline& pipeline)
	: m_Swapchain(swapchain), m_Device(device), m_Pipeline(pipeline)
{
	CreateCommandBuffers();
}

CVulkanCommandBufferDrawer::~CVulkanCommandBufferDrawer()
{
	vkFreeCommandBuffers(Accessors::Device::GetDevice(m_Device), Accessors::Device::GetCommandPool(m_Device), CCast<UInt32>(m_CommandBuffers.size()), m_CommandBuffers.data());
	m_CommandBuffers.clear();
}

void CVulkanCommandBufferDrawer::CreateCommandBuffers()
{
	m_CommandBuffers.resize(m_Swapchain->GetImageCount());

	VkCommandBufferAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocateInfo.commandPool = Accessors::Device::GetCommandPool(m_Device);
	allocateInfo.commandBufferCount = CCast<UInt32>(m_CommandBuffers.size());

	if (vkAllocateCommandBuffers(Accessors::Device::GetDevice(m_Device), &allocateInfo, m_CommandBuffers.data()) != VK_SUCCESS)
		throw std::runtime_error("Failed to allocate command buffers!");
}

SCommandBuffer CVulkanCommandBufferDrawer::Begin(const PWorld& world, UInt32 imageIndex)
{
	VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
	if (vkBeginCommandBuffer(m_CommandBuffers.at(imageIndex), &beginInfo) != VK_SUCCESS)
		throw std::runtime_error("Failed to call vkBeginCommandBuffer()");

	auto sunobj = world->OneWith<SComponentSun>(); // There CAN be single one on a scene
	auto rendererSettings = world->GetRendererSettings(); // as well as renderer settings

	CCamera* mainCamera = nullptr;
	auto cam_obj = world->OneWith<SComponentCamera>();
	auto componentCamera = cam_obj->GetComponent<SComponentCamera>();
	if (componentCamera->Primary) {
		mainCamera = &componentCamera->Camera;
	}

	// submit constant buffer
	SRendererConstants constants = {};
	constants.SunDirection = sunobj ? -sunobj->GetComponent<SComponentSun>()->Direction : SVector3{};
	constants.Ambient = rendererSettings.Ambient;
	constants.Brightness = rendererSettings.Brightness;
	constants.ProjectionView = mainCamera->GetViewProjection();

	auto& constantBuffer = world->GetConstantBuffer();
	constantBuffer->SubmitUniformBuffer(&constants, m_Swapchain->GetFrameIndex());

	m_Swapchain->BeginRenderPass(CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex)), imageIndex);

	return CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex));
}

void CVulkanCommandBufferDrawer::End(UInt32 imageIndex)
{
	if (vkEndCommandBuffer(m_CommandBuffers.at(imageIndex)) != VK_SUCCESS)
		throw std::runtime_error("Failed to record command buffer!");
}

void CVulkanCommandBufferDrawer::SubmitDraw(const PWorld& world, UInt32 imageIndex)
{
	m_Pipeline->BindDrawCommandBuffer(CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex)));

	CCamera* mainCamera = nullptr;
	auto cam_obj = world->OneWith<SComponentCamera>();
	auto [componentCamera, componentTransform] = cam_obj->Group<SComponentCamera, SComponentTransform>();
	componentCamera->Camera.SetPerspective(glm::radians(65.0F), m_Swapchain->GetExtentAspectRatio());
	if (componentCamera->Primary) {
		auto view = glm::lookAt(componentTransform->Translation, componentTransform->Translation + componentCamera->Camera.Front(), componentCamera->Camera.Up());
		componentCamera->Camera.SetViewMatrix(view);
		mainCamera = &componentCamera->Camera;
	}

	if (mainCamera)
	{
		auto renderable_objs = world->AllWith<SComponentRenderable, SComponentTransform>(); // all renderables MUST have a transform component!!!
		for (auto renderable_obj: renderable_objs) {
			auto [rrc, rtc] = renderable_obj->Group<SComponentRenderable, SComponentTransform>();

			if (!rrc->Geometry.Empty()) {
				SMaterialData materialData = {};
				auto modelMatrix = rtc->Transform();
				materialData.Transform = mainCamera->GetViewProjection() * modelMatrix;
				materialData.ModelMatrix = modelMatrix;
				m_Pipeline->PushMaterialData(CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex)), 0, &materialData);
				rrc->Geometry.SubmitDraw(CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex)));
			}
		}
	}
}

VISRCEND
