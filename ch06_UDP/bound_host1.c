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
    char message[BUF_SIZE];
    struct sockaddr_in adr1, adr2;
    socklen_t adr_sz;
    int str_len;

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(-1 == sock)
        printf("socket() error!\n");

    memset(&adr1, 0x00, sizeof(adr1));
    adr1.sin_family = AF_INET;
    adr1.sin_addr.s_addr = htonl(INADDR_ANY);
    adr1.sin_port = htons(atoi(argv[1]));

    if(bind(sock, (struct sockaddr*)&adr1, sizeof(adr1)) == -1)
        printf("bind() error! \n");

    for (int i = 0; i < 3; ++i)
    {
        //sleep(5);
        adr_sz = sizeof(adr2);
        str_len = recvfrom(sock, message, BUF_SIZE, 0, 
            (struct sockaddr*)&adr2, &adr_sz);
        printf("Message %d: %s \n", i+1, message);
    }
    close(sock);

    return 0;
}