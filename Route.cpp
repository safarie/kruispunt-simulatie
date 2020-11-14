#include "Route.hpp"

Route::Route(int routeID, std::vector<IModel*>* ptr_models) {
    ID = routeID;
    models = ptr_models;
}

void Route::addSection(ISection* section)
{
    sections.push_back(section);
}

void Route::addModel(int modelID)
{
    VehicleInfo vehicle{};
    vehicle.ID = modelID;
    vehicle.section = 0;
    vehicle.radius = models->at(modelID)->getColRad();

    vehicles.push_back(vehicle);
}

void Route::addModel(int modelID, int startSection)
{
    VehicleInfo vehicle{};
    vehicle.ID = modelID;
    vehicle.section = startSection;
    vehicle.radius = models->at(modelID)->getColRad();

    vehicles.push_back(vehicle);
}

int Route::removeModel()
{
    VehicleInfo modelID = vehicles.front();
    vehicles.erase(vehicles.begin());
    return modelID.ID;
}

void Route::update(float &delta)
{
    for (auto &v : vehicles) {
        int next = sections[v.section]->update(delta, models->at(v.ID), v.section);
        if (next == -1)
            removeModel();
        else
            v.section = next;
    }
}