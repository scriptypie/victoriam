#include <iostream>

#include <Ved/VEditorState.hpp>
#include <Victoriam/Application/AStartPoint.hpp>

VISRCBEG

class VIsualApp : public CRuntimeInstance
{
public:
	explicit VIsualApp(SRuntimeInstanceCreateInfo createInfo) : CRuntimeInstance(std::move(createInfo)) {
		AddState(new VEditorState());
	}
};

CRuntimeInstance* FCreateRuntimeInstance(const CArgumentLineTool& args)
{
	SRuntimeInstanceCreateInfo createInfo = {};
	createInfo.Arguments = args;
	createInfo.CWD = args[0].substr(0, args[0].size() - 6); // current path
	createInfo.AppName = "Ved";
	return new VIsualApp(createInfo);
}

VISRCEND
