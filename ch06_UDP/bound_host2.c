#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

int main(int argc, char* argv[])
{
    int sock;
    char msg1[] = "Hi!";
    char msg2[] = "I'm another UDP host!";
    char msg3[] = "Nice to meet you";

    struct sockaddr_in adr;
    socklen_t adr_sz;
    int str_len;

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(-1 == sock)
        printf("socket() error! \n");

    memset(&adr, 0x00, sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = inet_addr(argv[1]);
    adr.sin_port = htons(atoi(argv[2]));

    sendto(sock, msg1, sizeof(msg1), 0, (struct sockaddr*)&adr, sizeof(adr));
    sendto(sock, msg2, sizeof(msg2), 0, (struct sockaddr*)&adr, sizeof(adr));
    sendto(sock, msg3, sizeof(msg3), 0, (struct sockaddr*)&adr, sizeof(adr));

    close(sock);

    return 0;
}