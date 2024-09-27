#include "SimpleScene.h"
#include <iostream>

SimpleScene::SimpleScene(Renderer& renderer) : renderer(renderer) {}

void SimpleScene::Initialize() {
    // Initialize scene-specific entities or resources here
}

void SimpleScene::Update(float deltaTime) {
    // Update scene logic here
}

void SimpleScene::Render() {
    renderer.Clear();
    renderer.DrawQuad({100, 100}, {50, 50}, {1.0f, 0.0f, 0.0f, 1.0f}); // Red square
    renderer.DrawQuad({200, 200}, {100, 75}, {0.0f, 1.0f, 0.0f, 1.0f}); // Green rectangle
    renderer.Render();
}

void SimpleScene::OnEnter() {
    std::cout << "Entered SimpleScene" << std::endl;
}

void SimpleScene::OnExit() {
    std::cout << "Exited SimpleScene" << std::endl;
}
