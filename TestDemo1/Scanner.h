#include <map>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class Scanner {
public:
	Scanner(unsigned p, const char *ip) { port = p; ipAddr = ip; ports.insert({ 1, 1 }); }
	bool ScanPort();
	void CloseConnet();
	map<int, int> ports;
private:
	unsigned port = 0;
	const char *ipAddr = "127.0.0.1";
	SOCKET s; //Socket handle
};

bool Scanner::ScanPort()
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
	target.sin_port = htons(this->port); //Port to connect on
	target.sin_addr.s_addr = inet_addr(this->ipAddr); //Target IP

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

void Scanner::CloseConnet()
{
	//Close the socket if it exists
	if (s)
		closesocket(s);

	WSACleanup(); //Clean up Winsock
}
