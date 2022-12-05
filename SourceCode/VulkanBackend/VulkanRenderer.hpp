//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_VULKANRENDERER_HPP
#define VICTORIAM_VULKANRENDERER_HPP

#include <Victoriam/Graphics/GRenderer.hpp>
#include <Victoriam/Graphics/GDescriptorWriter.hpp>
#include <Victoriam/Graphics/GRenderSubrender.hpp>
#include <Victoriam/Graphics/GRenderPass.hpp>
#include <Victoriam/Graphics/GIndexBuffer.hpp>
#include <Victoriam/Graphics/GVertexBuffer.hpp>

#include "VulkanGraphicsContext.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanPipeline.hpp"

VISRCBEG

class VIDECL CVulkanRenderer : public CRenderer {
	VIDECL PGraphicsContext m_Context = {};
	VIDECL PSwapchain m_Swapchain = {};
	VIDECL PRenderPass m_MainRenderPass = {};
	VIDECL PWindow m_Window = {};
	VIDECL PDescriptorPool m_GlobalPool = {};
	VIDECL PDescriptorSetLayout m_GlobalDescriptorSetLayout = {};
	VIDECL CSet<SDescriptorSet> m_GlobalDescriptorSets = {};
	VIDECL UInt32 m_ImageIndex = {};
	VIDECL VkDescriptorPool m_GUIPool = {};
	VIDECL CSet<PRenderSubrender> m_SubPasses = {};
public:
	VIDECL explicit CVulkanRenderer(const SRendererCreateInfo& createInfo);
	VIDECL ~CVulkanRenderer() override = default;

	VIDECL          void Setup() override;
	VIDECL VIREQOUT inline PSwapchain& GetSwapchain() override { return m_Swapchain; }
	VIDECL VIREQOUT PVertexBuffer CreateVertexBuffer(const CSet<SVertex>& vertices) override;
	VIDECL VIREQOUT PIndexBuffer CreateIndexBuffer(const CSet<UInt32>& indices) override;
	VIDECL VIREQOUT PUniformBuffer CreateUniformBuffer() override;
	VIDECL          void CreateDescriptors(const PWorld& world) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const CSet<SVertex>& vertices) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const CSet<SVertex>& vertices, const CSet<UInt32>& indices) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const PVertexBuffer& vertexBuffer) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const PVertexBuffer& vertexBuffer, const PIndexBuffer& indexBuffer) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const SGeometryDataCreateInfo& createInfo) override;

	VIDECL          void OnWindowResize(const SExtent2D& extent) override;
	VIDECL VIREQOUT SFrameInfo BeginFrame() override;
	VIDECL          void DrawFrame(SFrameInfo& frameInfo, const PWorld& world) override;
	VIDECL          void EndFrame(const SFrameInfo& frameInfo) override;
	VIDECL          void BeginUIFrame() override;
	VIDECL          void EndUIFrame(SCommandBuffer commandBuffer) override;
	VIDECL          void Shutdown(const PWorld& world) override;
private:
	VIDECL void RecreateSwapchain(const SExtent2D& newExtent);
	VIDECL void CreateDescriptors();
	VIDECL void CreateDescriptorSetLayout();
};

VISRCEND

#endif //VICTORIAM_VULKANRENDERER_HPP
