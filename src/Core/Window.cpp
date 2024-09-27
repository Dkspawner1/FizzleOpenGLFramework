#include "Window.h"
#include <stdexcept>
#include <iostream>

Window::Window(int width, int height, const std::string& title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_Window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetWindowUserPointer(m_Window, this);
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        std::cout << "Window close callback triggered" << std::endl;
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        win->Close();
    });
}

Window::~Window() {
    std::cout << "Window destructor called" << std::endl;
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}
bool Window::IsKeyPressed(int key) const {
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}
void Window::SwapBuffers() {
    glfwSwapBuffers(m_Window);
}

void Window::PollEvents() {
    glfwPollEvents();
}

bool Window::ShouldClose() const {
    bool shouldClose = glfwWindowShouldClose(m_Window);
    if (shouldClose) {
        std::cout << "Window::ShouldClose() returning true" << std::endl;
    }
    return shouldClose;
}

void Window::Close() {
    std::cout << "Window::Close() called" << std::endl;
    glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}

void Window::MakeContextCurrent() {
    glfwMakeContextCurrent(m_Window);
}
