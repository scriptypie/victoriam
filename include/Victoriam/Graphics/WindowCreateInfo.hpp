//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_WINDOWCREATEINFO_HPP
#define VICTORIAM_WINDOWCREATEINFO_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Graphics/WindowExtent.hpp>

VISRCBEG

enum eWindowCreateWindowFlags : FlagDef
{
	WindowCreateWindowFlag_DefaultWindow = 0x0000000000000000,
	WindowCreateWindowFlags_Fullscreen = 0x0000000000000001,
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

#endif //VICTORIAM_WINDOWCREATEINFO_HPP
