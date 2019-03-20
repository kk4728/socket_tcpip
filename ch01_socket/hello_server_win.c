#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;
	int szClntAddr;
	char msg[] = "Hello World!";
	if(argc != 2)
	{
		printf("Usage: %s <port> \n", argv[0]);
		exit(1);
	}	

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		printf("WSAStartup() error!\n");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if(hServSock == INVALID_SOCKET)
		printf("socket() error!\n");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	if(bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr) == SOCKET_ERROR))
		printf("bind() error!\n");

	if(listen(hServSock, 5) == SOCKET_ERROR)
		printf("listen() error!\n");

	szClntAddr = sizeof(clntAddr);
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
	if(hClntSock == INVALID_SOCKET)
		printf("accept() error!\n");

	send(hClntSock, msg, sizeof(msg), 0);

	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();

	return 0;
}
