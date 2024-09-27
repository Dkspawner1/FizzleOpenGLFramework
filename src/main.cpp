#include "Core/SceneChangedEvent.h"
#include "Core/Renderer.h"
#include "Core/Window.h"
#include "Core/EventSystem.h"
#include "Scenes/GameStateManager.h"
#include "Scenes/SceneManager.h"
#include "Scenes/SimpleScene.h"
#include "Scenes/SimpleGameState.h"
#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>

int main() {
    try {
        std::cout << "Initializing window..." << std::endl;
        Window window(800, 600, "2D Renderer");

        std::cout << "Making OpenGL context current..." << std::endl;
        window.MakeContextCurrent();

        std::cout << "Creating renderer..." << std::endl;
        Renderer renderer;

        std::cout << "Initializing renderer..." << std::endl;
        renderer.Initialize();

        std::cout << "Creating event system..." << std::endl;
        EventSystem eventSystem;

        std::cout << "Creating scene manager..." << std::endl;
        SceneManager sceneManager(eventSystem);

        std::cout << "Creating game state manager..." << std::endl;
        GameStateManager stateManager;

        std::cout << "Setting up event handler..." << std::endl;
        eventSystem.addHandler<SceneChangedEvent>([](const SceneChangedEvent& event) {
            std::cout << "Scene changed from " << event.oldSceneName
                      << " to " << event.newSceneName << std::endl;
        });

        std::cout << "Adding simple scene..." << std::endl;
        sceneManager.AddScene("SimpleScene", std::make_unique<SimpleScene>(renderer));

        std::cout << "Pushing initial game state..." << std::endl;
        stateManager.PushState(std::make_unique<SimpleGameState>(sceneManager));

        std::cout << "Entering main loop..." << std::endl;
        while (!window.ShouldClose()) {
            float deltaTime = 0.016f; // Assume 60 FPS for simplicity

            eventSystem.processEvents();
            stateManager.Update(deltaTime);
            stateManager.Render();

            window.SwapBuffers();
            window.PollEvents();

            // Check for ESC key press
            if (window.IsKeyPressed(GLFW_KEY_ESCAPE)) {
                std::cout << "ESC key pressed, closing window..." << std::endl;
                window.Close();
            }
        }
        std::cout << "Exiting main loop..." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }

    std::cout << "Program ended normally" << std::endl;
    return 0;
}