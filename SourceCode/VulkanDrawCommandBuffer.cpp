//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanDrawCommandBuffer.hpp"

#include <Victoriam/Graphics/Structs/GMaterialData.hpp>
#include <Victoriam/Graphics/GCamera.hpp>

VISRCBEG

CVulkanDrawCommandBuffer::CVulkanDrawCommandBuffer(PSwapchain &swapchain, PDevice& device, PPipeline& pipeline)
	: m_Swapchain(swapchain), m_Device(device), m_Pipeline(pipeline)
{
	CreateCommandBuffers();
}

CVulkanDrawCommandBuffer::~CVulkanDrawCommandBuffer()
{
	vkFreeCommandBuffers(Accessors::Device::GetDevice(m_Device), Accessors::Device::GetCommandPool(m_Device), CCast<UInt32>(m_CommandBuffers.size()), m_CommandBuffers.data());
	m_CommandBuffers.clear();
}

void CVulkanDrawCommandBuffer::CreateCommandBuffers()
{
	m_CommandBuffers.resize(m_Swapchain->GetImageCount());

	VkCommandBufferAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocateInfo.commandPool = Accessors::Device::GetCommandPool(m_Device);
	allocateInfo.commandBufferCount = CCast<UInt32>(m_CommandBuffers.size());

	if (vkAllocateCommandBuffers(Accessors::Device::GetDevice(m_Device), &allocateInfo, m_CommandBuffers.data()) != VK_SUCCESS)
		throw std::runtime_error("Failed to allocate command buffers!");
}

SCommandBuffer CVulkanDrawCommandBuffer::Begin(UInt32 imageIndex)
{
	VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
	if (vkBeginCommandBuffer(m_CommandBuffers.at(imageIndex), &beginInfo) != VK_SUCCESS)
		throw std::runtime_error("Failed to call vkBeginCommandBuffer()");

	m_Swapchain->BeginRenderPass(CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex)), imageIndex);

	return CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex));
}

void CVulkanDrawCommandBuffer::End(UInt32 imageIndex)
{
	if (vkEndCommandBuffer(m_CommandBuffers.at(imageIndex)) != VK_SUCCESS)
		throw std::runtime_error("Failed to record command buffer!");
}

void CVulkanDrawCommandBuffer::SubmitDraw(const PWorld& world, UInt32 imageIndex)
{
	m_Pipeline->BindDrawCommandBuffer(CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex)));

	CCamera* mainCamera = nullptr;
	auto camera_objs = world->FindGameObjectsWithComponent<SComponentCamera>();
	for (auto cam_obj : camera_objs)
	{
		auto componentCamera = cam_obj->GetComponent<SComponentCamera>();

		componentCamera->Camera.SetPerspective(glm::radians(65.0F), m_Swapchain->GetExtentAspectRatio());

		auto componentTransform = cam_obj->GetComponent<SComponentTransform>();

		if (componentCamera->Primary) {
			if (!mainCamera) {
				auto view = glm::lookAt(componentTransform->Translation, componentTransform->Translation + componentCamera->Camera.Front(), componentCamera->Camera.Up());
				componentCamera->Camera.SetViewMatrix(view);
				mainCamera = &componentCamera->Camera;

			} else {
				ViLog("There is impossible to have a two cameras within the single scene!!!\n");
			}
		}
	}

	if (mainCamera)
	{
		auto renderable_objs = world->FindGameObjectsWithComponent<SComponentRenderable>(); // all renderables MUST have a transform component!!!
		for (auto renderable_obj: renderable_objs) {
			auto rrc = renderable_obj->GetComponent<SComponentRenderable>();
			auto rtc = renderable_obj->GetComponent<SComponentTransform>();
			// rtc.Rotation.y = glm::mod(rtc.Rotation.y + 0.01F, glm::two_pi<Float32>());
			// rtc.Rotation.x = glm::mod(rtc.Rotation.x + 0.01F, glm::two_pi<Float32>());
			// rtc.Rotation.z = glm::mod(rtc.Rotation.z + 0.01F, glm::two_pi<Float32>());

			if (!rrc->Geometry.Empty()) {
				SMaterialData materialData = {};
				materialData.Transform = rtc->Transform();
				materialData.ViewProjection = mainCamera->GetViewProjection();
				materialData.Color = SVector4(rrc->Color, 1.0f);
				m_Pipeline->PushSharedMaterialData(CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex)), 0,
				                                   &materialData);
				rrc->Geometry.SubmitDraw(CCast<SCommandBuffer>(m_CommandBuffers.at(imageIndex)));
			}
		}
	}
}

VISRCEND
