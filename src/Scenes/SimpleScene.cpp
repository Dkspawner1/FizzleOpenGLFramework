// SimpleScene.cpp
#include "SimpleScene.h"
#include <glm/ext/vector_float2.hpp>
#include <iostream>

SimpleScene::SimpleScene(Renderer& renderer, World& world) 
    : m_renderer(renderer), m_world(world) {}

void SimpleScene::Initialize() {
    std::cout << "SimpleScene initialized" << std::endl;

    Entity* entity = m_world.CreateEntity();
    m_world.AddComponent<SpriteComponent>(entity, "Path.png");
    m_world.AddComponent<TransformComponent>(entity, glm::vec2(100,100), glm::vec2(50,50));
    m_entities.push_back(entity);
}

void SimpleScene::Update(float deltaTime) {
    (void)deltaTime; // Suppress unused parameter warning
    for(const auto& entity : m_entities)
    {
        (void)entity; // Suppress unused variable warning
        // Add update logic here if needed
    }
}

void SimpleScene::Render() {
    m_renderer.Clear();

    for(const auto& entity : m_entities) {
        try {
            const auto& sprite = m_world.GetComponent<SpriteComponent>(entity);
            const auto& transform = m_world.GetComponent<TransformComponent>(entity);
            m_renderer.DrawTexturedQuad(transform.position, transform.size, sprite.GetTexture());
        } catch (const std::exception& e) {
            std::cerr << "Error rendering entity: " << e.what() << std::endl;
        }
    }

    m_renderer.DrawQuad({100, 100}, {50, 50}, {1.0f, 0.0f, 0.0f, 1.0f}); // Red square
    m_renderer.DrawQuad({200, 200}, {100, 75}, {0.0f, 1.0f, 0.0f, 1.0f}); // Green rectangle
    m_renderer.Render();
}

void SimpleScene::OnEnter() {
    std::cout << "Entered SimpleScene" << std::endl;
}

void SimpleScene::OnExit() {
    std::cout << "Exited SimpleScene" << std::endl;
}