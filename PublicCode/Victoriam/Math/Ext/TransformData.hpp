//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_TRANSFORMDATA_HPP
#define VICTORIAM_TRANSFORMDATA_HPP

#include <Victoriam/Math/Vector/TypeVector3.hpp>

VISRCBEG

struct VIDECL STransformData
{
	SVector3 Translation;
	SVector3 Rotation;
	SVector3 Scale;
};

VISRCEND

#endif //VICTORIAM_TRANSFORMDATA_HPP
