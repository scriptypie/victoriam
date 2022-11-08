//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#include <filesystem>
#include <utility>

#include <Victoriam/Application/ARuntimeApp.hpp>
#include <Victoriam/EventSystem/EEventDispatcher.hpp>
#include <Victoriam/Utils/UGeometryBuilder.hpp>
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
		info.Resolution = {1280, 800};
		info.Flags += WindowCreateWindowFlag_DefaultWindow;
		m_Window = CWindow::Create(info);
	}
	m_Window->SetEventCallbackFunction(BIND_EVENT_FN(CRuntimeApp::OnEvent));
	CInput::Init(m_Window);
	rendererCreateInfo.WindowPtr = m_Window;
	m_Renderer = CRenderer::Create(rendererCreateInfo);
	m_Renderer->Setup();

	m_World = CWorld::Create(m_Renderer);
	m_Renderer->CreateDescriptors(m_World);



	SGeometryDataCreateInfo sphereCreateInfo = CGeometryBuilder::Get().LoadDefaultFromFile("testsphere.obj");
	SGeometryDataCreateInfo cubeCreateInfo = CGeometryBuilder::Get().LoadDefaultFromFile("testcube.obj");
	SGeometryDataCreateInfo monkeyCreateInfo = CGeometryBuilder::Get().LoadDefaultFromFile("monkey.obj");

	CGeometryData sphereGeometryData = m_Renderer->CreateGeometryData(sphereCreateInfo);
	CGeometryData cubeGeometryData = m_Renderer->CreateGeometryData(cubeCreateInfo);
	CGeometryData monkeyGeometryData = m_Renderer->CreateGeometryData(monkeyCreateInfo);

	{
		auto cube = m_World->CreateGameObject("TestSphere");
		cube->AddComponent<SComponentRenderable>(sphereGeometryData);
		auto transform = cube->AddComponent<SComponentTransform>();
		transform->Translation = { -2, 0, 2 };
	}
	{
		auto monkey = m_World->CreateGameObject("TestMonkey");
		monkey->AddComponent<SComponentRenderable>(monkeyGeometryData);
		auto transform = monkey->AddComponent<SComponentTransform>();
		transform->Translation = { 0, 2, 3 };
		transform->Rotation = { 0, -30, 180 };
	}
	{
		auto cube = m_World->CreateGameObject("TestCube");
		cube->AddComponent<SComponentRenderable>(cubeGeometryData);
		auto transform = cube->AddComponent<SComponentTransform>();
		transform->Translation = { 2, 0, 3 };
		transform->Scale = 2.0F;
	}
	{
		auto sun = m_World->CreateGameObject("Sun");
		sun->AddComponent<SComponentSun>(SVector3(1.0F, 3.0F, -3.0F));
	}
	{
		auto camera = m_World->CreateGameObject("MainCamera");
		auto camcomp = camera->AddComponent<SComponentCamera>();
		camcomp->Camera.SetViewBounds(0.01F, 1000.0F);
		camcomp->Camera.SetFovY(glm::radians(65.0F));
		auto ctc = camera->AddComponent<SComponentTransform>();
		ctc->Translation = { 0.3F, 0.7F, 9.5F };
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
	CTimestep currentTime = {};

	while (m_running) {
		m_Window->Update();

		CTimestep newTime = {};
		Float32 frameTime = currentTime.Delta() - newTime.Delta();
		currentTime = newTime;

		for (auto & state : m_stateController)
		{
			state->OnUpdate(frameTime);
		}
		// m_Renderer->BeginUIFrame();
		for (auto& state : m_stateController)
		{
			//state->OnUpdateGUI();
		}
		if (auto frameInfo = m_Renderer->BeginFrame(m_World))
		{
			m_Renderer->DrawFrame(frameInfo, m_World);
			//m_Renderer->EndUIFrame(frameInfo.CommandBuffer);
			m_Renderer->EndFrame(frameInfo);
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
