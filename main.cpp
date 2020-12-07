#include "Simulation.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "Socket.hpp"
#include "Camera.hpp"
#include <thread>

/// <summary>
/// instructions on how to start the intire app
/// </summary>
/// <returns></returns>
int main()
{
    std::shared_ptr<Camera> ptr_camera(new Camera);
    std::shared_ptr<Simulation> ptr_simulation(new Simulation);
    std::shared_ptr<Window> ptr_window(new Window(ptr_camera));
    std::shared_ptr<Socket> ptr_socket(new Socket(ptr_simulation));
    std::shared_ptr<Renderer> ptr_renderer(new Renderer(ptr_window, ptr_camera, ptr_simulation));

    bool connected = false;
    float previousTime = 0.0f;
    float frameTime = 0.0f;
    float connectionTimeout = 0.0f;
    std::thread t1, t2;

    // 1. initialize camera & window
    ptr_camera->initCamera();
    ptr_window->initWindow();

    // 2. initialize vulkan
    ptr_renderer->initvulkan();

    // 3. initialize simulator
    ptr_simulation->initSimulator();

    // 4. sockets
    connected = ptr_socket->connecting();
    if (connected) {
        t1 = std::thread(&Socket::receiving, ptr_socket);
        t2 = std::thread(&Socket::sending, ptr_socket);
    }

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
        connected ? connectionTimeout = 0.0f : connectionTimeout += delta;

        if (frameTime <= 1.0f / 60.0f) {
            continue;
        }

        ptr_simulation->update(frameTime);
        ptr_simulation->lateUpdate(frameTime);
        ptr_camera->update(frameTime);
        ptr_renderer->drawFrame();

        frameTime = 0.0f;

        /*if (connectionTimeout >= 10.0f && !connected) {
            connected = ptr_socket->Connect();
            if (connected)
                t1 = std::thread(&Socket::Receiving, ptr_socket);
        }*/
    }

    // wait till current frame is done
    vkDeviceWaitIdle(ptr_renderer->getDevice());

    // 6. cleanup
    ptr_socket->close();
    t2.join();
    t1.join();
    ptr_socket.reset();
    ptr_renderer->cleanup();
    ptr_renderer.reset();
    ptr_simulation.reset();
    ptr_window->cleanup();
    ptr_window.reset();
    ptr_camera.reset();
}