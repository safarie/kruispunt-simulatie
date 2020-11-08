#include "Route.hpp"

void Route::update(float &delta)
{
	for (IModel *vehicle : roadUsers)
	{
        glm::mat4* modelMat = &vehicle->getPos();

        float speed = 14.0f;                            // meters per second
        float distance = 30.0f;	                        // distance in meters
        float radius = 8.0f;                            // radius of the turn
        float circumference = (radius * 2) * M_PI;      // circumference of the turn
        float degPerMeter = 360.0f / circumference;     // how many degrees per meter
        float angle = speed * degPerMeter;              // degrees per second based on speed
        float time = vehicle->getTime();                // time this vehicle spent on the road

        if (time * speed < distance) {
            *modelMat = glm::translate(*modelMat, delta * speed * glm::vec3(-1.0f, 0.0f, 0.0f));
        }
        else if (time * speed > distance && (time - (distance / speed)) * angle <= 90.0f) {
            *modelMat = glm::translate(*modelMat, delta * speed * glm::vec3(-1.0, 0.0f, 0.0f));
            *modelMat = glm::rotate(*modelMat, delta * glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        else {
            vehicle->resetTime();
        }

		vehicle->update(delta, *modelMat);
	}
}