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

CRuntimeApp::CRuntimeApp(SRuntimeAppCreateInfo createInfo)
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
	SRendererCreateInfo rendererCreateInfo = {};
	{
		SWindowCreateInfo info;
		info.Name = m_info.AppName + " - NewWindow";
		info.Offset = {100, 100};
		info.Resolution = {500, 500};
		info.Flags += WindowCreateWindowFlag_DefaultWindow;
		m_Window = CWindow::Create(info);
	}
	m_Window->SetEventCallbackFunction(BIND_EVENT_FN(CRuntimeApp::OnEvent));
	CInput::Init(m_Window);

	rendererCreateInfo.WindowPtr = m_Window;

	m_Renderer = CRenderer::Create(rendererCreateInfo);

	const List<SVertex> vertices = {
			{ { 0.0F, -0.5F }, { 1.0F, 0.0F, 0.0F, 1.0F } },
			{ { 0.5F,  0.5F }, { 0.0F, 1.0F, 0.0F, 1.0F } },
			{ {-0.5F,  0.5F }, { 0.0F, 0.0F, 1.0F, 1.0F } },
	};
	m_Renderer->Setup();
	m_running = true;

	PVertexBuffer vertexBuffer = m_Renderer->CreateVertexBuffer(vertices);
	m_World = CWorld::Create();

	{
		auto triangle = m_World->CreateGameObject();
		auto &trc = triangle->AddComponent<SComponentRenderable>();
		trc.VertexBuffer = vertexBuffer;
		trc.Color = {0.1F, 0.8F, 0.1F};
		auto &ttc = triangle->AddComponent<SComponentTransform>();
		ttc.Translation = {};
	}
	{
		auto triangle2 = m_World->CreateGameObject();
		auto &trc = triangle2->AddComponent<SComponentRenderable>();
		trc.VertexBuffer = vertexBuffer;
		trc.Color = {0.8F, 0.1F, 0.2F};
		auto &ttc = triangle2->AddComponent<SComponentTransform>();
		ttc.Translation = { 0.3F, 0.4F };
		ttc.Scale = { 1.5F, 0.2F };
	}

}

CRuntimeApp::~CRuntimeApp() {
	if (m_running)
		Reload();
}

void CRuntimeApp::AddState(CAppState* state) {
	m_stateController.AddState(state);
	state->OnCreate();
}

void CRuntimeApp::AddOverlayState(CAppState* overlay) {
	m_stateController.AddOverlayState(overlay);
	overlay->OnCreate();
}

void CRuntimeApp::Reload() {
	m_running = false;
}

void CRuntimeApp::Close()
{
	g_Reload = false;
	m_running = false;
}

void Vi::CRuntimeApp::Startup() {
	while (m_running) {
		m_Window->Update();

		// begin gui update
		for (auto & state : m_stateController)
		{
			state->OnUpdate();
			state->OnUpdateGUI();
		}
		// end gui update

		m_Renderer->DrawFrame(m_World);
	}
	m_Renderer->Shutdown();
}

void CRuntimeApp::OnEvent(CEvent &e) {
	CEventDispatcher dispatcher(e);
	dispatcher.Dispatch<CWindowResizeEvent>(BIND_EVENT_FN(CRuntimeApp::OnWindowResize));
	dispatcher.Dispatch<CWindowCloseEvent>(BIND_EVENT_FN(CRuntimeApp::OnWindowClose));
}

bool CRuntimeApp::OnWindowResize(const CWindowResizeEvent &e) {
	printf("%s\n", e.ToString().c_str());
	m_Renderer->OnWindowResize(e.GetExtent());
	return true;
}

bool CRuntimeApp::OnWindowClose(const CWindowCloseEvent &e) {
	Close();
	return true;
}

VISRCEND
