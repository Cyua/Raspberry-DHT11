#include "protocol.h"

Protocol::Protocol(char* sa, int sp){
	count = 0;
	g_maxLen = 1024;
	g_remainLen = 0;
  servInetAddr = sa;
  servPort = sp;
}

int Protocol::setnonblocking(int sockfd)
{
	if ( fcntl( sockfd, F_SETFL, fcntl( sockfd, F_GETFD, 0 ) | O_NONBLOCK ) == -1 )
	{
		return -1;
	}
	return 0;
}

void Protocol::sendGwInfo()
{
  	ASD_GENERAL_MESSAGE asd_general_message = {0};
  	asd_general_message.identity = RESPONSE_TO_QUERY_GATEWAY_ID;
  	GWID uti;
  	uti.iid = 1234;
  	memcpy(asd_general_message.optional, uti.ucid, 4);
  	asd_general_message.size = 57;
  	char name[50] = "asdfasdfasd";
  	memcpy(asd_general_message.s, name, 50);
  	send(connfd, (char*)&asd_general_message, asd_general_message.size, 0);
}

void recvET(int sockfd)
{
//memset(recvline, 0, MAXLINE);
  	while(true)  
  	{
  		bool exit_flag = false;
  		int len = 0;
  		ioctl(sockfd, FIONREAD, &len);
  		if(len>=2)
  		{
  			int real_size = 0;
  			int r = recv(sockfd, recvline, SIZE_OFFSET, MSG_PEEK);  
  			if(r == 2) {
  				real_size = recvline[1];
  			} else {
  				printf("errno : %d\n", errno);
  				return;
  			}

  			memset(recvline, 0, MAXLINE);
  			while(true) 
  			{
  				int r = recv(sockfd, recvline + g_remainLen, real_size - g_remainLen, 0);  
  				if(r < 0){
								// 由于是非阻塞的模式,所以当errno为EAGAIN时,表示当前缓冲区已无数据可读  
								// 在这里就当作是该次事件已处理处.  
  					if(errno == EAGAIN) {
  						printf("EAGAIN\n");
  						exit_flag = true;
  						break;  
  					} else {
  						return;  
  					}
  				} else if(r == 0) {
								// 这里表示对端的socket已正常关闭. 
  					printf("echoclient: server terminated prematurely\n");
  					break;
  				}
  				g_remainLen += r;
  				if (g_remainLen == real_size) 
  				{
  					ASD_GENERAL_MESSAGE package;
  					memcpy(&package, recvline, real_size);
  					printf("Recv from srv, content : %d-%d-%d-%d-%s-%d %d\n", 
  						package.identity, package.size, package.type, 
  						package.authgroup, package.optional, package.s[0], package.s[1]);
  					g_remainLen = 0;
  					memset(recvline, 0, MAXLINE);
  				}
  				cout << "@@@@" << r << "@@@@" << endl;
  			}
  			if (exit_flag)
  				break;		
  		}
  	}
}


void Protocol::handle(int sockfd)
{
	recvET(sockfd);
}

void handleEvent(struct epoll_event* pEvent)
{
  	printf("handleEvent function, HANDLE: %d, EVENT is %d\n",
  		pEvent->data.fd,
  		pEvent->events);

  	if ( (pEvent->events & EPOLLERR) ||
  		(pEvent->events & EPOLLHUP) ||
  		!(pEvent->events & EPOLLIN) )
  	{
  		printf ( "epoll error\n");
  		close (pEvent->data.fd);
  		return;
  	}

  	if (pEvent->data.fd == connfd) 
	{//如果发生事件的fd是监听的srvfd，那么接受请求。
		handle(connfd);
	}
		//printf("exit handleEvent\n");
}

int Protocol::EpollHandle()
{
		/* 创建 epoll 句柄，把监听 socket 加入到 epoll 集合里 */
	epollfd = epoll_create(MAX_EVENTS);
	struct epoll_event event;
		/*
		   EPOLLIN：      表示对应的文件描述符可以读；
		   EPOLLOUT：     表示对应的文件描述符可以写；
		   EPOLLPRI：     表示对应的文件描述符有紧急的数据可读；
		   EPOLLERR：     表示对应的文件描述符发生错误；
		   EPOLLHUP：     表示对应的文件描述符被挂断；
		   EPOLLET：      表示对应的文件描述符有事件发生；
		 */
	event.events = EPOLLIN | EPOLLET;
	event.data.fd = connfd;
	if ( epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &event) < 0 ){
		printf("epoll Add Failed: fd=%d\n", connfd);
		return -1;
	}
	printf( "epollEngine startup\n");
	while (1){
				/*等待事件发生*/
		int nfds = epoll_wait(epollfd, eventList, MAX_EVENTS, -1);
   		printf("sth happen\n");
		if ( nfds == -1 ){
			printf( "epoll_wait" );				//continue;
		}
		int n = 0;
		for (; n < nfds; n++)
			handleEvent(eventList + n);
   		printf("sth enddown\n");
	}

	close(epollfd);
	close(connfd);
}

int Protocol::ConnectToSrv()
{
	struct sockaddr_in servaddr;
	connfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(servPort);
	inet_pton(AF_INET, servInetAddr, &servaddr.sin_addr);
	if (setnonblocking( connfd ) < 0 )
	{
		printf( "setnonblock error" );
		return -1;
	}
	if (connect(connfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1 
		&& errno != EINPROGRESS) {
		printf("Error in connect: %d,%s\n", errno,strerror(errno));
		close(connfd);
		return -1;
	}
	sendGwInfo();
}

bool Protocol::startClient(){
        ConnectToSrv();
        int res = pthread_create(&a_thread, NULL, SendToSrv, NULL);  
        if (res != 0)  
        {  
            perror("Thread creation failed!");  
            exit(EXIT_FAILURE);  
        }  
        EpollHandle();
        close(connfd);
}

void SendToSrv(){
  struct sockaddr_in servaddr;
    connfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(servPort);
    inet_pton(AF_INET, servInetAddr, &servaddr.sin_addr);

    if (setnonblocking( connfd ) < 0 )
    {
        printf( "setnonblock error" );
        return -1;
    }

    if (connect(connfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1 &&
            errno != EINPROGRESS) {
        printf("Error in connect: %d,%s\n", errno,strerror(errno));
        close(connfd);
        return -1;
    }
}