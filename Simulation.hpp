#pragma once

#include "Route.hpp"
#include "Vehicle.hpp"
#include "Straight.hpp"
#include "Corner.hpp"
#include "End.hpp"
#include <vector>

class Simulation
{
public:
    std::vector<Route> routes;
    std::vector<IModel*> models;

    void InitSimulator();
    void InitRoutes();
    void Update(float& delta);
    void LateUpdate(float& delta);

private:
};