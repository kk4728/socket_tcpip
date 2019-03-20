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
    int str_len;
    socklen_t adr_sz;
    struct sockaddr_in svr_adr, from_adr;

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(-1 == sock)
        printf("socket() error! \n");

    memset(&svr_adr, 0x00, sizeof(svr_adr));
    svr_adr.sin_family = AF_INET;
    svr_adr.sin_addr.s_addr = inet_addr(argv[1]);
    svr_adr.sin_port = htons(atoi(argv[2]));

    while(1)
    {
        fputs("Insert message(q to quit): ", stdout);
        fgets(message, sizeof(message), stdin);
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        sendto(sock, message, strlen(message), 0,
            (struct sockaddr*)&svr_adr, sizeof(svr_adr));
        
        adr_sz = sizeof(from_adr);
        str_len = recvfrom(sock, message, BUF_SIZE, 0,
            (struct sockaddr*)&from_adr, &adr_sz);

        message[str_len] = 0;
        printf("Message from server: %s ", message);
    }
    close(sock);

    return 0;
}