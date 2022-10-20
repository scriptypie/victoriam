//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_GRENDERER_HPP
#define VICTORIAM_GRENDERER_HPP

#include "Victoriam/Graphics/Structs/GRendererCreateInfo.hpp"
#include <Victoriam/Graphics/GVertexBuffer.hpp>

VISRCBEG

class cRenderer
{
public:
	virtual ~cRenderer() = default;

	VIDECL VIREQOUT static UPtr<cRenderer> Create(const sRendererCreateInfo& createInfo);

	virtual void Setup() = 0;
	virtual void PushVertexBuffer(const List<sVertex>& vertices) = 0;

	virtual void OnWindowResize(const sWindowExtent& extent) = 0;
	virtual void DrawFrame() = 0;
	virtual void Shutdown() = 0;
};

VIDECL typedef UPtr<cRenderer> pRenderer;

VISRCEND

#endif //VICTORIAM_GRENDERER_HPP
