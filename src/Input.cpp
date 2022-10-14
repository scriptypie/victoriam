//
// Created by Вячеслав Кривенко on 11.10.2022.
//

#include "GLFWWindow.hpp"

#include <Victoriam/Input/Input.hpp>

VISRCBEG

void cInput::Init(const SPtr<cWindow> &window) {
	m_InputStatePtr = &((cGLFWWindow*)window.get())->m_Data.InputState;
}

Bool cInput::IsKeyDown(const eKeyCode &code) {
	return m_InputStatePtr->keyboard.pressed[code];
}

Bool cInput::IsKeyUp(const eKeyCode &code) {
	return m_InputStatePtr->keyboard.released[code];
}

Bool cInput::IsMouseDown(const eMouseCode &code) {
	return m_InputStatePtr->mouse.pressed[code];
}

Bool cInput::IsMouseUp(const eMouseCode &code) {
	return m_InputStatePtr->mouse.released[code];
}

sVector2 cInput::GetMousePosition() {
	return m_InputStatePtr->mouse.position;
}

Float32 cInput::GetMousePositionX() {
	return GetMousePosition().x;
}

Float32 cInput::GetMousePositionY() {
	return GetMousePosition().y;
}

String cInput::GetInput() {
	return m_InputStatePtr->keyboard.input;
}

VISRCEND
