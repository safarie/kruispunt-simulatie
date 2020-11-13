#include "Simulation.hpp"

void Simulation::InitSimulator()
{
	for (size_t i = 0; i < 25; i++)		// !! if you change size here, check total modelcount in Renderer.cpp (ln 609)
	{
		models.push_back(new Vehicle(i));
	}

	InitTrafficLights();
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

void Simulation::InitTrafficLights()
{
	const std::vector<std::string> trafficLightNames = 
	{ 
		"A1-1", "A1-2", "A1-3",	"B1-1",	"B1-2",	"F1-1",	"F1-2",	"V1-1",	"V1-2",	"V1-3",	"V1-4",
		"A2-1",	"A2-2",	"A2-3",	"A2-4",	"F2-1",	"F2-2",	"V2-1",	"V2-2",	"V2-3",	"V2-4",
		"A3-1",	"A3-2",	"A3-3",	"A3-4",
		"A4-1",	"A4-2",	"A4-3",	"A4-4",	"B4-1",	"F4-1",	"F4-2",	"V4-1",	"V4-2",	"V4-3",	"V4-4",	
		"A5-1",	"A5-2",	"A5-3",	"A5-4",	"F5-1",	"F5-2",	"V5-1",	"V5-2",	"V5-3",	"V5-4",	
		"A6-1",	"A6-2",	"A6-3",	"A6-4" 
	};

	for (size_t i = 0; i < trafficLightNames.size(); i++)
	{
		TrafficLichtInfo light{};
		light.ID = trafficLightNames[i];
		light.state = 0;
		trafficLights.push_back(light);
	}
}

void Simulation::InitRoutes() 
{
	Route route0(0, &models);
	//route1.addSection(new Straight(glm::vec3(-71.75f, -80.0f, 0.0f), -90.0f, 50.0f));
	route0.addSection(new TrafficLight(glm::vec3(-71.75f, -80.0f, 0.0f), -90, 50.0f, 11, &trafficLights)); // A2-1
	route0.addSection(new Corner(glm::vec3(-71.75f, -30.0f, 0.0f), -90, 22.75f, -90.0f));
	route0.addSection(new Straight(glm::vec3(-49.0f, -7.25f, 0.0f), -180, 126.0f));
	route0.addSection(new Corner(glm::vec3(77.0f, -7.25f, 0.0f), -180, 16.25f, 90.0f));
	route0.addSection(new Straight(glm::vec3(93.25f, 9.0f, 0.0f), -90, 69.0f));
	route0.addSection(new End(glm::vec3(0.0f,0.0f,-10.0f), 0));
	route0.addModel(15);
	
	routes.push_back(route0);
}
