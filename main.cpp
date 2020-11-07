#include "Simulation.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "Socket.hpp"

int main()
{
    std::shared_ptr<Window> ptr_window(new Window);
    std::shared_ptr<Simulation> ptr_simulation(new Simulation);
    std::shared_ptr<Renderer> ptr_renderer(new Renderer(ptr_window, ptr_simulation));
    Socket socket;

    bool connected = true;
    float previousTime = 0.0f;
    float frameTime = 0.0f;

    //testing sockets
    socket.Connect();

    // 1. initialize window
    ptr_window->initWindow();

    // 2. initialize vulkan
    ptr_renderer->initvulkan();

    // 3. initialize simulator
    ptr_simulation->InitSimulator();

    // 4. main loop
    while (!glfwWindowShouldClose(ptr_window->get()))
    {
        static auto startTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
        float delta = time - previousTime;
        previousTime = time;

        glfwPollEvents();
        if (connected)
            connected = socket.Reciving();

        frameTime += delta;
        if (frameTime <= 1.0f / 60.0f) {
            continue;
        }

        ptr_simulation->Update(frameTime);
        ptr_simulation->LateUpdate(frameTime);    
        ptr_renderer->drawFrame();

        frameTime = 0.0f;
    }

    // wait till current frame is done
    vkDeviceWaitIdle(ptr_renderer->getDevice());

    // 5. cleanup
    socket.Close();
    ptr_renderer->cleanup();
    ptr_renderer.reset();
    ptr_simulation.reset();
    ptr_window->cleanup();
    ptr_window.reset();
}