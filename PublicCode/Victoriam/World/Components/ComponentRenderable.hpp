//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_COMPONENTRENDERABLE_HPP
#define VICTORIAM_COMPONENTRENDERABLE_HPP

#include <Victoriam/World/Components/ComponentBase.hpp>
#include <Victoriam/Graphics/GVertexBuffer.hpp>
#include <Victoriam/Math/MVector3.hpp>

VISRCBEG

struct VIDECL SComponentRenderable : public SComponentBase
{
	friend class CGameObject;
	inline static UInt32 GetStaticComponentID() { return 1; }
	UInt32 GetComponentID() override { return GetStaticComponentID(); }

	PVertexBuffer VertexBuffer;
	SVector3 Color;

};

VISRCEND

#endif //VICTORIAM_COMPONENTRENDERABLE_HPP
