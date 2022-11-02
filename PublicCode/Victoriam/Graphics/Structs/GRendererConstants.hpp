//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#ifndef VICTORIAM_GRENDERERCONSTANTS_HPP
#define VICTORIAM_GRENDERERCONSTANTS_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

struct VIDECL SRendererConstants
{
	VIDECL SMatrix4 ProjectionView;
	VIDECL SVector3 SunDirection;
	VIDECL Float32 Ambient;
	VIDECL Float32 Brightness;
};

VISRCEND

#endif //VICTORIAM_GRENDERERCONSTANTS_HPP
