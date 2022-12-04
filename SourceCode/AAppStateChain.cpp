//
// Created by Вячеслав Кривенко on 07.10.2022.
//


#include <Victoriam/Application/AAppStateChain.hpp>

VISRCBEG

void CAppStateChain::AddState(CAppState* state) {
    m_states.Emplace(m_states.begin() + m_insertIndex, state);
    m_insertIndex += 1;
}

void CAppStateChain::RemoveState(CAppState* state) {
    auto pos = FFind(m_states.begin(), m_states.begin() + m_insertIndex, state);
    if (pos != m_states.begin() + m_insertIndex)
    {
        m_states.Erase(pos);
        m_insertIndex -= 1;
    }
}

void CAppStateChain::AddOverlayState(CAppState* state) {
    m_states.EmplaceBack(state);
}

void CAppStateChain::RemoveOverlayState(CAppState* state) {
    auto pos = FFind(m_states.begin(), m_states.end(), state);
    if (pos != m_states.end())
        m_states.Erase(pos);
}

CAppStateChain::~CAppStateChain() {
    for (auto& state : m_states) {
        state->OnDestroy();
        delete state;
    }
}

VISRCEND
