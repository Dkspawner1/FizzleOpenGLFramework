#include "Window.h"
#include <iostream>
#include <stdexcept>

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
    glfwSetKeyCallback(m_Window, KeyCallback);
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Window::SwapBuffers() {
    glfwSwapBuffers(m_Window);
}

void Window::PollEvents() {
    glfwPollEvents();
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_Window);
}

void Window::Close() {
    std::cout << "Window::Close() called" << std::endl;
    glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}

void Window::MakeContextCurrent() {
    glfwMakeContextCurrent(m_Window);
}

bool Window::IsKeyPressed(int key) const {
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        std::cout << "ESC key pressed in callback" << std::endl;
        win->Close();
    }
}