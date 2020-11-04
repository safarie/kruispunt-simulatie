#pragma once

#include "Route.hpp"
#include <vector>

class Simulation
{
public:
    std::vector<Route> routes;

    void InitSimulator();
    void Update(float& delta);
    void LateUpdate(float& delta);

private:
};