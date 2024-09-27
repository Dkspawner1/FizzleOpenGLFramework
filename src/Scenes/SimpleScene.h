// SimpleScene.h

#pragma once
#include "../Core/Renderer.h"
#include "../ECS/Entity.h"
#include "../ECS/SpriteComponent.h"
#include "../ECS/TransformComponent.h"
#include "../ECS/World.h"
#include "Scene.h"
#include <vector>

class SimpleScene : public Scene {
public:
  SimpleScene(Renderer &renderer, World &world);
  void Initialize() override;
  void Update(float deltaTime) override;
  void Render() override;
  void OnEnter() override;
  void OnExit() override;

private:
    Renderer& m_renderer;
    World& m_world;
    std::vector<Entity*> m_entities;
};
