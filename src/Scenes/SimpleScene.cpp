// SimpleScene.cpp
#include "SimpleScene.h"
#include <iostream>

SimpleScene::SimpleScene(Renderer& renderer) : m_renderer(renderer) {}

void SimpleScene::Initialize() {
    std::cout << "SimpleScene initialized" << std::endl;
}

void SimpleScene::Update(float deltaTime) {
    // Update logic here
}

void SimpleScene::Render() {
    m_renderer.Clear();
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
