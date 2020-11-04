#pragma once

#include "IModel.hpp"

class Vehicle : public IModel
{
public:
	Vehicle(int newID);
	float getTime();
	glm::mat4 getPos();
	int getID();

private:
	int ID;
};