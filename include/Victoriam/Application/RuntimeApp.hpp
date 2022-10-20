//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_RUNTIMEAPP_HPP
#define VICTORIAM_RUNTIMEAPP_HPP

#include <Victoriam/Application/AppStateController.hpp>
#include <Victoriam/Application/RuntimeAppCreateInfo.hpp>
#include <Victoriam/Graphics/Renderer.hpp>

VISRCBEG

class cRuntimeApp
{
	friend Int32 Main(Int32, Int8**);
	friend class cRenderer;
	inline static cRuntimeApp* s_instance = nullptr;
	sRuntimeAppCreateInfo m_info = {};
	Bool m_running = {};
	cAppStateController m_stateController = {};
	pRenderer m_Renderer = {};
	pWindow m_Window = nullptr;
public:
	VIDECL explicit cRuntimeApp(sRuntimeAppCreateInfo  createInfo);
	virtual ~cRuntimeApp();

	VIDECL void AddState(cAppState* state);
	VIDECL void AddOverlayState(cAppState* overlay);

	VIDECL void Close();
	VIDECL void Reload();

	VIDECL inline static cRuntimeApp& Get() { return *s_instance; }
	VIDECL inline pRenderer& Renderer() { return m_Renderer; }
	VIDECL VIREQOUT inline String CWD() const { return m_info.CWD; }
	VIDECL VIREQOUT inline const sRuntimeAppCreateInfo& GetInfo() const { return m_info; }
private:
	void Startup();
	void OnEvent(cEvent& e);

	bool OnWindowResize(const cWindowResizeEvent& e);
	bool OnWindowClose(const cWindowCloseEvent& e);
};

// Needs to be defined on the client side
cRuntimeApp* CreateRuntimeApp(const cArgumentLineTool& args);

VISRCEND

#endif //VICTORIAM_RUNTIMEAPP_HPP
