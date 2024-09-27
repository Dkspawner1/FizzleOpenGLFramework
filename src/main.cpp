#include "Core/SceneChangedEvent.h"
#include "Core/Renderer.h"
#include "Core/Window.h"
#include "Scenes/GameStateManager.h"
#include "Scenes/SceneManager.h"
#include "Scenes/SimpleScene.h"
#include "Scenes/SimpleGameState.h"
#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>
#include <csignal>
#include <atomic>

std::atomic<bool> g_shouldExit(false);

void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    g_shouldExit = true;
}

int main() {
    signal(SIGINT, signalHandler);

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
        int frameCount = 0;
        auto lastTime = std::chrono::high_resolution_clock::now();

        while (!window.ShouldClose() && !g_shouldExit) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
            lastTime = currentTime;

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

            frameCount++;
            if (frameCount % 60 == 0) {
                std::cout << "Frame " << frameCount << " completed. Window should close: "
                          << (window.ShouldClose() ? "true" : "false")
                          << ", g_shouldExit: " << (g_shouldExit ? "true" : "false") << std::endl;
            }

            // Add a small sleep to prevent busy-waiting
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
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
