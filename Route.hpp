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

		// !! if you change size here, check total modelcount in Renderer.cpp (ln 609)
		for (size_t i = 0; i < 20; i++)
		{
			addRoadUser(new Vehicle(i, i * 3.0f));
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