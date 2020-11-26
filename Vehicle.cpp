#include "Vehicle.hpp"

Vehicle::Vehicle(int vehicleID, int type, float speed, float collision) {
	this->ID = vehicleID;
	this->type = type;
	this->collisionRadius = collision;
	this->speed = speed;
	float initialize = 0.0f;
	update(initialize, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f)));
	// color / texture, model, type(car / bus), collision radius
};

int Vehicle::getID() {
	return ID;
}

int Vehicle::getType() {
	return type;
}

float Vehicle::getSpeed()
{
	return speed;
}

void Vehicle::setSpeed(float Mps)
{
	speed = Mps;
}
