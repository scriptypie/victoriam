//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_STARTPOINT_HPP
#define VICTORIAM_STARTPOINT_HPP

#include <Victoriam/Core/Base.hpp>
#include <Victoriam/Application/RuntimeApp.hpp>


VISRCBEG

extern cRuntimeApp* CreateRuntimeApp(const cArgumentLineTool& args);

Bool g_Reload = true;

Int32 Main(Int32 Argc, Int8** Args)
{
	while (g_Reload)
	{
		auto application = CreateRuntimeApp({Argc, Args});
		application->Startup();
		delete application;
	}
	return 0;
}

VISRCEND

#ifndef _WIN32
int main(int argc, char** argv)
{
	return Vi::Main(argc, argv);
}
#else
#include <Windows.h>
INT WinMain(HINSTANCE, HINSTANCE, PSTR, INT)
{
	return Vi::Main(__argc, __argv);
}
#endif

#endif //VICTORIAM_STARTPOINT_HPP
