#pragma once

#include "IModel.hpp"
#include <glm/glm.hpp>

class Vehicle : public IModel
{
public:
	Vehicle(glm::vec3 position);

private:
	glm::vec3 startPosition;
};