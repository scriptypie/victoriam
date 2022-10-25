//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_GMATERIALDATA_HPP
#define VICTORIAM_GMATERIALDATA_HPP

#include <Victoriam/Math/MVector2.hpp>
#include <Victoriam/Math/MVector3.hpp>
#include <Victoriam/Math/MMatrix4.hpp>

VISRCBEG

struct VIDECL SMaterialData
{
	Matrix4 Transform;
	Vector2 Offset;
	alignas(16)
	Vector3 Color;
};

VISRCEND

#endif //VICTORIAM_GMATERIALDATA_HPP
