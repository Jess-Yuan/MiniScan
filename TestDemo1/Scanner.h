#include <map>
#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

const char *ipAddr = "127.0.0.1";
map<int, int> ports = { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 445, 445 }, { 443, 443 }, { 5, 5 }, {10,10},
{ 11, 11 }, {12,12} };
map<int, int>::const_iterator item = ports.cbegin();
SOCKET s;
HANDLE mutex;

bool ConnectToHost(int port,const char* ipAddr)
{

	//Start up Winsock¡­
	WSADATA wsadata;

	int error = WSAStartup(0x0202, &wsadata);

	//Did something happen?
	if (error)
		return false;
	//Did we get the right Winsock version?
	if (wsadata.wVersion != 0x0202)
	{
		WSACleanup(); //Clean up Winsock
		return false;
	}
	//Fill out the information needed to initialize a socket¡­
	SOCKADDR_IN target; //Socket address information

	target.sin_family = AF_INET; // address family Internet
	target.sin_port = htons(port); //Port to connect on
	target.sin_addr.s_addr = inet_addr(ipAddr); //Target IP

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_IP); //Create socket
	//s = socket (AF_INET, SOCK_RAW,IPPROTO_ICMP);
	//s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == INVALID_SOCKET)
	{
		return false; //Couldn't create the socket
	}

	//Try connecting...

	if (connect(s, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
	{
		return false; //Couldn't connect
	}
	else
		return true; //Success
}

void CloseConnet()
{
	//Close the socket if it exists
	if (s)
		closesocket(s);

	WSACleanup(); //Clean up Winsock
}

DWORD WINAPI Proc1(LPVOID lpParam)
{
	while (true) {
		WaitForSingleObject(mutex, INFINITE);
		if (item != ports.end()) {
			if (ConnectToHost(item->second, "127.0.0.1")) {
				cout << "Proc1 " << item->second << " is open!!!" << endl;
				item++;
				ReleaseMutex(mutex);
			}
			else {
				cout << "Proc1 " << item->second << " is close" << endl;
				item++;
				ReleaseMutex(mutex);
			}
		}
		else {
			break;
		}
	}

	return 0;
	
}

DWORD WINAPI Proc2(LPVOID lpParam)
{
	while (true) {
		WaitForSingleObject(mutex, INFINITE);
		if (item != ports.cend()) {
			if (ConnectToHost(item->second, "127.0.0.1")) {
				cout << "Proc2  " << item->second << " is open!!!" << endl;
				item++;
				//ReleaseMutex(mutex);
			}
			else {
				cout << "Proc2  " << item->second << " is close" << endl;
				item++;
				ReleaseMutex(mutex);
			}
		}
		else {
			break;
		}
	}

	return 0;

}
