#include "Socket.hpp"

bool Socket::Connect()
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
		Close();
		return false;
    }

	return true;
}

void Socket::Receiving()
{
	while (isRunning) 
	{
		received = recv(client, buffer, 1023, 0);

		if (received <= 0)
		{
			std::cout << WSAGetLastError() << std::endl;
			std::cout << "recv() failed or connection closed prematurely" << std::endl;
			closesocket(client);
			isRunning = false;
		}

		printf("%s\n", buffer);
		updateTrafficLights();
	};
}

void Socket::updateTrafficLights()
{
	std::copy(buffer + 4, buffer + (sizeof(buffer) / sizeof(buffer[0])), buffer + 0); //remove header

	rapidjson::Document doc;
	doc.Parse(buffer);

	for (size_t i = 0; i < ptr_simulation->trafficLights.size(); i++)
	{
		rapidjson::Value& light = doc[ptr_simulation->trafficLights[i].ID.c_str()];
		ptr_simulation->trafficLights[i].state = light.GetInt();
	}
}

void Socket::Close()
{
	isRunning = false;
	ptr_simulation.reset();
	closesocket(client);
	WSACleanup();
}
