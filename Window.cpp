#include "Window.hpp"

Window* Window::window_ = nullptr;;

Window* Window::GetInstance()
{
    if (window_ == nullptr) {
        window_ = new Window();
    }
    return window_;
}

void Window::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Traffic Simulation", nullptr, nullptr);
}

GLFWwindow* Window::getMemAddres() {
    return window;
}

struct WindowSpecs Window::getSpecs()
{
    return { WIDTH, HEIGHT };
}

void Window::cleanup() {
    glfwDestroyWindow(window);

    glfwTerminate();
}