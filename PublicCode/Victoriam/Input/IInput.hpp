//
// Created by Вячеслав Кривенко on 11.10.2022.
//

#ifndef VICTORIAM_IINPUT_HPP
#define VICTORIAM_IINPUT_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/Input/IKeycode.hpp>
#include <Victoriam/Input/IMousecode.hpp>
#include <Victoriam/Input/IPadcode.hpp>
#include <Victoriam/Input/IPadaxis.hpp>
#include <Victoriam/Math/MVector2.hpp>
#include <Victoriam/Graphics/GWindow.hpp>

VISRCBEG

class VIDECL CInput
{
	inline static struct SInputState* m_InputStatePtr = nullptr;
public:
	VIDECL static void Init(const SPtr<CWindow>& window);
	VIDECL static Bool IsKeyDown(const EKeyCode& code);
	VIDECL static Bool IsKeyUp(const EKeyCode& code);
	VIDECL static Bool IsMouseDown(const EMouseCode& code);
	VIDECL static Bool IsMouseUp(const EMouseCode& code);
	VIDECL static String GetInput();
	VIDECL static SVector2 GetMousePosition();
	VIDECL static Float32 GetMousePositionX();
	VIDECL static Float32 GetMousePositionY();
};

VISRCEND

#endif //VICTORIAM_IINPUT_HPP
