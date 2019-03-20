#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void error_handling(char* msg);

int main()
{
	int fd;
	char buf[] = "Let's go!\n";

	fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC);
	if(-1 == fd)
		printf("open() error!\n");
	printf("file descriptor: %d \n", fd);

	if(write(fd, buf, sizeof(buf)) == -1)
		printf("write() error!\n");
	close(fd);

	return 0;
}
