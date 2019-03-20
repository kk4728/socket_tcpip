#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ     4

int main(int argc, char* argv[])
{
    int sock;
    char opmsg[BUF_SIZE];
    int result, opnd_cnt;
    struct sockaddr_in svr_adr;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == sock) {
        printf("socket() error!\n");
    } else {
        printf("socket: %d\n", sock);
    }

    memset(&svr_adr, 0x00, sizeof(svr_adr));
    svr_adr.sin_family = AF_INET;
    svr_adr.sin_addr.s_addr = inet_addr(argv[1]);
    svr_adr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&svr_adr, sizeof(svr_adr)) == -1)
        printf("connect() error!\n");
    else
        puts("connect.................\n");

    fputs("Operand count: ", stdout);
    scanf("%d", &opnd_cnt);
    opmsg[0] = (char)opnd_cnt;

    for (int i = 0; i < opnd_cnt; ++i)
    {
        printf("Operand %d: \n", i+1);
        scanf("%d", (int*)(&opmsg[i*OPSZ+1]));
    }
    fgetc(stdin);
    fputs("Operand: ", stdout);
    scanf("%c", &opmsg[opnd_cnt*OPSZ+1]);
    write(sock, opmsg, opnd_cnt*OPSZ+2);
    read(sock, &result, RLT_SIZE);

    printf("Operation result: %d \n", result);
    close(sock);
    printf("close client socket!\n");

    return 0;
}