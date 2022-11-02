//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_VULKANRENDERER_HPP
#define VICTORIAM_VULKANRENDERER_HPP

#include <Victoriam/Graphics/GRenderer.hpp>

#include "VulkanDevice.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanPipeline.hpp"
#include "VulkanCommandBufferDrawer.hpp"

#include "Accessors/ACommandBufferDrawer.hpp"

VISRCBEG

class CVulkanRenderer : public CRenderer {
	VIDECL PDevice m_Device = {};
	VIDECL PSwapchain m_Swapchain = {};
	VIDECL PPipeline m_Pipeline = {};
	VIDECL PDrawCommandBuffer m_CommandBufferDrawer = {};
	VIDECL PWindow m_Window = {};
	VIDECL UInt32 m_ImageIndex = {};
public:
	explicit CVulkanRenderer(const SRendererCreateInfo& createInfo);
	~CVulkanRenderer() override;

	void Setup() override;
	VIDECL VIREQOUT PBuffer CreateVertexBuffer(const List<SVertex>& vertices) override;
	VIDECL VIREQOUT PBuffer CreateIndexBuffer(const List<UInt32>& indices) override;
	VIDECL VIREQOUT PBuffer CreateUniformBuffer() override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const List<SVertex>& vertices) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const List<SVertex>& vertices, const List<UInt32>& indices) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const PBuffer& vertexBuffer) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const PBuffer& vertexBuffer, const PBuffer& indexBuffer) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const SGeometryDataCreateInfo& createInfo) override;

	void OnWindowResize(const SWindowExtent& extent) override;
	SFrameInfo BeginFrame(const PWorld& world) override;
	void DrawFrame(const SFrameInfo& frameInfo, const PWorld& world) override;
	void EndFrame(const SFrameInfo& frameInfo) override;
	void BeginUIFrame() override;
	void EndUIFrame() override;
	void Shutdown(const PWorld& world) override;
private:
	void CreatePipeline();
	void RecreateSwapchain(const SWindowExtent& newExtent);
};

VISRCEND

#endif //VICTORIAM_VULKANRENDERER_HPP
