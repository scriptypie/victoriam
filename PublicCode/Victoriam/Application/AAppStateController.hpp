//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_AAPPSTATECONTROLLER_HPP
#define VICTORIAM_AAPPSTATECONTROLLER_HPP

#include <Victoriam/Application/AAppState.hpp>

VISRCBEG

class cAppStateController
{
    List<cAppState*> m_states = {};
    UInt32 m_insertIndex = {};
public:
    cAppStateController() = default;
    ~cAppStateController();

    void AddState(cAppState* state);
    void RemoveState(cAppState* state);
    void AddOverlayState(cAppState* state);
    void RemoveOverlayState(cAppState* state);

    VIDECL inline List<cAppState*>::iterator begin() { return m_states.begin(); }
    VIDECL inline List<cAppState*>::iterator end() { return m_states.end(); }
    VIDECL inline List<cAppState*>::reverse_iterator rbegin() { return m_states.rbegin(); }
    VIDECL inline List<cAppState*>::reverse_iterator rend() { return m_states.rend(); }
};

VISRCEND

#endif //VICTORIAM_AAPPSTATECONTROLLER_HPP
