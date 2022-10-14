//
// Created by Вячеслав Кривенко on 09.10.2022.
//

#include "WindowGlfwImpl.hpp"

VISRCBEG

static bool g_FirstWindow = true;

namespace
{
	inline void glfwErrorCallback(Int32 error, const char* desc)
	{
		printf("GLFW Error(%d): %s\n", error, desc);
	}
}

cWindowGLFWImpl::cWindowGLFWImpl(const sWindowCreateInfo &info) {
	CreateWindow(info);
}

cWindowGLFWImpl::~cWindowGLFWImpl() {
	DestroyWindow();
}

void cWindowGLFWImpl::Update() {
	glfwPollEvents();
	// swap context buffers
}

void cWindowGLFWImpl::CreateWindow(const sWindowCreateInfo &info) {
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

	auto fullscreen = (m_Data.Flags.Contains(WindowCreateWindowFlags_Fullscreen)) ? glfwGetPrimaryMonitor() : nullptr;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_Window = glfwCreateWindow(
	CCast<Int32>(m_Data.Resolution.x),
	CCast<Int32>(m_Data.Resolution.y),
	m_Data.Name.c_str(),
	fullscreen, nullptr
	);
	g_FirstWindow = false;

	// create context here

	glfwSetWindowUserPointer(m_Window, &m_Data);

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	{
		auto& data = Cast<sWindowGLFWImplData>(glfwGetWindowUserPointer(window));
		cWindowCloseEvent close_event;
		if (data.Callback)
			data.Callback(close_event);
	});

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, Int32 width, Int32 height)
	{
		auto& data = Cast<sWindowGLFWImplData>(glfwGetWindowUserPointer(window));
		data.Resolution = { CCast<Float32>(width), CCast<Float32>(height) };
		cWindowResizeEvent resize_event(CCast<UInt32>(width), CCast<UInt32>(height));
		if (data.Callback)
			data.Callback(resize_event);
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, Int32 key, Int32 scancode, Int32 action, Int32 mode)
	{
		auto& data = Cast<sWindowGLFWImplData>(glfwGetWindowUserPointer(window));

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
			}
	});

	glfwSetCharCallback(m_Window, [](GLFWwindow* window, UInt32 keycode)
	{
		auto& data = Cast<sWindowGLFWImplData>(glfwGetWindowUserPointer(window));
		data.InputState.keyboard.input = { CCast<char>(keycode) };
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, Int32 button, Int32 action, Int32 mods)
	{
		auto& data = Cast<sWindowGLFWImplData>(glfwGetWindowUserPointer(window));

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
		}
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, Float64 x, Float64 y)
	{
		auto& data = Cast<sWindowGLFWImplData>(glfwGetWindowUserPointer(window));
		data.InputState.mouse.scroll = { CCast<Float32>(x), CCast<Float32>(y) };
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, Float64 x, Float64 y)
	{
		auto& data = Cast<sWindowGLFWImplData>(glfwGetWindowUserPointer(window));
		data.InputState.mouse.position = { CCast<Float32>(x), CCast<Float32>(y) };
	});

}

void cWindowGLFWImpl::DestroyWindow() {
	if (m_Window)
		glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void cWindowGLFWImpl::CreateWindowSurface() {
	if (glfwCreateWindowSurface(m_Instance, m_Window, nullptr, m_Surface) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create window surface!");
	}
}

VISRCEND
