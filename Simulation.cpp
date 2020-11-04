#include "Simulation.hpp"

void Simulation::InitSimulator()
{
	// todo: spit roads in straights and corners classes -- > trafic direction and length of the road

	routes.push_back(Route(1));
}

void Simulation::Update(float &delta) {
	for (Route &route : routes)
	{
		route.update(delta);
	}
}

void Simulation::LateUpdate(float& delta) { }