#include <unistd.h>
#include <sys/types.h>       /* basic system data types */
#include <sys/epoll.h>
#include <sys/socket.h>      /* basic socket definitions */
#include <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>       /* inet(3) functions */
#include <netdb.h> 	      /*gethostbyname function */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <iostream>
#include <pthread.h>
#include <string>
#include <semaphore.h>
#include <fcntl.h> 
#include <sys/procfs.h>
#include <sys/ioctl.h>
using namespace std;

typedef struct{
	unsigned char identity;					//指定是请求报文还是反馈报文
	unsigned char size;						//长度
	unsigned char type;						//指定具体报文类型
	unsigned char authgroup;				//指明是否是主监控PC
	unsigned char optional[4];				//网关ID，用于定位到某个网关
	unsigned char s[MAXLINE];				//该字段表示上面提到的具体报文内容
}ASD_GENERAL_MESSAGE;

typedef union{
	unsigned char ucid[4];
	int iid;
}GWID;

struct Info {
	int equip_num;
	int len;
	char data[1024];
};

class Protocol{
private:
	static const MAXLINE = 1016
	static const MAXBUFSIZE = 1024
	static const SIZE_OFFSET = 2
	static const ASD_GENERAL_MESSAGE_HAND_LEN = 8
	static const MAX_EVENTS = 500
	static const RESPONSE_TO_QUERY_GATEWAY_ID = 121

	int 				count;
	int 				epollfd;
	static int 			connfd;
	struct epoll_event 	eventList[MAX_EVENTS];
	queue<Info>			recv_que;
	sem_t 				sem;						//semaphore
	pthread_t 			a_thread;
	pthread_mutex_t 	mutex;
	int 				g_maxLen;
	int 				g_remainLen;
	char 				recvline[MAXLINE];
	char*				servInetAddr;
	int 				servPort;
public:
	Protocol(char* servInetAddr, int servPort);
	int setnonblocking(int sockfd);
	void sendGwInfo();
	void recvET(int sockfd);
	void handle(int sockfd);
	void handleEvent(struct epoll_event* pEvent);
	int EpollHandle();
	int ConnectToSrv(char* servInetAddr, int servPort);
	bool startClient();
	void SendToSrv();

};




