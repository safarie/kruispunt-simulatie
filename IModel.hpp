#pragma once

#include <glm/gtc/matrix_transform.hpp>

class IModel
{
public:
	void update(float &delta, glm::mat4 pos) {
		if (isMoving) {
			time += delta;
			position = pos;
		}
	}

	void resetTime() {
		time = 0.0f;
	}

	void start() {
		isMoving = true;
	}

	void stop() {
		isMoving = false;
	}

	float getTime() {
		return time;
	}

	glm::mat4 getPos() {
		return position;
	}

	virtual int getID() = 0;
	virtual float getSpeed() = 0;
	virtual void setSpeed(float Mps) = 0;

protected:
	bool isMoving = true;
	float time = 0.0f;
	glm::mat4 position = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
};