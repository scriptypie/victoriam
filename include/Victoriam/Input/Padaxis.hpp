//
// Created by Вячеслав Кривенко on 11.10.2022.
//

#ifndef VICTORIAM_PADAXIS_HPP
#define VICTORIAM_PADAXIS_HPP

#include <Victoriam/Core/Base.hpp>

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

#endif //VICTORIAM_PADAXIS_HPP
