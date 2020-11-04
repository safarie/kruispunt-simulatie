#include "Vehicle.hpp"

Vehicle::Vehicle(int newID) {
	ID = newID;
	float initialize = 0.0f;
	update(initialize, glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, -5.0f, 0.0f)));
	// color / texture, model, type(car / bus), collision radius
};

int Vehicle::getID() {
	return ID;
}

float Vehicle::getTime() {
	return time;
}

glm::mat4 Vehicle::getPos() {
	return position;
}
