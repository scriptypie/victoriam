//
// Created by Вячеслав Кривенко on 11.10.2022.
//

#ifndef VICTORIAM_IPADAXIS_HPP
#define VICTORIAM_IPADAXIS_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

enum eGamepadAxis : UInt32
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

#endif //VICTORIAM_IPADAXIS_HPP
