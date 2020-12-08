#pragma once

#include "ISection.hpp"
#include <iostream>

/// <summary>
/// struct with traffic light info
/// </summary>
struct TrafficLichtInfo {
	std::string ID;
	glm::vec3 position;
	int traffic;
	int state;
};

/// <summary>
/// trafficlight class
/// </summary>
class TrafficLight : public ISection
{
public:

	/// <summary>
	/// contructor
	/// </summary>
	/// <param name="startPos">start position</param>
	/// <param name="direction">facing direction of the vehicle in degree</param>
	/// <param name="length">length of the check zone in meters</param>
	/// <param name="trafficLight">traffic light ID</param>
	/// <param name="ptr_trafficLights">ptr to list of traffic lights</param>
	TrafficLight(glm::vec3 startPos, float direction, float length, int trafficLight, std::vector<TrafficLichtInfo>* trafficLights);

	/// <summary>
	/// update the given vehicle
	/// </summary>
	/// <param name="delta">time past since last frame</param>
	/// <param name="model">model(vehicle) to update</param>
	/// <param name="section">current section number</param>
	/// <returns>next section number</returns>
	int update(float& delta, IModel* model, int section);

private:
	float length;
	int ID;
	std::vector<TrafficLichtInfo>* trafficLights;
};