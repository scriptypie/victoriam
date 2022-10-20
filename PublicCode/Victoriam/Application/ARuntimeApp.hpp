//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_ARUNTIMEAPP_HPP
#define VICTORIAM_ARUNTIMEAPP_HPP

#include <Victoriam/Application/AAppStateController.hpp>
#include <Victoriam/Application/ARuntimeAppCreateInfo.hpp>
#include <Victoriam/Graphics/GRenderer.hpp>

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
	List<pVertexBuffer> m_VertexBuffers = {};
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

#endif //VICTORIAM_ARUNTIMEAPP_HPP
