#include "Window.hpp"
#include "Renderer.hpp"

Window* Window::window_ = nullptr;
Renderer* renderer = Renderer::GetInstance();

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

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, renderer->framebufferResizeCallback);
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