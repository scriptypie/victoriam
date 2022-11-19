//
// Created by Вячеслав Кривенко on 19.11.2022.
//

#ifndef VICTORIAM_MEXTENT_HPP
#define VICTORIAM_MEXTENT_HPP

#include <Victoriam/Matemia/Base/Base.hpp>

VISRCBEG

struct VIDECL SExtent2D {
	UInt32 Width = {};
	UInt32 Height = {};
};

struct VIDECL SExtent3D : SExtent2D {
	UInt32 Depth = 1;
};

VISRCEND

#endif //VICTORIAM_MEXTENT_HPP
