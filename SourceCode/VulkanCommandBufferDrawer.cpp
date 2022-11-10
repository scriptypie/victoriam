//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include "VulkanCommandBufferDrawer.hpp"

#include <Victoriam/Graphics/Structs/GRendererConstants.hpp>
#include <Victoriam/Graphics/GCamera.hpp>

VISRCBEG

CVulkanCmdBufferSolver::CVulkanCmdBufferSolver(PSwapchain &swapchain, PGraphicsContext& context)
	: m_Swapchain(swapchain), m_Context(context)
{
	CreateCmdBuffers();
}

CVulkanCmdBufferSolver::~CVulkanCmdBufferSolver()
{
	vkFreeCommandBuffers(
			Accessors::GraphicsContext::GetDevice(m_Context),
			Accessors::GraphicsContext::GetCommandPool(m_Context),
			CCast<UInt32>(m_CmdBuffers.size()),
			m_CmdBuffers.data());

	m_CmdBuffers.clear();
}

void CVulkanCmdBufferSolver::CreateCmdBuffers()
{
	m_CmdBuffers.resize(m_Swapchain->GetImageCount());

	VkCommandBufferAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocateInfo.commandPool = Accessors::GraphicsContext::GetCommandPool(m_Context);
	allocateInfo.commandBufferCount = CCast<UInt32>(m_CmdBuffers.size());

	if (vkAllocateCommandBuffers(Accessors::GraphicsContext::GetDevice(m_Context), &allocateInfo, m_CmdBuffers.data()) != VK_SUCCESS)
		ViAbort("Failed to allocate command buffers!");
}

SCommandBuffer CVulkanCmdBufferSolver::Begin(const PWorld& world, const UInt32& imageIndex)
{
	VkCommandBufferBeginInfo beginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
	if (vkBeginCommandBuffer(m_CmdBuffers.at(imageIndex), &beginInfo) != VK_SUCCESS)
		ViAbort("Failed to call vkBeginCommandBuffer()");

	auto sunobj = world->OneWith<SComponentSun>(); // There CAN be single one on a scene
	auto rendererSettings = world->GetRendererSettings(); // as well as renderer settings

	CCamera* mainCamera = nullptr;
	{
		auto cam_obj = world->OneWith<SComponentCamera, SComponentTransform>();
		auto [componentCamera, componentTransform] = cam_obj->Group<SComponentCamera, SComponentTransform>();
		if (componentCamera->Primary) {
			componentCamera->Camera.SetPerspective(m_Swapchain->GetExtentAspectRatio());
			componentCamera->Camera.SetViewMatrix(glm::lookAt(componentTransform->Translation,
			                                                  componentTransform->Translation +
			                                                  componentCamera->Camera.Front(),
			                                                  componentCamera->Camera.Up()));
			mainCamera = &componentCamera->Camera;
		}
	}

	auto lightObj = world->OneWith<SComponentPointLight>();
	auto componentPointLight = lightObj->GetComponent<SComponentPointLight>();
	auto componentTransform = lightObj->GetComponent<SComponentTransform>();

	// submit constants buffer
	SRendererConstants constants = {};
	constants.SunDirection = sunobj ? SVector4(-sunobj->GetComponent<SComponentSun>()->Direction, 1.0F) : SVector4();
	constants.Ambient = rendererSettings.Ambient;
	constants.Brightness = rendererSettings.Brightness;
	constants.Projection = mainCamera->GetProjection();
	constants.View = mainCamera->GetView();
	constants.LightColor = componentPointLight->LightColor;
	constants.LightPosition = SVector4(componentTransform->Translation, 1.0F);

	auto& constantBuffer = world->GetConstantsBuffer(m_Swapchain->GetFrameIndex());
	constantBuffer->SubmitToGPU(constants);

	m_Swapchain->BeginRenderPass(CCast<SCommandBuffer>(m_CmdBuffers.at(imageIndex)), imageIndex);

	return CCast<SCommandBuffer>(m_CmdBuffers.at(imageIndex));
}

void CVulkanCmdBufferSolver::End(const SCommandBuffer& commandBuffer) const
{
	if (vkEndCommandBuffer(CCast<VkCommandBuffer>(commandBuffer)) != VK_SUCCESS)
		ViAbort("Failed to record command buffer!");
}

VISRCEND
