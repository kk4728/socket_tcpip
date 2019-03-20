#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	WSADATA	 wsaData;

	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
		printf("WSAStartup() error!\n ");

	//inet_addr
	char* addr = "127.212.124.78";
	unsigned long conv_addr = inet_addr(addr);
	if(conv_addr==INADDR_NONE)
		printf("Error occured!\n");
	else 
		printf("Network ordered integer addr: %#lx \n", conv_addr);



	WSACleanup();
	return 0;
}
