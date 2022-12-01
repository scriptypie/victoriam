//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_AAPPSTATE_HPP
#define VICTORIAM_AAPPSTATE_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

/**
 * Application State.
 * Single Application may handle several different states.
 */
class VIDECL CAppState
{
public:
    VIDECL virtual ~CAppState() = default;
	/**
	 * Will be called once when state is created.
	 */
    VIDECL virtual void OnCreate() = 0;
	/**
	 * Will be called every application tick.
	 * @param dt Delta time if Float32
	 */
    VIDECL virtual void OnUpdate(const Float32& dt) = 0;
	/**
	 * Will be called every application tick,
	 * update internal engine's GUI
	 */
	VIDECL virtual void OnUpdateGUI() = 0;
	/**
	 * Will be called once when state is getting destroyed,
	 * usually on application close.
	 */
	VIDECL virtual void OnDestroy() = 0;
};

/*
 * Poiner Type of AppState class
 */
VIDECL typedef SUnique<CAppState> PAppState;

VISRCEND

#endif //VICTORIAM_AAPPSTATE_HPP
