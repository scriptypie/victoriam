//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_VULKANRENDERER_HPP
#define VICTORIAM_VULKANRENDERER_HPP

#include <Victoriam/Graphics/GRenderer.hpp>
#include <Victoriam/Graphics/GDescriptorWriter.hpp>
#include <Victoriam/Graphics/GRenderSubrender.hpp>

#include "VulkanGraphicsContext.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanPipeline.hpp"
#include "VulkanCmdBufferSolver.hpp"

#include "Accessors/ACmdBufferSolver.hpp"
#include "Accessors/ADescriptorWriter.hpp"
#include "Accessors/AVertexBuffer.hpp"
#include "Accessors/AUniformBuffer.hpp"

VISRCBEG

class VIDECL CVulkanRenderer : public CRenderer {
	VIDECL PGraphicsContext m_Context = {};
	VIDECL PSwapchain m_Swapchain = {};
	VIDECL PCmdBufferSolver m_CmdBufferSolver = {};
	VIDECL PWindow m_Window = {};
	VIDECL PDescriptorPool m_GlobalPool = {};
	VIDECL PDescriptorSetLayout m_GlobalDescriptorSetLayout = {};
	VIDECL CList<SDescriptorSet> m_GlobalDescriptorSets = {};
	VIDECL UInt32 m_ImageIndex = {};
	VIDECL VkDescriptorPool m_GUIPool = {};

	VIDECL CList<PRenderSubrender> m_SubPasses = {};
public:
	VIDECL explicit CVulkanRenderer(const SRendererCreateInfo& createInfo);
	VIDECL ~CVulkanRenderer() override = default;

	VIDECL          void Setup() override;
	VIDECL VIREQOUT inline PSwapchain& GetSwapchain() override { return m_Swapchain; }
	VIDECL VIREQOUT PVertexBuffer CreateVertexBuffer(const CList<SVertex>& vertices) override;
	VIDECL VIREQOUT PIndexBuffer CreateIndexBuffer(const CList<UInt32>& indices) override;
	VIDECL VIREQOUT PUniformBuffer CreateUniformBuffer() override;
	VIDECL          void CreateDescriptors(const PWorld& world) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const CList<SVertex>& vertices) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const CList<SVertex>& vertices, const CList<UInt32>& indices) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const PVertexBuffer& vertexBuffer) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const PVertexBuffer& vertexBuffer, const PIndexBuffer& indexBuffer) override;
	VIDECL VIREQOUT CGeometryData CreateGeometryData(const SGeometryDataCreateInfo& createInfo) override;

	VIDECL          void OnWindowResize(const SWindowExtent& extent) override;
	VIDECL VIREQOUT SFrameInfo BeginFrame(const PWorld& world) override;
	VIDECL          void DrawFrame(SFrameInfo& frameInfo, const PWorld& world) override;
	VIDECL          void EndFrame(const SFrameInfo& frameInfo) override;
	VIDECL          void BeginUIFrame() override;
	VIDECL          void EndUIFrame(SCommandBuffer commandBuffer) override;
	VIDECL          void Shutdown(const PWorld& world) override;
private:
	VIDECL void RecreateSwapchain(const SWindowExtent& newExtent);
	VIDECL void CreateDescriptors();
	VIDECL void CreateDescriptorSetLayout();
};

VISRCEND

#endif //VICTORIAM_VULKANRENDERER_HPP
