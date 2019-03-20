#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET svr_sock, clnt_sock;
	char message[1024];
	int str_len, i;
	SOCKADDR_IN svr_adr, clnt_adr;
	int  clnt_adr_sz;

	if(argc != 2) {
		printf(" != 2\n");
		exit(1);
	}

	if(0 != WSAStartup(MAKEWORD(2,2), &wsaData))
		printf("WSAStartup() error!\n");

	svr_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(-1 == svr_sock) {
		printf("socket() error!\n");
	}

	memset(&svr_adr, 0x00, sizeof(svr_adr));
	svr_adr.sin_family = AF_INET;
	svr_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	svr_adr.sin_port = htons(atoi(argv[1]));

	if(bind(svr_sock, (SOCKADDR*)&svr_adr, sizeof(svr_adr)) == SOCKET_ERROR) {
		printf("bind() error!\n");
	}

	if(listen(svr_sock, 5)  == -1) {
		printf("listen() error!");
	}

	clnt_adr_sz = sizeof(clnt_adr);
	for(i=0; i<5; i++) {
		clnt_sock = accept(svr_sock, (SOCKADDR*)&clnt_adr, &clnt_adr_sz);
		if(-1 == clnt_sock) {
			printf("accept() error!\n");
		} else {
			printf("connected client %d \n", i+1);
		}

		while((str_len = recv(clnt_sock, message, 1024, 0)) != 0)
			write(clnt_sock, message, str_len);

		closesocket(clnt_sock);
	}

	closesocket(svr_sock);
	WSACleanup();

	return 0;
}