#pragma once

#include "Vehicle.hpp"

#define _USE_MATH_DEFINES

#include <vector>
#include <string>
#include <math.h>

class Route
{
public:
	std::vector<IModel*> roadUsers;	// list of road users currently on this route

	Route(int ID) {
		routeID = ID;

		// !! if you change size here, change OBJECT_INSTANCES in Renderer.hpp (ln 42)
		for (size_t i = 0; i < 5; i++)
		{
			addRoadUser(new Vehicle(i));
		}
	};

	void update(float &delta);

	void addRoadUser(Vehicle *user)
	{
		roadUsers.push_back(user);
	}

	void removeRoadUser() {
	
	}

private:
	int routeID;					// route id
	const float speed = 20.0f;      // meters per second
	const float distance = 15.0f;	// distance in meters
};