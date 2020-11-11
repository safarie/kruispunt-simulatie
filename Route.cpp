#include "Route.hpp"
#include "Simulation.hpp"

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
    VehicleInfo newVehicle{};
    newVehicle.ID = modelID;
    newVehicle.section = 0;

    vehicles.push_back(newVehicle);
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