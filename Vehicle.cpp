#include "Vehicle.hpp"

/// <summary>
/// contructor
/// </summary>
/// <param name="vehicleID">new ID</param>
/// <param name="type">vehicle type, [0 = car, 1 = bus, 2 = bicycle, 3 = pedestrian]</param>
/// <param name="speed">speed of the vehicle</param>
/// <param name="collision">collision radius</param>
Vehicle::Vehicle(int vehicleID, int type, float speed, float collision) {
	this->ID = vehicleID;
	this->type = type;
	this->collisionRadius = collision;
	this->speed = speed;
	float initialize = 0.0f;
	update(initialize, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f)));
	// color / texture, model, type(car / bus), collision radius
};

/// <summary>
/// return vehicle ID
/// </summary>
/// <returns></returns>
int Vehicle::getID() {
	return ID;
}

/// <summary>
/// get the type of the vehicle
/// </summary>
/// <returns>vehicle type, [0 = car, 1 = bus, 2 = bicycle, 3 = pedestrian]</returns>
int Vehicle::getType() {
	return type;
}

/// <summary>
/// get the current speed
/// </summary>
/// <returns>current speed in meter per second</returns>
float Vehicle::getSpeed()
{
	return speed;
}

/// <summary>
/// change the speed of the vehicle
/// </summary>
/// <param name="Mps">new speed in meter per second</param>
void Vehicle::setSpeed(float Mps)
{
	speed = Mps;
}
