//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#include <Ved/VEditorState.hpp>
#include <Victoriam/Application/ARuntimeInstance.hpp>
#include <Victoriam/Input/IInput.hpp>

#include <imgui/imgui.h>

VISRCBEG

void VEditorState::OnCreate() {

}

void VEditorState::OnUpdate(const Float32& dt) {
	if (CInput::IsKeyDown(EKeyCode::Q) && CInput::IsKeyDown(EKeyCode::LeftCommand)) // Shortcut for fast (safe) exit
		CRuntimeInstance::Get().Shutdown();

	auto camera = CRuntimeInstance::Get().World()->FindGameObjectByName("MainCamera");
	auto [componentTransform, componentCamera] = camera->Group<SComponentTransform, SComponentCamera>();
	auto transform = componentTransform;
	auto cam = componentCamera->Camera;

	Float32 speed;
	if (CInput::IsKeyDown(EKeyCode::LeftShift))
		speed = 48.0F;
	else
		speed = 16.0F;

	if (CInput::IsKeyDown(EKeyCode::E))
		transform->Translation -= cam.Up() * dt * speed;
	if (CInput::IsKeyDown(EKeyCode::Q))
		transform->Translation += cam.Up() * dt * speed;
	if (CInput::IsKeyDown(EKeyCode::W))
		transform->Translation += cam.Front() * dt * speed;
	if (CInput::IsKeyDown(EKeyCode::S))
		transform->Translation -= cam.Front() * dt * speed;
	if (CInput::IsKeyDown(EKeyCode::A))
		transform->Translation -= cam.Right() * dt * speed;
	if (CInput::IsKeyDown(EKeyCode::D))
		transform->Translation += cam.Right() * dt * speed;

}

void VEditorState::OnDestroy() {

}

void VEditorState::OnUpdateGUI() {

}

VEditorState::~VEditorState() = default;

VISRCEND
