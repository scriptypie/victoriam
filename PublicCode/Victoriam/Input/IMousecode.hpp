//
// Created by Вячеслав Кривенко on 11.10.2022.
//

#ifndef VICTORIAM_IMOUSECODE_HPP
#define VICTORIAM_IMOUSECODE_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

enum VIDECL EMouseCode : UInt32
{
	// From glfw3.h
	Button0                = 0,
	Button1                = 1,
	Button2                = 2,
	Button3                = 3,
	Button4                = 4,
	Button5                = 5,
	Button6                = 6,
	Button7                = 7,
	MouseMax                  ,

	ButtonLast             = Button7,
	ButtonLeft             = Button0,
	ButtonRight            = Button1,
	ButtonMiddle           = Button2
};

VISRCEND

#endif //VICTORIAM_IMOUSECODE_HPP
