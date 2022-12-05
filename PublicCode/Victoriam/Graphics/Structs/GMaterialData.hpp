//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_GMATERIALDATA_HPP
#define VICTORIAM_GMATERIALDATA_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

/**
 * Per-mesh struct that handles information required for every mesh to render.
 */
struct VIDECL SMaterialData {
	VIDECL SMatrix4 ModelMatrix;
};

VISRCEND

#endif //VICTORIAM_GMATERIALDATA_HPP
