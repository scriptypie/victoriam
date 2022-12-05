//
// Created by Вячеслав Кривенко on 28.10.2022.
//

#ifndef VICTORIAM_GGEOMETRYDATACREATEINFO_HPP
#define VICTORIAM_GGEOMETRYDATACREATEINFO_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

/**
 * Generalization ot vertex and index data.
 */
struct VIDECL SGeometryDataCreateInfo {
	VIDECL CSet<SVertex> Vertices;
	VIDECL CSet<UInt32> Indices;
};

VISRCEND

#endif //VICTORIAM_GGEOMETRYDATACREATEINFO_HPP
