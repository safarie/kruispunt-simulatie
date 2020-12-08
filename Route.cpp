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
    models->at(modelID)->activate();

    VehicleInfo vehicle{};
    vehicle.ID = modelID;
    vehicle.section = 0;

    vehicles.push_back(vehicle);
}

void Route::addModel(int modelID, int startSection)
{
    VehicleInfo vehicle{};
    vehicle.ID = modelID;
    vehicle.section = startSection;

    vehicles.push_back(vehicle);
}

int Route::removeModel(int ID)
{
    vehicles.erase(vehicles.begin());
    return ID;
}

void Route::update(float &delta)
{
    for (size_t i = 0; i < vehicles.size();)
    {
        currentModel = models->at(vehicles[i].ID);

        if (precedingModel != nullptr)
        {
            float dx = currentModel->getPos()[3].x - precedingModel->getPos()[3].x;
            float dy = currentModel->getPos()[3].y - precedingModel->getPos()[3].y;
            float distance = std::sqrtf(dx * dx + dy * dy);

            if (distance < currentModel->getColRad() + precedingModel->getColRad())
                currentModel->stop();
            else
                currentModel->start();
        }

        int next = sections[vehicles[i].section]->update(delta, currentModel, vehicles[i].section);
        if (next == -1) {
            if (i < vehicles.size() - 1) models->at(vehicles[i + 1].ID)->start();
            removeModel(vehicles[i].ID);
        }
        else {
            vehicles[i].section = next;
            precedingModel = currentModel;
            i++;
        }
    }
    precedingModel = nullptr;
}