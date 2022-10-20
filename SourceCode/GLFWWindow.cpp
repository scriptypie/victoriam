//
// Created by Вячеслав Кривенко on 09.10.2022.
//

#include "GLFWWindow.hpp"

VISRCBEG

static bool g_FirstWindow = true;

namespace
{
	inline void glfwErrorCallback(Int32 error, const char* desc)
	{
		printf("GLFW Error(%d): %s\n", error, desc);
	}
}

cGLFWWindow::cGLFWWindow(const sWindowCreateInfo &info) {
	CreateWindow(info);
}

cGLFWWindow::~cGLFWWindow() {
	DestroyWindow();
}

void cGLFWWindow::Update() {
	glfwPollEvents();
}

void cGLFWWindow::CreateWindow(const sWindowCreateInfo &info) {
	m_Data.Offset = info.Offset;
	m_Data.Resolution = info.Resolution;
	m_Data.Flags = info.Flags;
	m_Data.Name = info.Name;

	if (g_FirstWindow)
	{
		Int32 initResult = glfwInit();
		assert(initResult && "GLFW couldn't initialize!");
		glfwSetErrorCallback(glfwErrorCallback);
	}

	auto fullscreen = (m_Data.Flags.Contains(WindowCreateWindowFlag_Fullscreen)) ? glfwGetPrimaryMonitor() : nullptr;

	if (m_Data.Flags.Contains(WindowCreateWindowFlags_NoResize))
	{
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_Window = glfwCreateWindow(
	CCast<Int32>(m_Data.Resolution.Width),
	CCast<Int32>(m_Data.Resolution.Height),
	m_Data.Name.c_str(),
	fullscreen, nullptr
	);
	g_FirstWindow = false;

	// create context here

	glfwSetWindowUserPointer(m_Window, &m_Data);

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	{
		auto& data = Cast<sGLFWWindowData>(glfwGetWindowUserPointer(window));
		cWindowCloseEvent close_event;
		if (data.Callback)
			data.Callback(close_event);
	});

	glfwSetWindowRefreshCallback(m_Window, [](GLFWwindow* window)
	{
		auto& data = Cast<sGLFWWindowData>(glfwGetWindowUserPointer(window));
		cWindowResizeEvent resize_event(CCast<UInt32>(data.Resolution.Width), CCast<UInt32>(data.Resolution.Height));
		if (data.Callback)
			data.Callback(resize_event);
	});

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, Int32 width, Int32 height)
	{
		auto& data = Cast<sGLFWWindowData>(glfwGetWindowUserPointer(window));
		data.Resolution = { CCast<UInt32>(width), CCast<UInt32>(height) };
		cWindowResizeEvent resize_event(CCast<UInt32>(width), CCast<UInt32>(height));
		if (data.Callback)
			data.Callback(resize_event);
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, Int32 key, Int32 scancode, Int32 action, Int32 mode)
	{
		auto& data = Cast<sGLFWWindowData>(glfwGetWindowUserPointer(window));

		if (data.Callback)
			switch (action)
			{
				case GLFW_PRESS:
				{
					data.InputState.keyboard.pressed[key] = true;
					data.InputState.keyboard.released[key] = false;
					break;
				}
				case GLFW_RELEASE:
				{
					data.InputState.keyboard.pressed[key] = false;
					data.InputState.keyboard.released[key] = true;
					break;
				}
				default: break;
			}
	});

	glfwSetCharCallback(m_Window, [](GLFWwindow* window, UInt32 keycode)
	{
		auto& data = Cast<sGLFWWindowData>(glfwGetWindowUserPointer(window));
		data.InputState.keyboard.input = { CCast<char>(keycode) };
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, Int32 button, Int32 action, Int32 mods)
	{
		auto& data = Cast<sGLFWWindowData>(glfwGetWindowUserPointer(window));

		switch (action)
		{
			case GLFW_PRESS:
			{
				data.InputState.mouse.pressed[button] = true;
				data.InputState.mouse.released[button] = false;
				break;
			}
			case GLFW_RELEASE:
			{
				data.InputState.mouse.pressed[button] = false;
				data.InputState.mouse.released[button] = true;
				break;
			}
			default: break;
		}
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, Float64 x, Float64 y)
	{
		auto& data = Cast<sGLFWWindowData>(glfwGetWindowUserPointer(window));
		data.InputState.mouse.scroll = { CCast<Float32>(x), CCast<Float32>(y) };
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, Float64 x, Float64 y)
	{
		auto& data = Cast<sGLFWWindowData>(glfwGetWindowUserPointer(window));
		data.InputState.mouse.position = { CCast<Float32>(x), CCast<Float32>(y) };
	});

}

void cGLFWWindow::DestroyWindow() {
	if (m_Window)
		glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void cGLFWWindow::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
	if (glfwCreateWindowSurface(instance, m_Window, nullptr, surface) != VK_SUCCESS)
		throw std::runtime_error("Failed to create window surface!");
}

void cGLFWWindow::WaitForEvents()
{
	glfwWaitEvents();
}

VISRCEND
