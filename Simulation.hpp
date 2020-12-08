#pragma once

#include "Route.hpp"
#include "Vehicle.hpp"
#include "TrafficLight.hpp"
#include "Straight.hpp"
#include "Corner.hpp"
#include "Transition.hpp"
#include "End.hpp"
#include <vector>

/// <summary>
/// struct with all model info
/// </summary>
struct ModelInfo {
    std::string model;
    int type;
    int modelCount;
    float modelSpeed;
    float collisionRadius;
    uint32_t indicesCount;
    uint32_t vertexCount;
};

/// <summary>
/// simulation class
/// </summary>
class Simulation
{
public:
    std::vector<Route> routes;
    std::vector<IModel*> models;
    std::vector<TrafficLichtInfo> trafficLights;
    std::vector<ModelInfo>* modelInfo;
    std::vector<glm::vec3> streetLightPos;
    std::vector<glm::vec3> sidewalkLightPos;

    /// <summary>
    /// initialization of static data
    /// </summary>
    void initSimulator();

    /// <summary>
    /// update all routes
    /// </summary>
    /// <param name="delta">time past sins last frame</param>
    void update(float& delta);

    /// <summary>
    /// after the main update check if there any "idle" vehicles and respawn them at 10 sec intervals
    /// </summary>
    /// <param name="delta">time past sins last frame</param>
    void lateUpdate(float& delta);

private:
    std::vector<std::vector<int>> spawnRoutes;
    
    /// <summary>
    /// create all vehicles (logic)
    /// </summary>
    void initTraffic();

    /// <summary>
    /// setup all trafficlights and streetlight positions
    /// </summary>
    void initTrafficLights();

    /// <summary>
    /// setup all routes for traffic to follow
    /// </summary>
    void initRoutes();

    /// <summary>
    /// spawn the indicated vehicle on a random spawnroute
    /// </summary>
    /// <param name="vehicleID"></param>
    void spawn(int vehicleID);

    /// <summary>
    /// random fuction
    /// </summary>
    /// <param name="first">first value</param>
    /// <param name="last">last value</param>
    /// <returns>returns a random float between the first and last values</returns>
    float random(float first, float last);
    float timeOut = 9.0f;
};