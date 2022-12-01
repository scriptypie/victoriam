//
// Created by Вячеслав Кривенко on 09.10.2022.
//

#include <Victoriam/Graphics/GWindow.hpp>

#include "GLFWWindow.hpp"

VISRCBEG

PWindow CWindow::Create(const SWindowCreateInfo &info)
{
	return FMakeShared<CGLFWWindow>(info);
}

VISRCEND
