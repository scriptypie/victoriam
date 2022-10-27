//
// Created by Вячеслав Кривенко on 11.10.2022.
//

#include "GLFWWindow.hpp"

#include "Victoriam/Input/IInput.hpp"

VISRCBEG

void CInput::Init(const SPtr<CWindow> &window) {
	m_InputStatePtr = &CCast<CGLFWWindow*>(window.get())->m_Data.InputState;
}

Bool CInput::IsKeyDown(const EKeyCode &code) {
	return m_InputStatePtr->keyboard.pressed[code];
}

Bool CInput::IsKeyUp(const EKeyCode &code) {
	return m_InputStatePtr->keyboard.released[code];
}

Bool CInput::IsMouseDown(const EMouseCode &code) {
	return m_InputStatePtr->mouse.pressed[code];
}

Bool CInput::IsMouseUp(const EMouseCode &code) {
	return m_InputStatePtr->mouse.released[code];
}

SVector2 CInput::GetMousePosition() {
	return m_InputStatePtr->mouse.position;
}

Float32 CInput::GetMousePositionX() {
	return GetMousePosition().x;
}

Float32 CInput::GetMousePositionY() {
	return GetMousePosition().y;
}

String CInput::GetInput() {
	return m_InputStatePtr->keyboard.input;
}

VISRCEND
