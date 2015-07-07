#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <WinSock.h>

using namespace std;

SOCKET s; //Socket handle

//CONNECTTOHOST ¨C Connects to a remote host
bool ConnectToHostTCP(int PortNo, const char* IPAddress)
{
	//Start up Winsock¡­
	WSADATA wsadata;

	int error = WSAStartup(MAKEWORD(2, 2), &wsadata);

	//Did something happen?
	if (error)
		return false;
	//Did we get the right Winsock version?
	//if (wsadata.wVersion != 2)
	//{
	//	WSACleanup(); //Clean up Winsock
	//	return false;
	//}
	//Fill out the information needed to initialize a socket¡­
	SOCKADDR_IN target; //Socket address information

	target.sin_family = AF_INET; // address family Internet
	target.sin_port = htons(PortNo); //Port to connect on
	target.sin_addr.S_un.S_addr = inet_addr(IPAddress); //Target IP

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
	if (s == INVALID_SOCKET)
	{
		closesocket(s);
		WSACleanup();
		return false; //Couldn't create the socket
	}

	//Try connecting...

	if (connect(s, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
	{
		closesocket(s);
		WSACleanup();
		return false; //Couldn't connect
	}
	else {
		closesocket(s);
		WSACleanup();
		return true; //Success
	}
}

//Connecto To Host with UDP protocol
bool ConnectToHostUDP(int PortNo, const char* IPAddress)
{
	//Start up Winsock¡­
	WSADATA wsadata;

	int error = WSAStartup(MAKEWORD(2, 2), &wsadata);

	//Did something happen?
	if (error)
		return false;
	//Did we get the right Winsock version?
	//if (wsadata.wVersion != 2)
	//{
	//	WSACleanup(); //Clean up Winsock
	//	return false;
	//}
	//Fill out the information needed to initialize a socket¡­
	SOCKADDR_IN target; //Socket address information

	target.sin_family = AF_INET; // address family Internet
	target.sin_port = htons(PortNo); //Port to connect on
	target.sin_addr.S_un.S_addr = inet_addr(IPAddress); //Target IP

	s = socket(AF_INET, SOCK_DGRAM, 0); //Create socket
	if (s == INVALID_SOCKET)
	{
		closesocket(s);
		WSACleanup();
		return false; //Couldn't create the socket
	}

	//Try connecting...

	if (connect(s, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
	{
		closesocket(s);
		WSACleanup();
		return false; //Couldn't connect
	}
	else {
		closesocket(s);
		WSACleanup();
		return true; //Success
	}
}

void CloseConnection()
{
	//Close the socket if it exists
	if (s)
		closesocket(s);

	WSACleanup(); //Clean up Winsock
}
