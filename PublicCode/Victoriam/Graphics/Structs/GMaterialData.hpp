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
	alignas(16)
	SVector4 Color;
};

VISRCEND

#endif //VICTORIAM_GMATERIALDATA_HPP
