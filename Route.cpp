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
    for (size_t i = 0; i < vehicles.size(); i++)
    {
        IModel* model = models->at(vehicles[i].ID);
        int next = sections[vehicles[i].section]->update(delta, model, vehicles[i].section);
        if (next == -1)
            removeModel();
        else
            vehicles[i].section = next;

        if (i == 0)
            continue;

        IModel* precedingModel = models->at(vehicles[i - 1].ID);

        float dx = model->getPos()[3].x - precedingModel->getPos()[3].x;
        float dy = model->getPos()[3].y - precedingModel->getPos()[3].y;
        float distance = std::sqrtf(dx * dx + dy * dy);

        if (distance < model->getColRad() + precedingModel->getColRad())
            model->stop();
        else
            model->start();
    }
}