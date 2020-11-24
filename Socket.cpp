#include "Socket.hpp"

bool Socket::connecting()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << WSAGetLastError() << std::endl;
		std::cout << "WSAStartup failed" << std::endl;
		isRunning = false;
		return false;
		WSACleanup();
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_pton(AF_INET, host, &server.sin_addr.s_addr);

	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (client == INVALID_SOCKET)
	{
		std::cout << WSAGetLastError() << std::endl;
		std::cout << "socket creation failed" << std::endl;
		isRunning = false;
		return false;
		WSACleanup();
	}

	connection = connect(client, (struct sockaddr*)&server, sizeof(server));

    if (connection == SOCKET_ERROR)
    {
		std::cout << WSAGetLastError() << std::endl;
		std::cout << "Connection Failed" << std::endl;
		close();
		return false;
    }

	isRunning = true;
	return true;
}

void Socket::sending()
{
	float previousTime = 0.0f;
	float interval = 0.0f;

	while (isRunning)
	{
		static auto startTime = std::chrono::high_resolution_clock::now();
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
		float delta = time - previousTime;
		previousTime = time;

		dataReceived ? interval += delta : interval = 0.0f;

		if (interval <= 5.0)
			continue;

		std::string temp = "451:";
		temp.append(getTraffic());
		sendBuffer = &temp[0];

		forward = send(client, sendBuffer, (int)strlen(sendBuffer), 0);

		if (forward == SOCKET_ERROR) {
			std::cout << WSAGetLastError() << std::endl;
			std::cout << "send() failed or connection closed prematurely" << std::endl;
			closesocket(client);
			isRunning = false;
		}

		printf("%s\n", "Traffic data send!");

		interval = 0.0f;
	}
}

void Socket::receiving()
{
	while (isRunning) 
	{
		received = recv(client, receiveBuffer, sizeof(receiveBuffer), 0);

		if (received <= 0)
		{
			std::cout << WSAGetLastError() << std::endl;
			std::cout << "recv() failed or connection closed prematurely" << std::endl;
			closesocket(client);
			isRunning = false;
		}

		printf("%s\n", receiveBuffer);
		dataReceived = true;
		updateTrafficLights();
	};
}

std::string Socket::getTraffic()
{
	rapidjson::Document doc;
	doc.Parse(tempBuffer);

	for (size_t i = 0; i < ptr_simulation->trafficLights.size(); i++)
	{
		rapidjson::Value& light = doc[ptr_simulation->trafficLights[i].ID.c_str()];
		light.SetInt(ptr_simulation->trafficLights[i].traffic);
	}

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	return buffer.GetString();
}

void Socket::updateTrafficLights()
{
	std::copy(receiveBuffer + 4, receiveBuffer + sizeof(receiveBuffer), receiveBuffer); //remove header
	std::copy(std::begin(receiveBuffer), std::end(receiveBuffer), tempBuffer); //copy buffer for sending back data

	rapidjson::Document doc;
	doc.Parse(receiveBuffer);

	for (size_t i = 0; i < ptr_simulation->trafficLights.size(); i++)
	{
		rapidjson::Value& light = doc[ptr_simulation->trafficLights[i].ID.c_str()];
		ptr_simulation->trafficLights[i].state = light.GetInt();
	}
}

void Socket::close()
{
	isRunning = false;
	ptr_simulation.reset();
	closesocket(client);
	WSACleanup();
}
