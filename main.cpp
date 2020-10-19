#include "Simulation.hpp"
#include "Window.hpp"
#include "Renderer.hpp"

int main()
{
    Simulation simulation;
    Window* window = Window::GetInstance();
    Renderer* renderer = Renderer::GetInstance();

    // 1. initialize window
    window->initWindow();

    // 2. initialize vulkan
    renderer->initvulkan();

    // 3. main loop
    while (!glfwWindowShouldClose(window->getMemAddres()))
    {
        glfwPollEvents();
        simulation.Update();
        simulation.LateUpdate();
        renderer->drawFrame();
    }

    vkDeviceWaitIdle(renderer->getDevice());

    // 4. cleanup
    renderer->cleanup();
    window->cleanup();
}