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
		"A1-1", "A1-2", "A1-3",	"B1-1",	"B1-2",	"F1-1",	"F1-2",	"V1-1",	"V1-2",	"V1-3",	"V1-4", // 0  - 10 (11)
		"A2-1",	"A2-2",	"A2-3",	"A2-4",	"F2-1",	"F2-2",	"V2-1",	"V2-2",	"V2-3",	"V2-4",			// 11 - 20 (10)
		"A3-1",	"A3-2",	"A3-3",	"A3-4",															// 21 - 24 ( 4)
		"A4-1",	"A4-2",	"A4-3",	"A4-4",	"B4-1",	"F4-1",	"F4-2",	"V4-1",	"V4-2",	"V4-3",	"V4-4",	// 25 - 35 (11)
		"A5-1",	"A5-2",	"A5-3",	"A5-4",	"F5-1",	"F5-2",	"V5-1",	"V5-2",	"V5-3",	"V5-4",			// 36 - 45 (10)
		"A6-1",	"A6-2",	"A6-3",	"A6-4"															// 46 - 49 ( 4)
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
	// routeIn 0-16, routeOut 17-24, routeCon 25-32, transitions 33-48

	// starting routes
	Route routeIn0(0, &models);
	routeIn0.addSection(new Straight(glm::vec3(-71.75f, -80.0f, 0.0f), -90.0f, 48.0f));
	routeIn0.addSection(new TrafficLight(glm::vec3(-71.75f, -32.0f, 0.0f), -90, 2.0f, 0, &trafficLights)); // A1-1
	// trans
	routes.push_back(routeIn0);

	Route routeIn1(1, &models);
	routeIn1.addSection(new Straight(glm::vec3(-75.25f, -80.0f, 0.0f), -90.0f, 48.0f));
	routeIn1.addSection(new TrafficLight(glm::vec3(-75.25f, -32.0f, 0.0f), -90, 2.0f, 1, &trafficLights)); // A1-2
	// trans
	routes.push_back(routeIn1);

	Route routeIn2(2, &models);
	routeIn2.addSection(new Straight(glm::vec3(-78.75f, -80.0f, 0.0f), -90.0f, 48.0f));
	routeIn2.addSection(new TrafficLight(glm::vec3(-78.75f, -32.0f, 0.0f), -90, 2.0f, 2, &trafficLights)); // A1-3
	routeIn2.addSection(new Straight(glm::vec3(-78.75f, -30.0f, 0.0f), -90, 21.0f));
	routeIn2.addSection(new Corner(glm::vec3(-78.75f, -9.0f, 0.0f), -90, 23.25f, 90));
	//trans
	routes.push_back(routeIn2);

	Route routeIn3(3, &models);
	routeIn3.addSection(new Straight(glm::vec3(-82.25f, -80.0f, 0.0f), -90.0f, 48.0f));
	routeIn3.addSection(new TrafficLight(glm::vec3(-82.25f, -32.0f, 0.0f), -90, 2.0f, 3, &trafficLights)); // B1-1
	routeIn3.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeIn3);

	Route routeIn4(4, &models);
	routeIn4.addSection(new Straight(glm::vec3(-150.0f, -21.25f, 0.0f), -180, 46.0f));
	routeIn4.addSection(new TrafficLight(glm::vec3(-104.0f, -21.25f, 0.0f), -180, 2.0f, 11, &trafficLights)); // A2-1
	routeIn4.addSection(new Corner(glm::vec3(-102.0f, -21.25f, 0.0f), -180, 8.75f, -90));
	routes.push_back(routeIn4);

	Route routeIn5(5, &models);
	routeIn5.addSection(new Straight(glm::vec3(-150.0f, -17.75f, 0.0f), -180, 46.0f));
	routeIn5.addSection(new TrafficLight(glm::vec3(-104.0f, -17.75f, 0.0f), -180, 2.0f, 12, &trafficLights)); // A2-2
	routeIn5.addSection(new Corner(glm::vec3(-102.0f, -17.75f, 0.0f), -180, 12.25f, -90));
	routes.push_back(routeIn5);

	Route routeIn6(6, &models);
	routeIn6.addSection(new Straight(glm::vec3(-150.0f, -14.25f, 0.0f), -180, 46.0f));
	routeIn6.addSection(new TrafficLight(glm::vec3(-104.0f, -14.25f, 0.0f), -180, 2.0f, 13, &trafficLights)); // A2-3
	routeIn6.addSection(new Straight(glm::vec3(-102.0f, -14.25f, 0.0f), -180, 14.0f));
	routes.push_back(routeIn6);

	Route routeIn7(7, &models);
	routeIn7.addSection(new Straight(glm::vec3(-150.0f, -10.75f, 0.0f), -180, 46.0f));
	routeIn7.addSection(new TrafficLight(glm::vec3(-104.0f, -10.75f, 0.0f), -180, 2.0f, 14, &trafficLights)); // A2-4
	routeIn7.addSection(new Straight(glm::vec3(-102.0f, -10.75f, 0.0f), -180, 14.0f));
	routes.push_back(routeIn7);

	Route routeIn8(8, &models);
	routeIn8.addSection(new Straight(glm::vec3(82.25f, 80.0f, 0.0f), 90.0f, 48.0f));
	routeIn8.addSection(new TrafficLight(glm::vec3(82.25f, 32.0f, 0.0f), 90, 2.0f, 25, &trafficLights)); // A4-1
	routeIn8.addSection(new Straight(glm::vec3(82.25f, 30.0f, 0.0f), 90, 21.0f));
	routeIn8.addSection(new Corner(glm::vec3(82.25f, 9.0f, 0.0f), 90, 19.75f, 90));
	routes.push_back(routeIn8);

	Route routeIn9(9, &models);
	routeIn9.addSection(new Straight(glm::vec3(78.75f, 80.0f, 0.0f), 90.0f, 48.0f));
	routeIn9.addSection(new TrafficLight(glm::vec3(78.75f, 32.0f, 0.0f), 90, 2.0f, 26, &trafficLights)); // A4-2
	routeIn9.addSection(new Straight(glm::vec3(78.75f, 30.0f, 0.0f), 90, 21.0f));
	routeIn9.addSection(new Corner(glm::vec3(78.75f, 9.0f, 0.0f), 90, 23.25f, 90));
	routes.push_back(routeIn9);

	Route routeIn10(10, &models);
	routeIn10.addSection(new Straight(glm::vec3(75.25f, 80.0f, 0.0f), 90.0f, 48.0f));
	routeIn10.addSection(new TrafficLight(glm::vec3(75.25f, 32.0f, 0.0f), 90, 2.0f, 27, &trafficLights)); // A4-3
	routes.push_back(routeIn10);

	Route routeIn11(11, &models);
	routeIn11.addSection(new Straight(glm::vec3(71.75f, 80.0f, 0.0f), 90.0f, 48.0f));
	routeIn11.addSection(new TrafficLight(glm::vec3(71.75f, 32.0f, 0.0f), 90, 2.0f, 28, &trafficLights)); // A4-4
	routes.push_back(routeIn11);

	Route routeIn12(12, &models);
	routeIn12.addSection(new Straight(glm::vec3(68.25f, 80.0f, 0.0f), 90.0f, 48.0f));
	routeIn12.addSection(new TrafficLight(glm::vec3(68.25f, 32.0f, 0.0f), 90, 2.0f, 29, &trafficLights)); // B4-1
	routeIn12.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeIn12);

	Route routeIn13(13, &models);
	routeIn13.addSection(new Straight(glm::vec3(150.0f, 10.75f, 0.0f), 0, 46.0f));
	routeIn13.addSection(new TrafficLight(glm::vec3(104.0f, 10.75f, 0.0f), 0, 2.0f, 36, &trafficLights)); // A5-1
	routeIn13.addSection(new Straight(glm::vec3(102.0f, 10.75f, 0.0f), 0, 14.0f));
	routes.push_back(routeIn13);

	Route routeIn14(14, &models);
	routeIn14.addSection(new Straight(glm::vec3(150.0f, 14.25f, 0.0f), 0, 46.0f));
	routeIn14.addSection(new TrafficLight(glm::vec3(104.0f, 14.25f, 0.0f), 0, 2.0f, 37, &trafficLights)); // A5-2
	routeIn14.addSection(new Straight(glm::vec3(102.0f, 14.25f, 0.0f), 0, 14.0f));
	routes.push_back(routeIn14);

	Route routeIn15(15, &models);
	routeIn15.addSection(new Straight(glm::vec3(150.0f, 17.75f, 0.0f), 0, 46.0f));
	routeIn15.addSection(new TrafficLight(glm::vec3(104.0f, 17.75f, 0.0f), 0, 2.0f, 38, &trafficLights)); // A5-3
	routeIn15.addSection(new Corner(glm::vec3(102.0f, 17.75f, 0.0f), 0, 12.25f, -90));
	routes.push_back(routeIn15);

	Route routeIn16(16, &models);
	routeIn16.addSection(new Straight(glm::vec3(150.0f, 21.25f, 0.0f), 0, 46.0f));
	routeIn16.addSection(new TrafficLight(glm::vec3(104.0f, 21.25f, 0.0f), 0, 2.0f, 39, &trafficLights)); // A5-4
	routeIn16.addSection(new Corner(glm::vec3(102.0f, 21.25f, 0.0f), 0, 8.75f, -90));
	routes.push_back(routeIn16);

	// connection routes
	Route routeCon17(17, &models);
	routeCon17.addSection(new Straight(glm::vec3(-60.0f, -14.25f, 0.0f), -180, 135.0f));
	routeCon17.addSection(new TrafficLight(glm::vec3(75.0f, -14.25f, 0.0f), -180, 2.0f, 46, &trafficLights)); // A6-1
	routeCon17.addSection(new Straight(glm::vec3(77.0f, -14.25f, 0.0f), -180, 25.0f));
	// trans
	routes.push_back(routeCon17);

	Route routeCon18(18, &models);
	routeCon18.addSection(new Straight(glm::vec3(-60.0f, -10.75f, 0.0f), -180, 135.0f));
	routeCon18.addSection(new TrafficLight(glm::vec3(75.0f, -10.75f, 0.0f), -180, 2.0f, 47, &trafficLights)); // A6-2
	routeCon18.addSection(new Straight(glm::vec3(77.0f, -10.75f, 0.0f), -180, 25.0f));
	// trans
	routes.push_back(routeCon18);

	Route routeCon19(19, &models);
	routeCon19.addSection(new Straight(glm::vec3(-60.0f, -7.25f, 0.0f), -180, 135.0f));
	routeCon19.addSection(new TrafficLight(glm::vec3(75.0f, -7.25f, 0.0f), -180, 2.0f, 48, &trafficLights)); // A6-3
	routeCon19.addSection(new Corner(glm::vec3(77.0f, -7.25f, 0.0f), -180, 16.25f, 90.0f));
	routeCon19.addSection(new Straight(glm::vec3(93.25f, 9.0f, 0.0f), -90, 21.0f));
	// trans
	routes.push_back(routeCon19);

	Route routeCon20(20, &models);
	routeCon20.addSection(new Straight(glm::vec3(-60.0f, -3.75f, 0.0f), -180, 135.0f));
	routeCon20.addSection(new TrafficLight(glm::vec3(75.0f, -3.75f, 0.0f), -180, 2.0f, 49, &trafficLights)); // A6-4
	routeCon20.addSection(new Corner(glm::vec3(77.0f, -3.75f, 0.0f), -180, 12.75f, 90.0f));
	routeCon20.addSection(new Straight(glm::vec3(89.75f, 9.0f, 0.0f), -90, 21.0f));
	// trans
	routes.push_back(routeCon20);

	Route routeCon21(21, &models);
	routeCon21.addSection(new Straight(glm::vec3(60.0f, 3.75f, 0.0f), 0, 135.0f));
	routeCon21.addSection(new TrafficLight(glm::vec3(-75.0f, 3.75f, 0.0f), 0, 2.0f, 21, &trafficLights)); // A3-1
	routeCon21.addSection(new Corner(glm::vec3(-77.0f, 3.75f, 0.0f), 0, 12.75f, 90.0f));
	routeCon21.addSection(new Straight(glm::vec3(-89.75f, -9.0f, 0.0f), 90, 21.0f));
	// trans
	routes.push_back(routeCon21);

	Route routeCon22(22, &models);
	routeCon22.addSection(new Straight(glm::vec3(60.0f, 7.25f, 0.0f), 0, 135.0f));
	routeCon22.addSection(new TrafficLight(glm::vec3(-75.0f, 7.25f, 0.0f), 0, 2.0f, 22, &trafficLights)); // A3-2
	routeCon22.addSection(new Corner(glm::vec3(-77.0f, 7.25f, 0.0f), 0, 16.25f, 90.0f));
	routeCon22.addSection(new Straight(glm::vec3(-93.25f, -9.0f, 0.0f), 90, 21.0f));
	// trans
	routes.push_back(routeCon22);

	Route routeCon23(23, &models);
	routeCon23.addSection(new Straight(glm::vec3(60.0f, 10.75f, 0.0f), 0, 135.0f));
	routeCon23.addSection(new TrafficLight(glm::vec3(-75.0f, 10.75f, 0.0f), 0, 2.0f, 23, &trafficLights)); // A3-3
	routeCon23.addSection(new Straight(glm::vec3(-77.0f, 10.75f, 0.0f), 0, 25.0f));
	// trans
	routes.push_back(routeCon23);

	Route routeCon24(24, &models);
	routeCon24.addSection(new Straight(glm::vec3(60.0f, 14.25f, 0.0f), 0, 135.0f));
	routeCon24.addSection(new TrafficLight(glm::vec3(-75.0f, 14.25f, 0.0f), 0, 2.0f, 24, &trafficLights)); // A3-4
	routeCon24.addSection(new Straight(glm::vec3(-77.0f, 14.25f, 0.0f), 0, 25.0f));
	// trans
	routes.push_back(routeCon24);


	// exit routes
	Route routeOut25(25, &models);
	routeOut25.addSection(new Straight(glm::vec3(-89.75f, -30.0f, 0.0f), 90, 50.0f));
	routeOut25.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeOut25);

	Route routeOut26(26, &models);
	routeOut26.addSection(new Straight(glm::vec3(-93.25f, -30.0f, 0.0f), 90, 50.0f));
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
	routeOut29.addSection(new Straight(glm::vec3(93.25f, 30.0f, 0.0f), -90, 50.0f));
	routeOut29.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeOut29);

	Route routeOut30(30, &models);
	routeOut30.addSection(new Straight(glm::vec3(89.75f, 30.0f, 0.0f), -90, 50.0f));
	routeOut30.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeOut30);

	Route routeOut31(31, &models);
	routeOut31.addSection(new Straight(glm::vec3(102.0f, -14.25, 0.0f), -180, 48.0f));
	routeOut31.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeOut31);

	Route routeOut32(32, &models);
	routeOut32.addSection(new Straight(glm::vec3(102.0f, -10.75, 0.0f), -180, 48.0f));
	routeOut32.addSection(new End(glm::vec3(0.0f, 0.0f, -10.0f), 0));
	routes.push_back(routeOut32);


	// transition routes
	Route routeTrans33(33, &models);
	routeTrans33.addSection(new Straight(glm::vec3(-71.75f, -30.0f, 0.0f), -90, 4.0f));
	routeTrans33.addSection(new Corner(glm::vec3(-71.75f, -26.0f, 0.0f), -90, 11.75f, -90.0f));
	routes.push_back(routeTrans33);

	Route routeTrans34(34, &models);
	routeTrans34.addSection(new Straight(glm::vec3(-71.75f, -30.0f, 0.0f), -90, 7.5f));
	routeTrans34.addSection(new Corner(glm::vec3(-71.75f, -22.5f, 0.0f), -90, 11.75f, -90.0f));
	routes.push_back(routeTrans34);

	Route routeTrans35(35, &models);
	routeTrans35.addSection(new Straight(glm::vec3(-75.25f, -30.0f, 0.0f), -90, 11.0f));
	routeTrans35.addSection(new Corner(glm::vec3(-75.25f, -19.0f, 0.0f), -90, 11.75f, -90.0f));
	routeTrans35.addSection(new Straight(glm::vec3(-63.5f, -7.25f, 0.0f), -180, 3.5f));
	routes.push_back(routeTrans35);

	Route routeTrans36(36, &models);
	routeTrans36.addSection(new Straight(glm::vec3(-75.25f, -30.0f, 0.0f), -90, 14.5f));
	routeTrans36.addSection(new Corner(glm::vec3(-75.25f, -15.5f, 0.0f), -90, 11.75f, -90.0f));
	routeTrans36.addSection(new Straight(glm::vec3(-63.5f, -3.75f, 0.0f), -180, 3.5f));
	routes.push_back(routeTrans36);

	Route routeTrans37(37, &models);
	routeTrans37.addSection(new Straight(glm::vec3(-88.0f, -14.25f, 0.0f), -180, 28.0f));
	routes.push_back(routeTrans37);

	Route routeTrans38(38, &models);
	routeTrans38.addSection(new Straight(glm::vec3(-88.0f, -14.25f, 0.0f), -172.875f, 28.2179f));
	routes.push_back(routeTrans38);

	Route routeTrans39(39, &models);
	routeTrans39.addSection(new Straight(glm::vec3(-88.0f, -10.75f, 0.0f), -172.875f, 27.2179f));
	routes.push_back(routeTrans39);

	Route routeTrans40(40, &models);
	routeTrans40.addSection(new Straight(glm::vec3(-88.0f, -10.75f, 0.0f), -165.9638f, 28.8617f));
	routes.push_back(routeTrans40);

	Route routeTrans41(41, &models);
	routeTrans41.addSection(new Straight(glm::vec3(75.25f, 30.0f, 0.0f), 90, 14.5f));
	routeTrans41.addSection(new Corner(glm::vec3(75.25f, 15.5f, 0.0f), 90, 11.75f, -90.0f));
	routeTrans41.addSection(new Straight(glm::vec3(63.5f, 3.75f, 0.0f), 0, 3.5f));
	routes.push_back(routeTrans41);

	Route routeTrans42(42, &models);
	routeTrans42.addSection(new Straight(glm::vec3(75.25f, 30.0f, 0.0f), 90, 11.0f));
	routeTrans42.addSection(new Corner(glm::vec3(75.25f, 19.0f, 0.0f), 90, 11.75f, -90.0f));
	routeTrans42.addSection(new Straight(glm::vec3(63.5f, 7.25f, 0.0f), 0, 3.5f));
	routes.push_back(routeTrans42);

	Route routeTrans43(43, &models);
	routeTrans43.addSection(new Straight(glm::vec3(71.75f, 30.0f, 0.0f), 90, 7.5f));
	routeTrans43.addSection(new Corner(glm::vec3(71.75f, 22.5f, 0.0f), 90, 11.75f, -90.0f));
	routes.push_back(routeTrans43);

	Route routeTrans44(44, &models);
	routeTrans44.addSection(new Straight(glm::vec3(71.75f, 30.0f, 0.0f), 90, 4.0f));
	routeTrans44.addSection(new Corner(glm::vec3(71.75f, 26.0f, 0.0f), 90, 11.75f, -90.0f));
	routes.push_back(routeTrans44);

	Route routeTrans45(45, &models);
	routeTrans45.addSection(new Straight(glm::vec3(88.0f, 10.75f, 0.0f), 14.0362f, 28.8617f));
	routes.push_back(routeTrans45);

	Route routeTrans46(46, &models);
	routeTrans46.addSection(new Straight(glm::vec3(88.0f, 10.75f, 0.0f), 7.1250f, 27.2179f));
	routes.push_back(routeTrans46);

	Route routeTrans47(47, &models);
	routeTrans47.addSection(new Straight(glm::vec3(88.0f, 14.25f, 0.0f), 7.1250f, 28.2179f));
	routes.push_back(routeTrans47);

	Route routeTrans48(48, &models);
	routeTrans48.addSection(new Straight(glm::vec3(88.0f, 14.25f, 0.0f), 0, 28.0f));
	routes.push_back(routeTrans48);


	// transitions
	routes[0].addSection(new Transition(&routes[33], &routes[34]));
	routes[1].addSection(new Transition(&routes[35], &routes[36]));
	routes[2].addSection(new Transition(&routes[28]));
	routes[4].addSection(new Transition(&routes[26]));
	routes[5].addSection(new Transition(&routes[25]));
	routes[6].addSection(new Transition(&routes[37], &routes[38]));
	routes[7].addSection(new Transition(&routes[39], &routes[40]));
	routes[8].addSection(new Transition(&routes[32]));
	routes[9].addSection(new Transition(&routes[31]));
	routes[10].addSection(new Transition(&routes[41], &routes[42]));
	routes[11].addSection(new Transition(&routes[43], &routes[44]));
	routes[13].addSection(new Transition(&routes[45], &routes[46]));
	routes[14].addSection(new Transition(&routes[47], &routes[48]));
	routes[15].addSection(new Transition(&routes[30]));
	routes[16].addSection(new Transition(&routes[29]));
	routes[17].addSection(new Transition(&routes[31]));
	routes[18].addSection(new Transition(&routes[32]));
	routes[19].addSection(new Transition(&routes[29]));
	routes[20].addSection(new Transition(&routes[30]));
	routes[21].addSection(new Transition(&routes[25]));
	routes[22].addSection(new Transition(&routes[26]));
	routes[23].addSection(new Transition(&routes[27]));
	routes[24].addSection(new Transition(&routes[28]));

	routes[33].addSection(new Transition(&routes[17]));
	routes[34].addSection(new Transition(&routes[18]));
	routes[35].addSection(new Transition(&routes[19]));
	routes[36].addSection(new Transition(&routes[20]));
	routes[37].addSection(new Transition(&routes[17]));
	routes[38].addSection(new Transition(&routes[18]));
	routes[39].addSection(new Transition(&routes[19]));
	routes[40].addSection(new Transition(&routes[20]));
	routes[41].addSection(new Transition(&routes[21]));
	routes[42].addSection(new Transition(&routes[22]));
	routes[43].addSection(new Transition(&routes[23]));
	routes[44].addSection(new Transition(&routes[24]));
	routes[45].addSection(new Transition(&routes[21]));
	routes[46].addSection(new Transition(&routes[22]));
	routes[47].addSection(new Transition(&routes[23]));
	routes[48].addSection(new Transition(&routes[24]));


	// test vehicles
	for (size_t i = 0; i < 17; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			routes[i].addModel(j + (i * 8));
		}
	}
}