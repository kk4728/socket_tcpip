#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

int main(int argc, char * argv[])
{
	int sock;
	int snd_buf = 1024*3;
	int rcv_buf = 1024*3;
	int state;
	socklen_t len;

	sock = socket(PF_INET, SOCK_STREAM, 0);

	printf("==============set option=======================\n");
	//
	state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, sizeof(rcv_buf));
	if(state) {
		printf("setsockopt() error! \n");
		exit(0);
	}

	state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, sizeof(snd_buf));
	if(state) {
		printf("setsockopt() error! \n");
		exit(-1);
	}

	printf("==============get option=======================\n");

	len = sizeof(snd_buf); //建议len值不要为0
	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &len);
	if(state) {
		printf("getsockopt() error! \n");
		exit(0);
	}

	len = sizeof(rcv_buf);
	state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, &len);
	if(state) {
		printf("getsockopt() error! \n");
		exit(-1);
	}
	printf("Input Buffer size: %d \n", rcv_buf);
	printf("Output Buffer size: %d \n", snd_buf);



	return 0;
}