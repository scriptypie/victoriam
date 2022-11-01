//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_GMATERIALDATA_HPP
#define VICTORIAM_GMATERIALDATA_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

struct VIDECL SMaterialData
{
	SMatrix4 Transform;
	SMatrix4 ModelMatrix;
	alignas(16)
	SVector3 SunDirection;
};

VISRCEND

#endif //VICTORIAM_GMATERIALDATA_HPP
