#pragma once

#include "Camera.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

class Window
{
public:
    bool framebufferResized = false;

    Window(std::shared_ptr<Camera> ptr_c) : ptr_camera(move(ptr_c)) {}
    void initWindow();
    void cleanup();
    GLFWwindow* get();
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    static void keyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseClickCallback(GLFWwindow* window, int button, int action, int mods);
    static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
    const uint32_t WIDTH =1280;
    const uint32_t HEIGHT = 720;
    std::shared_ptr<Camera> ptr_camera;
    GLFWwindow* window;
};