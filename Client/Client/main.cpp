#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main(int argc, char* argv[])
{
	// start winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOK = WSAStartup(version, &data);
	if (wsOK != 0)
	{
		cout << "Can't start Winsock!" << wsOK << endl;
	}

	// Create a hint structure for the server
	sockaddr_in server;
	int serverLength = sizeof(server);
	ZeroMemory(&server, serverLength);
	server.sin_family = AF_INET;
	server.sin_port = htons(54000);
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

	// Socket Creation
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

	// Write out to the socket
	string s(argv[1]);
	int sendOK = sendto(out, s.c_str(), s.size() +1, 0, (sockaddr*)&server, sizeof(server));

	char buf[1024];

	if (sendOK == SOCKET_ERROR)
	{
		cout << "didnt work" << WSAGetLastError() << endl;
	}

	while (true)
	{
		ZeroMemory(buf, 1024);
		// wait for message
		int bytesIn = recvfrom(out, buf, 1024, 0, (sockaddr*)&server, &serverLength);
		if (bytesIn == SOCKET_ERROR)
		{
			cout << "ERROR receiving from Server" << WSAGetLastError() << endl;
			continue;
		}
		char serverIp[256];
		ZeroMemory(serverIp, 256);
		inet_ntop(AF_INET, &server.sin_addr, serverIp, 256);

		cout << "Message recv from " << serverIp << " : " << buf << endl;
	}

	// Close the socket
	closesocket(out);

	//close Winsock
	WSACleanup();
}