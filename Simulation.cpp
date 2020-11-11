#include "Simulation.hpp"

void Simulation::InitSimulator()
{
	// !! if you change size here, check total modelcount in Renderer.cpp (ln 609)
	for (size_t i = 0; i < 25; i++)
	{
		models.push_back(new Vehicle(i));
	}

	InitRoutes();
}

void Simulation::Update(float &delta) 
{
	for (Route &route : routes)
	{
		route.update(delta);
	}
}

void Simulation::LateUpdate(float& delta) 
{ 

}

void Simulation::InitRoutes() 
{
	Route route1(0, &models);
	route1.addSection(new Straight(glm::vec3(-71.75f, -80.0f, 0.0f), -90.0f, 50.0f));
	route1.addSection(new Corner(glm::vec3(-71.75f, -30.0f, 0.0f), -90.0f, 22.75f, -90.0f));
	route1.addSection(new Straight(glm::vec3(-49.0f, -7.25f, 0.0f), -180.0f, 126.0f));
	route1.addSection(new Corner(glm::vec3(77.0f, -7.25f, 0.0f), -180.0f, 16.25f, 90.0f));
	route1.addSection(new Straight(glm::vec3(93.25f, 9.0f, 0.0f), -90.0f, 69.0f));
	route1.addSection(new End(glm::vec3(0.0f,0.0f,-10.0f), 0));
	route1.addModel(1);
	
	routes.push_back(route1);
}