//
// Created by Вячеслав Кривенко on 17.10.2022.
//

#ifndef VICTORIAM_GRENDERERCREATEINFO_HPP
#define VICTORIAM_GRENDERERCREATEINFO_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

/**
 * Contains all information required to create renderer object.
 */
struct VIDECL SRendererCreateInfo {
	PWindow WindowPtr = {};
};

VISRCEND

#endif //VICTORIAM_GRENDERERCREATEINFO_HPP
