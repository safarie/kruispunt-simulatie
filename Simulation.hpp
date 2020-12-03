#pragma once

#include "Route.hpp"
#include "Vehicle.hpp"
#include "TrafficLight.hpp"
#include "Straight.hpp"
#include "Corner.hpp"
#include "Transition.hpp"
#include "End.hpp"
#include <vector>


struct ModelInfo {
    std::string model;
    int type;
    int modelCount;
    float modelSpeed;
    float collisionRadius;
    uint32_t indicesCount;
    uint32_t vertexCount;
};

class Simulation
{
public:
    std::vector<Route> routes;
    std::vector<IModel*> models;
    std::vector<TrafficLichtInfo> trafficLights;
    std::vector<ModelInfo>* modelInfo;
    std::vector<glm::vec3> streetLightPos;
    std::vector<glm::vec3> sidewalkLightPos;

    void initSimulator();
    void update(float& delta);
    void lateUpdate(float& delta);

private:
    std::vector<std::vector<int>> spawnRoutes;
    void initTraffic();
    void initTrafficLights();
    void initRoutes();
    void spawn(int vehicleID);
    int random(float first, float last);
    float timeOut = 9.0f;
};