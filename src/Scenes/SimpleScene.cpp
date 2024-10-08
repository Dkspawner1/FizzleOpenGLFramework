// SimpleScene.cpp
#include "FizzleFramework/Scenes/SimpleScene.h"
#include <glm/ext/vector_float2.hpp>
#include <iostream>
#include <filesystem>

SimpleScene::SimpleScene(Renderer &renderer, World &world)
    : m_renderer(renderer), m_world(world) {}

    void SimpleScene::Initialize() {
    std::cout << "SimpleScene::Initialize() called" << std::endl;
    std::cout << "Current path is " << std::filesystem::current_path() << std::endl;

    std::string texturePath = "assets/wallhaven-l8x1pr.jpg";
    std::cout << "Attempting to load texture: " << texturePath << std::endl;

    if (std::filesystem::exists(texturePath)) {
        std::cout << "Texture file exists" << std::endl;
    } else {
        std::cout << "Texture file does not exist. Full path: " 
                  << std::filesystem::absolute(texturePath) << std::endl;
    }

    Entity *entity = m_world.CreateEntity();
    std::cout << "Entity created" << std::endl;

    try {
        auto& spriteComponent = m_world.AddComponent<SpriteComponent>(entity, texturePath);
        std::cout << "SpriteComponent added to entity" << std::endl;

        m_world.AddComponent<TransformComponent>(entity, glm::vec2(0, 0), glm::vec2(500, 500));
        std::cout << "TransformComponent added to entity" << std::endl;

        m_entities.push_back(entity);

        if (spriteComponent.IsTextureLoaded()) {
            std::cout << "Texture loaded successfully for entity" << std::endl;
        } else {
            std::cout << "Failed to load texture for entity" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error initializing entity: " << e.what() << std::endl;
    }

    std::cout << "SimpleScene::Initialize() completed" << std::endl;
}

void SimpleScene::Update(float deltaTime) {
    (void)deltaTime; // Suppress unused parameter warning
    for (const auto &entity : m_entities) {
        (void)entity; // Suppress unused variable warning
        // Add update logic here if needed
    }
}
void SimpleScene::Render() {
    m_renderer.Clear();

    for (const auto &entity : m_entities) {
        try {
            const auto &sprite = m_world.GetComponent<SpriteComponent>(entity);
            const auto &transform = m_world.GetComponent<TransformComponent>(entity);
            m_renderer.DrawTexturedQuad(transform.position, transform.size, sprite.GetTexture());
        } catch (const std::exception &e) {
            std::cerr << "Error rendering entity: " << e.what() << std::endl;
        }
    }

    // Draw these after the textured quad if you want them on top
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
