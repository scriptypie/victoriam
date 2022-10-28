//
// Created by Вячеслав Кривенко on 28.10.2022.
//

#ifndef VICTORIAM_GGEOMETRYDATACREATEINFO_HPP
#define VICTORIAM_GGEOMETRYDATACREATEINFO_HPP

#include <Victoriam/Graphics/Structs/GVertex.hpp>

VISRCBEG

struct VIDECL SGeometryDataCreateInfo
{
	VIDECL const List<SVertex>* pVertices;
	VIDECL const List<UInt32>* pIndices;
};

VISRCEND

#endif //VICTORIAM_GGEOMETRYDATACREATEINFO_HPP
