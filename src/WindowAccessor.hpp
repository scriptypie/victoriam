//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_WINDOWACCESSOR_HPP
#define VICTORIAM_WINDOWACCESSOR_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <Victoriam/Graphics/Basics.hpp>
#include "GLFWWindow.hpp"

VISRCBEG

class cWindowAccessor
{
public:
	static GLFWwindow* GetWindow(const pWindow& window)
	{
		return ((cGLFWWindow*)window.get())->m_Window;
	}
	static void CreateWindowSurface(const pWindow& window, VkInstance instance, VkSurfaceKHR* surface)
	{
		return ((cGLFWWindow*)window.get())->CreateWindowSurface(instance, surface);
	}
};

VISRCEND

#endif //VICTORIAM_WINDOWACCESSOR_HPP
