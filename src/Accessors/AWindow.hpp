//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_AWINDOW_HPP
#define VICTORIAM_AWINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Victoriam/Graphics/Basics.hpp"
#include "../GLFWWindow.hpp"

VISRCBEG

namespace Accessors {

	class Window {
	public:
		VIDECL static GLFWwindow *GetGLFWWindow(const pWindow &window) {
			return CCast<cGLFWWindow*>(window.get())->m_Window;
		}
		VIDECL static void CreateWindowSurface(const pWindow &window, VkInstance instance, VkSurfaceKHR *surface) {
			return CCast<cGLFWWindow*>(window.get())->CreateWindowSurface(instance, surface);
		}
	};

}

VISRCEND

#endif //VICTORIAM_AWINDOW_HPP
