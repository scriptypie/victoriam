//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_WINDOWCREATEINFO_HPP
#define VICTORIAM_WINDOWCREATEINFO_HPP

#include <Victoriam/Graphics/Basics.hpp>
#include <Victoriam/Math/Vector2.hpp>

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
	Vector2 Offset;
	Vector2 Resolution;
	sFlags Flags;
};

VISRCEND

#endif //VICTORIAM_WINDOWCREATEINFO_HPP
