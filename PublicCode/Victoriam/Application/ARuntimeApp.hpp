//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_ARUNTIMEAPP_HPP
#define VICTORIAM_ARUNTIMEAPP_HPP

#include <Victoriam/Application/AAppStateController.hpp>
#include <Victoriam/Application/ARuntimeAppCreateInfo.hpp>
#include <Victoriam/Graphics/GRenderer.hpp>
#include <Victoriam/World/WWorld.hpp>

VISRCBEG

class CRuntimeApp
{
	friend Int32 Main(Int32, Int8**);
	friend class CRenderer;
	inline static CRuntimeApp* s_instance = nullptr;
	SRuntimeAppCreateInfo m_info = {};
	Bool m_running = {};
	CAppStateController m_stateController = {};
	PRenderer m_Renderer = {};
	PWindow m_Window = nullptr;
	List<PVertexBuffer> m_VertexBuffers = {};
	PWorld m_World = {};
public:
	VIDECL explicit CRuntimeApp(SRuntimeAppCreateInfo  createInfo);
	virtual ~CRuntimeApp();

	VIDECL void AddState(CAppState* state);
	VIDECL void AddOverlayState(CAppState* overlay);

	VIDECL void Close();
	VIDECL void Reload();

	VIDECL inline static CRuntimeApp& Get() { return *s_instance; }
	VIDECL inline PRenderer& Renderer() { return m_Renderer; }
	VIDECL VIREQOUT inline String CWD() const { return m_info.CWD; }
	VIDECL VIREQOUT inline const SRuntimeAppCreateInfo& GetInfo() const { return m_info; }
private:
	void Startup();
	void OnEvent(CEvent& e);

	bool OnWindowResize(const CWindowResizeEvent& e);
	bool OnWindowClose(const CWindowCloseEvent& e);
};

// Needs to be defined on the client side
CRuntimeApp* CreateRuntimeApp(const CArgumentLineTool& args);

VISRCEND

#endif //VICTORIAM_ARUNTIMEAPP_HPP
