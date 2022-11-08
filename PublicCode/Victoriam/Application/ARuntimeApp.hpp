//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_ARUNTIMEAPP_HPP
#define VICTORIAM_ARUNTIMEAPP_HPP

#include <Victoriam/Application/AAppStateController.hpp>
#include <Victoriam/Application/ARuntimeAppCreateInfo.hpp>
#include <Victoriam/Graphics/GRenderer.hpp>
#include <Victoriam/Utils/UTimestep.hpp>
#include <Victoriam/World/WWorld.hpp>

VISRCBEG

class VIDECL CRuntimeApp
{
	friend Int32 Main(Int32, Int8**);
	friend class CRenderer;

	inline static CRuntimeApp* s_instance = nullptr;

	SRuntimeAppCreateInfo m_info = {};
	Bool m_running = {};
	CAppStateController m_stateController = {};
	PRenderer m_Renderer = {};
	PWindow m_Window = nullptr;
	PWorld m_World = {};
public:
	VIDECL explicit CRuntimeApp(SRuntimeAppCreateInfo  createInfo);
	VIDECL virtual ~CRuntimeApp();

	VIDECL void AddState(CAppState* state);
	VIDECL void AddOverlayState(CAppState* overlay);

	VIDECL void Close();
	VIDECL void Reload();

	VIDECL VIREQOUT inline PWorld World() { return m_World;}
	VIDECL inline static CRuntimeApp& Get() { return *s_instance; }
	VIDECL VIREQOUT inline PRenderer& Renderer() { return m_Renderer; }
	VIDECL VIREQOUT inline String CWD() const { return m_info.CWD; }
	VIDECL VIREQOUT inline const SRuntimeAppCreateInfo& GetInfo() const { return m_info; }
private:
	VIDECL void Startup();
	VIDECL void OnEvent(CEvent& e);

	VIDECL bool OnWindowResize(const CWindowResizeEvent& e);
	VIDECL bool OnWindowClose(const CWindowCloseEvent& e);
};

// Needs to be defined on the client side
VIDECL VIREQOUT CRuntimeApp* CreateRuntimeApp(const CArgumentLineTool& args);

VISRCEND

#endif //VICTORIAM_ARUNTIMEAPP_HPP
