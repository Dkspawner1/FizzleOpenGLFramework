// SimpleScene.h
#pragma once
#include "Scene.h"
#include "../Core/Renderer.h"

class SimpleScene : public Scene {
public:
    SimpleScene(Renderer& renderer);
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
    void OnEnter() override;
    void OnExit() override;

private:
    Renderer& m_renderer;
};
