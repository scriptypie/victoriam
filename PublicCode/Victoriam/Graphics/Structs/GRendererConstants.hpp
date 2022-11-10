//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#ifndef VICTORIAM_GRENDERERCONSTANTS_HPP
#define VICTORIAM_GRENDERERCONSTANTS_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

/**
 * Contains all information required per-frame.
 */
struct VIDECL SRendererConstants
{
	VIDECL SMatrix4 View;
	VIDECL SMatrix4 Projection;
	VIDECL SVector4 SunDirection; // ignore w component
	VIDECL SVector4 LightPosition; // ignore w component
	VIDECL SVector4 LightColor; // w is intensity
	VIDECL SVector4 Ambient; // w is intensity
	VIDECL Float32 Brightness; // RANGE: [0.0...1.0]
};

VISRCEND

#endif //VICTORIAM_GRENDERERCONSTANTS_HPP
