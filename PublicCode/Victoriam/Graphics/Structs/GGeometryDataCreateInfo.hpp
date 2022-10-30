//
// Created by Вячеслав Кривенко on 28.10.2022.
//

#ifndef VICTORIAM_GGEOMETRYDATACREATEINFO_HPP
#define VICTORIAM_GGEOMETRYDATACREATEINFO_HPP

#include <Victoriam/Graphics/Structs/GVertex.hpp>

VISRCBEG

struct VIDECL SGeometryDataCreateInfo
{
	VIDECL List<SVertex> Vertices;
	VIDECL List<UInt32> Indices;
};

VISRCEND

#endif //VICTORIAM_GGEOMETRYDATACREATEINFO_HPP
