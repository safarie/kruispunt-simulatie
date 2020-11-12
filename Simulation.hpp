#pragma once

#include "Route.hpp"
#include "Vehicle.hpp"
#include "TrafficLight.hpp"
#include "Straight.hpp"
#include "Corner.hpp"
#include "End.hpp"
#include <vector>

class Simulation
{
public:
    std::vector<Route> routes;
    std::vector<IModel*> models;
    std::vector<bool> trafficLights;

    void InitSimulator();
    void InitRoutes();
    void updateTrafficLights(std::vector<bool> trafficLights);
    void Update(float& delta);
    void LateUpdate(float& delta);

private:
};