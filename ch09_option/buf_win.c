#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	SOCKET sock;
	WSADATA wsaData;

	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		printf("WSAStartup() error!\n ");
		exit(-1);
	}


	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock != -1) {
		printf("socket() error!\n ");
		exit(-1);
	}

	


	return 0;
}

