#include <memory>

#include "Simulation.hpp"
#include "Renderer.hpp"
#include "Window.hpp"

#include "Socket.hpp"

int main()
{
    std::shared_ptr<Window> ptr_window(new Window);
    std::shared_ptr<Renderer> ptr_renderer(new Renderer(ptr_window));
    Simulation simulation;
    Socket socket;

    //testing sockets
    socket.Connect();

    //// 1. initialize window
    //ptr_window->initWindow();

    //// 2. initialize vulkan
    //ptr_renderer->initvulkan();

    //// 3. main loop
    //while (!glfwWindowShouldClose(ptr_window->get()))
    //{
    //    glfwPollEvents();
    //    simulation.Update();
    //    simulation.LateUpdate();
    //    ptr_renderer->drawFrame();
    //}

    //vkDeviceWaitIdle(ptr_renderer->getDevice());

    // 4. cleanup
    socket.Close();
    //ptr_renderer->cleanup();
    //ptr_renderer.reset();
    //ptr_window->cleanup();
    //ptr_window.reset();
}