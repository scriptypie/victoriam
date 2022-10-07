//
// Created by Вячеслав Кривенко on 07.10.2022.
//


#include <Victoriam/Application/AppStateController.hpp>

void Vi::cAppStateController::AddState(Vi::cAppState* state) {
    m_states.emplace(m_states.begin() + m_insertIndex, state);
    m_insertIndex += 1;
}

void Vi::cAppStateController::RemoveState(Vi::cAppState* state) {
    auto pos = std::find(m_states.begin(), m_states.begin() + m_insertIndex, state);
    if (pos != m_states.begin() + m_insertIndex)
    {
        m_states.erase(pos);
        m_insertIndex -= 1;
    }
}

void Vi::cAppStateController::AddOverlayState(Vi::cAppState* state) {
    m_states.emplace_back(state);
}

void Vi::cAppStateController::RemoveOverlayState(Vi::cAppState* state) {
    auto pos = std::find(m_states.begin(), m_states.end(), state);
    if (pos != m_states.end())
    {
        m_states.erase(pos);
    }
}

Vi::cAppStateController::~cAppStateController() {
    for (auto& state : m_states)
    {
        state->OnDestroy();
        delete state;
    }
}
