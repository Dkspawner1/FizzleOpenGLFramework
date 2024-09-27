#pragma once
#include "GameState.h"
#include "SceneManager.h"

class SimpleGameState : public GameState {
public:
    SimpleGameState(SceneManager& sceneManager);
    void Enter() override;
    void Exit() override;
    void Update(float deltaTime) override;
    void Render() override;

private:
    SceneManager& sceneManager;
};
