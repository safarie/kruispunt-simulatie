#pragma once

#include "IModel.hpp"

#include <vector>

class ISection
{
public:
	virtual int update(float& delta, IModel* model, int section) = 0;

protected:
	int direction;
	glm::mat4 start;
};