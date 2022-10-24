//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_AAPPSTATECONTROLLER_HPP
#define VICTORIAM_AAPPSTATECONTROLLER_HPP

#include <Victoriam/Application/AAppState.hpp>

VISRCBEG

class CAppStateController
{
    List<CAppState*> m_states = {};
    UInt32 m_insertIndex = {};
public:
    CAppStateController() = default;
    ~CAppStateController();

    void AddState(CAppState* state);
    void RemoveState(CAppState* state);
    void AddOverlayState(CAppState* state);
    void RemoveOverlayState(CAppState* state);

    VIDECL inline List<CAppState*>::iterator begin() { return m_states.begin(); }
    VIDECL inline List<CAppState*>::iterator end() { return m_states.end(); }
    VIDECL inline List<CAppState*>::reverse_iterator rbegin() { return m_states.rbegin(); }
    VIDECL inline List<CAppState*>::reverse_iterator rend() { return m_states.rend(); }
};

VISRCEND

#endif //VICTORIAM_AAPPSTATECONTROLLER_HPP
