#pragma once

#include "IModel.hpp"
#include "ISection.hpp"

#include <vector>
#include <string>

struct VehicleInfo
{
	int ID;
	int section;
};

class Route
{
public:
	Route(int routeID, std::vector<IModel*>* ptr_models);
	void addSection(ISection* section);
	void addModel(int modelID);
	int removeModel();
	void update(float &delta);

private:
	int ID;
	std::vector<VehicleInfo> vehicles;
	std::vector<ISection*> sections;
	std::vector<IModel*>* models;
};