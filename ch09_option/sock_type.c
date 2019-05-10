#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
	int sock_tcp;
	int sock_udp;
	int sock_type;
	int state;
	socklen_t optlen;

	optlen = sizeof(sock_type); //切记此赋值，否则在后续函数可能出错，optlen值不要为0
	sock_tcp = socket(PF_INET, SOCK_STREAM, 0);
	sock_udp = socket(PF_INET, SOCK_DGRAM, 0);
	printf("SOCK_STREAM: %d\n", SOCK_STREAM);
	printf("SOCK_DGRAM: %d\n", SOCK_DGRAM);

	state = getsockopt(sock_tcp, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen);
	if(state) {
		printf("getsockopt() error! \n");
		exit(0);
	}
	printf("Socket type one: %d\n", sock_type);

	state = getsockopt(sock_udp, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen);
	if(state) {
		printf("getsockopt() error! \n");
		exit(0);
	}
	printf("Socket type two: %d\n", sock_type);

	return 0;
}
