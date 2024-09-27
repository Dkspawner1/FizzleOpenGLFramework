// Window.h
#pragma once
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    void MakeContextCurrent();
    void SwapBuffers();
    void PollEvents();
    bool ShouldClose() const;
    void Close();

private:
    GLFWwindow* m_Window;
};
