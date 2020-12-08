#pragma once

#include <glm/gtc/matrix_transform.hpp>

/// <summary>
/// model interface
/// </summary>
class IModel
{
public:
	/// <summary>
	/// update the model position
	/// </summary>
	/// <param name="delta">time past since last frame</param>
	/// <param name="pos">new position</param>
	void update(float &delta, glm::mat4 pos) {
		if (moving) {
			time += delta;
			position = pos;
		}
	}

	/// <summary>
	/// set the vehicle to active
	/// </summary>
	void activate() {
		active = true;
	}

	/// <summary>
	/// set the vehicle to inactive
	/// </summary>
	void deactivate() {
		active = false;
	}

	/// <summary>
	/// check if a vehicle is active
	/// </summary>
	/// <returns></returns>
	bool isActive() {
		return active;
	}

	/// <summary>
	/// reset the internal time of the vehicle
	/// </summary>
	void resetTime() {
		time = 0.0f;
	}

	/// <summary>
	/// set vehicle status to moving
	/// </summary>
	void start() {
		moving = true;
	}
	
	/// <summary>
	/// set the vhicle status to stoped
	/// </summary>
	void stop() {
		moving = false;
	}

	/// <summary>
	/// get the collision radius
	/// </summary>
	/// <returns>collision radius</returns>
	float getColRad() {
		return collisionRadius;
	}

	/// <summary>
	/// get the internal timer
	/// </summary>
	/// <returns>time</returns>
	float getTime() {
		return time;
	}

	/// <summary>
	/// get the current position
	/// </summary>
	/// <returns>return the position</returns>
	glm::mat4 getPos() {
		return position;
	}

	virtual int getID() = 0;
	virtual int getType() = 0;
	virtual float getSpeed() = 0;
	virtual void setSpeed(float Mps) = 0;

protected:
	float collisionRadius = 0.0f;
	bool moving = true;
	bool active = false;
	float time = 0.0f;
	glm::mat4 position = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
};