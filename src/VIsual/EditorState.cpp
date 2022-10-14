//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#include <iostream>

#include "VIsual/EditorState.hpp"
#include <Victoriam/Application/RuntimeApp.hpp>
#include <Victoriam/Input/Input.hpp>

VISRCBEG

void EditorState::OnCreate() {

}

void EditorState::OnUpdate() {
	if (cInput::IsKeyDown(eKeyCode::Q) && cInput::IsKeyDown(eKeyCode::LeftCommand)) // Shortcut for fast (safe) exit
		cRuntimeApp::Get().Close();

}

void EditorState::OnDestroy() {

}

void EditorState::OnUpdateGUI() {

}

EditorState::~EditorState() = default;

VISRCEND
