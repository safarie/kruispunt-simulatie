#pragma once

#include "IModel.hpp"
#include "ISection.hpp"

#include <vector>
#include <string>
#include <cmath>

#include <iostream>

struct VehicleInfo
{
	int ID;
	int section;
	int radius;
};

class Route
{
public:
	Route(int routeID, std::vector<IModel*>* ptr_models);
	void addSection(ISection *section);
	void addModel(int modelID);
	void addModel(int modelID, int startSection);
	int removeModel(int ID);
	void update(float &delta);

private:
	int ID;
	std::vector<VehicleInfo> vehicles;
	std::vector<ISection*> sections;
	std::vector<IModel*>* models;
};