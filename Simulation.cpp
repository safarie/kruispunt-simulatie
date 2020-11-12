#include "Simulation.hpp"

void Simulation::InitSimulator()
{
	for (size_t i = 0; i < 25; i++)		// !! if you change size here, check total modelcount in Renderer.cpp (ln 609)
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
	trafficLights.resize(50, false);

	Route route0(0, &models);
	//route1.addSection(new Straight(glm::vec3(-71.75f, -80.0f, 0.0f), -90.0f, 50.0f));
	route0.addSection(new TrafficLight(glm::vec3(-71.75f, -80.0f, 0.0f), -90, 50.0f, trafficLights.at(7)));
	route0.addSection(new Corner(glm::vec3(-71.75f, -30.0f, 0.0f), -90, 22.75f, -90.0f));
	route0.addSection(new Straight(glm::vec3(-49.0f, -7.25f, 0.0f), -180, 126.0f));
	route0.addSection(new Corner(glm::vec3(77.0f, -7.25f, 0.0f), -180, 16.25f, 90.0f));
	route0.addSection(new Straight(glm::vec3(93.25f, 9.0f, 0.0f), -90, 69.0f));
	route0.addSection(new End(glm::vec3(0.0f,0.0f,-10.0f), 0));
	route0.addModel(15);
	
	routes.push_back(route0);
}

void Simulation::updateTrafficLights(std::vector<bool> trafficLights)
{
	this->trafficLights = trafficLights;
	/*for (size_t i = 0; i < this->trafficLights.size() ; i++)
	{
		this->trafficLights[i] = trafficLights[i];
	}*/
}
