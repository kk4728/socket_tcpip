#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TRUE 	1
#define FALSE 	0

int main(int argc, char* argv[])
{
	int sock_svr, sock_clnt;
	char message[30];
	int option, str_len;
	socklen_t optlen, clnt_cdr_sz;
	struct sockaddr_in adr_svr, adr_clnt;

	sock_svr = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sock_svr) {
		printf("socket() error! \n");
		exit(-1);
	}

	
	optlen = sizeof(option);
	option = TRUE;
	setsockopt(sock_svr, SOL_SOCKET, SO_REUSEADDR, (void*)&option, optlen);
	

	memset(&adr_svr, 0x00, sizeof(adr_svr));
	adr_svr.sin_family = AF_INET;
	adr_svr.sin_addr.s_addr = htonl(INADDR_ANY);
	adr_svr.sin_port = htons(atoi(argv[1]));

	if(bind(sock_svr, (struct sockaddr*)&adr_svr, sizeof(adr_svr))) {
		printf("bind() error!\n");
		exit(-1);
	}
	if(listen(sock_svr, 5) == -1) {
		printf("listen() error!\n");
		exit(-1);
	}
	
	clnt_cdr_sz =sizeof(adr_clnt);
	sock_clnt = accept(sock_svr, (struct sockaddr*)&adr_clnt, &clnt_cdr_sz);
	printf("accep connect from clinet.\n");
	while(0 != (str_len = read(sock_clnt, message, sizeof(message))))
	{
		write(sock_clnt, message, str_len);
		write(1, message, str_len);

	}

	printf("close res!!!!!!!!!\n");
	close(sock_clnt);
	close(sock_svr);


	return 0;
}
