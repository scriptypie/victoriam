//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#include <iostream>

#include "VIsual/VEditorState.hpp"
#include <Victoriam/Application/ARuntimeApp.hpp>
#include "Victoriam/Input/IInput.hpp"

VISRCBEG

void VEditorState::OnCreate() {

}

void VEditorState::OnUpdate() {
	if (CInput::IsKeyDown(EKeyCode::Q) && CInput::IsKeyDown(EKeyCode::LeftCommand)) // Shortcut for fast (safe) exit
		CRuntimeApp::Get().Close();

}

void VEditorState::OnDestroy() {

}

void VEditorState::OnUpdateGUI() {

}

VEditorState::~VEditorState() = default;

VISRCEND
