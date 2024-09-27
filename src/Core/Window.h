#pragma once

#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool ShouldClose() const;
    void SwapBuffers() const;
    void PollEvents();

private:
    GLFWwindow* m_window;
};
