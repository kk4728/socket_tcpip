#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define OPSZ     4

int calculate(int opnum, int opnds[], char op)
{
    int result = opnds[0];
    int i = 0;
    switch(op)
    {
    case '+':
        for (i = 1; i < opnum; ++i) result += opnds[i];
        break;
    case '-':
        for (i = 1; i < opnum; ++i) result -= opnds[i];
        break;
    case '*':
        for (i = 1; i < opnum; ++i) result *= opnds[i];
        break;
    default:
        break;
    }

    return result;
}



int main(int argc, char *argv[]) 
{
    int svr_sock, clnt_sock;
    char opinfo[BUF_SIZE];
    int result, opnd_cnt; 
    int recv_cnt, recv_len;
    struct sockaddr_in svr_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    svr_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == svr_sock)
        printf("socket() error!\n");

    memset(&svr_adr, 0x00, sizeof(svr_adr));
    svr_adr.sin_family = AF_INET;
    svr_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    svr_adr.sin_port = htons(atoi(argv[1]));

    if(bind(svr_sock, (struct sockaddr*)&svr_adr, sizeof(svr_adr)) == -1)
        printf("bind() error! \n");
    if(listen(svr_sock, 5) == -1)
        printf("listen() error! \n");

    clnt_adr_sz = sizeof(clnt_adr);

    for (int i = 0; i < 5; ++i)
    {
        printf("T.B.D: %d ...\n", i+1);
        opnd_cnt = 0;
        clnt_sock = accept(svr_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        read(clnt_sock, &opnd_cnt, 1);

        recv_len = 0;
        while(opnd_cnt*OPSZ +1 > recv_len)
        {
            recv_cnt = read(clnt_sock, &opinfo, BUF_SIZE-1);
            recv_len += recv_cnt;
        }

        result = calculate(opnd_cnt, (int*)opinfo, opinfo[recv_len-1]);
        write(clnt_sock, (char*)&result, sizeof(result));
        close(clnt_sock);
        printf("close socket partially!\n");
    }

    return 0;
}