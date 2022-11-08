//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_GWINDOWCREATEINFO_HPP
#define VICTORIAM_GWINDOWCREATEINFO_HPP

#include "Victoriam/Graphics/Basics.hpp"
#include "GWindowExtent.hpp"

VISRCBEG

enum VIDECL EWindowCreateWindowFlags : FlagDef
{
	WindowCreateWindowFlag_DefaultWindow = 0x0000000000000000,
	WindowCreateWindowFlag_Fullscreen = 0x0000000000000001,
	WindowCreateWindowFlags_NoResize = 0x0000000000000010,
};

struct VIDECL SWindowCreateInfo
{
	VIDECL String Name;
	VIDECL SWindowExtent Offset;
	VIDECL SWindowExtent Resolution;
	VIDECL SFlags Flags;
};

VISRCEND

#endif //VICTORIAM_GWINDOWCREATEINFO_HPP
