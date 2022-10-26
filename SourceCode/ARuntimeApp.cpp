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
		info.Resolution = {680, 680};
		info.Flags += WindowCreateWindowFlag_DefaultWindow;
		m_Window = CWindow::Create(info);
	}
	m_Window->SetEventCallbackFunction(BIND_EVENT_FN(CRuntimeApp::OnEvent));
	CInput::Init(m_Window);
	m_World = CWorld::Create();

	rendererCreateInfo.WindowPtr = m_Window;
	m_Renderer = CRenderer::Create(rendererCreateInfo);
	m_Renderer->Setup();

	const List<SVertex> vertices = {
			// left face (white)
			{{-.5f, -.5f, -.5f}, {.9f, .9f, .9f, 1}},
			{{-.5f, .5f, .5f}, {.9f, .9f, .9f, 1}},
			{{-.5f, -.5f, .5f}, {.9f, .9f, .9f, 1}},
			{{-.5f, -.5f, -.5f}, {.9f, .9f, .9f, 1}},
			{{-.5f, .5f, -.5f}, {.9f, .9f, .9f, 1}},
			{{-.5f, .5f, .5f}, {.9f, .9f, .9f, 1}},

			// right face (yellow)
			{{.5f, -.5f, -.5f}, {.8f, .8f, .1f, 1}},
			{{.5f, .5f, .5f}, {.8f, .8f, .1f, 1}},
			{{.5f, -.5f, .5f}, {.8f, .8f, .1f, 1}},
			{{.5f, -.5f, -.5f}, {.8f, .8f, .1f, 1}},
			{{.5f, .5f, -.5f}, {.8f, .8f, .1f, 1}},
			{{.5f, .5f, .5f}, {.8f, .8f, .1f, 1}},

			// top face (orange, remember y axis points down)
			{{-.5f, -.5f, -.5f}, {.9f, .6f, .1f, 1}},
			{{.5f, -.5f, .5f}, {.9f, .6f, .1f, 1}},
			{{-.5f, -.5f, .5f}, {.9f, .6f, .1f, 1}},
			{{-.5f, -.5f, -.5f}, {.9f, .6f, .1f, 1}},
			{{.5f, -.5f, -.5f}, {.9f, .6f, .1f, 1}},
			{{.5f, -.5f, .5f}, {.9f, .6f, .1f, 1}},

			// bottom face (red)
			{{-.5f, .5f, -.5f}, {.8f, .1f, .1f, 1}},
			{{.5f, .5f, .5f}, {.8f, .1f, .1f, 1}},
			{{-.5f, .5f, .5f}, {.8f, .1f, .1f, 1}},
			{{-.5f, .5f, -.5f}, {.8f, .1f, .1f, 1}},
			{{.5f, .5f, -.5f}, {.8f, .1f, .1f, 1}},
			{{.5f, .5f, .5f}, {.8f, .1f, .1f, 1}},

			// nose face (blue)
			{{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f, 1}},
			{{.5f, .5f, 0.5f}, {.1f, .1f, .8f, 1}},
			{{-.5f, .5f, 0.5f}, {.1f, .1f, .8f, 1}},
			{{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f, 1}},
			{{.5f, -.5f, 0.5f}, {.1f, .1f, .8f, 1}},
			{{.5f, .5f, 0.5f}, {.1f, .1f, .8f, 1}},

			// tail face (green)
			{{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f, 1}},
			{{.5f, .5f, -0.5f}, {.1f, .8f, .1f, 1}},
			{{-.5f, .5f, -0.5f}, {.1f, .8f, .1f, 1}},
			{{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f, 1}},
			{{.5f, -.5f, -0.5f}, {.1f, .8f, .1f, 1}},
			{{.5f, .5f, -0.5f}, {.1f, .8f, .1f, 1}}
	};

	PVertexBuffer vertexBuffer = m_Renderer->CreateVertexBuffer(vertices);

	{
		auto triangle = m_World->CreateGameObject();
		auto &trc = triangle->AddComponent<SComponentRenderable>();
		trc.VertexBuffer = vertexBuffer;
		trc.Color = {0.2F, 0.8F, 0.3F};
		auto& ttc = triangle->AddComponent<SComponentTransform>();
		ttc.Translation = { 0, 0, 0.5F };
		ttc.Scale = { 0.2F, 0.2F, 0.2F };
	}

	m_running = true;
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
		if (auto commandBuffer = m_Renderer->BeginFrame())
		{
			m_Renderer->DrawFrame(commandBuffer, m_World);
			m_Renderer->EndFrame(commandBuffer);
		}
	}
	m_Renderer->Shutdown(m_World);
}

void CRuntimeApp::OnEvent(CEvent &e) {
	CEventDispatcher dispatcher(e);
	dispatcher.Dispatch<CWindowResizeEvent>(BIND_EVENT_FN(CRuntimeApp::OnWindowResize));
	dispatcher.Dispatch<CWindowCloseEvent>(BIND_EVENT_FN(CRuntimeApp::OnWindowClose));
}

bool CRuntimeApp::OnWindowResize(const CWindowResizeEvent &e) {
	ViLog("%s\n", e.ToString().c_str());
	m_Renderer->OnWindowResize(e.GetExtent());
	return true;
}

bool CRuntimeApp::OnWindowClose(const CWindowCloseEvent &e) {
	Close();
	return true;
}

VISRCEND
