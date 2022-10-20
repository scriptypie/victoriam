//
// Created by Вячеслав Кривенко on 09.10.2022.
//

#ifndef VICTORIAM_GLFWWINDOW_HPP
#define VICTORIAM_GLFWWINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <Victoriam/Graphics/GWindow.hpp>
#include <Victoriam/Input/IKeycode.hpp>
#include <Victoriam/Input/IMousecode.hpp>
#include <Victoriam/Input/IPadcode.hpp>
#include <Victoriam/Input/IPadaxis.hpp>
#include <Victoriam/Math/MVector2.hpp>

VISRCBEG

struct VIDECL sInputState
{
	struct VIDECL sKeyboardInputState
	{
		Bool pressed[KeyboardMax];
		Bool released[KeyboardMax];
		String input;
	} keyboard;
	struct VIDECL sMouseInputState
	{
		sVector2 position;
		sVector2 scroll;
		Bool pressed[MouseMax];
		Bool released[MouseMax];
	} mouse;
};

struct sGLFWWindowData
{
	String Name;
	sWindowExtent Offset;
	sWindowExtent Resolution;
	sFlags Flags;

	sInputState InputState;
	cWindow::EventCallbackFn Callback;
};

namespace Accessors { class Window; }

class cGLFWWindow : public cWindow {
	friend class cInput;
	friend class Accessors::Window;

	sGLFWWindowData m_Data = {};
	GLFWwindow* m_Window = nullptr;

public:
	~cGLFWWindow() override;
	explicit cGLFWWindow(const sWindowCreateInfo& info);

	void Update() override;
	VIREQOUT inline UInt32 GetWidth() const override { return m_Data.Resolution.Width; }
	VIREQOUT inline UInt32 GetHeight() const override { return m_Data.Resolution.Height; }
	VIREQOUT inline UInt32 GetOffsetX() const override { return m_Data.Offset.Width; }
	VIREQOUT inline UInt32 GetOffsetY() const override { return m_Data.Offset.Height; }
	VIREQOUT inline sWindowExtent GetExtent() const override { return { GetWidth(), GetHeight() }; }
	inline void SetExtent(const sWindowExtent& extent) override { m_Data.Resolution = extent; }
	inline void SetEventCallbackFunction(const EventCallbackFn& fn) override { m_Data.Callback = fn; }
	void WaitForEvents() override;
private:
	void CreateWindow(const sWindowCreateInfo& info);
	void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
	void DestroyWindow();
};


VISRCEND

#endif //VICTORIAM_GLFWWINDOW_HPP
