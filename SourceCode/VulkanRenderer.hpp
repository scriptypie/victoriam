//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_VULKANRENDERER_HPP
#define VICTORIAM_VULKANRENDERER_HPP

#include <Victoriam/Graphics/GRenderer.hpp>
#include <Victoriam/Graphics/GDescriptorWriter.hpp>

#include "VulkanGraphicsContext.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanPipeline.hpp"
#include "VulkanCommandBufferDrawer.hpp"

#include "Accessors/ACommandBufferDrawer.hpp"
#include "Accessors/ADescriptorWriter.hpp"
#include "Accessors/ABuffer.hpp"

VISRCBEG

class VIDECL CVulkanRenderer : public CRenderer {
	VIDECL PGraphicsContext m_Context = {};
	VIDECL PSwapchain m_Swapchain = {};
	VIDECL PPipeline m_Pipeline = {};
	VIDECL PCommandBufferDrawer m_CommandBufferDrawer = {};
	VIDECL PWindow m_Window = {};
	VIDECL PDescriptorPool m_GlobalPool = {};
	VIDECL PDescriptorSetLayout m_GlobalDescriptorSetLayout = {};
	VIDECL List<SDescriptorSet> m_GlobalDescriptorSets = {};
	VIDECL UInt32 m_ImageIndex = {};
public:
	VIDECL explicit CVulkanRenderer(const SRendererCreateInfo& createInfo);
	VIDECL ~CVulkanRenderer() override = default;

	VIDECL          void Setup() override;
	VIDECL VIREQOUT inline PSwapchain& GetSwapchain() override { return m_Swapchain; }
	VIDECL VIREQOUT PBuffer CreateVertexBuffer(const List<SVertex>& vertices) override;
	VIDECL VIREQOUT PBuffer CreateIndexBuffer(const List<UInt32>& indices) override;
	VIDECL VIREQOUT PUniformBuffer CreateUniformBuffer() override;
	VIDECL          void CreateDescriptors(const PWorld& world) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const List<SVertex>& vertices) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const List<SVertex>& vertices, const List<UInt32>& indices) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const PBuffer& vertexBuffer) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const PBuffer& vertexBuffer, const PBuffer& indexBuffer) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const SGeometryDataCreateInfo& createInfo) override;

	VIDECL          void OnWindowResize(const SWindowExtent& extent) override;
	VIDECL VIREQOUT SFrameInfo BeginFrame(const PWorld& world) override;
	VIDECL          void DrawFrame(const SFrameInfo& frameInfo, const PWorld& world) override;
	VIDECL          void EndFrame(const SFrameInfo& frameInfo) override;
	VIDECL          void BeginUIFrame() override;
	VIDECL          void EndUIFrame() override;
	VIDECL          void Shutdown(const PWorld& world) override;
private:
	VIDECL void CreatePipeline(const String& name);
	VIDECL void RecreateSwapchain(const SWindowExtent& newExtent);
	VIDECL void CreateDescriptors();
	VIDECL void CreateDescriptorSetLayout();
};

VISRCEND

#endif //VICTORIAM_VULKANRENDERER_HPP
