#include "Vehicle.hpp"

Vehicle::Vehicle(int newID, float offset) {
	ID = newID;
	float initialize = 0.0f;
	update(initialize, glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -15.0f + offset, 0.0f)));
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
