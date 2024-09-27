#pragma once
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();
    bool IsKeyPressed(int key) const;

    void SwapBuffers();
    void PollEvents();
    bool ShouldClose() const;
    void Close();
    void MakeContextCurrent();

private:
    GLFWwindow* m_Window;
};
