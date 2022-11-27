//
// Created by Вячеслав Кривенко on 27.11.2022.
//

#ifndef VICTORIAM_CTOGGLE_HPP
#define VICTORIAM_CTOGGLE_HPP

#include <Victoriam/Core/Containers/CConstant.hpp>
#include <Victoriam/Core/CMacroDefinitions.hpp>
#include <Victoriam/Core/CNumerics.hpp>
#include <Victoriam/Core/CCast.hpp>

VISRCBEG

class VIDECL CToggle {
	enum EState : Int8 {
		Undefined = -1,
		FalseState,
		TrueState
	};
	EState m_State;
public:
	VIDECL CToggle() : m_State(EState::Undefined) {}
	VIDECL CToggle(const Bool& b) : m_State(CCast<EState>(b)) {}
	VIDECL CToggle& operator=(const Bool& b) { m_State = CCast<EState>(b); return *this; }
	VIDECL ~CToggle() = default;

	VIDECL void Switch() { if (*this) *this = false; else *this = true; }
	VIDECL VIREQOUT Bool Get() const { return CCast<Bool>(m_State); }

	VIDECL constexpr operator Bool() const {
		return Get();
	}
	VIDECL Bool operator()() const {
		return Get();
	}
};

VISRCEND

#endif //VICTORIAM_CTOGGLE_HPP
