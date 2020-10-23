#include "Socket.hpp"

void Socket::Connect()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << WSAGetLastError() << std::endl;
		std::cout << "WSAStartup failed" << std::endl;
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
		WSACleanup();
	}

	connection = connect(client, (struct sockaddr*)&server, sizeof(server));

    if (connection == SOCKET_ERROR)
    {
		std::cout << WSAGetLastError() << std::endl;
		std::cout << "Connection Failed" << std::endl;
		Close();
    }

    char valread = recv(client, buffer, 1023, 0);
    printf("%s\n", buffer);
}

void Socket::Close()
{
	closesocket(client);
	WSACleanup();
}
