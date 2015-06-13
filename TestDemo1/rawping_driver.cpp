#include <winsock2.h>
#include <iostream>

#include "rawping.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define DEFAULT_PACKET_SIZE 32
#define DEFAULT_TTL 30
#define MAX_PING_DATA_SIZE 1024
#define MAX_PING_PACKET_SIZE (MAX_PING_DATA_SIZE + sizeof(IPHeader))

int allocate_buffers(ICMPHeader*& send_buf, IPHeader*& recv_buf,
	int packet_size);

///////////////////////////////////////////////////////////////////////
// Program entry point



int main()
{
	// Init some variables at top, so they aren't skipped by the
	// cleanup routines.
	int seq_no = 0;
	ICMPHeader* send_buf = 0;
	IPHeader* recv_buf = 0;

	// Did user pass enough parameters?
	//if (argc < 2) {
	//	cerr << "usage: " << argv[0] << " <host> [data_size] [ttl]" <<
	//		endl;
	//	cerr << "\tdata_size can be up to " << MAX_PING_DATA_SIZE <<
	//		" bytes.  Default is " << DEFAULT_PACKET_SIZE << "." <<
	//		endl;
	//	cerr << "\tttl should be 255 or lower.  Default is " <<
	//		DEFAULT_TTL << "." << endl;
	//	return 1;
	//}

	// Figure out how big to make the ping packet
	int packet_size = DEFAULT_PACKET_SIZE;
	int ttl = DEFAULT_TTL;
	//if (argc > 2) {
	//	int temp = atoi(argv[2]);
	//	if (temp != 0) {
	//		packet_size = temp;
	//	}
	//	if (argc > 3) {
	//		temp = atoi(argv[3]);
	//		if ((temp >= 0) && (temp <= 255)) {
	//			ttl = temp;
	//		}
	//	}
	//}

	packet_size = atoi("55");
	ttl = atoi("21");

	packet_size = max(sizeof(ICMPHeader),
		min(MAX_PING_DATA_SIZE, (unsigned int)packet_size));

	// Start Winsock up
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0) {
		cerr << "Failed to find Winsock 2.1 or better." << endl;
		return 1;
	}

	// Set up for pinging
	SOCKET sd;
	sockaddr_in dest, source;
	if (setup_for_ping("192.168.199.1", ttl, sd, dest) < 0) {
		goto cleanup;
	}
	if (allocate_buffers(send_buf, recv_buf, packet_size) < 0) {
		goto cleanup;
	}
	init_ping_packet(send_buf, packet_size, seq_no);

	// Send the ping and receive the reply
	if (send_ping(sd, dest, send_buf, packet_size) >= 0) {
		while (1) {
			// Receive replies until we either get a successful read,
			// or a fatal error occurs.
			if (recv_ping(sd, source, recv_buf, MAX_PING_PACKET_SIZE) <
				0) {
				// Pull the sequence number out of the ICMP header.  If 
				// it's bad, we just complain, but otherwise we take 
				// off, because the read failed for some reason.
				unsigned short header_len = recv_buf->h_len * 4;
				ICMPHeader* icmphdr = (ICMPHeader*)
					((char*)recv_buf + header_len);
				if (icmphdr->seq != seq_no) {
					cerr << "bad sequence number!" << endl;
					continue;
				}
				else {
					break;
				}
			}
			if (decode_reply(recv_buf, packet_size, &source) == 0) {
				// Success or fatal error (as opposed to a minor error) 
				// so take off.
				cout << "YES";
				break;
			}
			else
			{
				cout << "NO";
			}
		}
	}

cleanup:
	delete[]send_buf;
	delete[]recv_buf;
	WSACleanup();
	return 0;
}


/////////////////////////// allocate_buffers ///////////////////////////
// Allocates send and receive buffers.  Returns < 0 for failure.

int allocate_buffers(ICMPHeader*& send_buf, IPHeader*& recv_buf,
	int packet_size)
{
	// First the send buffer
	send_buf = (ICMPHeader*)new char[packet_size];
	if (send_buf == 0) {
		cerr << "Failed to allocate output buffer." << endl;
		return -1;
	}

	// And then the receive buffer
	recv_buf = (IPHeader*)new char[MAX_PING_PACKET_SIZE];
	if (recv_buf == 0) {
		cerr << "Failed to allocate output buffer." << endl;
		return -1;
	}

	return 0;
}