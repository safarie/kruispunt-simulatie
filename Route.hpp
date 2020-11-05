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

		// !! if you change size here, change OBJECT_INSTANCES in Renderer.hpp (ln 43)
		for (size_t i = 0; i < 1; i++)
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
};