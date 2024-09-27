#include "SimpleGameState.h"
#include <iostream>

SimpleGameState::SimpleGameState(SceneManager& sceneManager) : sceneManager(sceneManager) {}

void SimpleGameState::Enter() {
    std::cout << "Entered SimpleGameState" << std::endl;
    sceneManager.SetActiveScene("SimpleScene");
}

void SimpleGameState::Exit() {
    std::cout << "Exited SimpleGameState" << std::endl;
}

void SimpleGameState::Update(float deltaTime) {
    sceneManager.Update(deltaTime);
}

void SimpleGameState::Render() {
    sceneManager.Render();
}
