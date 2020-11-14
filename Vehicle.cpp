#include "Vehicle.hpp"

Vehicle::Vehicle(int vehicleID, float collision) {
	ID = vehicleID;
	collisionRadius = collision;
	float initialize = 0.0f;
	update(initialize, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f)));
	// color / texture, model, type(car / bus), collision radius
};

int Vehicle::getID() {
	return ID;
}

float Vehicle::getSpeed()
{
	return speed;
}

void Vehicle::setSpeed(float Mps)
{
	speed = Mps;
}
