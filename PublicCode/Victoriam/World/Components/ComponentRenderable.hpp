//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_COMPONENTRENDERABLE_HPP
#define VICTORIAM_COMPONENTRENDERABLE_HPP

#include <Victoriam/World/Components/ComponentBase.hpp>
#include <Victoriam/Graphics/GVertexBuffer.hpp>

VISRCBEG

struct VIDECL SComponentRenderable : SComponentBase
{
	COMPONENT_DECL(ComponentRenderable)

	PVertexBuffer VertexBuffer;
	SVector3 Color;

};

VISRCEND

#endif //VICTORIAM_COMPONENTRENDERABLE_HPP
