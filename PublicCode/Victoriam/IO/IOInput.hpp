//
// Created by Вячеслав Кривенко on 11.10.2022.
//

#ifndef VICTORIAM_IOINPUT_HPP
#define VICTORIAM_IOINPUT_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/IO/IOKeycode.hpp>
#include <Victoriam/IO/IOMousecode.hpp>
#include <Victoriam/IO/IOPadcode.hpp>
#include <Victoriam/IO/IOPadaxis.hpp>
#include <Victoriam/Graphics/GWindow.hpp>

VISRCBEG

class VIDECL CInput
{
	inline static struct SInputState* m_InputStatePtr = nullptr;
public:
	VIDECL          static void Init(const SShared<CWindow>& window);
	VIDECL VIREQOUT static Bool IsKeyDown(const EKeyCode& code);
	VIDECL VIREQOUT static Bool IsKeyUp(const EKeyCode& code);
	VIDECL VIREQOUT static Bool IsMouseDown(const EMouseCode& code);
	VIDECL VIREQOUT static Bool IsMouseUp(const EMouseCode& code);
	VIDECL VIREQOUT static String GetInput();
	VIDECL VIREQOUT static SVector2 GetMousePosition();
	VIDECL VIREQOUT static Float32 GetMousePositionX();
	VIDECL VIREQOUT static Float32 GetMousePositionY();
};

VISRCEND

#endif //VICTORIAM_IOINPUT_HPP
