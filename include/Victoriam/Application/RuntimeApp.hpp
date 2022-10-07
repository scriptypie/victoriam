//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_RUNTIMEAPP_HPP
#define VICTORIAM_RUNTIMEAPP_HPP

#include <Victoriam/Application/AppStateController.hpp>
#include <Victoriam/Application/RuntimeAppCreateInfo.hpp>

VISRCBEG

class cRuntimeApp
{
	inline static cRuntimeApp* s_instance = nullptr;
	friend Int32 Main(Int32, Int8**);
	sRuntimeAppCreateInfo m_info = {};
	Bool m_running = {};
	cAppStateController m_stateController = {};
public:
	VIDECL explicit cRuntimeApp(sRuntimeAppCreateInfo  createInfo);
	virtual ~cRuntimeApp();

	VIDECL void AddState(cAppState* state);
	VIDECL void AddOverlayState(cAppState* overlay);

	VIDECL void Close();

	VIDECL inline static cRuntimeApp& Get() { return *s_instance; }
	VIDECL inline const sRuntimeAppCreateInfo& GetInfo() const { return m_info; }
private:
	void Startup();
};

// Needs to be defined on the client side
cRuntimeApp* CreateRuntimeApp(const cArgumentLineTool& args);

VISRCEND

#endif //VICTORIAM_RUNTIMEAPP_HPP
