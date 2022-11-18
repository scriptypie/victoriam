//
// Created by Вячеслав Кривенко on 17.11.2022.
//

#ifndef VICTORIAM_MFRUSTUM_HPP
#define VICTORIAM_MFRUSTUM_HPP

#include <Victoriam/Matemia/MPlane.hpp>
#include <Victoriam/Matemia/MVector4.hpp>

VISRCBEG

struct VIDECL SFrustum {
	SPlane top;
	SPlane bottom;
	SPlane right;
	SPlane left;
	SPlane far;
	SPlane near;
};

VISRCEND

#endif //VICTORIAM_MFRUSTUM_HPP
