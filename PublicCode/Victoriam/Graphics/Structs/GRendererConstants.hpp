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

struct VIDECL SPointLightInfo
{
	VIDECL SVector4 Position; // w is radius
	VIDECL SVector4 Color;
};

VIDECL constexpr UInt32 MAX_POINT_LIGHTS = 32U;

struct VIDECL SRendererConstants
{
	VIDECL SMatrix4 View;
	VIDECL SMatrix4 Projection;
	VIDECL SVector4 SunDirection; // ignore w component
	VIDECL SVector4 Ambient; // w is intensity
	VIDECL SPointLightInfo PointLights[MAX_POINT_LIGHTS];
	VIDECL Float32 Brightness; // RANGE: [0.0...1.0]
	VIDECL Int32 ActiveLightsCount;
};

VISRCEND

#endif //VICTORIAM_GRENDERERCONSTANTS_HPP
