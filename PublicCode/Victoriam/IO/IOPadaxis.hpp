//
// Created by Вячеслав Кривенко on 11.10.2022.
//

#ifndef VICTORIAM_IOPADAXIS_HPP
#define VICTORIAM_IOPADAXIS_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

enum VIDECL EGamepadAxis : UInt32
{
	AxisLeftX       = 0,
	AxisLeftY       = 1,
	AxisRightX      = 2,
	AxisRightY      = 3,
	AxisLeftTrigger = 4,
	AxisRightTrigger= 5,
	AxisMax
};

VISRCEND

#endif //VICTORIAM_IOPADAXIS_HPP
