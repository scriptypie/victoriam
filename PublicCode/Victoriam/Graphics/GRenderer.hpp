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

	virtual void Setup() = 0;
	virtual PVertexBuffer CreateVertexBuffer(const List<SVertex>& vertices) = 0;
	virtual PIndexBuffer CreateIndexBuffer(const List<UInt32>& indices) = 0;
	virtual CGeometryData CreateGeometryData(const List<SVertex>& vertices) = 0;
	virtual CGeometryData CreateGeometryData(const List<SVertex>& vertices, const List<UInt32>& indices) = 0;
	virtual CGeometryData CreateGeometryData(const SGeometryDataCreateInfo& createInfo) = 0;
	virtual CGeometryData CreateGeometryData(const PVertexBuffer& vertexBuffer) = 0;
	virtual CGeometryData CreateGeometryData(const PVertexBuffer& vertexBuffer, const PIndexBuffer& indexBuffer) = 0;

	virtual void OnWindowResize(const SWindowExtent& extent) = 0;
	virtual SCommandBuffer BeginFrame() = 0;
	virtual void DrawFrame(const SCommandBuffer& commandBuffer, const PWorld& world) = 0;
	virtual void EndFrame(const SCommandBuffer& commandBuffer) = 0;
	virtual void Shutdown(const PWorld& world) = 0;
};

VIDECL typedef UPtr<CRenderer> PRenderer;

VISRCEND

#endif //VICTORIAM_GRENDERER_HPP
