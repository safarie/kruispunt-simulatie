#pragma once

#define _USE_MATH_DEFINES

#include "ISection.hpp"

#include <math.h>

class Corner : public ISection
{
public:
	Corner(glm::vec3 startPos, int direction, float radius, int degree);
	int update(float& delta, IModel* model, int section);

private:
	float radius;
	int degree;
	float circumference;
	float degPerMeter;
};