// SimpleGameState.cpp
#include "SimpleGameState.h"
#include <iostream>

SimpleGameState::SimpleGameState(SceneManager& sceneManager) : m_sceneManager(sceneManager) {}

void SimpleGameState::Enter() {
    std::cout << "Entered SimpleGameState" << std::endl;
    m_sceneManager.SetActiveScene("SimpleScene");
    if (auto activeScene = m_sceneManager.GetActiveScene()) {
        activeScene->Initialize();
    } else {
        std::cerr << "Failed to get active scene in SimpleGameState::Enter()" << std::endl;
    }
}

void SimpleGameState::Exit() {
    std::cout << "Exited SimpleGameState" << std::endl;
}

void SimpleGameState::Update(float deltaTime) {
    m_sceneManager.Update(deltaTime);
}

void SimpleGameState::Render() {
    m_sceneManager.Render();
}