#include "Simulation.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "Socket.hpp"
#include "Camera.hpp"
#include <thread>

int main()
{
    std::shared_ptr<Camera> ptr_camera(new Camera);
    std::shared_ptr<Simulation> ptr_simulation(new Simulation);
    std::shared_ptr<Window> ptr_window(new Window(ptr_camera));
    std::shared_ptr<Socket> ptr_socket(new Socket(ptr_simulation));
    std::shared_ptr<Renderer> ptr_renderer(new Renderer(ptr_window, ptr_camera, ptr_simulation));

    bool connected = true;
    float previousTime = 0.0f;
    float frameTime = 0.0f;
    float socketTime = 0.0f;

    // 1. initialize camera & window
    ptr_camera->InitCamera();
    ptr_window->initWindow();

    // 2. initialize vulkan
    ptr_renderer->initvulkan();

    // 3. initialize simulator
    ptr_simulation->InitSimulator();

    // 4. sockets
    connected = ptr_socket->Connect();
    std::thread t1(&Socket::Receiving, ptr_socket);

    // 5. main loop
    while (!glfwWindowShouldClose(ptr_window->get()))
    {
        static auto startTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
        float delta = time - previousTime;
        previousTime = time;

        glfwPollEvents();

        frameTime += delta;
        socketTime += delta;
        
        if (frameTime <= 1.0f / 60.0f) {
            continue;
        }

        ptr_simulation->Update(frameTime);
        ptr_simulation->LateUpdate(frameTime);
        ptr_camera->Update(frameTime);
        ptr_renderer->drawFrame();
         
        frameTime = 0.0f;
    }

    // wait till current frame is done
    vkDeviceWaitIdle(ptr_renderer->getDevice());
    ptr_socket->Close();
    t1.join();

    // 6. cleanup
    ptr_socket.reset();
    ptr_renderer->cleanup();
    ptr_renderer.reset();
    ptr_simulation.reset();
    ptr_window->cleanup();
    ptr_window.reset();
}