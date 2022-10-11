//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#include <iostream>

#include "VIsual/EditorState.hpp"
#include <Victoriam/Application/RuntimeApp.hpp>
#include <Victoriam/Input/Input.hpp>

VISRCBEG

void EditorState::OnCreate() {
	std::cout << "EditorState::OnCreate()" << std::endl;
}

void EditorState::OnUpdate() {
	if (cInput::IsKeyDown(eKeyCode::Escape) && cInput::IsKeyDown(eKeyCode::LeftAlt)) // Shortcut for fast (safe) exit
		cRuntimeApp::Get().Close();

	
	std::cout << "Input: " << cInput::GetInput() << std::endl;
}

void EditorState::OnDestroy() {
	std::cout << "EditorState::OnDestroy()" << std::endl;
}

void EditorState::OnUpdateGUI() {

}

EditorState::~EditorState() {
	std::cout << "EditorState::~EditorState()" << std::endl;
}

VISRCEND
