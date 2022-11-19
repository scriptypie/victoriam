//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_GWINDOWCREATEINFO_HPP
#define VICTORIAM_GWINDOWCREATEINFO_HPP

#include "Victoriam/Graphics/Basics.hpp"

VISRCBEG

/**
 * Additional flags for window creation.
 */
enum VIDECL EWindowCreateWindowFlags : FlagDef
{
	/**
	 * Create default window with default settings.
	 */
	WindowCreateWindowFlag_DefaultWindow = 0x0000000000000000,
	/**
	 * Create fullscreen window without any borders.
	 */
	WindowCreateWindowFlag_Fullscreen = 0x0000000000000001,
	/**
	 * Creates default but non-resizable window.
	 */
	WindowCreateWindowFlags_NoResize = 0x0000000000000010,
};

/**
 * Contains all information required to create window object.
 */
struct VIDECL SWindowCreateInfo
{
	String Name;
	SExtent2D Offset;
	SExtent2D Resolution;
	SFlags Flags;
};

VISRCEND

#endif //VICTORIAM_GWINDOWCREATEINFO_HPP
