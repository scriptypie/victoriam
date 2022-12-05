//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_ARUNTIMEINSTANCE_HPP
#define VICTORIAM_ARUNTIMEINSTANCE_HPP

#include <Victoriam/Application/AAppStateChain.hpp>
#include <Victoriam/Application/ARuntimeInstanceCreateInfo.hpp>
#include <Victoriam/EventSystem/EWindowEvents.hpp>
#include <Victoriam/Graphics/GRenderer.hpp>
#include <Victoriam/Graphics/GWindow.hpp>
#include <Victoriam/Utils/UTimestep.hpp>
#include <Victoriam/World/WWorld.hpp>

VISRCBEG

/**
 * Main engine's class, where all systems born and dies.
 */
class VIDECL CRuntimeInstance
{
	friend Int32 Main(Int32, Int8**);
	friend class CRenderer;

	inline static CRuntimeInstance* s_instance = nullptr;

	SRuntimeInstanceCreateInfo m_info = {};
	Bool m_running = {};
	CAppStateChain m_stateController = {};
	PRenderer m_Renderer = {};
	PWindow m_Window = nullptr;
	PWorld m_World = {};
public:
	VIDECL explicit CRuntimeInstance(SRuntimeInstanceCreateInfo  createInfo);
	VIDECL virtual ~CRuntimeInstance();

	VIDECL void AddState(CAppState* state);
	VIDECL void AddOverlayState(CAppState* overlay);

	/**
	 * Safety destroy all systems, their resources, and exit
	 */
	VIDECL void Shutdown();
	/**
	 * Safety destroy all systems, their resources, exit, and then reload application.
	 */
	VIDECL void Reload();
	/**
	 * Getting access to actual loaded world.
	 * @return Reference to PWorld object.
	 */
	VIDECL VIREQOUT inline PWorld& World() { return m_World;}
	/**
	 * Getting access to engine's runtime.
	 * @return Reference to RuntimeApp class.
	 */
	VIDECL inline static CRuntimeInstance& Get() { return *s_instance; }
	/**
	 * Getting access to main renderer.
	 * @return Reference to PRenderer object.
	 */
	VIDECL VIREQOUT inline PRenderer& Renderer() { return m_Renderer; }
	/**
	 * Getting current working directory,
	 * @return String of current working directory.
	 */
	VIDECL VIREQOUT inline String CWD() const { return m_info.CWD; }
	VIDECL VIREQOUT inline const SRuntimeInstanceCreateInfo& GetInfo() const { return m_info; }
private:
	/**
	 * Called once on engine created and initialize all main systems.
	 */
	VIDECL void Startup();
	/**
	 * Handles all internal engine events (window resizing, input, etc..)
	 * @param e Reference to event object.
	 */
	VIDECL void OnEvent(CEvent& e);
	/**
	 * Callback to window resize event, getting called every time
	 * main window is resized.
	 * @param e Reference to window resize event object.
	 * @return Event handled or not. (PROBABLY MUST BE TRUE).
	 */
	VIDECL bool OnWindowResize(const CWindowResizeEvent& e);
	/**
	 * Callback to window close event, getting called if main window is closed.
	 * @param e Reference to window close event object.
	 * @return Event handled or not. (PROBABLY MUST BE TRUE).
	 */
	VIDECL bool OnWindowClose(const CWindowCloseEvent& e);
};

/**
 * Client defined function to create engine's runtime instance.
 * @param args Command line tool
 * @return New heap-allocated engine instance.
 */
VIDECL VIREQOUT CRuntimeInstance* FCreateRuntimeInstance(const CArgumentLineTool& args);

VISRCEND

#endif //VICTORIAM_ARUNTIMEINSTANCE_HPP
