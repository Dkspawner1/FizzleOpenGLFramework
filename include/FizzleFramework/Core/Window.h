#pragma once
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    void SwapBuffers();
    void PollEvents();
    bool ShouldClose() const;
    void Close();
    void MakeContextCurrent();
    bool IsKeyPressed(int key) const;

private:
    GLFWwindow* m_Window;
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};