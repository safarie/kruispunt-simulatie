#pragma once

#include "Route.hpp"
#include "Vehicle.hpp"
#include "TrafficLight.hpp"
#include "Straight.hpp"
#include "Corner.hpp"
#include "End.hpp"
#include <vector>


struct ModelInfo {
    std::string model;
    int modelCount;
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

    void InitSimulator();
    void Update(float& delta);
    void LateUpdate(float& delta);
    void InitTraffic();
    void InitTrafficLights();
    void InitRoutes();

private:
};