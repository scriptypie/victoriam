//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#include <filesystem>
#include <utility>

#include <Victoriam/Application/ARuntimeApp.hpp>
#include <Victoriam/EventSystem/EEventDispatcher.hpp>
#include "Victoriam/Input/IInput.hpp"

VISRCBEG

extern Bool g_Reload;

cRuntimeApp::cRuntimeApp(sRuntimeAppCreateInfo createInfo)
	: m_info(std::move(createInfo))
{
	s_instance = this;
	if (m_info.CWD.empty())
		m_info.CWD = std::filesystem::current_path().string();
	else {
#ifndef NDEBUG
		if      (m_info.CWD != "/Volumes/cdev/victoriam/cmake-build-debug/")
			std::filesystem::current_path(m_info.CWD);
#else
		if (m_info.CWD != "/Volumes/cdev/victoriam/cmake-build-release/")
			std::filesystem::current_path(m_info.CWD);
#endif
	}
	sRendererCreateInfo rendererCreateInfo = {};
	{
		sWindowCreateInfo info;
		info.Name = m_info.AppName + " - NewWindow";
		info.Offset = {100, 100};
		info.Resolution = {1280, 720};
		info.Flags += WindowCreateWindowFlag_DefaultWindow;
		m_Window = cWindow::Create(info);
	}
	m_Window->SetEventCallbackFunction(BIND_EVENT_FN(cRuntimeApp::OnEvent));
	cInput::Init(m_Window);

	rendererCreateInfo.WindowPtr = m_Window;

	m_Renderer = cRenderer::Create(rendererCreateInfo);

	const List<sVertex> vertices = {
			{ { 0.0F, -0.5F } },
			{ { 0.5F,  0.5F } },
			{ {-0.5F,  0.5F } },
	};
	m_Renderer->PushVertexBuffer(vertices);

	m_Renderer->Setup();
	m_running = true;
}

cRuntimeApp::~cRuntimeApp() {
	if (m_running)
		Reload();
}

void cRuntimeApp::AddState(cAppState* state) {
	m_stateController.AddState(state);
	state->OnCreate();
}

void cRuntimeApp::AddOverlayState(cAppState* overlay) {
	m_stateController.AddOverlayState(overlay);
	overlay->OnCreate();
}

void cRuntimeApp::Reload() {
	m_running = false;
}

void cRuntimeApp::Close()
{
	g_Reload = false;
	m_running = false;
}

void Vi::cRuntimeApp::Startup() {
	while (m_running) {
		m_Window->Update();

		// begin gui update
		for (auto & state : m_stateController)
		{
			state->OnUpdate();
			state->OnUpdateGUI();
		}
		// end gui update

		m_Renderer->DrawFrame();
	}
	m_Renderer->Shutdown();
}

void cRuntimeApp::OnEvent(cEvent &e) {
	cEventDispatcher dispatcher(e);
	dispatcher.Dispatch<cWindowResizeEvent>(BIND_EVENT_FN(cRuntimeApp::OnWindowResize));
	dispatcher.Dispatch<cWindowCloseEvent>(BIND_EVENT_FN(cRuntimeApp::OnWindowClose));
}

bool cRuntimeApp::OnWindowResize(const cWindowResizeEvent &e) {
	printf("%s\n", e.ToString().c_str());
	m_Renderer->OnWindowResize(e.GetExtent());
	return true;
}

bool cRuntimeApp::OnWindowClose(const cWindowCloseEvent &e) {
	Close();
	return true;
}

VISRCEND
