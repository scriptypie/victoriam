//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#include <filesystem>

#include <Victoriam/Application/ARuntimeInstance.hpp>
#include <Victoriam/EventSystem/EEventDispatcher.hpp>
#include <Victoriam/Utils/UGeometryBuilder.hpp>
#include <Victoriam/IO/IO.hpp>

VISRCBEG

extern Bool g_Reload;

CRuntimeInstance::CRuntimeInstance(SRuntimeInstanceCreateInfo createInfo)
	: m_info(std::move(createInfo))
{
	s_instance = this;
	if (m_info.CWD.empty())
		m_info.CWD = std::filesystem::current_path().string();
	else {
#ifndef NDEBUG
		if (m_info.CWD != "/Volumes/cdev/victoriam/build/debug/")
			std::filesystem::current_path(m_info.CWD);
#else
		if (m_info.CWD != "/Volumes/cdev/victoriam/build/release/")
			std::filesystem::current_path(m_info.CWD);
#endif
	}
	SRendererCreateInfo rendererCreateInfo = {};
	{
		SWindowCreateInfo info;
		info.Name = m_info.AppName + " - NewWindow";
		info.Resolution = {800, 500};
		info.Flags += WindowCreateWindowFlag_DefaultWindow;
		m_Window = Window::Create(info);
		m_Window->SetEventCallbackFunction(BIND(CRuntimeInstance::OnEvent));
	}
	CInput::Init(m_Window);
	rendererCreateInfo.WindowPtr = m_Window;
	m_Renderer = Renderer::Create(rendererCreateInfo);
	m_Renderer->Setup();

	m_World = CWorld::Create(m_Renderer);
	m_Renderer->CreateDescriptors(m_World);

	SGeometryDataCreateInfo sphereCreateInfo = CGeometryBuilder::Get().LoadDefaultFromFile("sphere.vi3d");
	SGeometryDataCreateInfo cubeCreateInfo = CGeometryBuilder::Get().LoadDefaultFromFile("cube.vi3d");
	SGeometryDataCreateInfo monkeyCreateInfo = CGeometryBuilder::Get().LoadDefaultFromFile("monkey.vi3d");
	SGeometryDataCreateInfo quadCreateInfo = CGeometryBuilder::Get().LoadDefaultFromFile("quad.vi3d");

	CGeometryData sphereGeometryData = m_Renderer->CreateGeometryData(sphereCreateInfo);
	CGeometryData cubeGeometryData = m_Renderer->CreateGeometryData(cubeCreateInfo);
	CGeometryData monkeyGeometryData = m_Renderer->CreateGeometryData(monkeyCreateInfo);
	CGeometryData quadGeometryData = m_Renderer->CreateGeometryData(quadCreateInfo);

	for (auto x = 0; x < 32; x++) for (auto z = 0; z < 32; z++)
	{
		auto monkey = m_World->CreateGameObject("TestMonkey");
		monkey->AddComponent<SComponentRenderable>(monkeyGeometryData);
		monkey->AddComponent<SComponentRenderable>(monkeyGeometryData);
		auto transform = monkey->AddComponent<SComponentTransform>();
		auto sc = CRandom<Float32>::Range(20.0F, 100.0F);
		transform->Translation = { x * 5 * sc - 700, -10, z * 5 * sc - 700 };
		transform->Rotation = { 0, 0, 180 };
		transform->Scale = sc;
	}
	{
		auto plane = m_World->CreateGameObject("Plane");
		plane->AddComponent<SComponentRenderable>(quadGeometryData);
		auto transform = plane->AddComponent<SComponentTransform>();
		transform->Translation = { 0, 0, 0 };
		transform->Rotation = { 180.0F, 0.0F, 0.0F };
		transform->Scale = 1000.0F;
	}
	{
		auto sun = m_World->CreateGameObject("Sun");
		sun->AddComponent<SComponentSun>(SVector3(1.0F, 3.0F, -3.0F));
	}
	for (auto i = 0; i < 8; i++)
	{
		for (auto j = 0; j < 8; j++) {
			auto light = m_World->CreateGameObject("Light");
			auto componentTransform = light->AddComponent<SComponentTransform>();
			componentTransform->Translation = {i * 50, -10, j * 50};
			auto componentPointLight = light->AddComponent<SComponentPointLight>();
			componentPointLight->LightColor.w = 50.0F;
		}
	}
	{
		auto camera = m_World->CreateGameObject("MainCamera");
		auto componentCamera = camera->AddComponent<SComponentCamera>();
		componentCamera->Camera.SetViewBounds(0.1F, 10000.0F);
		componentCamera->Camera.SetFovY(FRadians(65.0F));
		auto componentTransform = camera->AddComponent<SComponentTransform>();
		componentTransform->Translation = { -75, -50, -32 };
	}

	m_running = true;
}

CRuntimeInstance::~CRuntimeInstance() {
	if (m_running)
		Reload();
}

void CRuntimeInstance::AddState(CAppState* state) {
	m_stateController.AddState(state);
	state->OnCreate();
}

void CRuntimeInstance::AddOverlayState(CAppState* overlay) {
	m_stateController.AddOverlayState(overlay);
	overlay->OnCreate();
}

void CRuntimeInstance::Reload() {
	m_running = false;
}

void CRuntimeInstance::Shutdown()
{
	g_Reload = false;
	m_running = false;
}

void Vi::CRuntimeInstance::Startup() {
	CTimestep currentTime = {};

	while (m_running) {
		m_Window->Update();

		CTimestep newTime = {};
		Float32 frameTime = currentTime.Delta() - newTime.Delta();
		currentTime = newTime;

		for (auto & state : m_stateController) {
			state->OnUpdate(frameTime);
		}
		if (auto frameInfo = m_Renderer->BeginFrame()) {
			m_Renderer->DrawFrame(frameInfo, m_World);
			m_Renderer->EndFrame(frameInfo);
		}
	}
	m_Renderer->Shutdown(m_World);
}

void CRuntimeInstance::OnEvent(CEvent &e) {
	CEventDispatcher dispatcher(e);
	dispatcher.Dispatch<CWindowResizeEvent>(BIND(CRuntimeInstance::OnWindowResize));
	dispatcher.Dispatch<CWindowCloseEvent>(BIND(CRuntimeInstance::OnWindowClose));
}

bool CRuntimeInstance::OnWindowResize(const CWindowResizeEvent &e) {
	m_Renderer->OnWindowResize(e.GetExtent());
	return true;
}

bool CRuntimeInstance::OnWindowClose(const CWindowCloseEvent &e) {
	Shutdown();
	return true;
}

VISRCEND
