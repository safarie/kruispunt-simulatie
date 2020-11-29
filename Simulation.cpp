#include "Simulation.hpp"

void Simulation::initSimulator()
{
	initTrafficLights();
	initRoutes();
	initTraffic();
}

void Simulation::update(float &delta) 
{
	for (Route &route : routes)
	{
		route.update(delta);
	}
}

void Simulation::lateUpdate(float& delta) 
{ 
	for (IModel *vehicle : models) {
		if (!vehicle->isActive()) {
			spawn(vehicle->getID());
		}
	}
}

void Simulation::initTrafficLights()
{
	const std::vector<std::string> trafficLightNames = 
	{ 
		"A1-1", "A1-2", "A1-3",	"B1-1",	"B1-2",	"F1-1",	"F1-2",	"V1-1",	"V1-2",	"V1-3",	"V1-4",		// 0  - 10 (11)
		"A2-1",	"A2-2",	"A2-3",	"A2-4",	"F2-1",	"F2-2",	"V2-1",	"V2-2",	"V2-3",	"V2-4",				// 11 - 20 (10)
		"A3-1",	"A3-2",	"A3-3",	"A3-4",																// 21 - 24 ( 4)
		"A4-1",	"A4-2",	"A4-3",	"A4-4",	"B4-1",	"F4-1",	"F4-2",	"V4-1",	"V4-2",	"V4-3",	"V4-4",		// 25 - 35 (11)
		"A5-1",	"A5-2",	"A5-3",	"A5-4",	"F5-1",	"F5-2",	"V5-1",	"V5-2",	"V5-3",	"V5-4",				// 36 - 45 (10)
		"A6-1",	"A6-2",	"A6-3",	"A6-4"																// 46 - 49 ( 4)
	};

	for (size_t i = 0; i < trafficLightNames.size(); i++)
	{
		TrafficLichtInfo light{};
		light.ID = trafficLightNames[i];
		light.state = 0;
		light.traffic = 0;
		trafficLights.push_back(light);
	}
}

