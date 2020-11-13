#pragma once

#include "ISection.hpp"
#include <iostream>

struct TrafficLichtInfo {
	std::string ID;
	int state;
};

class TrafficLight : public ISection
{
public:
	TrafficLight(glm::vec3 startPos, int direction, float length, int trafficLight, std::vector<TrafficLichtInfo>* trafficLights);
	int update(float& delta, IModel* model, int section);

private:
	float length;
	int ID;
	std::vector<TrafficLichtInfo>* trafficLights;
};