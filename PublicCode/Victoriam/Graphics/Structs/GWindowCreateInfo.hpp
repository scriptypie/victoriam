//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_GWINDOWCREATEINFO_HPP
#define VICTORIAM_GWINDOWCREATEINFO_HPP

#include "Victoriam/Graphics/Basics.hpp"
#include "GWindowExtent.hpp"

VISRCBEG

enum eWindowCreateWindowFlags : FlagDef
{
	WindowCreateWindowFlag_DefaultWindow = 0x0000000000000000,
	WindowCreateWindowFlag_Fullscreen = 0x0000000000000001,
	WindowCreateWindowFlags_NoResize = 0x0000000000000010,
};

struct sWindowCreateInfo
{
	String Name;
	sWindowExtent Offset;
	sWindowExtent Resolution;
	sFlags Flags;
};

VISRCEND

#endif //VICTORIAM_GWINDOWCREATEINFO_HPP
