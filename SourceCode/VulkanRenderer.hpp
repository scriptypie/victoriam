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

class CVulkanRenderer : public CRenderer {
	VIDECL PDevice m_Device = {};
	VIDECL PSwapchain m_Swapchain = {};
	VIDECL PPipeline m_Pipeline = {};
	VIDECL PDrawCommandBuffer m_DrawCommandBuffer = {};
	VIDECL PWindow m_Window = {};
	VIDECL UInt32 m_ImageIndex = {};
public:
	explicit CVulkanRenderer(const SRendererCreateInfo& createInfo);
	~CVulkanRenderer() override;

	void Setup() override;
	PVertexBuffer CreateVertexBuffer(const List<SVertex>& vertices) override;

	void OnWindowResize(const SWindowExtent& extent) override;
	SCommandBuffer BeginFrame() override;
	void DrawFrame(const SCommandBuffer& commandBuffer, const PWorld& world) override;
	void EndFrame(const SCommandBuffer& commandBuffer) override;
	void Shutdown(const PWorld& world) override;
private:
	void CreatePipeline();
	void RecreateSwapchain(const SWindowExtent& newExtent);
};

VISRCEND

#endif //VICTORIAM_VULKANRENDERER_HPP
