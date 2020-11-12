#pragma comment(lib, "Ws2_32.lib")

#include "document.h"
#include "Simulation.hpp"

#include <iostream>
#include <vector>
#include <winsock2.h>
#include <Ws2tcpip.h>

class Socket 
{
public:
	Socket(std::shared_ptr<Simulation> ptr_s) : ptr_simulation(move(ptr_s)) {};
	bool Connect();
	void Receiving();
	std::vector<bool> getTrafficLights();
	void Close();

private:
	std::shared_ptr<Simulation> ptr_simulation;
	WSADATA wsaData;
	SOCKET client = INVALID_SOCKET;
	int connection, received;
	bool isRunning = true;
	const int port = 54000;
	const PCSTR host = "127.0.0.1";
	struct sockaddr_in server;
	char buffer[1024] = { 0 };
	std::vector<std::string> trafficLightNames = {
		"A1-1",
		"A1-2",
		"A1-3",
		"B1-1",
		"B1-2",
		"F1-1",
		"F1-2",
		"V1-1",
		"V1-2",
		"V1-3",
		"V1-4",
		"A2-1",
		"A2-2",
		"A2-3",
		"A2-4",
		"F2-1",
		"F2-2",
		"V2-1",
		"V2-2",
		"V2-3",
		"V2-4",
		"A3-1",
		"A3-2",
		"A3-3",
		"A3-4",
		"A4-1",
		"A4-2",
		"A4-3",
		"A4-4",
		"B4-1",
		"F4-1",
		"F4-2",
		"V4-1",
		"V4-2",
		"V4-3",
		"V4-4",
		"A5-1",
		"A5-2",
		"A5-3",
		"A5-4",
		"F5-1",
		"F5-2",
		"V5-1",
		"V5-2",
		"V5-3",
		"V5-4",
		"A6-1",
		"A6-2",
		"A6-3",
		"A6-4"
	};
};