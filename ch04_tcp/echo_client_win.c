#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int 
main(int argc, char* argv[])
{
    int sock;
    char message[1024];
    int str_len;
    struct sockaddr_in svr_adr;

    if(argc != 3) {
        printf("param counter error!\n");
        exit(1);
    }
    
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == sock) {
        printf("socket() error!\n");
    }

    memset(&svr_adr, 0x00, sizeof(svr_adr));
    svr_adr.sin_family = AF_INET;
    svr_adr.sin_addr.s_addr = inet_addr(argv[1]);
    svr_adr.sin_port = htons(atoi(argv[2]));

    if(-1 == connect(sock, (struct sockaddr*)&svr_adr, sizeof(svr_adr)))
        printf("connect() error\n");
    else 
        printf("Connected.................\n");

    while(1){
        fputs("Input message(Q to quit): ", stderr);
        fgets(message, 1024, stdin);

        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        write(sock, message, strlen(message));
        str_len = read(sock, message, 1023);
        message[str_len] = 0;
        printf("Message from svr: %s \n", message);
    }

    close(sock);

	return 0;
}