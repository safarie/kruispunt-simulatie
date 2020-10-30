#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>

class Socket 
{
public:
	void Connect();
	bool Reciving();
	void Close();

private:
	WSADATA wsaData;
	SOCKET client = INVALID_SOCKET;
	int connection, recieved;
	const int port = 54000;
	const PCSTR host = "127.0.0.1";
	struct sockaddr_in server;
	char buffer[1024] = { 0 };
};