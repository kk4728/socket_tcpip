#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 30

#pragma comment(lib, "ws2_32.lib")


int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET svrSock;
    char message[BUF_SIZE];
    int strLen;
    int clntAdrSz;
    SOCKADDR_IN svrAdr, clntAdr;
    if(WSAStartup(MAKEWORD(2,2)) != 0)
        printf("WSAStartup() error! \n");

    svrSock = socket(PF_INET, SOCK_DGRAM, 0);
    if(svrSock == INVALID_SOCKET)
        printf("UDP socket() creation error! \n");

    memset(&svrAdr, 0x00, sizeof(svrAdr));
    svrAdr.sin_family = AF_INET;
    svrAdr.sin_addr.s_addr = htonl(INADDR_ANY);
    svrAdr.sin_port = htons(atoi(argv[1]));
    

    closesocket(svrSock);
    WSACleanup();


    return 0;
}