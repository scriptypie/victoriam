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

struct VIDECL SInputState
{
	struct VIDECL SKeyboardInputState
	{
		Bool pressed[KeyboardMax];
		Bool released[KeyboardMax];
		String input;
	} keyboard;
	struct VIDECL SMouseInputState
	{
		SVector2 position;
		SVector2 scroll;
		Bool pressed[MouseMax];
		Bool released[MouseMax];
	} mouse;
};

struct SGLFWWindowData
{
	String Name;
	SWindowExtent Offset;
	SWindowExtent Resolution;
	SFlags Flags;

	SInputState InputState;
	CWindow::EventCallbackFn Callback;
};

namespace Accessors { class Window; }

class CGLFWWindow : public CWindow {
	friend class CInput;
	friend class Accessors::Window;

	SGLFWWindowData m_Data = {};
	GLFWwindow* m_Window = nullptr;

public:
	~CGLFWWindow() override;
	explicit CGLFWWindow(const SWindowCreateInfo& info);

	void Update() override;
	VIREQOUT inline UInt32 GetWidth() const override { return m_Data.Resolution.Width; }
	VIREQOUT inline UInt32 GetHeight() const override { return m_Data.Resolution.Height; }
	VIREQOUT inline UInt32 GetOffsetX() const override { return m_Data.Offset.Width; }
	VIREQOUT inline UInt32 GetOffsetY() const override { return m_Data.Offset.Height; }
	VIREQOUT inline SWindowExtent GetExtent() const override { return {GetWidth(), GetHeight() }; }
	inline void SetExtent(const SWindowExtent& extent) override { m_Data.Resolution = extent; }
	inline void SetEventCallbackFunction(const EventCallbackFn& fn) override { m_Data.Callback = fn; }
	void WaitForEvents() override;
private:
	void CreateWindow(const SWindowCreateInfo& info);
	void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
	void DestroyWindow();
};


VISRCEND

#endif //VICTORIAM_GLFWWINDOW_HPP
