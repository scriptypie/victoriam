#include <iostream>

#include "VIsual/EditorState.hpp"
#include "Victoriam/Application/StartPoint.hpp"

VISRCBEG

class VIsualApp : public cRuntimeApp
{
public:
	explicit VIsualApp(sRuntimeAppCreateInfo createInfo) : cRuntimeApp(std::move(createInfo)) {
		AddState(new EditorState());
	}
};

cRuntimeApp* CreateRuntimeApp(const cArgumentLineTool& args)
{
	sRuntimeAppCreateInfo createInfo = {};
	createInfo.Arguments = args;
	createInfo.AppName = "VIsual";
	return new VIsualApp(createInfo);
}

VISRCEND
