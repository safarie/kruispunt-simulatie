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
    std::vector<TrafficLichtInfo> trafficLights;

    void InitSimulator();
    void Update(float& delta);
    void LateUpdate(float& delta);
    void InitTrafficLights();
    void InitRoutes();

private:
};