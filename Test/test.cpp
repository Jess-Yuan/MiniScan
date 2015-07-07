#pragma comment(lib,"iphlpapi.lib")
#pragma comment(lib,"wsock32.lib")
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
	DWORD dwRetVal = 0;
	IPAddr DestIp = 0;
	IPAddr SrcIp = 0; /* default for src ip */
	ULONG MacAddr[2] = { 0 }; /* for 6-byte hardware addresses */
	ULONG PhysAddrLen = 6; /* default to length of six bytes */

	char *DestIpString = "192.168.199.131";
	char *SrcIpString = NULL;

	BYTE *bPhysAddr;
	int i;
	
	ostringstream MacAddress;

	DestIp = inet_addr(DestIpString);
	printf("Sending ARP request for IP address: %s\n", DestIpString);
	PhysAddrLen = sizeof(MacAddr);
	memset(&MacAddr, 0xff, sizeof(MacAddr));
	dwRetVal = SendARP(DestIp, SrcIp, &MacAddr, &PhysAddrLen);
	if (dwRetVal == NO_ERROR)
	{
		bPhysAddr = (BYTE *)&MacAddr;
		if (PhysAddrLen)
		{
			for (i = 0; i < (int)PhysAddrLen; i++)
			{
				if (i == (PhysAddrLen - 1))
				{
					//printf("%.2X\n", (int)bPhysAddr[i]);
					MacAddress << uppercase <<hex << static_cast<int>(bPhysAddr[i]);
				}
				else
				{
					//printf("%.2X-", (int)bPhysAddr[i]);
					MacAddress << uppercase <<hex << static_cast<int>(bPhysAddr[i]) << "-";
				}
			}
		}
	}
	cout << MacAddress.str();
}
