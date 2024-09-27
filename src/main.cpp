#include <GL/glew.h>
#include "Core/Renderer.h"
#include "Core/Window.h"
#include <iostream>

int main() {
    try {
        Window window(800, 600, "2D Renderer");
        Renderer renderer;
        renderer.Initialize();

        while (!window.ShouldClose()) {
            renderer.Clear();

            // Draw some quads
            renderer.DrawQuad({100, 100}, {50, 50}, {1.0f, 0.0f, 0.0f, 1.0f}); // Red square
            renderer.DrawQuad({200, 200}, {100, 75}, {0.0f, 1.0f, 0.0f, 1.0f}); // Green rectangle

            renderer.Render();
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
