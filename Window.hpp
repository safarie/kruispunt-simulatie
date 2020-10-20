#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Window
{
public:
    bool framebufferResized = false;

    void initWindow();
    void cleanup();
    GLFWwindow* get();
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

private:
    const uint32_t WIDTH =1280;
    const uint32_t HEIGHT = 720;
    
    GLFWwindow* window;
};