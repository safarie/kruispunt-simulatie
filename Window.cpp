#include "Window.hpp"

void Window::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Traffic Simulation", nullptr, nullptr);
}

GLFWwindow* Window::getWindow() {
    return window;
}

void Window::cleanup() {
    glfwDestroyWindow(window);

    glfwTerminate();
}