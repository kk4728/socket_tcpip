#include <stdio.h>
#include <string.h>

#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

void ErrorHandling(char* msg);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	{
		char* addr = "127.212.124.78";
		unsigned long conv_addr = inet_addr(addr);
		if(conv_addr == INADDR_NONE)
			printf("Error occured! \n");
		else
			printf("Network ordered integer addr: %#lx \n", conv_addr);
	}

	{
		struct sockaddr_in addr;
		char* strPtr;
		char strArr[20];
		
		addr.sin_addr.s_addr = htonl(0x10203040);
		strPtr = inet_ntoa(addr.sin_addr);
		strcpy(strArr, strPtr);
		printf("Hotted-Decimal notation3 %s \n", strArr);
	}

	WSACleanup();

	return 0;
}

void ErrorHandling(char* msg)
{
	fputs(msg, stdout);
	fputc('\n', stdout);
}
