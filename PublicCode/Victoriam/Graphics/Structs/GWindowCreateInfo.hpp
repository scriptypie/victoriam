//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_GWINDOWCREATEINFO_HPP
#define VICTORIAM_GWINDOWCREATEINFO_HPP

#include "Victoriam/Graphics/Basics.hpp"
#include "GWindowExtent.hpp"

VISRCBEG

enum EWindowCreateWindowFlags : FlagDef
{
	WindowCreateWindowFlag_DefaultWindow = 0x0000000000000000,
	WindowCreateWindowFlag_Fullscreen = 0x0000000000000001,
	WindowCreateWindowFlags_NoResize = 0x0000000000000010,
};

struct SWindowCreateInfo
{
	String Name;
	SWindowExtent Offset;
	SWindowExtent Resolution;
	SFlags Flags;
};

VISRCEND

#endif //VICTORIAM_GWINDOWCREATEINFO_HPP
