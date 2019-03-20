#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

int main(int argc, char* argv[])
{
    int svr_sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t clnt_adr_sz;
    struct sockaddr_in svr_adr, clnt_adr;

    svr_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(-1 == svr_sock)
        printf("UDP socket creation error!\n");

    memset(&svr_adr, 0x00, sizeof(svr_adr));
    svr_adr.sin_family = AF_INET;
    svr_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    svr_adr.sin_port = htons(atoi(argv[1]));

    if(bind(svr_sock, (struct sockaddr* )&svr_adr, sizeof(svr_adr)) == -1)
        printf("bind() eror! \n");

    while(1)
    {
        clnt_adr_sz = sizeof(clnt_adr);
        str_len = recvfrom(svr_sock, message, BUF_SIZE, 0x00, 
            (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        sendto(svr_sock, message, str_len, 0, 
            (struct sockaddr*)&clnt_adr, clnt_adr_sz);
    }
    close(svr_sock);

    return 0;
}