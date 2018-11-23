#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Item.h"

#pragma comment (lib, "ws2_32.lib")

using namespace std;

vector<Item> loadStoreData()
{
	vector<Item> itemList;
	ifstream file("input.txt");
	if (file.is_open())
	{
		string line;    //line from file
		string word;    //word from line
		string subLine;    //subtr of line
		string anItem[3];
		string itemDesc;
		int itemUnits, itemPrice;
		while (getline(file, line)) {
			subLine = line.substr(0, 4);
			if (subLine == "Item") {    //if the word is Item_
				int itemIndex = 0;
				istringstream iss(line);
				while (iss >> word) {
					anItem[itemIndex] = word;
					itemIndex++;
				}
				itemDesc = anItem[0];
				itemUnits = atoi(anItem[1].c_str());
				itemPrice = atoi(anItem[2].c_str());
				Item newItem = Item(itemDesc, itemUnits, itemPrice);
				itemList.push_back(newItem);
			}
		}

		file.close();
		return itemList;
	}
	else
	{
		cout << "Unable to open file";
		exit;
	}
}

void main()
{
	// start winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOK = WSAStartup(version, &data);
	if (wsOK != 0)
	{
		cout << "Can't start Winsock!" << wsOK << endl;
	}
	//bind socket to ip address and port
	SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);

	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(54000); // convert from little to big endian

	if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
	{
		cout << "Can't bind socket!" << WSAGetLastError() << endl;
		return;
	}

	sockaddr_in client;
	int clientLength = sizeof(client);
	ZeroMemory(&client, clientLength);

	char buf[1024];

	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

	//test sending parts of an item
	vector<Item> items = loadStoreData();
	vector<string> s;
	for ( int i = 0;  i < items.size(); i++)
	{
		s.push_back(items[i].getDescription() + " " + to_string(items[i].getUnits()) + " " + to_string(items[i].getPrice()));
	}

	//enter a loop
	while (true)
	{
		ZeroMemory(buf, 1024);
		// wait for message
		int bytesIn = recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength);
		if (bytesIn == SOCKET_ERROR)
		{
			cout << "ERROR receiving from Client" << WSAGetLastError() << endl;
			continue;
		}
		else
		{
			for (int i =0; i <items.size(); i++)
			{
				int sendOK = sendto(out, s[i].c_str(), s[i].size() + 1, 0, (sockaddr*)&client, sizeof(client));
				if (sendOK == SOCKET_ERROR)
				{
					cout << "didnt work" << WSAGetLastError() << endl;
				}
			}
		}
		// display response 
		char clientIp[256];
		ZeroMemory(clientIp, 256);

		inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

		cout << "Message recv from " << clientIp << " : " << buf << endl;
	}

	//close socket
	closesocket(in);

	//shutdown winsock
	WSACleanup();
}