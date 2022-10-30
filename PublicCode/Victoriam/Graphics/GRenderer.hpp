//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_GRENDERER_HPP
#define VICTORIAM_GRENDERER_HPP

#include "Victoriam/Graphics/Structs/GRendererCreateInfo.hpp"
#include <Victoriam/Graphics/Structs/GGeometryDataCreateInfo.hpp>
#include <Victoriam/World/WWorld.hpp>

VISRCBEG

class CRenderer
{
public:
	virtual ~CRenderer() = default;

	VIDECL VIREQOUT static UPtr<CRenderer> Create(const SRendererCreateInfo& createInfo);

	VIDECL virtual void Setup() = 0;
	VIDECL VIREQOUT virtual PVertexBuffer CreateVertexBuffer(const List<SVertex>& vertices) = 0;
	VIDECL VIREQOUT virtual PIndexBuffer  CreateIndexBuffer(const List<UInt32>& indices) = 0;
	VIDECL VIREQOUT virtual CGeometryData CreateGeometryData(const List<SVertex>& vertices) = 0;
	VIDECL VIREQOUT virtual CGeometryData CreateGeometryData(const List<SVertex>& vertices, const List<UInt32>& indices) = 0;
	VIDECL VIREQOUT virtual CGeometryData CreateGeometryData(const SGeometryDataCreateInfo& createInfo) = 0;
	VIDECL VIREQOUT virtual CGeometryData CreateGeometryData(const PVertexBuffer& vertexBuffer) = 0;
	VIDECL VIREQOUT virtual CGeometryData CreateGeometryData(const PVertexBuffer& vertexBuffer, const PIndexBuffer& indexBuffer) = 0;

	VIDECL virtual void OnWindowResize(const SWindowExtent& extent) = 0;
	VIDECL virtual SCommandBuffer BeginFrame() = 0;
	VIDECL virtual void DrawFrame(const SCommandBuffer& commandBuffer, const PWorld& world) = 0;
	VIDECL virtual void EndFrame(const SCommandBuffer& commandBuffer) = 0;
	VIDECL virtual void BeginUIFrame() = 0;
	VIDECL virtual void EndUIFrame() = 0;
	VIDECL virtual void Shutdown(const PWorld& world) = 0;
};

VIDECL typedef UPtr<CRenderer> PRenderer;

VISRCEND

#endif //VICTORIAM_GRENDERER_HPP
