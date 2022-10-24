//
// Created by Вячеслав Кривенко on 07.10.2022.
//


#include <Victoriam/Application/AAppStateController.hpp>

void Vi::CAppStateController::AddState(Vi::CAppState* state) {
    m_states.emplace(m_states.begin() + m_insertIndex, state);
    m_insertIndex += 1;
}

void Vi::CAppStateController::RemoveState(Vi::CAppState* state) {
    auto pos = std::find(m_states.begin(), m_states.begin() + m_insertIndex, state);
    if (pos != m_states.begin() + m_insertIndex)
    {
        m_states.erase(pos);
        m_insertIndex -= 1;
    }
}

void Vi::CAppStateController::AddOverlayState(Vi::CAppState* state) {
    m_states.emplace_back(state);
}

void Vi::CAppStateController::RemoveOverlayState(Vi::CAppState* state) {
    auto pos = std::find(m_states.begin(), m_states.end(), state);
    if (pos != m_states.end())
    {
        m_states.erase(pos);
    }
}

Vi::CAppStateController::~CAppStateController() {
    for (auto& state : m_states)
    {
        state->OnDestroy();
        delete state;
    }
}
