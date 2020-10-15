#include "Simulation.hpp"
#include "Window.hpp"

int main()
{
    Simulation simulation;
    Window window;

    // 1. initialize window
    window.initWindow();

    // 2. initialize vulkan


    // 3. main loop
    while (!glfwWindowShouldClose(window.getWindow()))
    {
        glfwPollEvents();
        simulation.Update();
        simulation.LateUpdate();
        simulation.Draw();
    }

    // 4. cleanup
    window.cleanup();
}