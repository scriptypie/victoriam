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
	VIDECL VIREQOUT PVertexBuffer CreateVertexBuffer(const List<SVertex>& vertices) override;
	VIDECL VIREQOUT PIndexBuffer CreateIndexBuffer(const List<UInt32>& indices) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const List<SVertex>& vertices) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const List<SVertex>& vertices, const List<UInt32>& indices) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const PVertexBuffer& vertexBuffer) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const PVertexBuffer& vertexBuffer, const PIndexBuffer& indexBuffer) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const SGeometryDataCreateInfo& createInfo) override;

	void OnWindowResize(const SWindowExtent& extent) override;
	SCommandBuffer BeginFrame() override;
	void DrawFrame(const SCommandBuffer& commandBuffer, const PWorld& world) override;
	void EndFrame(const SCommandBuffer& commandBuffer) override;
	void BeginUIFrame() override;
	void EndUIFrame() override;
	void Shutdown(const PWorld& world) override;
private:
	void CreatePipeline();
	void RecreateSwapchain(const SWindowExtent& newExtent);
};

VISRCEND

#endif //VICTORIAM_VULKANRENDERER_HPP
