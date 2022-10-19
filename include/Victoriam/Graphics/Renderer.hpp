//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_RENDERER_HPP
#define VICTORIAM_RENDERER_HPP

#include <Victoriam/Graphics/RendererCreateInfo.hpp>
#include <Victoriam/Graphics/DrawCommandBuffer.hpp>

VISRCBEG

class cRenderer
{
public:
	virtual ~cRenderer() = default;

	VIDECL VIREQOUT static UPtr<cRenderer> Create(const sRendererCreateInfo& createInfo);

	virtual void DrawFrame() = 0;
	virtual void Shutdown() = 0;
};

VIDECL typedef UPtr<cRenderer> pRenderer;

VISRCEND

#endif //VICTORIAM_RENDERER_HPP
