#include <iostream>

#include "VIsual/VEditorState.hpp"
#include "Victoriam/Application/AStartPoint.hpp"

VISRCBEG

class VIsualApp : public CRuntimeApp
{
public:
	explicit VIsualApp(SRuntimeAppCreateInfo createInfo) : CRuntimeApp(std::move(createInfo)) {
		AddState(new VEditorState());
	}
};

CRuntimeApp* CreateRuntimeApp(const CArgumentLineTool& args)
{
	SRuntimeAppCreateInfo createInfo = {};
	createInfo.Arguments = args;
	createInfo.CWD = args[0].substr(0, args[0].size() - 6); // current path
	createInfo.AppName = "Ved";
	return new VIsualApp(createInfo);
}

VISRCEND
