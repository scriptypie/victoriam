//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_VULKANRENDERER_HPP
#define VICTORIAM_VULKANRENDERER_HPP

#include <Victoriam/Graphics/GRenderer.hpp>

#include "VulkanDevice.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanPipeline.hpp"
#include "VulkanDrawCommandBuffer.hpp"

#include "Accessors/ADrawCommandBuffer.hpp"

VISRCBEG

class cVulkanRenderer : public cRenderer {
	VIDECL pDevice m_Device = {};
	VIDECL pSwapchain m_Swapchain = {};
	VIDECL pPipeline m_Pipeline = {};
	VIDECL pDrawCommandBuffer m_DrawCommandBuffer = {};
	VIDECL List<pVertexBuffer> m_VertexBuffers = {};
	VIDECL pWindow m_Window = {};
public:
	explicit cVulkanRenderer(const sRendererCreateInfo& createInfo);
	~cVulkanRenderer() override;

	void Setup() override;
	void PushVertexBuffer(const List<sVertex>& vertices) override;

	void OnWindowResize(const sWindowExtent& extent) override;
	void DrawFrame() override;
	void Shutdown() override;
private:
	void BeginFrame();
	void EndFrame();

	void CreatePipeline();
	void RecreateSwapchain(const sWindowExtent& newExtent);
};

VISRCEND

#endif //VICTORIAM_VULKANRENDERER_HPP
