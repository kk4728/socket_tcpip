#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

void domain2ip(int argc, char** argv) {
	for (int i = 0; i < argc; ++i)
	{
		printf("%d:	%s\n", i+1, argv[i]);
	}

	struct hostent* p = gethostbyname(argv[1]);
	if(! p) {
		printf("localhost: \n");
	}

	printf("offical name:\t%s\n", p->h_name);

	for (int i = 0; p->h_aliases[i]; ++i)
		printf("Aliases %d: %s\n", i+1, p->h_aliases[i]);

	printf("Address type : %s \n", (p->h_addrtype==AF_INET) ? "AF_INET" : "AF_INET6");

	for (int i = 0; p->h_addr_list[i]; ++i)
		printf("IP addr %d: %s \n", i+1, inet_ntoa(*(struct in_addr*)p->h_addr_list[i]));
}

void ip2domain(int argc, char** argv){
	struct hostent* host;
	struct sockaddr_in addr;
	if(2 != argc) {
		printf("Usage: %s\n", argv[0]);
		exit(1);
	}

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	host = gethostbyaddr((char*)&addr.sin_addr, 4, AF_INET);
	if(!host) {
		printf("error: gethostbyaddr()\n");
		exit(1);
	}

	printf("offical name:\t%s\n", host->h_name);

	for (int i = 0; host->h_aliases[i]; ++i)
		printf("Aliases %d: %s\n", i+1, host->h_aliases[i]);

	printf("Address type : %s \n", (host->h_addrtype==AF_INET) ? "AF_INET" : "AF_INET6");

	for (int i = 0; host->h_addr_list[i]; ++i)
		printf("IP addr %d: %s \n", i+1, inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
}

int main(int argc, char** argv) {
	
	//domain2ip(argc, argv);
	ip2domain(argc, argv);

	return 0;
}