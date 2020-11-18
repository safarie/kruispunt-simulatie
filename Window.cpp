#include "Window.hpp"

void Window::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Traffic Simulation", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    glfwSetKeyCallback(window, keyPressCallback);
    glfwSetCursorPosCallback(window, mouseMoveCallback);
    glfwSetMouseButtonCallback(window, mouseClickCallback);
    glfwSetScrollCallback(window, mouseScrollCallback);
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    auto windowClass = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)); // creates a pointer to THIS class to be able to change "framebufferResized"
    windowClass->framebufferResized = true;
}

void Window::keyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto windowClass = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    Keys* keys = &windowClass->ptr_camera->keys;

    (key == GLFW_KEY_W || key == GLFW_KEY_UP) && (action == GLFW_PRESS || action == GLFW_REPEAT) ? keys->up = true : keys->up = false;
    (key == GLFW_KEY_S || key == GLFW_KEY_DOWN) && (action == GLFW_PRESS || action == GLFW_REPEAT) ? keys->down = true : keys->down = false;
    (key == GLFW_KEY_A || key == GLFW_KEY_LEFT) && (action == GLFW_PRESS || action == GLFW_REPEAT) ? keys->left = true : keys->left = false;
    (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) && (action == GLFW_PRESS || action == GLFW_REPEAT) ? keys->right = true : keys->right = false;
    key == GLFW_KEY_SPACE && action == GLFW_PRESS ? keys->space = true : keys->space = false;
}

void Window::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    auto windowClass = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    Mouse* mouse = &windowClass->ptr_camera->mouse;

    mouse->xPos = xpos;
    mouse->yPos = ypos;
}

void Window::mouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
    auto windowClass = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    Mouse* mouse = &windowClass->ptr_camera->mouse;

    button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS ? mouse->rightClick = true : mouse->rightClick = false;
    button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS ? mouse->leftClick = true : mouse->leftClick = false;
}

void Window::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto windowClass = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    Mouse* mouse = &windowClass->ptr_camera->mouse;

    xoffset < -0.025 || xoffset > 0.025 ? mouse->xScroll = xoffset : mouse->xScroll = 0;
    yoffset < -0.025 || yoffset > 0.025 ? mouse->yScroll = yoffset : mouse->yScroll = 0;
}

GLFWwindow* Window::get() {
    return window;
}

void Window::cleanup() {
    glfwDestroyWindow(window);

    glfwTerminate();
}