//
// Created by Вячеслав Кривенко on 09.10.2022.
//

#include <Victoriam/Graphics/Window.hpp>

#include "WindowGlfwImpl.hpp"

Vi::SPtr<Vi::cWindow> Vi::cWindow::Create(const Vi::sWindowCreateInfo &info)
{
	return Vi::CreateSPtr<Vi::cWindowGLFWImpl>(info);
}
