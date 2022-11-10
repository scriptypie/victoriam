//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_AAPPSTATECHAIN_HPP
#define VICTORIAM_AAPPSTATECHAIN_HPP

#include <Victoriam/Application/AAppState.hpp>

VISRCBEG

/**
 * Manager class for application's state objects.
 * With this class engine can manipulate with states
 * like std::vector does this
 */
class VIDECL CAppStateChain
{
    List<CAppState*> m_states = {};
    UInt32 m_insertIndex = {};
public:
    VIDECL CAppStateChain() = default;
    VIDECL ~CAppStateChain();
	/**
	 * Add new state to statechain, and call state's OnCreate() function.
	 * @param state Already allocated state.
	 */
    VIDECL void AddState(CAppState* state);
	/**
	 * Removes state from statechain and call state's OnDestroy() function.
	 * @param state Previously used state.
	 */
    VIDECL void RemoveState(CAppState* state);
	/**
	 * Add new overlay state to statechain, like AddState() does,
	 * but without keeping insert index.
	 * @param state Already allocated state.
	 */
    VIDECL void AddOverlayState(CAppState* state);
	/**
	 * Removes state from statechain and call state's OnDestroy() function.
	 * @param state Previously used state.
	 */
    VIDECL void RemoveOverlayState(CAppState* state);

    VIDECL VIREQOUT inline List<CAppState*>::iterator begin() { return m_states.begin(); }
    VIDECL VIREQOUT inline List<CAppState*>::iterator end() { return m_states.end(); }
    VIDECL VIREQOUT inline List<CAppState*>::reverse_iterator rbegin() { return m_states.rbegin(); }
    VIDECL VIREQOUT inline List<CAppState*>::reverse_iterator rend() { return m_states.rend(); }
};

VISRCEND

#endif //VICTORIAM_AAPPSTATECHAIN_HPP
