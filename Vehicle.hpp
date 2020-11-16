#pragma once

#include "IModel.hpp"

class Vehicle : public IModel
{
public:
	Vehicle(int vehicleID, float collision);
	int getID();
	float getSpeed();
	void setSpeed(float Mps);

private:
	int ID;
	float speed = 14.0f;
};