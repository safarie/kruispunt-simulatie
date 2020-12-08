#pragma once

#include "IModel.hpp"
#include "ISection.hpp"

#include <vector>
#include <string>
#include <cmath>

#include <iostream>

/// <summary>
/// struct with vehicle info
/// </summary>
struct VehicleInfo
{
	int ID;
	int section;
};

/// <summary>
/// route class
/// </summary>
class Route
{
public:
	/// <summary>
	/// route contructor
	/// </summary>
	/// <param name="routeID">new route ID</param>
	/// <param name="ptr_models">ptr to list with all vehicles</param>
	Route(int routeID, std::vector<IModel*>* ptr_models);

	/// <summary>
	/// add a new road section to this route 
	/// </summary>
	/// <param name="section">section to add</param>
	void addSection(ISection *section);

	/// <summary>
	/// add a model to keep track whos driving on the route
	/// </summary>
	/// <param name="modelID"></param>
	void addModel(int modelID);
	
	/// <summary>
	/// add a vehicle to a speciffic part of the route
	/// </summary>
	/// <param name="modelID"></param>
	/// <param name="startSection"></param>
	void addModel(int modelID, int startSection);

	/// <summary>
	/// remove the vehicle of the route
	/// </summary>
	/// <param name="ID">vehicle to remove</param>
	/// <returns>return id of the removed vehicle</returns>
	int removeModel(int ID);

	/// <summary>
	/// update all vehicles on this route
	/// </summary>
	/// <param name="delta">time passed since last frame</param>
	void update(float &delta);

private:
	int ID;
	IModel* currentModel = nullptr;
	IModel* precedingModel = nullptr;
	std::vector<VehicleInfo> vehicles;
	std::vector<ISection*> sections;
	std::vector<IModel*>* models;
};