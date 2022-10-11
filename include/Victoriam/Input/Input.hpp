//
// Created by Вячеслав Кривенко on 11.10.2022.
//

#ifndef VICTORIAM_INPUT_HPP
#define VICTORIAM_INPUT_HPP

#include <Victoriam/Core/Base.hpp>
#include <Victoriam/Input/Keycode.hpp>
#include <Victoriam/Input/Mousecode.hpp>
#include <Victoriam/Input/Padcode.hpp>
#include <Victoriam/Input/Padaxis.hpp>
#include <Victoriam/Math/Vector2.hpp>
#include <Victoriam/Graphics/Window.hpp>

VISRCBEG

class VIDECL cInput
{
	inline static struct sInputState* m_InputStatePtr = nullptr;
public:
	VIDECL static void Init(const SPtr<cWindow>& window);
	VIDECL static Bool IsKeyDown(const eKeyCode& code);
	VIDECL static Bool IsKeyUp(const eKeyCode& code);
	VIDECL static Bool IsMouseDown(const eMouseCode& code);
	VIDECL static Bool IsMouseUp(const eMouseCode& code);
	VIDECL static String GetInput();
	VIDECL static sVector2 GetMousePosition();
	VIDECL static Float32 GetMousePositionX();
	VIDECL static Float32 GetMousePositionY();
};

VISRCEND

#endif //VICTORIAM_INPUT_HPP
