#include "protocol.h"
#include <iostream>
int main(int argc, char const *argv[])
{
	char * servInetAddr = "127.0.0.1";
	int servPort = 6888;
	//char buf[MAXLINE];
	//int connfd;
	//struct sockaddr_in servaddr;
	//可以在执行的时候带参数，第一个参数为srv的IP，第二个为srv的端口
	if (argc == 2) {
			servInetAddr = argv[1];
	}
	if (argc == 3) {
			servInetAddr = argv[1];
			servPort = atoi(argv[2]);
	}
	if (argc > 3) {
			printf("usage: echoclient <IPaddress> <Port>\n");
			return -1;
	}
	printf("welcome to echoclient\n");

	

	printf("exit\n");
	exit(0);
}