//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_GRENDERER_HPP
#define VICTORIAM_GRENDERER_HPP

#include "Victoriam/Graphics/Structs/GRendererCreateInfo.hpp"
#include <Victoriam/Graphics/GVertexBuffer.hpp>
#include <Victoriam/World/WWorld.hpp>

VISRCBEG

class CRenderer
{
public:
	virtual ~CRenderer() = default;

	VIDECL VIREQOUT static UPtr<CRenderer> Create(const SRendererCreateInfo& createInfo);

	virtual void Setup() = 0;
	virtual PVertexBuffer CreateVertexBuffer(const List<SVertex>& vertices) = 0;

	virtual void OnWindowResize(const SWindowExtent& extent) = 0;
	virtual SCommandBuffer BeginFrame() = 0;
	virtual void DrawFrame(const SCommandBuffer& commandBuffer, const PWorld& world) = 0;
	virtual void EndFrame(const SCommandBuffer& commandBuffer) = 0;
	virtual void Shutdown(const PWorld& world) = 0;
};

VIDECL typedef UPtr<CRenderer> PRenderer;

VISRCEND

#endif //VICTORIAM_GRENDERER_HPP
