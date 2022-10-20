#include <iostream>

#include "VIsual/VEditorState.hpp"
#include "Victoriam/Application/AStartPoint.hpp"

VISRCBEG

class VIsualApp : public cRuntimeApp
{
public:
	explicit VIsualApp(sRuntimeAppCreateInfo createInfo) : cRuntimeApp(std::move(createInfo)) {
		AddState(new VEditorState());
	}
};

cRuntimeApp* CreateRuntimeApp(const cArgumentLineTool& args)
{
	sRuntimeAppCreateInfo createInfo = {};
	createInfo.Arguments = args;
	createInfo.CWD = args[0].substr(0, args[0].size() - 6); // current path
	createInfo.AppName = "VIsual";
	return new VIsualApp(createInfo);
}

VISRCEND
