#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

struct WindowSpecs
{
    uint32_t width;
    uint32_t height;
};

class Window
{
protected:
    Window() { }

    static Window* window_;
public:
    Window(Window& other) = delete;
    void operator=(const Window&) = delete;

    static Window* GetInstance();

    void initWindow();
    void cleanup();
    GLFWwindow* getMemAddres();
    struct WindowSpecs getSpecs();

private:
    const uint32_t WIDTH = 1280;
    const uint32_t HEIGHT = 720;
    
    GLFWwindow* window;
};