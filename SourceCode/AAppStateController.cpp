//
// Created by Вячеслав Кривенко on 07.10.2022.
//


#include <Victoriam/Application/AAppStateController.hpp>

VISRCBEG

void CAppStateController::AddState(CAppState* state) {
    m_states.emplace(m_states.begin() + m_insertIndex, state);
    m_insertIndex += 1;
}

void CAppStateController::RemoveState(CAppState* state) {
    auto pos = std::find(m_states.begin(), m_states.begin() + m_insertIndex, state);
    if (pos != m_states.begin() + m_insertIndex)
    {
        m_states.erase(pos);
        m_insertIndex -= 1;
    }
}

void CAppStateController::AddOverlayState(CAppState* state) {
    m_states.emplace_back(state);
}

void CAppStateController::RemoveOverlayState(CAppState* state) {
    auto pos = std::find(m_states.begin(), m_states.end(), state);
    if (pos != m_states.end())
        m_states.erase(pos);
}

CAppStateController::~CAppStateController() {
    for (auto& state : m_states)
    {
        state->OnDestroy();
        delete state;
    }
}

VISRCEND
