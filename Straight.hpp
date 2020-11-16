#pragma once

#include "ISection.hpp"

class Straight : public ISection
{
public:
	Straight(glm::vec3 startPos, float direction, float length);
	int update(float& delta, IModel* model, int section);

private:
	float length;
};