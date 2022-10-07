//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#include <filesystem>

#include <Victoriam/Application/RuntimeApp.hpp>
#include <utility>

Vi::cRuntimeApp::cRuntimeApp(sRuntimeAppCreateInfo createInfo)
	: m_info(std::move(createInfo))
{
	s_instance = this;
	if (m_info.CWD.empty())
		m_info.CWD = std::filesystem::current_path().string();

	//m_running = true;
}

Vi::cRuntimeApp::~cRuntimeApp() {
	if (m_running)
		Close();
}

void Vi::cRuntimeApp::AddState(cAppState* state) {
	m_stateController.AddState(state);
	state->OnCreate();
}

void Vi::cRuntimeApp::AddOverlayState(cAppState* overlay) {
	m_stateController.AddOverlayState(overlay);
	overlay->OnCreate();
}

void Vi::cRuntimeApp::Close() {
	m_running = false;
}

void Vi::cRuntimeApp::Startup() {
	while (m_running)
	{

	}
}
