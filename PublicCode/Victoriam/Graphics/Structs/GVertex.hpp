//
// Created by Вячеслав Кривенко on 20.10.2022.
//

#ifndef VICTORIAM_GVERTEX_HPP
#define VICTORIAM_GVERTEX_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

struct VIDECL SVertex
{
	SVector3 Position;
	SVector4 Color;
	SVector3 Normal;
	SVector2 UV;
};

VIDECL inline static const List<SVertex> DefaultVertices = {
		{ { 0.0F, 0.0F, 0.0F }, { 1.0F, 1.0F, 1.0F, 1.0F }, { 1.0F, 1.0F, 1.0F }, { 1.0F, 1.0F } },
		{ { 0.0F, 0.0F, 0.0F }, { 1.0F, 1.0F, 1.0F, 1.0F }, { 1.0F, 1.0F, 1.0F }, { 1.0F, 1.0F } },
		{ { 0.0F, 0.0F, 0.0F }, { 1.0F, 1.0F, 1.0F, 1.0F }, { 1.0F, 1.0F, 1.0F }, { 1.0F, 1.0F } },
};

VIDECL inline static const List<UInt32> DefaultIndices = {
		0, 1, 2
};

VISRCEND

#endif //VICTORIAM_GVERTEX_HPP
