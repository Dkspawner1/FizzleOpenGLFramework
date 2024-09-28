
#include "FizzleFramework/Core/SceneChangedEvent.h"
#include "FizzleFramework/Core/Renderer.h"
#include "FizzleFramework/Core/Window.h"
#include "FizzleFramework/Core/EventSystem.h"
#include "FizzleFramework/Scenes/GameStateManager.h"
#include "FizzleFramework/Scenes/SceneManager.h"
#include "FizzleFramework/Scenes/SimpleScene.h"
#include "FizzleFramework/Scenes/SimpleGameState.h"
#include "FizzleFramework/ECS/World.h"

#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>
#include <filesystem>

int main() {
    std::cout << "Current path is "<< std::filesystem::current_path() << std::endl;
    try {
        std::cout << "Initializing window..." << std::endl;
        Window window(1600, 900, "2D Renderer");

        std::cout << "Making OpenGL context current..." << std::endl;
        window.MakeContextCurrent();

        std::cout << "Creating renderer..." << std::endl;
        Renderer renderer;

        std::cout << "Initializing renderer..." << std::endl;
        renderer.Initialize();

        std::cout << "Creating event system..." << std::endl;
        EventSystem eventSystem;

        std::cout << "Creating world..." << std::endl;
        World world;

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
        sceneManager.AddScene("SimpleScene", std::make_unique<SimpleScene>(renderer, world));

        std::cout << "Pushing initial game state..." << std::endl;
        stateManager.PushState(std::make_unique<SimpleGameState>(sceneManager));

        std::cout << "Entering main loop..." << std::endl;
        while (!window.ShouldClose()) {
            float deltaTime = 0.016f; // Assume 60 FPS for simplicity

            eventSystem.processEvents();
            stateManager.Update(deltaTime);
            stateManager.Render(); // Make sure this is calling SimpleScene::Render()

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
