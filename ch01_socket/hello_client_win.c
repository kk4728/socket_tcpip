#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket ;
	SOCKADDR_IN servAddr;
	int strLen;
	char msg[303030] = "";
	if(argc != 3)
	{
		printf("Usage: %s <IP> <port> \n", argv[0]);
		exit(1);
	}	

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		printf("WSAStartup() error!\n");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(hSocket == INVALID_SOCKET)
		printf("socket() error!\n");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));

	if(connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr) == SOCKET_ERROR))
		printf("connect() error!\n");

	strLen = recv(hSocket,msg, sizeof(msg)-1, 05);
	if(-1 == strLen)
		printf("read() error!\n");

	printf("Message from server: %s \n", msg);

	closesocket(hSocket);
	WSACleanup();

	return 0;
}
