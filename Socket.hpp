#pragma comment(lib, "Ws2_32.lib")

#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "Simulation.hpp"

#include <iostream>
#include <chrono>
#include <vector>
#include <winsock2.h>
#include <Ws2tcpip.h>

class Socket 
{
public:
	Socket(std::shared_ptr<Simulation> ptr_s) : ptr_simulation(move(ptr_s)) {};
	bool connecting();
	void sending();
	void receiving();
	std::string getTraffic();
	void updateTrafficLights();
	void close();

private:
	std::shared_ptr<Simulation> ptr_simulation;
	WSADATA wsaData;
	SOCKET client = INVALID_SOCKET;
	int connection, received, forward;
	bool isRunning = true;
	const int port = 54000;
	const PCSTR host = "127.0.0.1";
	struct sockaddr_in server;
	char reciveBuffer[1024] = { 0 };
	char tempBuffer[1024] = { 0 };
	char* sendBuffer;
};