#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char* argv[]) 
{
	int sock;
    char message[1024];
    int str_len;
    struct sockaddr_in adr_svr;

    if(argc != 3) {
    	printf("argc error! \n");
    	exit(-1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == sock) {
    	printf("socket() error! \n");
		exit(-1);
    }

    memset(&adr_svr, 0x00, sizeof(adr_svr));
    adr_svr.sin_family = AF_INET;
    adr_svr.sin_addr.s_addr = inet_addr(argv[1]);
    adr_svr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&adr_svr, sizeof(adr_svr)) == -1) 
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
