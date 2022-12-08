//
// Created by Вячеслав Кривенко on 01.11.2022.
//

#ifndef VICTORIAM_GWORLDRENDERERSETTINGS_HPP
#define VICTORIAM_GWORLDRENDERERSETTINGS_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

/**
 * Contains renderer settings per-world.
 */
struct VIDECL SWorldRendererSettings {
	SVector4 Ambient = {1.0F, 1.0F, 1.0F, 0.01F};
	Float32 Brightness = 1.0F;
	Float32 IlluminationDistance = 1000.0F;
};

VISRCEND

#endif //VICTORIAM_GWORLDRENDERERSETTINGS_HPP
