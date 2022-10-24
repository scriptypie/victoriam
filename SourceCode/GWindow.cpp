//
// Created by Вячеслав Кривенко on 09.10.2022.
//

#include <Victoriam/Graphics/GWindow.hpp>

#include "GLFWWindow.hpp"

Vi::PWindow Vi::CWindow::Create(const Vi::SWindowCreateInfo &info)
{
	return Vi::CreateSPtr<Vi::CGLFWWindow>(info);
}
