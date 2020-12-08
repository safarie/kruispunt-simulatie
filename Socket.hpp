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
	/// <summary>
	/// contructor
	/// </summary>
	/// <param name="ptr_s">ptr to simuliation</param>
	Socket(std::shared_ptr<Simulation> ptr_s) : ptr_simulation(move(ptr_s)) {};

	/// <summary>
	/// Set up connection with a controller
	/// </summary>
	/// <returns>ture when succeeded</returns>
	bool connecting();

	/// <summary>
	/// this function is running on a seperate thread sending back traffic position every 5 seconds
	/// </summary>
	void sending();

	/// <summary>
	/// on a seperate thread listen for incomming trafficlight updates
	/// </summary>
	void receiving();

	/// <summary>
	/// goes through the list of trafficlights and checks if theres traffic waiting
	/// </summary>
	/// <returns>json string with waiting traffic</returns>
	std::string getTraffic();

	/// <summary>
	/// goes throeg the list with trafficlights and updates the light states based on the received data
	/// </summary>
	void updateTrafficLights();

	/// <summary>
	/// closes the socket connection
	/// </summary>
	void close();

private:
	std::shared_ptr<Simulation> ptr_simulation;
	WSADATA wsaData;
	SOCKET client = INVALID_SOCKET;
	int connection, received, forward;
	bool isRunning = true;
	bool dataReceived = false;
	const int port = 54000;
	const PCSTR host = "127.0.0.1";
	struct sockaddr_in server;
	char receiveBuffer[1024] = { 0 };
	char tempBuffer[1024] = { 0 };
	char* sendBuffer;
};