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

	class VIDECL Window {
	public:
		VIDECL VIREQOUT static GLFWwindow *GetGLFWWindow(const PWindow &window) {
			return CCast<CGLFWWindow*>(window.Get())->m_Window;
		}
		VIDECL static void CreateWindowSurface(const PWindow &window, VkInstance instance, VkSurfaceKHR *surface) {
			CCast<CGLFWWindow*>(window.Get())->CreateWindowSurface(instance, surface);
		}
	};

}

VISRCEND

#endif //VICTORIAM_AWINDOW_HPP
