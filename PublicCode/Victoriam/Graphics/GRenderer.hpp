//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_GRENDERER_HPP
#define VICTORIAM_GRENDERER_HPP

#include <Victoriam/Graphics/Structs/GRendererCreateInfo.hpp>
#include <Victoriam/Graphics/Structs/GGeometryDataCreateInfo.hpp>
#include <Victoriam/Graphics/Structs/GFrameInfo.hpp>
#include <Victoriam/Graphics/GUniformBuffer.hpp>
#include <Victoriam/World/WWorld.hpp>

VISRCBEG

class VIDECL CRenderer
{
public:
	VIDECL virtual ~CRenderer() = default;

	VIDECL VIREQOUT static CUnique<CRenderer> Create(const SRendererCreateInfo& createInfo);

	VIDECL          virtual void Setup() = 0;
	VIDECL VIREQOUT virtual PSwapchain& GetSwapchain() = 0;
	VIDECL VIREQOUT virtual PVertexBuffer CreateVertexBuffer(const CSet<SVertex>& vertices) = 0;
	VIDECL VIREQOUT virtual PIndexBuffer CreateIndexBuffer(const CSet<UInt32>& indices) = 0;
	VIDECL VIREQOUT virtual PUniformBuffer CreateUniformBuffer() = 0;
	VIDECL          virtual void CreateDescriptors(const PWorld& world) = 0;
	VIDECL VIREQOUT virtual CGeometryData CreateGeometryData(const CSet<SVertex>& vertices) = 0;
	VIDECL VIREQOUT virtual CGeometryData CreateGeometryData(const CSet<SVertex>& vertices, const CSet<UInt32>& indices) = 0;
	VIDECL VIREQOUT virtual CGeometryData CreateGeometryData(const SGeometryDataCreateInfo& createInfo) = 0;
	VIDECL VIREQOUT virtual CGeometryData CreateGeometryData(const PVertexBuffer& vertexBuffer) = 0;
	VIDECL VIREQOUT virtual CGeometryData CreateGeometryData(const PVertexBuffer& vertexBuffer, const PIndexBuffer& indexBuffer) = 0;

	VIDECL          virtual void OnWindowResize(const SExtent2D& extent) = 0;
	VIDECL VIREQOUT virtual SFrameInfo BeginFrame() = 0;
	VIDECL          virtual void DrawFrame(SFrameInfo& frameInfo, const PWorld& world) = 0;
	VIDECL          virtual void EndFrame(const SFrameInfo& frameInfo) = 0;
	VIDECL          virtual void BeginUIFrame() = 0;
	VIDECL          virtual void EndUIFrame(SCommandBuffer commandBuffer) = 0;
	VIDECL          virtual void Shutdown(const PWorld& world) = 0;
};

VIDECL typedef CUnique<CRenderer> PRenderer;

VISRCEND

#endif //VICTORIAM_GRENDERER_HPP
