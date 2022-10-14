//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#include <filesystem>
#include <utility>

#include <Victoriam/Application/RuntimeApp.hpp>
#include <Victoriam/EventSystem/EventDispatcher.hpp>
#include <Victoriam/Input/Input.hpp>

VISRCBEG

extern Bool g_Reload;

cRuntimeApp::cRuntimeApp(sRuntimeAppCreateInfo createInfo)
	: m_info(std::move(createInfo))
{
	s_instance = this;
	if (m_info.CWD.empty())
		m_info.CWD = std::filesystem::current_path().string();

	{
		sWindowCreateInfo info;
		info.Name = m_info.AppName + " - NewWindow";
		info.Offset = {100, 100};
		info.Resolution = {1280, 800};
		info.Flags += WindowCreateWindowFlag_DefaultWindow;
		m_Window = cWindow::Create(info);
	}
	m_Window->SetEventCallbackFunction(BIND_EVENT_FN(cRuntimeApp::OnEvent));
	cInput::Init(m_Window);

	m_Device = cDevice::Create(m_Window);

	m_Pipeline = cPipeline::Create(m_Device, sPipelineCreateInfo(m_Window->GetWidth(), m_Window->GetHeight()));
	m_Pipeline->SetShader("Default");

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
	}
}

void cRuntimeApp::OnEvent(cEvent &e) {
	cEventDispatcher dispatcher(e);
	dispatcher.Dispatch<cWindowResizeEvent>(BIND_EVENT_FN(cRuntimeApp::OnWindowResize));
	dispatcher.Dispatch<cWindowCloseEvent>(BIND_EVENT_FN(cRuntimeApp::OnWindowClose));
}

bool cRuntimeApp::OnWindowResize(const cWindowResizeEvent &e) {
	printf("%s\n", e.ToString().c_str());
	return true;
}

bool cRuntimeApp::OnWindowClose(const cWindowCloseEvent &e) {
	Close();
	return true;
}

VISRCEND
