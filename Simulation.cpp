#include "Simulation.hpp"

void Simulation::InitSimulator()
{
	InitTraffic();
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

void Simulation::InitTraffic()
{	
	int totalModelCount = 0;
	for (auto& mi : *modelInfo) {
		for (uint32_t i = totalModelCount; i < mi.modelCount + totalModelCount; i++)
		{
			models.push_back(new Vehicle(i, mi.collisionRadius));
		}
		totalModelCount += mi.modelCount;
	}
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
	// (x y z). degrees
	// routeIn 0-16, routeOut 17-24, routeCon 25-32

	// starting routes
	Route routeIn0(0, &models);
	routeIn0.addSection(new Straight(glm::vec3(-71.75f, -80.0f, 0.0f), -90.0f, 48.0f));
	routeIn0.addSection(new TrafficLight(glm::vec3(-71.75f, -32.0f, 0.0f), -90, 2.0f, 0, &trafficLights)); // A1-1
	routeIn0.addSection(new Corner(glm::vec3(-71.75f, -30.0f, 0.0f), -90, 22.75f, -90.0f));
	routeIn0.addModel(1);
	routes.push_back(routeIn0);
	routes[0].addModel(3);

	Route routeIn1(1, &models);
	routeIn1.addSection(new Straight(glm::vec3(-75.25f, -80.0f, 0.0f), -90.0f, 48.0f));
	routeIn1.addSection(new TrafficLight(glm::vec3(-75.25f, -32.0f, 0.0f), -90, 2.0f, 1, &trafficLights)); // A1-2
	// trans
	routes.push_back(routeIn1);

	Route routeIn2(1, &models);
	routeIn2.addSection(new Straight(glm::vec3(-78.75f, -80.0f, 0.0f), -90.0f, 48.0f));
	routeIn2.addSection(new TrafficLight(glm::vec3(-78.75f, -32.0f, 0.0f), -90, 2.0f, 2, &trafficLights)); // A1-3
	//trans
	routes.push_back(routeIn2);

	Route routeIn3(1, &models);
	routeIn3.addSection(new Straight(glm::vec3(-82.25f, -80.0f, 0.0f), -90.0f, 48.0f));
	routeIn3.addSection(new TrafficLight(glm::vec3(-82.25f, -32.0f, 0.0f), -90, 2.0f, 3, &trafficLights)); // B1-1
	routeIn3.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeIn3);

	Route routeIn4(4, &models);
	routes.push_back(routeIn4);

	Route routeIn5(5, &models);
	routes.push_back(routeIn5);

	Route routeIn6(6, &models);
	routes.push_back(routeIn6);
	
	Route routeIn7(7, &models);
	routes.push_back(routeIn7);

	Route routeIn8(8, &models);
	routes.push_back(routeIn8);
	
	Route routeIn9(9, &models);
	routes.push_back(routeIn9);

	Route routeIn10(10, &models);
	routes.push_back(routeIn10);

	Route routeIn11(11, &models);
	routes.push_back(routeIn11);

	Route routeIn12(12, &models);
	routes.push_back(routeIn12);

	Route routeIn13(13, &models);
	routes.push_back(routeIn13);

	Route routeIn14(14, &models);
	routes.push_back(routeIn14);

	Route routeIn15(15, &models);
	routes.push_back(routeIn15);

	Route routeIn16(16, &models);
	routes.push_back(routeIn16);

	// connection routes
	Route routeCon17(17, &models);
	routeCon17.addSection(new Straight(glm::vec3(-49.0f, -14.25f, 0.0f), -180, 124.0f));
	routeCon17.addSection(new TrafficLight(glm::vec3(75.0f, -14.25f, 0.0f), -180, 2.0f, 46, &trafficLights)); // A6-1
	routeCon17.addSection(new Corner(glm::vec3(77.0f, -14.25f, 0.0f), -180, 16.25f, 90.0f));
	// trans
	routes.push_back(routeCon17);
	
	Route routeCon18(18, &models);
	routeCon18.addSection(new Straight(glm::vec3(-49.0f, -10.75f, 0.0f), -180, 124.0f));
	routeCon18.addSection(new TrafficLight(glm::vec3(75.0f, -10.75f, 0.0f), -180, 2.0f, 47, &trafficLights)); // A6-2
	routeCon18.addSection(new Corner(glm::vec3(77.0f, -10.75f, 0.0f), -180, 16.25f, 90.0f));
	// trans
	routes.push_back(routeCon18);

	Route routeCon19(19, &models);
	routeCon19.addSection(new Straight(glm::vec3(-49.0f, -7.25f, 0.0f), -180, 124.0f));
	routeCon19.addSection(new TrafficLight(glm::vec3(75.0f, -7.25f, 0.0f), -180, 2.0f, 48, &trafficLights)); // A6-3
	routeCon19.addSection(new Corner(glm::vec3(77.0f, -7.25f, 0.0f), -180, 16.25f, 90.0f));
	// trans
	routes.push_back(routeCon19);

	Route routeCon20(20, &models);
	routeCon20.addSection(new Straight(glm::vec3(-49.0f, -3.75f, 0.0f), -180, 124.0f));
	routeCon20.addSection(new TrafficLight(glm::vec3(75.0f, -3.75f, 0.0f), -180, 2.0f, 49, &trafficLights)); // A6-4
	routeCon20.addSection(new Corner(glm::vec3(77.0f, -3.75f, 0.0f), -180, 16.25f, 90.0f));
	// trans
	routes.push_back(routeCon20);

	Route routeCon21(21, &models);
	routeCon21.addSection(new Straight(glm::vec3(75.0f, 3.75f, 0.0f), 0, 124.0f));
	routeCon21.addSection(new TrafficLight(glm::vec3(-49.0f, 3.75f, 0.0f), 0, 2.0f, 20, &trafficLights)); // A3-1
	routeCon21.addSection(new Corner(glm::vec3(-51.0f, 3.75f, 0.0f), 0, 16.25f, 90.0f));
	// trans
	routes.push_back(routeCon21);

	Route routeCon22(22, &models);
	routeCon22.addSection(new Straight(glm::vec3(75.0f, 7.25f, 0.0f), 0, 124.0f));
	routeCon22.addSection(new TrafficLight(glm::vec3(-49.0f, 7.25f, 0.0f), 0, 2.0f, 21, &trafficLights)); // A3-2
	routeCon22.addSection(new Corner(glm::vec3(-51.0f, 7.25f, 0.0f), 0, 16.25f, 90.0f));
	// trans
	routes.push_back(routeCon22);

	Route routeCon23(23, &models);
	routeCon23.addSection(new Straight(glm::vec3(75.0f, 10.75f, 0.0f), 0, 124.0f));
	routeCon23.addSection(new TrafficLight(glm::vec3(-49.0f, 10.75f, 0.0f), 0, 2.0f, 22, &trafficLights)); // A3-3
	routeCon23.addSection(new Straight(glm::vec3(-51.0f, 10.75f, 0.0f), 0, 52.0f));
	// trans
	routes.push_back(routeCon23);

	Route routeCon24(24, &models);
	routeCon24.addSection(new Straight(glm::vec3(75.0f, 14.25f, 0.0f), 0, 124.0f));
	routeCon24.addSection(new TrafficLight(glm::vec3(-49.0f, 14.25f, 0.0f), 0, 2.0f, 23, &trafficLights)); // A3-4
	routeCon24.addSection(new Straight(glm::vec3(-51.0f, 14.25f, 0.0f), 0, 52.0f));
	// trans
	routes.push_back(routeCon24);


	// exit routes
	Route routeOut25(25, &models);
	routeOut25.addSection(new Straight(glm::vec3(-89.75f, -9.0f, 0.0f), 90, 50.0f));
	routeOut25.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeOut25);

	Route routeOut26(26, &models);
	routeOut26.addSection(new Straight(glm::vec3(-93.25f, -9.0f, 0.0f), 90, 50.0f));
	routeOut26.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeOut26);

	Route routeOut27(27, &models);
	routeOut27.addSection(new Straight(glm::vec3(-102.0f, 10.75, 0.0f), 0, 48.0f));
	routeOut27.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeOut27);

	Route routeOut28(28, &models);
	routeOut28.addSection(new Straight(glm::vec3(-102.0f, 14.25, 0.0f), 0, 48.0f));
	routeOut28.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeOut28);

	Route routeOut29(29, &models);
	routeOut29.addSection(new Straight(glm::vec3(89.75f, 9.0f, 0.0f), -90, 50.0f));
	routeOut29.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeOut29);

	Route routeOut30(30, &models);
	routeOut30.addSection(new Straight(glm::vec3(93.25f, 9.0f, 0.0f), -90, 50.0f));
	routeOut30.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeOut30);

	Route routeOut31(31, &models);
	routeOut31.addSection(new Straight(glm::vec3(102.0f, -10.75, 0.0f), -180, 48.0f));
	routeOut31.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeOut31);

	Route routeOut32(32, &models);
	routeOut32.addSection(new Straight(glm::vec3(102.0f, -14.25, 0.0f), -180, 48.0f));
	routeOut32.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeOut32);

	// transitions
	routes[0].addSection(new Transition(glm::vec3(-49.0f, -10.75f, 0.0f), -180, &routes[19]));
	routes[19].addSection(new Transition(glm::vec3(-49.0f, -10.75f, 0.0f), -180, &routes[30]));
}
