#pragma once

#include "IModel.hpp"

class Vehicle : public IModel
{
public:
	Vehicle(int vehicleID, int type, float speed, float collision);
	int getID();
	int getType();
	float getSpeed();
	void setSpeed(float Mps);

private:
	int ID;
	float speed = 14.0f;
	int type;
};