void Simulation::initRoutes()
{
	for (size_t i = 0; i < 177; i++)
	{
		routes.push_back(Route(i, &models));
	}

	spawnRoutes.push_back({0,1,2,4,5,6,7,8,9,10,11,13,14,15,16});
	spawnRoutes.push_back({3,4,12,13});
	spawnRoutes.push_back({49,50,51,52,53,54,55});
	spawnRoutes.push_back({113,114,115,116,117,118,119});


	// cars & busses
	// routeIn 0-16, routeCon 17-24, routeOut 25-32, transitions 33-48

	// starting routes
	routes[0].addSection(new Straight(glm::vec3(-71.75f, -80.0f, 0.0f), -90.0f, 40.0f));
	routes[0].addSection(new TrafficLight(glm::vec3(-71.75f, -40.0f, 0.0f), -90, 2.0f, 0, &trafficLights)); // A1-1
	routes[0].addSection(new Straight(glm::vec3(-71.75f, -38.0f, 0.0f), -90.0f, 8.0f));
	routes[0].addSection(new Transition(&routes[33], &routes[34]));

	routes[1].addSection(new Straight(glm::vec3(-75.25f, -80.0f, 0.0f), -90.0f, 40.0f));
	routes[1].addSection(new TrafficLight(glm::vec3(-75.25f, -40.0f, 0.0f), -90, 2.0f, 1, &trafficLights)); // A1-2
	routes[1].addSection(new Straight(glm::vec3(-75.25f, -38.0f, 0.0f), -90.0f, 8.0f));
	routes[1].addSection(new Transition(&routes[35], &routes[36]));

	routes[2].addSection(new Straight(glm::vec3(-78.75f, -80.0f, 0.0f), -90.0f, 40.0f));
	routes[2].addSection(new TrafficLight(glm::vec3(-78.75f, -40.0f, 0.0f), -90, 2.0f, 2, &trafficLights)); // A1-3
	routes[2].addSection(new Straight(glm::vec3(-78.75f, -38.0f, 0.0f), -90, 29.0f));
	routes[2].addSection(new Corner(glm::vec3(-78.75f, -9.0f, 0.0f), -90, 23.25f, 90));
	routes[2].addSection(new Transition(&routes[28]));

	routes[3].addSection(new Straight(glm::vec3(-82.25f, -80.0f, 0.0f), -90.0f, 40.0f));
	routes[3].addSection(new TrafficLight(glm::vec3(-82.25f, -40.0f, 0.0f), -90, 2.0f, 3, &trafficLights)); // B1-1
	routes[3].addSection(new Straight(glm::vec3(-82.25f, -38.0f, 0.0f), -90, 29.0f));
	routes[3].addSection(new Corner(glm::vec3(-82.25f, -9.0f, 0.0f), -90, 19.75f, 90));
	routes[3].addSection(new Transition(&routes[27]));

	routes[4].addSection(new Straight(glm::vec3(-150.0f, -21.25f, 0.0f), -180, 38.0f));
	routes[4].addSection(new TrafficLight(glm::vec3(-112.0f, -21.25f, 0.0f), -180, 2.0f, 11, &trafficLights)); // A2-1
	routes[4].addSection(new Straight(glm::vec3(-110.0f, -21.25f, 0.0f), -180, 8.0f));
	routes[4].addSection(new Corner(glm::vec3(-102.0f, -21.25f, 0.0f), -180, 8.75f, -90));
	routes[4].addSection(new Transition(&routes[26]));

	routes[5].addSection(new Straight(glm::vec3(-150.0f, -17.75f, 0.0f), -180, 38.0f));
	routes[5].addSection(new TrafficLight(glm::vec3(-112.0f, -17.75f, 0.0f), -180, 2.0f, 12, &trafficLights)); // A2-2
	routes[5].addSection(new Straight(glm::vec3(-110.0f, -17.75f, 0.0f), -180, 8.0f));
	routes[5].addSection(new Corner(glm::vec3(-102.0f, -17.75f, 0.0f), -180, 12.25f, -90));
	routes[5].addSection(new Transition(&routes[25]));

	routes[6].addSection(new Straight(glm::vec3(-150.0f, -14.25f, 0.0f), -180, 38.0f));
	routes[6].addSection(new TrafficLight(glm::vec3(-112.0f, -14.25f, 0.0f), -180, 2.0f, 13, &trafficLights)); // A2-3
	routes[6].addSection(new Straight(glm::vec3(-110.0f, -14.25f, 0.0f), -180, 22.0f));
	routes[6].addSection(new Transition(&routes[37], &routes[38]));

	routes[7].addSection(new Straight(glm::vec3(-150.0f, -10.75f, 0.0f), -180, 38.0f));
	routes[7].addSection(new TrafficLight(glm::vec3(-112.0f, -10.75f, 0.0f), -180, 2.0f, 14, &trafficLights)); // A2-4
	routes[7].addSection(new Straight(glm::vec3(-110.0f, -10.75f, 0.0f), -180, 22.0f));
	routes[7].addSection(new Transition(&routes[39], &routes[40]));

	routes[8].addSection(new Straight(glm::vec3(82.25f, 80.0f, 0.0f), 90.0f, 36.0f));
	routes[8].addSection(new TrafficLight(glm::vec3(82.25f, 44.0f, 0.0f), 90, 2.0f, 25, &trafficLights)); // A4-1
	routes[8].addSection(new Straight(glm::vec3(82.25f, 42.0f, 0.0f), 90, 33.0f));
	routes[8].addSection(new Corner(glm::vec3(82.25f, 9.0f, 0.0f), 90, 19.75f, 90));
	routes[8].addSection(new Transition(&routes[32]));

	routes[9].addSection(new Straight(glm::vec3(78.75f, 80.0f, 0.0f), 90.0f, 36.0f));
	routes[9].addSection(new TrafficLight(glm::vec3(78.75f, 44.0f, 0.0f), 90, 2.0f, 26, &trafficLights)); // A4-2
	routes[9].addSection(new Straight(glm::vec3(78.75f, 42.0f, 0.0f), 90, 33.0f));
	routes[9].addSection(new Corner(glm::vec3(78.75f, 9.0f, 0.0f), 90, 23.25f, 90));
	routes[9].addSection(new Transition(&routes[31]));

	routes[10].addSection(new Straight(glm::vec3(75.25f, 80.0f, 0.0f), 90.0f, 36.0f));
	routes[10].addSection(new TrafficLight(glm::vec3(75.25f, 44.0f, 0.0f), 90, 2.0f, 27, &trafficLights)); // A4-3
	routes[10].addSection(new Straight(glm::vec3(75.25f, 42.0f, 0.0f), 90.0f, 12.0f));
	routes[10].addSection(new Transition(&routes[41], &routes[42]));

	routes[11].addSection(new Straight(glm::vec3(71.75f, 80.0f, 0.0f), 90.0f, 36.0f));
	routes[11].addSection(new TrafficLight(glm::vec3(71.75f, 44.0f, 0.0f), 90, 2.0f, 28, &trafficLights)); // A4-4
	routes[11].addSection(new Straight(glm::vec3(71.75f, 42.0f, 0.0f), 90.0f, 12.0f));
	routes[11].addSection(new Transition(&routes[43], &routes[44]));

	routes[12].addSection(new Straight(glm::vec3(68.25f, 80.0f, 0.0f), 90.0f, 34.0f));
	routes[12].addSection(new TrafficLight(glm::vec3(68.25f, 46.0f, 0.0f), 90, 2.0f, 29, &trafficLights)); // B4-1
	routes[12].addSection(new Corner(glm::vec3(68.25f, 45.0f, 0.0f), 115.0169f, 7.0f, 25.0169f));
	routes[12].addSection(new Straight(glm::vec3(70.25f, 43.0f, 0.0f), 115.0169f, 15.0f));
	routes[12].addSection(new Corner(glm::vec3(70.25f, 33.0f, 0.0f), 115.0169f, 7.0f, -25.0169f));
	routes[12].addSection(new Transition(&routes[41], &routes[42]));

	routes[13].addSection(new Straight(glm::vec3(150.0f, 10.75f, 0.0f), 0, 38.0f));
	routes[13].addSection(new TrafficLight(glm::vec3(112.0f, 10.75f, 0.0f), 0, 2.0f, 36, &trafficLights)); // A5-1
	routes[13].addSection(new Straight(glm::vec3(110.0f, 10.75f, 0.0f), 0, 22.0f));
	routes[13].addSection(new Transition(&routes[45], &routes[46]));

	routes[14].addSection(new Straight(glm::vec3(150.0f, 14.25f, 0.0f), 0, 38.0f));
	routes[14].addSection(new TrafficLight(glm::vec3(112.0f, 14.25f, 0.0f), 0, 2.0f, 37, &trafficLights)); // A5-2
	routes[14].addSection(new Straight(glm::vec3(110.0f, 14.25f, 0.0f), 0, 22.0f));
	routes[14].addSection(new Transition(&routes[47], &routes[48]));

	routes[15].addSection(new Straight(glm::vec3(150.0f, 17.75f, 0.0f), 0, 38.0f));
	routes[15].addSection(new TrafficLight(glm::vec3(112.0f, 17.75f, 0.0f), 0, 2.0f, 38, &trafficLights)); // A5-3
	routes[15].addSection(new Straight(glm::vec3(110.0f, 17.75f, 0.0f), 0, 8.0f));
	routes[15].addSection(new Corner(glm::vec3(102.0f, 17.75f, 0.0f), 0, 12.25f, -90));
	routes[15].addSection(new Transition(&routes[30]));

	routes[16].addSection(new Straight(glm::vec3(150.0f, 21.25f, 0.0f), 0, 38.0f));
	routes[16].addSection(new TrafficLight(glm::vec3(112.0f, 21.25f, 0.0f), 0, 2.0f, 39, &trafficLights)); // A5-4
	routes[16].addSection(new Straight(glm::vec3(110.0f, 21.25f, 0.0f), 0, 8.0f));
	routes[16].addSection(new Corner(glm::vec3(102.0f, 21.25f, 0.0f), 0, 8.75f, -90));
	routes[16].addSection(new Transition(&routes[29]));


	// connection routes
	routes[17].addSection(new Straight(glm::vec3(-60.0f, -14.25f, 0.0f), -180, 127.0f));
	routes[17].addSection(new TrafficLight(glm::vec3(67.0f, -14.25f, 0.0f), -180, 2.0f, 46, &trafficLights)); // A6-1
	routes[17].addSection(new Straight(glm::vec3(69.0f, -14.25f, 0.0f), -180, 33.0f));
	routes[17].addSection(new Transition(&routes[31]));

	routes[18].addSection(new Straight(glm::vec3(-60.0f, -10.75f, 0.0f), -180, 127.0f));
	routes[18].addSection(new TrafficLight(glm::vec3(67.0f, -10.75f, 0.0f), -180, 2.0f, 47, &trafficLights)); // A6-2
	routes[18].addSection(new Straight(glm::vec3(69.0f, -10.75f, 0.0f), -180, 33.0f));
	routes[18].addSection(new Transition(&routes[32]));

	routes[19].addSection(new Straight(glm::vec3(-60.0f, -7.25f, 0.0f), -180, 127.0f));
	routes[19].addSection(new TrafficLight(glm::vec3(67.0f, -7.25f, 0.0f), -180, 2.0f, 48, &trafficLights)); // A6-3
	routes[19].addSection(new Straight(glm::vec3(69.0f, -7.25f, 0.0f), -180, 8.0f));
	routes[19].addSection(new Corner(glm::vec3(77.0f, -7.25f, 0.0f), -180, 16.25f, 90.0f));
	routes[19].addSection(new Straight(glm::vec3(93.25f, 9.0f, 0.0f), -90, 21.0f));
	routes[19].addSection(new Transition(&routes[29]));

	routes[20].addSection(new Straight(glm::vec3(-60.0f, -3.75f, 0.0f), -180, 127.0f));
	routes[20].addSection(new TrafficLight(glm::vec3(67.0f, -3.75f, 0.0f), -180, 2.0f, 49, &trafficLights)); // A6-4
	routes[20].addSection(new Straight(glm::vec3(69.0f, -3.75f, 0.0f), -180, 8.0f));
	routes[20].addSection(new Corner(glm::vec3(77.0f, -3.75f, 0.0f), -180, 12.75f, 90.0f));
	routes[20].addSection(new Straight(glm::vec3(89.75f, 9.0f, 0.0f), -90, 21.0f));
	routes[20].addSection(new Transition(&routes[30]));

	routes[21].addSection(new Straight(glm::vec3(60.0f, 3.75f, 0.0f), 0, 127.0f));
	routes[21].addSection(new TrafficLight(glm::vec3(-67.0f, 3.75f, 0.0f), 0, 2.0f, 21, &trafficLights)); // A3-1
	routes[21].addSection(new Straight(glm::vec3(-69.0f, 3.75f, 0.0f), 0, 8.0f));
	routes[21].addSection(new Corner(glm::vec3(-77.0f, 3.75f, 0.0f), 0, 12.75f, 90.0f));
	routes[21].addSection(new Straight(glm::vec3(-89.75f, -9.0f, 0.0f), 90, 21.0f));
	routes[21].addSection(new Transition(&routes[25]));

	routes[22].addSection(new Straight(glm::vec3(60.0f, 7.25f, 0.0f), 0, 127.0f));
	routes[22].addSection(new TrafficLight(glm::vec3(-67.0f, 7.25f, 0.0f), 0, 2.0f, 22, &trafficLights)); // A3-2
	routes[22].addSection(new Straight(glm::vec3(-69.0f, 7.25f, 0.0f), 0, 8.0f));
	routes[22].addSection(new Corner(glm::vec3(-77.0f, 7.25f, 0.0f), 0, 16.25f, 90.0f));
	routes[22].addSection(new Straight(glm::vec3(-93.25f, -9.0f, 0.0f), 90, 21.0f));
	routes[22].addSection(new Transition(&routes[26]));
	
	routes[23].addSection(new Straight(glm::vec3(60.0f, 10.75f, 0.0f), 0, 127.0f));
	routes[23].addSection(new TrafficLight(glm::vec3(-67.0f, 10.75f, 0.0f), 0, 2.0f, 23, &trafficLights)); // A3-3
	routes[23].addSection(new Straight(glm::vec3(-69.0f, 10.75f, 0.0f), 0, 33.0f));
	routes[23].addSection(new Transition(&routes[27]));
	
	routes[24].addSection(new Straight(glm::vec3(60.0f, 14.25f, 0.0f), 0, 127.0f));
	routes[24].addSection(new TrafficLight(glm::vec3(-67.0f, 14.25f, 0.0f), 0, 2.0f, 24, &trafficLights)); // A3-4
	routes[24].addSection(new Straight(glm::vec3(-69.0f, 14.25f, 0.0f), 0, 33.0f));
	routes[24].addSection(new Transition(&routes[28]));


	// exit routes
	routes[25].addSection(new Straight(glm::vec3(-89.75f, -30.0f, 0.0f), 90, 50.0f));
	routes[25].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[26].addSection(new Straight(glm::vec3(-93.25f, -30.0f, 0.0f), 90, 50.0f));
	routes[26].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[27].addSection(new Straight(glm::vec3(-102.0f, 10.75, 0.0f), 0, 48.0f));
	routes[27].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[28].addSection(new Straight(glm::vec3(-102.0f, 14.25, 0.0f), 0, 48.0f));
	routes[28].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[29].addSection(new Straight(glm::vec3(93.25f, 30.0f, 0.0f), -90, 50.0f));
	routes[29].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[30].addSection(new Straight(glm::vec3(89.75f, 30.0f, 0.0f), -90, 50.0f));
	routes[30].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[31].addSection(new Straight(glm::vec3(102.0f, -14.25, 0.0f), -180, 48.0f));
	routes[31].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[32].addSection(new Straight(glm::vec3(102.0f, -10.75, 0.0f), -180, 48.0f));
	routes[32].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));


	// transition routes
	routes[33].addSection(new Straight(glm::vec3(-71.75f, -30.0f, 0.0f), -90, 4.0f));
	routes[33].addSection(new Corner(glm::vec3(-71.75f, -26.0f, 0.0f), -90, 11.75f, -90.0f));
	routes[33].addSection(new Transition(&routes[17]));

	routes[34].addSection(new Straight(glm::vec3(-71.75f, -30.0f, 0.0f), -90, 7.5f));
	routes[34].addSection(new Corner(glm::vec3(-71.75f, -22.5f, 0.0f), -90, 11.75f, -90.0f));
	routes[34].addSection(new Transition(&routes[18]));

	routes[35].addSection(new Straight(glm::vec3(-75.25f, -30.0f, 0.0f), -90, 11.0f));
	routes[35].addSection(new Corner(glm::vec3(-75.25f, -19.0f, 0.0f), -90, 11.75f, -90.0f));
	routes[35].addSection(new Straight(glm::vec3(-63.5f, -7.25f, 0.0f), -180, 3.5f));
	routes[35].addSection(new Transition(&routes[19]));

	routes[36].addSection(new Straight(glm::vec3(-75.25f, -30.0f, 0.0f), -90, 14.5f));
	routes[36].addSection(new Corner(glm::vec3(-75.25f, -15.5f, 0.0f), -90, 11.75f, -90.0f));
	routes[36].addSection(new Straight(glm::vec3(-63.5f, -3.75f, 0.0f), -180, 3.5f));
	routes[36].addSection(new Transition(&routes[20]));

	routes[37].addSection(new Straight(glm::vec3(-88.0f, -14.25f, 0.0f), -180, 28.0f));
	routes[37].addSection(new Transition(&routes[17]));

	routes[38].addSection(new Straight(glm::vec3(-88.0f, -14.25f, 0.0f), -172.875f, 28.2179f));
	routes[38].addSection(new Transition(&routes[18]));

	routes[39].addSection(new Straight(glm::vec3(-88.0f, -10.75f, 0.0f), -172.875f, 27.2179f));
	routes[39].addSection(new Transition(&routes[19]));

	routes[40].addSection(new Straight(glm::vec3(-88.0f, -10.75f, 0.0f), -165.9638f, 28.8617f));
	routes[40].addSection(new Transition(&routes[20]));

	routes[41].addSection(new Straight(glm::vec3(75.25f, 30.0f, 0.0f), 90, 14.5f));
	routes[41].addSection(new Corner(glm::vec3(75.25f, 15.5f, 0.0f), 90, 11.75f, -90.0f));
	routes[41].addSection(new Straight(glm::vec3(63.5f, 3.75f, 0.0f), 0, 3.5f));
	routes[41].addSection(new Transition(&routes[21]));

	routes[42].addSection(new Straight(glm::vec3(75.25f, 30.0f, 0.0f), 90, 11.0f));
	routes[42].addSection(new Corner(glm::vec3(75.25f, 19.0f, 0.0f), 90, 11.75f, -90.0f));
	routes[42].addSection(new Straight(glm::vec3(63.5f, 7.25f, 0.0f), 0, 3.5f));
	routes[42].addSection(new Transition(&routes[22]));

	routes[43].addSection(new Straight(glm::vec3(71.75f, 30.0f, 0.0f), 90, 7.5f));
	routes[43].addSection(new Corner(glm::vec3(71.75f, 22.5f, 0.0f), 90, 11.75f, -90.0f));
	routes[43].addSection(new Transition(&routes[23]));

	routes[44].addSection(new Straight(glm::vec3(71.75f, 30.0f, 0.0f), 90, 4.0f));
	routes[44].addSection(new Corner(glm::vec3(71.75f, 26.0f, 0.0f), 90, 11.75f, -90.0f));
	routes[44].addSection(new Transition(&routes[24]));

	routes[45].addSection(new Straight(glm::vec3(88.0f, 10.75f, 0.0f), 14.0362f, 28.8617f));
	routes[45].addSection(new Transition(&routes[21]));

	routes[46].addSection(new Straight(glm::vec3(88.0f, 10.75f, 0.0f), 7.1250f, 27.2179f));
	routes[46].addSection(new Transition(&routes[22]));

	routes[47].addSection(new Straight(glm::vec3(88.0f, 14.25f, 0.0f), 7.1250f, 28.2179f));
	routes[47].addSection(new Transition(&routes[23]));

	routes[48].addSection(new Straight(glm::vec3(88.0f, 14.25f, 0.0f), 0, 28.0f));
	routes[48].addSection(new Transition(&routes[24]));


	// bicycles
	// routeIn 49-55, routeCon 56-63, routeOut 64-70, transitions 71-112

	// starting routes
	routes[49].addSection(new Straight(glm::vec3(-103.0f, -80.0f, 0.0f), -90.0f, 46.0f));
	routes[49].addSection(new Transition(&routes[71], &routes[72], &routes[73]));

	routes[50].addSection(new Straight(glm::vec3(-150.0f, -33.0f, 0.0f), -180.0f, 44.0f));
	routes[50].addSection(new Transition(&routes[74], &routes[75], &routes[76]));

	routes[51].addSection(new Straight(glm::vec3(-150.0f, 31.0f, 0.0f), -180.0f, 44.0f));
	routes[51].addSection(new Transition(&routes[77], &routes[78], &routes[79]));

	routes[52].addSection(new Straight(glm::vec3(-105.0f, 80.0f, 0.0f), 90.0f, 46.0f));
	routes[52].addSection(new Transition(&routes[80], &routes[81], &routes[82]));

	routes[53].addSection(new Straight(glm::vec3(150.0f, 33.0f, 0.0f), 0.0f, 44.0f));
	routes[53].addSection(new Transition(&routes[83], &routes[84]));

	routes[54].addSection(new Straight(glm::vec3(150.0f, -31.0f, 0.0f), 0.0f, 44.0f));
	routes[54].addSection(new Transition(&routes[85], &routes[86], &routes[87]));

	routes[55].addSection(new Straight(glm::vec3(105.0f, -80.0f, 0.0f), -90.0f, 46.0f));
	routes[55].addSection(new Transition(&routes[88], &routes[89], &routes[90]));


	// connection routes
	routes[56].addSection(new Straight(glm::vec3(102.0f, -31.0f, 0.0f), 0.0f, 170.0f));
	routes[56].addSection(new TrafficLight(glm::vec3(-68.0f, -31.0f, 0.0f), 0, 1.0f, 5, &trafficLights)); // F1-1
	routes[56].addSection(new Straight(glm::vec3(-69.0f, -31.0f, 0.0f), 0.0f, 33.0f));
	routes[56].addSection(new Transition(&routes[107], &routes[108], &routes[109]));

	routes[57].addSection(new Straight(glm::vec3(-102.0f, -33.0f, 0.0f), -180.0f, 5.0f));
	routes[57].addSection(new TrafficLight(glm::vec3(-97.0f, -33.0f, 0.0f), -180, 1.0f, 6, &trafficLights)); // F1-2
	routes[57].addSection(new Straight(glm::vec3(-96.0f, -33.0f, 0.0f), -180.0f, 198.0f));
	routes[57].addSection(new Transition(&routes[110], &routes[111], &routes[112]));

	routes[58].addSection(new Straight(glm::vec3(-103.0f, -30.0f, 0.0f), -90.0f, 5));
	routes[58].addSection(new TrafficLight(glm::vec3(-103.0f, -25.0f, 0.0f), -90, 1.0f, 15, &trafficLights)); // F2-1
	routes[58].addSection(new Straight(glm::vec3(-103.0f, -24.0f, 0.0f), -90.0f, 54));
	routes[58].addSection(new Transition(&routes[94], &routes[95], &routes[96]));

	routes[59].addSection(new Straight(glm::vec3(-105.0f, 30.0f, 0.0f), 90.0f, 12));
	routes[59].addSection(new TrafficLight(glm::vec3(-105.0f, 18.0f, 0.0f), 90, 1.0f, 16, &trafficLights)); // F2-2
	routes[59].addSection(new Straight(glm::vec3(-105.0f, 17.0f, 0.0f), 90.0f, 47));
	routes[59].addSection(new Transition(&routes[91], &routes[92], &routes[93]));

	routes[60].addSection(new Straight(glm::vec3(102.0f, 33.0f, 0.0f), 0.0f, 5.0f));
	routes[60].addSection(new TrafficLight(glm::vec3(97.0f, 33.0f, 0.0f), 0, 1.0f, 30, &trafficLights)); // F4-1
	routes[60].addSection(new Straight(glm::vec3(96.0f, 33.0f, 0.0f), 0.0f, 198.0f));
	routes[60].addSection(new Transition(&routes[97], &routes[98], &routes[99]));

	routes[61].addSection(new Straight(glm::vec3(-102.0f, 31.0f, 0.0f), -180.0f, 170.0f));
	routes[61].addSection(new TrafficLight(glm::vec3(68.0f, 31.0f, 0.0f), -180, 1.0f, 31, &trafficLights)); // F4-2
	routes[61].addSection(new Straight(glm::vec3(69.0f, 31.0f, 0.0f), -180.0f, 33.0f));
	routes[61].addSection(new Transition(&routes[100], &routes[101]));

	routes[62].addSection(new Straight(glm::vec3(105.0f, -30.0f, 0.0f), -90.0f, 12));
	routes[62].addSection(new TrafficLight(glm::vec3(105.0f, -18.0f, 0.0f), -90, 1.0f, 40, &trafficLights)); // F5-1
	routes[62].addSection(new Straight(glm::vec3(105.0f, -17.0f, 0.0f), -90.0f, 47));
	routes[62].addSection(new Transition(&routes[105], &routes[106]));

	routes[63].addSection(new Straight(glm::vec3(103.0f, 30.0f, 0.0f), 90.0f, 5));
	routes[63].addSection(new TrafficLight(glm::vec3(103.0f, 25.0f, 0.0f), 90, 1.0f, 41, &trafficLights)); // F5-2
	routes[63].addSection(new Straight(glm::vec3(103.0f, 24.0f, 0.0f), 90.0f, 54));
	routes[63].addSection(new Transition(&routes[102], &routes[103], &routes[104]));


	// exit routes
	routes[64].addSection(new Straight(glm::vec3(-105.0f, -34.0f, 0.0f), 90.0f, 46.0f));
	routes[64].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[65].addSection(new Straight(glm::vec3(-106.0f, -31.0f, 0.0f), 0.0f, 44.0f));
	routes[65].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[66].addSection(new Straight(glm::vec3(-106.0f, 33.0f, 0.0f), 0.0f, 44.0f));
	routes[66].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[67].addSection(new Straight(glm::vec3(-103.0f, 34.0f, 0.0f), -90.0f, 46.0f));
	routes[67].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[68].addSection(new Straight(glm::vec3(106.0f, 31.0f, 0.0f), -180.0f, 44.0f));
	routes[68].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[69].addSection(new Straight(glm::vec3(106.0f, -33.0f, 0.0f), -180.0f, 44.0f));
	routes[69].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[70].addSection(new Straight(glm::vec3(103.0f, -34.0f, 0.0f), 90.0f, 46.0f));
	routes[70].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));


	// transition routes
	routes[71].addSection(new Corner(glm::vec3(-103.0f, -34, 0.0f), -90.0f, 1.0f, -90.0f));
	routes[71].addSection(new Transition(&routes[57]));
	routes[72].addSection(new Straight(glm::vec3(-103.0f, -34, 0.0f), -90.0f, 4.0f));
	routes[72].addSection(new Transition(&routes[58]));
	routes[73].addSection(new Corner(glm::vec3(-103.0f, -34, 0.0f), -90.0f, 3.0f, 90.0f));
	routes[73].addSection(new Transition(&routes[65]));

	routes[74].addSection(new Corner(glm::vec3(-106.0f, -33, 0.0f), -180.0f, 1.0f, -90.0f));
	routes[74].addSection(new Transition(&routes[64]));
	routes[75].addSection(new Straight(glm::vec3(-106.0f, -33, 0.0f), -180.0f, 4.0f));
	routes[75].addSection(new Transition(&routes[57]));
	routes[76].addSection(new Corner(glm::vec3(-106.0f, -33, 0.0f), -180.0f, 3.0f, 90.0f));
	routes[76].addSection(new Transition(&routes[58]));

	routes[77].addSection(new Corner(glm::vec3(-106.0f, 31, 0.0f), -180.0f, 1.0f, -90.0f));
	routes[77].addSection(new Transition(&routes[59]));
	routes[78].addSection(new Straight(glm::vec3(-106.0f, 31, 0.0f), -180.0f, 4.0f));
	routes[78].addSection(new Transition(&routes[61]));
	routes[79].addSection(new Corner(glm::vec3(-106.0f, 31, 0.0f), -180.0f, 3.0f, 90.0f));
	routes[79].addSection(new Transition(&routes[67]));

	routes[80].addSection(new Corner(glm::vec3(-105.0f, 34, 0.0f), 90.0f, 1.0f, -90.0f));
	routes[80].addSection(new Transition(&routes[66]));
	routes[81].addSection(new Straight(glm::vec3(-105.0f, 34, 0.0f), 90.0f, 4.0f));
	routes[81].addSection(new Transition(&routes[59]));
	routes[82].addSection(new Corner(glm::vec3(-105.0f, 34, 0.0f), 90.0f, 3.0f, 90.0f));
	routes[82].addSection(new Transition(&routes[61]));

	routes[83].addSection(new Straight(glm::vec3(106.0f, 33, 0.0f), 0.0f, 4.0f));
	routes[83].addSection(new Transition(&routes[60]));
	routes[84].addSection(new Corner(glm::vec3(106.0f, 33, 0.0f), 0.0f, 3.0f, 90.0f));
	routes[84].addSection(new Transition(&routes[63]));
	
	routes[85].addSection(new Corner(glm::vec3(106.0f, -31, 0.0f), 0.0f, 1.0f, -90.0f));
	routes[85].addSection(new Transition(&routes[62]));
	routes[86].addSection(new Straight(glm::vec3(106.0f, -31, 0.0f), 0.0f, 4.0f));
	routes[86].addSection(new Transition(&routes[56]));
	routes[87].addSection(new Corner(glm::vec3(106.0f, -31, 0.0f), 0.0f, 3.0f, 90.0f));
	routes[87].addSection(new Transition(&routes[70]));

	routes[88].addSection(new Corner(glm::vec3(105.0f, -34, 0.0f), -90.0f, 1.0f, -90.0f));
	routes[88].addSection(new Transition(&routes[56]));
	routes[89].addSection(new Straight(glm::vec3(105.0f, -34, 0.0f), -90.0f, 4.0f));
	routes[89].addSection(new Transition(&routes[62]));
	routes[90].addSection(new Corner(glm::vec3(105.0f, -34, 0.0f), -90.0f, 3.0f, 90.0f));
	routes[90].addSection(new Transition(&routes[69]));

	routes[91].addSection(new Corner(glm::vec3(-105.0f, -30.0f, 0.0f), 90.0f, 1.0f, -90.0f));
	routes[91].addSection(new Transition(&routes[65]));
	routes[92].addSection(new Straight(glm::vec3(-105.0f, -30.0f, 0.0f), 90, 4.0f));
	routes[92].addSection(new Transition(&routes[64]));
	routes[93].addSection(new Corner(glm::vec3(-105.0f, -30.0f, 0.0f), 90.0f, 3.0f, 90.0f));
	routes[93].addSection(new Transition(&routes[57]));

	routes[94].addSection(new Corner(glm::vec3(-103.0f, 30.0f, 0.0f), -90.0f, 1.0f, -90.0f));
	routes[94].addSection(new Transition(&routes[61]));
	routes[95].addSection(new Straight(glm::vec3(-103.0f, 30.0f, 0.0f), -90, 4.0f));
	routes[95].addSection(new Transition(&routes[67]));
	routes[96].addSection(new Corner(glm::vec3(-103.0f, 30.0f, 0.0f), -90.0f, 3.0f, 90.0f));
	routes[96].addSection(new Transition(&routes[66]));

	routes[97].addSection(new Corner(glm::vec3(-102.0f, 33.0f, 0.0f), 0.0f, 1.0f, -90.0f));
	routes[97].addSection(new Transition(&routes[67]));
	routes[98].addSection(new Straight(glm::vec3(-102.0f, 33.0f, 0.0f), 0.0f, 4.0f));
	routes[98].addSection(new Transition(&routes[66]));
	routes[99].addSection(new Corner(glm::vec3(-102.0f, 33.0f, 0.0f), 0.0f, 3.0f, 90.0f));
	routes[99].addSection(new Transition(&routes[59]));

	routes[100].addSection(new Corner(glm::vec3(102.0f, 31.0f, 0.0f), -180.0f, 1.0f, -90.0f));
	routes[100].addSection(new Transition(&routes[63]));
	routes[101].addSection(new Straight(glm::vec3(102.0f, 31.0f, 0.0f), -180.0f, 4.0f));
	routes[101].addSection(new Transition(&routes[68]));

	routes[102].addSection(new Corner(glm::vec3(103.0f, -30.0f, 0.0f), 90.0f, 1.0f, -90.0f));
	routes[102].addSection(new Transition(&routes[56]));
	routes[103].addSection(new Straight(glm::vec3(103.0f, -30.0f, 0.0f), 90, 4.0f));
	routes[103].addSection(new Transition(&routes[70]));
	routes[104].addSection(new Corner(glm::vec3(103.0f, -30.0f, 0.0f), 90.0f, 3.0f, 90.0f));
	routes[104].addSection(new Transition(&routes[69]));
	
	routes[105].addSection(new Corner(glm::vec3(105.0f, 30.0f, 0.0f), -90.0f, 1.0f, -90.0f));
	routes[105].addSection(new Transition(&routes[68]));
	routes[106].addSection(new Corner(glm::vec3(105.0f, 30.0f, 0.0f), -90.0f, 3.0f, 90.0f));
	routes[106].addSection(new Transition(&routes[60]));

	routes[107].addSection(new Corner(glm::vec3(-102.0f, -31.0f, 0.0f), 0.0f, 1.0f, -90.0f));
	routes[107].addSection(new Transition(&routes[58]));
	routes[108].addSection(new Straight(glm::vec3(-102.0f, -31.0f, 0.0f), 0.0f, 4.0f));
	routes[108].addSection(new Transition(&routes[65]));
	routes[109].addSection(new Corner(glm::vec3(-102.0f, -31.0f, 0.0f), 0.0f, 3.0f, 90.0f));
	routes[109].addSection(new Transition(&routes[64]));

	routes[110].addSection(new Corner(glm::vec3(102.0f, -33.0f, 0.0f), -180.0f, 1.0f, -90.0f));
	routes[110].addSection(new Transition(&routes[70]));
	routes[111].addSection(new Straight(glm::vec3(102.0f, -33.0f, 0.0f), -180.0f, 4.0f));
	routes[111].addSection(new Transition(&routes[69]));
	routes[112].addSection(new Corner(glm::vec3(102.0f, -33.0f, 0.0f), -180.0f, 3.0f, 90.0f));
	routes[112].addSection(new Transition(&routes[62]));


	// pedestrians
	// routeIn 113-119, routeCon 120-129, routeOut 130-136, transitions 137-176

	// starting routes
	routes[113].addSection(new Straight(glm::vec3(-150.0f, -35.5f, 0.2f), -180.0f, 42.0f));
	routes[113].addSection(new Transition(&routes[137], &routes[138]));

	routes[114].addSection(new Straight(glm::vec3(-150.0f, 34.5f, 0.2f), -180.0f, 42.0f));
	routes[114].addSection(new Transition(&routes[139], &routes[140], &routes[141]));

	routes[115].addSection(new Straight(glm::vec3(-107.5f, 80.0f, 0.2f), 90.0f, 44.0f));
	routes[115].addSection(new Transition(&routes[142], &routes[143], &routes[144]));

	routes[116].addSection(new Straight(glm::vec3(65.0, 80.0f, 0.2f), 90.0f, 44.0f));
	routes[116].addSection(new Transition(&routes[145], &routes[146]));

	routes[117].addSection(new Straight(glm::vec3(150.0f, 35.5f, 0.2f), 0.0f, 42.0f));
	routes[117].addSection(new Transition(&routes[147], &routes[148]));

	routes[118].addSection(new Straight(glm::vec3(150.0f, -34.5f, 0.2f), 0.0f, 42.0f));
	routes[118].addSection(new Transition(&routes[149], &routes[150], &routes[151]));

	routes[119].addSection(new Straight(glm::vec3(107.5f, -80.0f, 0.2), -90.0f, 44.0f));
	routes[119].addSection(new Transition(&routes[152], &routes[153], &routes[154]));


	// connection routes
	routes[120].addSection(new Straight(glm::vec3(100.0f, -34.5f, 0.2f), 0.0f, 169.0f));
	routes[120].addSection(new TrafficLight(glm::vec3(-69.0f, -34.5f, 0.2f), 0, 1.0f, 7, &trafficLights)); // V1-1
	routes[120].addSection(new Straight(glm::vec3(-70.0f, -34.5f, 0.2f), 0.0f, 17.0f));
	routes[120].addSection(new TrafficLight(glm::vec3(-87.0f, -34.5f, 0.2f), 0, 1.0f, 9, &trafficLights)); // V1-3
	routes[120].addSection(new Straight(glm::vec3(-88.0f, -34.5f, 0.2f), 0.0f, 12.0f));
	routes[120].addSection(new Transition(&routes[155], &routes[156]));

	routes[121].addSection(new Straight(glm::vec3(-100.0f, -35.5f, 0.2f), -180.0f, 4.0f));
	routes[121].addSection(new TrafficLight(glm::vec3(-96.0f, -35.5f, 0.2f), -180, 1.0f, 10, &trafficLights)); // V1-4
	routes[121].addSection(new Straight(glm::vec3(-95.0f, -35.5f, 0.2f), -180.0f, 10.0f));
	routes[121].addSection(new TrafficLight(glm::vec3(-85.0f, -35.5f, 0.2f), -180, 1.0f, 8, &trafficLights)); // V1-2
	routes[121].addSection(new Straight(glm::vec3(-84.0f, -35.5f, 0.2f), -180.0f, 184.0f));
	routes[121].addSection(new Transition(&routes[157], &routes[158], &routes[159]));

	routes[122].addSection(new Straight(glm::vec3(-106.5f, -28.0f, 0.2f), -90.0f, 4));
	routes[122].addSection(new TrafficLight(glm::vec3(-106.5f, -24.0f, 0.2f), -90, 1.0f, 17, &trafficLights)); // V2-1
	routes[122].addSection(new Straight(glm::vec3(-106.5f, -23.0f, 0.2f), -90.0f, 31));
	routes[122].addSection(new TrafficLight(glm::vec3(-106.5f, 8.0f, 0.2f), -90, 1.0f, 19, &trafficLights)); // V2-3
	routes[122].addSection(new Straight(glm::vec3(-106.5f, 9.0f, 0.2f), -90.0f, 19));
	routes[122].addSection(new Transition(&routes[160], &routes[161], &routes[162]));

	routes[123].addSection(new Straight(glm::vec3(-107.5f, 28.0f, 0.2f), 90.0f, 11));
	routes[123].addSection(new TrafficLight(glm::vec3(-107.5f, 17.0f, 0.2f), 90, 1.0f, 20, &trafficLights)); // V2-4
	routes[123].addSection(new Straight(glm::vec3(-107.5f, 16.0f, 0.2f), 90.0f, 24));
	routes[123].addSection(new TrafficLight(glm::vec3(-107.5f, -8.0f, 0.2f), 90, 1.0f, 18, &trafficLights)); // V2-2
	routes[123].addSection(new Straight(glm::vec3(-107.5f, -9.0f, 0.2f), 90.0f, 19));
	routes[123].addSection(new Transition(&routes[163], &routes[164]));

	routes[124].addSection(new Straight(glm::vec3(100.0f, 35.5f, 0.2f), 0.0f, 4.0f));
	routes[124].addSection(new TrafficLight(glm::vec3(96.0f, 35.5f, 0.2f), 0, 1.0f, 32, &trafficLights)); // V4-1
	routes[124].addSection(new Straight(glm::vec3(95.0f, 35.5f, 0.2f), 0.0f, 10.0f));
	routes[124].addSection(new TrafficLight(glm::vec3(85.0f, 35.5f, 0.2f), 0, 1.0f, 34, &trafficLights)); // V4-3
	routes[124].addSection(new Straight(glm::vec3(84.0f, 35.5f, 0.2f), 0.0f, 17.5f));
	routes[124].addSection(new Transition(&routes[125], &routes[165]));

	routes[125].addSection(new Straight(glm::vec3(66.5f, 35.5f, 0.2f), 0.0f, 166.5f));
	routes[125].addSection(new Transition(&routes[166], &routes[167], &routes[168]));

	routes[126].addSection(new Straight(glm::vec3(-100.0f, 34.5f, 0.2f), -180.0f, 166.5f));
	routes[126].addSection(new Transition(&routes[127], &routes[169]));

	routes[127].addSection(new Straight(glm::vec3(66.5f, 34.5f, 0.2f), -180.0f, 2.5f));
	routes[127].addSection(new TrafficLight(glm::vec3(69.0f, 34.5f, 0.2f), -180, 1.0f, 35, &trafficLights)); // V4-4
	routes[127].addSection(new Straight(glm::vec3(70.0f, 34.5f, 0.2f), -180.0f, 17.0f));
	routes[127].addSection(new TrafficLight(glm::vec3(87.0f, 34.5f, 0.2f), -180, 1.0f, 33, &trafficLights)); // V4-2
	routes[127].addSection(new Straight(glm::vec3(88.0f, 34.5f, 0.2f), -180.0f, 12.0f));
	routes[127].addSection(new Transition(&routes[170], &routes[171]));

	routes[128].addSection(new Straight(glm::vec3(106.5f, 28.0f, 0.2f), 90.0f, 4));
	routes[128].addSection(new TrafficLight(glm::vec3(106.5f, 24.0f, 0.2f), 90, 1.0f, 45, &trafficLights)); // V5-4
	routes[128].addSection(new Straight(glm::vec3(106.5f, 23.0f, 0.2f), 90.0f, 31));
	routes[128].addSection(new TrafficLight(glm::vec3(106.5f, -8.0f, 0.2f), 90, 1.0f, 43, &trafficLights)); // V5-2
	routes[128].addSection(new Straight(glm::vec3(106.5f, -9.0f, 0.2f), 90.0f, 19));
	routes[128].addSection(new Transition(&routes[172], &routes[173], &routes[174]));

	routes[129].addSection(new Straight(glm::vec3(107.5f, -28.0f, 0.2f), -90.0f, 11));
	routes[129].addSection(new TrafficLight(glm::vec3(107.5f, -17.0f, 0.2f), -90, 1.0f, 42, &trafficLights)); // V5-1
	routes[129].addSection(new Straight(glm::vec3(107.5f, -16.0f, 0.2f), -90.0f, 24));
	routes[129].addSection(new TrafficLight(glm::vec3(107.5f, 8.0f, 0.2f), -90, 1.0f, 44, &trafficLights)); // V5-3
	routes[129].addSection(new Straight(glm::vec3(107.5f, 9.0f, 0.2f), -90.0f, 19));
	routes[129].addSection(new Transition(&routes[175], &routes[176]));


	// exit routes
	routes[130].addSection(new Straight(glm::vec3(-108.0f, -34.5f, 0.2f), 0.0f, 42.0f));
	routes[130].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[131].addSection(new Straight(glm::vec3(-108.0f, 35.5f, 0.2f), 0.0f, 42.0f));
	routes[131].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[132].addSection(new Straight(glm::vec3(-106.5f, 36.0f, 0.2f), -90.0f, 44.0f));
	routes[132].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[133].addSection(new Straight(glm::vec3(66.0f, 36.0f, 0.2f), -90.0f, 44.0f));
	routes[133].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[134].addSection(new Straight(glm::vec3(108.0f, 34.5f, 0.2f), -180.0f, 42.0f));
	routes[134].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[135].addSection(new Straight(glm::vec3(108.0f, -35.5f, 0.2f), -180.0f, 42.0f));
	routes[135].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));

	routes[136].addSection(new Straight(glm::vec3(106.5f, -36.0f, 0.2f), 90.0f, 44.0f));
	routes[136].addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));


	// transition routes
	routes[137].addSection(new Straight(glm::vec3(-108.0f, -35.5f, 0.2f), -180.0f, 8.0));
	routes[137].addSection(new Transition(&routes[121]));
	routes[138].addSection(new Corner(glm::vec3(-108.0f, -35.5f, 0.2f), -180.0f, 1.5f, 90));
	routes[138].addSection(new Straight(glm::vec3(-106.5f, -34.0f, 0.2f), -90.0f, 6.0f));
	routes[138].addSection(new Transition(&routes[122]));

	routes[139].addSection(new Corner(glm::vec3(-108.0f, 34.5f, 0.2f), -180.0f, 0.5, -90.0f));
	routes[139].addSection(new Straight(glm::vec3(-107.5f, 34.0f, 0.2f), 90.0f, 6.0));
	routes[139].addSection(new Transition(&routes[123]));
	routes[140].addSection(new Straight(glm::vec3(-108.0f, 34.5f, 0.2f), -180.0f, 8.0));
	routes[140].addSection(new Transition(&routes[126]));
	routes[141].addSection(new Corner(glm::vec3(-108.0f, 34.5f, 0.2f), -180.0f, 1.5f, 90));
	routes[141].addSection(new Transition(&routes[132]));

	routes[142].addSection(new Corner(glm::vec3(-107.5, 36.0f, 0.2f), 90.0f, 0.5f, -90.0f));
	routes[142].addSection(new Transition(&routes[131]));
	routes[143].addSection(new Straight(glm::vec3(-107.5, 36.0f, 0.2f), 90.0f, 8.0f));
	routes[143].addSection(new Transition(&routes[123]));
	routes[144].addSection(new Corner(glm::vec3(-107.5, 36.0f, 0.2f), 90.0f, 1.5f, 90.0f));
	routes[144].addSection(new Straight(glm::vec3(-106.0, 34.5f, 0.2f), -180.0f, 6.0f));
	routes[144].addSection(new Transition(&routes[126]));

	routes[145].addSection(new Corner(glm::vec3(65.0f, 36.0f, 0.2f), 90.0f, 0.5f, -90.0f));
	routes[145].addSection(new Transition(&routes[125]));
	routes[146].addSection(new Corner(glm::vec3(65.0f, 36.0f, 0.2f), 90.0f, 1.5f, 90.0f));
	routes[146].addSection(new Transition(&routes[127]));

	routes[147].addSection(new Straight(glm::vec3(108.0f, 35.5f, 0.2f), 0.0f, 8.0f));
	routes[147].addSection(new Transition(&routes[124]));
	routes[148].addSection(new Corner(glm::vec3(108.0f, 35.5f, 0.2f), 0.0f, 1.5f, 90.0f));
	routes[148].addSection(new Straight(glm::vec3(106.5f, 34.0f, 0.2f), 90.0f, 6.0f));
	routes[148].addSection(new Transition(&routes[128]));

	routes[149].addSection(new Corner(glm::vec3(108.0f, -34.5f, 0.2f), 0.0f, 0.5, -90.0f));
	routes[149].addSection(new Straight(glm::vec3(107.5f, -34.0f, 0.2f), -90.0f, 6.0));
	routes[149].addSection(new Transition(&routes[129]));
	routes[150].addSection(new Straight(glm::vec3(108.0f, -34.5f, 0.2f), 0.0f, 8.0));
	routes[150].addSection(new Transition(&routes[120]));
	routes[151].addSection(new Corner(glm::vec3(108.0f, -34.5f, 0.2f), 0.0f, 1.5f, 90));
	routes[151].addSection(new Transition(&routes[136]));

	routes[152].addSection(new Corner(glm::vec3(107.5, -36.0f, 0.2f), -90.0f, 0.5f, -90.0f));
	routes[152].addSection(new Transition(&routes[135]));
	routes[153].addSection(new Straight(glm::vec3(107.5, -36.0f, 0.2f), -90.0f, 8.0f));
	routes[153].addSection(new Transition(&routes[129]));
	routes[154].addSection(new Corner(glm::vec3(107.5, -36.0f, 0.2f), -90.0f, 1.5f, 90.0f));
	routes[154].addSection(new Straight(glm::vec3(106.0, -34.5f, 0.2f), 0.0f, 6.0f));
	routes[154].addSection(new Transition(&routes[120]));

	routes[155].addSection(new Straight(glm::vec3(-100.0f, -34.5f, 0.2f), 0.0f, 6.0f));
	routes[155].addSection(new Corner(glm::vec3(-106.0f, -34.5f, 0.0f), 0.0f, 0.5f, -90.0f));
	routes[155].addSection(new Straight(glm::vec3(-106.5f, -34.0f, 0.0f), -90.0f, 6.6f));
	routes[155].addSection(new Transition(&routes[122]));
	routes[156].addSection(new Straight(glm::vec3(-100.0f, -34.5f, 0.2f), 0.0f, 8.0f));
	routes[156].addSection(new Transition(&routes[130]));

	routes[157].addSection(new Straight(glm::vec3(100.0f, -35.5, 0.2f), -180.0f, 6.0f));
	routes[157].addSection(new Corner(glm::vec3(106.0f, -35.5, 0.2f), -180.0f, 0.5f, -90.0f));
	routes[157].addSection(new Transition(&routes[136]));
	routes[158].addSection(new Straight(glm::vec3(100.0f, -35.5, 0.2f), -180.0f, 8.0f));
	routes[158].addSection(new Transition(&routes[135]));
	routes[159].addSection(new Straight(glm::vec3(100.0f, -35.5, 0.2f), -180.0f, 6.0f));
	routes[159].addSection(new Corner(glm::vec3(106.0f, -35.5, 0.2f), -180.0f, 1.5f, 90.0f));
	routes[159].addSection(new Transition(&routes[129]));

	routes[160].addSection(new Straight(glm::vec3(-106.5f, 28.0f, 0.2f), -90.0f, 6.0f));
	routes[160].addSection(new Corner(glm::vec3(-106.5f, 34.0f, 0.2f), -90.0f, 0.5f, -90.0));
	routes[160].addSection(new Straight(glm::vec3(-106.0f, 34.5f, 0.2f), -180.0f, 6.0f));
	routes[160].addSection(new Transition(&routes[126]));
	routes[161].addSection(new Straight(glm::vec3(-106.5f, 28.0f, 0.2f), -90.0f, 8.0f));
	routes[161].addSection(new Transition(&routes[132]));
	routes[162].addSection(new Straight(glm::vec3(-106.5f, 28.0f, 0.2f), -90.0f, 6.0f));
	routes[162].addSection(new Corner(glm::vec3(-106.5f, 34.0f, 0.2f), -90.0f, 1.5f, 90.0));
	routes[162].addSection(new Transition(&routes[131]));

	routes[163].addSection(new Straight(glm::vec3(-107.5f, -28.0f, 0.2f), 90.0f, 6.0f));
	routes[163].addSection(new Corner(glm::vec3(-107.5f, -34.0f, 0.2f), 90.0f, 0.5f, -90.0));
	routes[163].addSection(new Transition(&routes[130]));
	routes[164].addSection(new Straight(glm::vec3(-107.5f, -28.0f, 0.2f), 90.0f, 6.0f));
	routes[164].addSection(new Corner(glm::vec3(-107.5f, -34.0f, 0.2f), 90.0f, 1.5f, 90.0));
	routes[164].addSection(new Straight(glm::vec3(-106.0f, -35.5f, 0.2f), -180.0f, 6.0f));
	routes[164].addSection(new Transition(&routes[121]));

	routes[165].addSection(new Corner(glm::vec3(66.5f, 35.5f, 0.2f), 0.0f, 0.5f, -90.0f));
	routes[165].addSection(new Transition(&routes[133]));

	routes[166].addSection(new Straight(glm::vec3(-100.0f, 35.5f, 0.2f), 0.0f, 6.0f));
	routes[166].addSection(new Corner(glm::vec3(-106.0f, 35.5f, 0.2f), 0.0f, 0.5f, -90.0f));
	routes[166].addSection(new Transition(&routes[132]));
	routes[167].addSection(new Straight(glm::vec3(-100.0f, 35.5f, 0.2f), 0.0f, 8.0f));
	routes[167].addSection(new Transition(&routes[131]));
	routes[168].addSection(new Straight(glm::vec3(-100.0f, 35.5f, 0.2f), 0.0f, 6.0f));
	routes[168].addSection(new Corner(glm::vec3(-106.0f, 35.5f, 0.2f), 0.0f, 1.5f, 90.0f));
	routes[168].addSection(new Straight(glm::vec3(-107.8f, 34.0f, 0.2f), 90.0f, 6.0f));
	routes[168].addSection(new Transition(&routes[123]));

	routes[169].addSection(new Corner(glm::vec3(64.5f, 34.5, 0.2f), -180.0f, 1.5f, 90.0f));
	routes[169].addSection(new Transition(&routes[133]));

	routes[170].addSection(new Straight(glm::vec3(100.0f, 34.5f, 0.2f), -180.0f, 6.0f));
	routes[170].addSection(new Corner(glm::vec3(106.0f, 34.5f, 0.2f), -180.0f, 0.5f, -90.0f));
	routes[170].addSection(new Straight(glm::vec3(106.5f, 34.0f, 0.2f), 90.0f, 6.0f));
	routes[170].addSection(new Transition(&routes[128]));
	routes[171].addSection(new Straight(glm::vec3(100.0f, 34.5f, 0.2f), -180.0f, 8.0f));
	routes[171].addSection(new Transition(&routes[134]));

	routes[172].addSection(new Straight(glm::vec3(106.5f, -28.0f, 0.2f), 90.0f, 6.0f));
	routes[172].addSection(new Corner(glm::vec3(106.5f, -34.0f, 0.2f), 90.0f, 0.5f, -90.0f));
	routes[172].addSection(new Straight(glm::vec3(106.0f, -34.5f, 0.2f), 0.0f, 6.0f));
	routes[172].addSection(new Transition(&routes[120]));
	routes[173].addSection(new Straight(glm::vec3(106.5f, -28.0f, 0.2f), 90.0f, 8.0f));
	routes[173].addSection(new Transition(&routes[136]));
	routes[174].addSection(new Straight(glm::vec3(106.5f, -28.0f, 0.2f), 90.0f, 6.0f));
	routes[174].addSection(new Corner(glm::vec3(106.5f, -34.0f, 0.2f), 90.0f, 1.5f, 90.0f));
	routes[174].addSection(new Transition(&routes[135]));

	routes[175].addSection(new Straight(glm::vec3(107.5f, 28.0f, 0.2f), -90.0f, 6.0f));
	routes[175].addSection(new Corner(glm::vec3(107.5f, 34.0f, 0.2f), -90.0f, 0.5f, -90.0f));
	routes[175].addSection(new Transition(&routes[134]));
	routes[176].addSection(new Straight(glm::vec3(107.5f, 28.0f, 0.2f), -90.0f, 6.0f));
	routes[176].addSection(new Corner(glm::vec3(107.5f, 34.0f, 0.2f), -90.0f, 1.5f, 90.0f));
	routes[176].addSection(new Straight(glm::vec3(106.0f, 35.5f, 0.2f), 0.0f, 6.0f));
	routes[176].addSection(new Transition(&routes[124]));
}

void Simulation::initTraffic()
{
	int totalModelCount = 0;
	for (auto mi : *modelInfo) {
		for (uint32_t i = totalModelCount; i < mi.modelCount + totalModelCount; i++)
		{
			models.push_back(new Vehicle(i, mi.type, mi.modelSpeed, mi.collisionRadius));
		}
		totalModelCount += mi.modelCount;
	}
}

void Simulation::spawn(int vehicleID)
{
	int type = models.at(vehicleID)->getType();
	int size = spawnRoutes[type].size();
	routes[spawnRoutes[type][random(0, size)]].addModel(vehicleID);
}

int Simulation::random(float first, float last)
{
	std::uniform_real_distribution<float> distribution(first, last);
	std::random_device rd;
	std::default_random_engine generator(rd());
	return distribution(generator);
}