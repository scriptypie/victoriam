//
// Created by Вячеслав Кривенко on 20.10.2022.
//

#ifndef VICTORIAM_GVERTEX_HPP
#define VICTORIAM_GVERTEX_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Utils/UHash.hpp>

VISRCBEG

/**
 * General vertex structure.
 */
struct VIDECL SVertex
{
	VIDECL SVector3 Position;
	VIDECL SVector4 Color;
	VIDECL SVector3 Normal;
	VIDECL SVector2 UV;
};

VIDECL Bool operator==(const SVertex& a, const SVertex& b);
VIDECL Bool operator!=(const SVertex& a, const SVertex& b);

VIDECL inline static const CList<SVertex> DefaultVertices = {
		{ { 0.0F, 0.0F, 0.0F }, { 1.0F, 1.0F, 1.0F, 1.0F }, { 1.0F, 1.0F, 1.0F }, { 1.0F, 1.0F } },
		{ { 0.0F, 0.0F, 0.0F }, { 1.0F, 1.0F, 1.0F, 1.0F }, { 1.0F, 1.0F, 1.0F }, { 1.0F, 1.0F } },
		{ { 0.0F, 0.0F, 0.0F }, { 1.0F, 1.0F, 1.0F, 1.0F }, { 1.0F, 1.0F, 1.0F }, { 1.0F, 1.0F } },
};

VIDECL inline static const CList<UInt32> DefaultIndices = {
		0, 1, 2
};

VISRCEND

namespace std
{
	template<>
	struct hash<Vi::SVertex>
	{
		size_t operator()(const Vi::SVertex& vertex) const
		{
			size_t seed = 0;
			Vi::FHashCombined(seed, vertex.Position, vertex.Color, vertex.Normal, vertex.UV);
			return seed;
		}
	};
}

#endif //VICTORIAM_GVERTEX_HPP
