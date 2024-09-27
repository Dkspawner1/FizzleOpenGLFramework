#include "Core/SceneChangedEvent.h"
#include "Core/Renderer.h"
#include "Core/Window.h"
#include "Scenes/GameStateManager.h"
#include "Scenes/SceneManager.h"
#include "Scenes/SimpleGameState.h"
#include "Scenes/SimpleScene.h"
#include <iostream>

int main() {
    try {
        Window window(800, 600, "2D Renderer");
        Renderer renderer;
        renderer.Initialize();

        EventSystem eventSystem;
        SceneManager sceneManager(eventSystem);
        GameStateManager stateManager;

        // Set up event listener for scene changes
        eventSystem.addHandler<SceneChangedEvent>([](const SceneChangedEvent& event) {
            std::cout << "Scene changed from " << event.oldSceneName
                      << " to " << event.newSceneName << std::endl;
        });

        // Create and add scenes
        sceneManager.AddScene("SimpleScene", std::make_unique<SimpleScene>(renderer));

        // Set initial game state
        stateManager.PushState(std::make_unique<SimpleGameState>(sceneManager));

        while (!window.ShouldClose()) {
            float deltaTime = 0.016f; // Assume 60 FPS for simplicity

            // Process any pending events
            eventSystem.processEvents();

            // Update game state and scene
            stateManager.Update(deltaTime);

            // Render
            stateManager.Render();

            window.SwapBuffers();
            window.PollEvents();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
