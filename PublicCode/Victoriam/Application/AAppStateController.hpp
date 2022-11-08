//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_AAPPSTATECONTROLLER_HPP
#define VICTORIAM_AAPPSTATECONTROLLER_HPP

#include <Victoriam/Application/AAppState.hpp>

VISRCBEG

class VIDECL CAppStateController
{
    List<CAppState*> m_states = {};
    UInt32 m_insertIndex = {};
public:
    VIDECL CAppStateController() = default;
    VIDECL ~CAppStateController();

    VIDECL void AddState(CAppState* state);
    VIDECL void RemoveState(CAppState* state);
    VIDECL void AddOverlayState(CAppState* state);
    VIDECL void RemoveOverlayState(CAppState* state);

    VIDECL VIREQOUT inline List<CAppState*>::iterator begin() { return m_states.begin(); }
    VIDECL VIREQOUT inline List<CAppState*>::iterator end() { return m_states.end(); }
    VIDECL VIREQOUT inline List<CAppState*>::reverse_iterator rbegin() { return m_states.rbegin(); }
    VIDECL VIREQOUT inline List<CAppState*>::reverse_iterator rend() { return m_states.rend(); }
};

VISRCEND

#endif //VICTORIAM_AAPPSTATECONTROLLER_HPP
