//
// Created by Вячеслав Кривенко on 11.10.2022.
//

#ifndef VICTORIAM_PADCODE_HPP
#define VICTORIAM_PADCODE_HPP

#include <Victoriam/Core/Base.hpp>

VISRCBEG

enum eGamepadCode : UInt32
{
	ButtonA             = 0,
	ButtonB             = 1,
	ButtonX             = 2,
	ButtonY             = 3,
	ButtonLeftBumper    = 4,
	ButtonRightBumper   = 5,
	ButtonBack          = 6,
	ButtonStart         = 7,
	ButtonGuide         = 8,
	ButtonLeftThumb     = 9,
	ButtonRightThumb    = 10,
	DpadUp              = 11,
	DpadRight           = 12,
	DpadDown            = 13,
	DpadLeft            = 14,
	GamepadMax              ,
	ButtonCross         = ButtonA,
	ButtonCircle        = ButtonB,
	ButtonSquare        = ButtonX,
	ButtonTriangle      = ButtonY
};

VISRCEND

#endif //VICTORIAM_PADCODE_HPP
