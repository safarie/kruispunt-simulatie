#pragma once

#include "Camera.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

class Window
{
public:
    bool framebufferResized = false;

    /// <summary>
    /// constructor
    /// </summary>
    /// <param name="ptr_c">ptr to camera class</param>
    Window(std::shared_ptr<Camera> ptr_c) : ptr_camera(move(ptr_c)) {}

    /// <summary>
    /// create the window
    /// </summary>
    void initWindow();

    /// <summary>
    /// cleanup when app is closed
    /// </summary>
    void cleanup();

    /// <summary>
    /// get ptr to this class
    /// </summary>
    /// <returns>ptr to this class</returns>
    GLFWwindow* get();

    /// <summary>
    /// callback when the window gets rezised
    /// </summary>
    /// <param name="window">ptr to the window</param>
    /// <param name="width"></param>
    /// <param name="height"></param>
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    /// <summary>
    /// callback when a key is pressed
    /// </summary>
    /// <param name="window">ptr to the app window</param>
    /// <param name="key">key pressed</param>
    /// <param name="scancode">code of the key pressed</param>
    /// <param name="action">key action (pressed, hold, released)</param>
    /// <param name="mods"></param>
    static void keyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /// <summary>
    /// callback when the mouse is moved
    /// </summary>
    /// <param name="window">ptr to app window</param>
    /// <param name="xpos">x position</param>
    /// <param name="ypos">y position</param>
    static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);

    /// <summary>
    /// callback when mouse buttons are pressed
    /// </summary>
    /// <param name="window">ptr to app window</param>
    /// <param name="button">button pressed</param>
    /// <param name="action">button action (pressed, hold, released)</param>
    /// <param name="mods"></param>
    static void mouseClickCallback(GLFWwindow* window, int button, int action, int mods);

    /// <summary>
    /// callback when mouse scroll is used
    /// </summary>
    /// <param name="window">ptr to app window</param>
    /// <param name="xoffset">x scroll amount</param>
    /// <param name="yoffset">y scroll amount</param>
    static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
    const uint32_t WIDTH =1280;
    const uint32_t HEIGHT = 720;
    std::shared_ptr<Camera> ptr_camera;
    GLFWwindow* window;
};