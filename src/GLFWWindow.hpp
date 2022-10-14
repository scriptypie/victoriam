//
// Created by Вячеслав Кривенко on 09.10.2022.
//

#ifndef VICTORIAM_GLFWWINDOW_HPP
#define VICTORIAM_GLFWWINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <Victoriam/Graphics/Window.hpp>
#include <Victoriam/Input/Keycode.hpp>
#include <Victoriam/Input/Mousecode.hpp>
#include <Victoriam/Input/Padcode.hpp>
#include <Victoriam/Input/Padaxis.hpp>

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
	Vector2 Offset;
	Vector2 Resolution;
	sFlags Flags;

	sInputState InputState;
	cWindow::EventCallbackFn Callback;
};

class cGLFWWindow : public cWindow {
	friend class cInput;
	friend class cWindowAccessor;

	sGLFWWindowData m_Data;
	GLFWwindow* m_Window;

	VkInstance m_Instance;
	VkSurfaceKHR* m_Surface;
public:
	~cGLFWWindow() override;
	explicit cGLFWWindow(const sWindowCreateInfo& info);

	void Update() override;
	[[nodiscard]] inline UInt32 GetWidth() const override { return CCast<UInt32>(m_Data.Resolution.x); }
	[[nodiscard]] inline UInt32 GetHeight() const override { return CCast<UInt32>(m_Data.Resolution.y); }
	[[nodiscard]] inline UInt32 GetOffsetX() const override { return CCast<UInt32>(m_Data.Offset.x); }
	[[nodiscard]] inline UInt32 GetOffsetY() const override { return CCast<UInt32>(m_Data.Offset.y); }
	inline void SetEventCallbackFunction(const EventCallbackFn& fn) override { m_Data.Callback = fn; }
	inline void* GetNativeWindowVPtr() override { return CCast<void*>(m_Window); }

private:
	void CreateWindow(const sWindowCreateInfo& info);
	void CreateWindowSurface();
	void DestroyWindow();
};


VISRCEND

#endif //VICTORIAM_GLFWWINDOW_HPP
