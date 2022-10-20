//
// Created by Вячеслав Кривенко on 09.10.2022.
//

#include <Victoriam/Graphics/GWindow.hpp>

#include "GLFWWindow.hpp"

Vi::pWindow Vi::cWindow::Create(const Vi::sWindowCreateInfo &info)
{
	return Vi::CreateSPtr<Vi::cGLFWWindow>(info);
}
