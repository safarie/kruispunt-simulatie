#pragma once

#include "IModel.hpp"

/// <summary>
/// vehicle class
/// </summary>
class Vehicle : public IModel
{
public:
	/// <summary>
	/// contructor
	/// </summary>
	/// <param name="vehicleID">new ID</param>
	/// <param name="type">vehicle type, [0 = car, 1 = bus, 2 = bicycle, 3 = pedestrian]</param>
	/// <param name="speed">speed of the vehicle</param>
	/// <param name="collision">collision radius</param>
	Vehicle(int vehicleID, int type, float speed, float collision);

	/// <summary>
	/// return vehicle ID
	/// </summary>
	/// <returns></returns>
	int getID();

	/// <summary>
	/// get the type of the vehicle
	/// </summary>
	/// <returns>vehicle type, [0 = car, 1 = bus, 2 = bicycle, 3 = pedestrian]</returns>
	int getType();

	/// <summary>
	/// get the current speed
	/// </summary>
	/// <returns>current speed in meter per second</returns>
	float getSpeed();

	/// <summary>
	/// change the speed of the vehicle
	/// </summary>
	/// <param name="Mps">new speed in meter per second</param>
	void setSpeed(float Mps);

private:
	int ID;
	float speed = 14.0f;
	int type;
};