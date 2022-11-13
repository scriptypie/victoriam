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
	// Note: Switch this to true to enable dockspace
	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	float minWinSizeX = style.WindowMinSize.x;
	style.WindowMinSize.x = 370.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	style.WindowMinSize.x = minWinSizeX;

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1

			if (ImGui::MenuItem("Exit")) CRuntimeInstance::Get().Shutdown();
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::ShowDemoWindow();

	ImGui::End();
}

VEditorState::~VEditorState() = default;

VISRCEND
