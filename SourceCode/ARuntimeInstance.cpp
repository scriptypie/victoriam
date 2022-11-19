//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#include <filesystem>
#include <utility>

#include <Victoriam/Application/ARuntimeInstance.hpp>
#include <Victoriam/EventSystem/EEventDispatcher.hpp>
#include <Victoriam/Utils/UGeometryBuilder.hpp>
#include "Victoriam/IO/IO.hpp"

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
		m_Window = CWindow::Create(info);
	}
	m_Window->SetEventCallbackFunction(BIND(CRuntimeInstance::OnEvent));
	CInput::Init(m_Window);
	rendererCreateInfo.WindowPtr = m_Window;
	m_Renderer = CRenderer::Create(rendererCreateInfo);
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

	UInt64 totalPoly = 0;

	for (auto x = 0; x < 48; x++) for (auto z = 0; z < 48; z++)
	{
		auto monkey = m_World->CreateGameObject("TestMonkey");
		monkey->AddComponent<SComponentRenderable>(monkeyGeometryData);
		totalPoly += monkeyGeometryData.GetPolycount();
		auto transform = monkey->AddComponent<SComponentTransform>();
		auto sc = CRandom<Float32>::Range(1.0F, 10.0F);
		transform->Translation = { x * 5 * sc - 300, 0, z * 5 * sc - 300 };
		transform->Rotation = { 0, 0, 180 };
		transform->Scale = sc;
	}
	{
		auto plane = m_World->CreateGameObject("Plane");
		plane->AddComponent<SComponentRenderable>(quadGeometryData);
		totalPoly += quadGeometryData.GetPolycount();
		auto transform = plane->AddComponent<SComponentTransform>();
		transform->Translation = { 0, 1, 0 };
		transform->Rotation = { 180.0F, 0.0F, 0.0F };
		transform->Scale = 1000.0F;
	}
	/*{
		auto cube = m_World->CreateGameObject("TestCube");
		cube->AddComponent<SComponentRenderable>(cubeGeometryData);
		auto transform = cube->AddComponent<SComponentTransform>();
		transform->Translation = { 2, 0, 3 };
		transform->Scale = 2.0F;
	}*/
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
		auto camcomp = camera->AddComponent<SComponentCamera>();
		camcomp->Camera.SetViewBounds(0.1F, 1000.0F);
		camcomp->Camera.SetFovY(FRadians(55.0F));
		auto ctc = camera->AddComponent<SComponentTransform>();
		ctc->Translation = { -6, -11, 24 };
	}

	ViLog("Total polygons: %llu\n", totalPoly);

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
