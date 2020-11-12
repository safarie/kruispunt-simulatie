#pragma once

#include "ISection.hpp"

class TrafficLight : public ISection
{
public:
	TrafficLight(glm::vec3 startPos, int direction, float length, bool trafficLight);
	int update(float& delta, IModel* model, int section);

private:
	float length;
	bool *lightState = nullptr;
};