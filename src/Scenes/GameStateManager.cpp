// src/Scenes/GameStateManager.cpp
#include "GameStateManager.h"

void GameStateManager::PushState(std::unique_ptr<GameState> state) {
    if (!m_states.empty()) {
        m_states.top()->Exit();
    }
    m_states.push(std::move(state));
    m_states.top()->Enter();
}

void GameStateManager::PopState() {
    if (!m_states.empty()) {
        m_states.top()->Exit();
        m_states.pop();
    }
    if (!m_states.empty()) {
        m_states.top()->Enter();
    }
}

void GameStateManager::Update(float deltaTime) {
    if (!m_states.empty()) {
        m_states.top()->Update(deltaTime);
    }
}

void GameStateManager::Render() {
    if (!m_states.empty()) {
        m_states.top()->Render();
    }
}
