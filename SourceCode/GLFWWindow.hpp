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
		glm::vec2 position;
		glm::vec2 scroll;
		Bool pressed[MouseMax];
		Bool released[MouseMax];
	} mouse;
};

struct VIDECL SWindowData
{
	String Name;
	SExtent2D Offset;
	SExtent2D Resolution;
	SFlags Flags;

	SInputState InputState;
	CWindow::EventCallbackFn Callback;
};

namespace Accessors { class Window; }

class VIDECL CGLFWWindow : public CWindow {
	friend class CInput;
	friend class Accessors::Window;

	SWindowData m_Data = {};
	GLFWwindow* m_Window = nullptr;

public:
	VIDECL ~CGLFWWindow() override;
	VIDECL explicit CGLFWWindow(const SWindowCreateInfo& info);

	VIDECL          void Update() override;
	VIDECL VIREQOUT inline UInt32 GetWidth() const override { return m_Data.Resolution.Width; }
	VIDECL VIREQOUT inline UInt32 GetHeight() const override { return m_Data.Resolution.Height; }
	VIDECL VIREQOUT inline UInt32 GetOffsetX() const override { return m_Data.Offset.Width; }
	VIDECL VIREQOUT inline UInt32 GetOffsetY() const override { return m_Data.Offset.Height; }
	VIDECL VIREQOUT inline SExtent2D GetExtent() const override { return {GetWidth(), GetHeight() }; }
	VIDECL          inline void SetExtent(const SExtent2D& extent) override { m_Data.Resolution = extent; }
	VIDECL          inline void SetEventCallbackFunction(const EventCallbackFn& fn) override { m_Data.Callback = fn; }
	VIDECL          void WaitForEvents() override;
private:
	VIDECL          void CreateWindow(const SWindowCreateInfo& info);
	VIDECL          void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
	VIDECL          void DestroyWindow();
};


VISRCEND

#endif //VICTORIAM_GLFWWINDOW_HPP
