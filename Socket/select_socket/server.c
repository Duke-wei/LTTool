#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>


#define PORT 8888
#define MAX_LINE 2048
#define LISTENQ 20


int main(int argc , char **argv)
{
	int i, maxi, maxfd, listenfd, connfd, sockfd;

	int nready , client[FD_SETSIZE];
	
	ssize_t n, ret;
		
	fd_set rset , allset;

	char buf[MAX_LINE];

	socklen_t clilen;

	struct sockaddr_in servaddr , cliaddr;

	/*(1) 得到监听描述符*/
	listenfd = socket(AF_INET , SOCK_STREAM , 0);

	/*(2) 绑定套接字*/
	bzero(&servaddr , sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	bind(listenfd , (struct sockaddr *)&servaddr , sizeof(servaddr));

	/*(3) 监听*/
	listen(listenfd , LISTENQ);

	/*(4) 设置select*/
	maxfd = listenfd;
	maxi = -1;
	for(i=0 ; i<FD_SETSIZE ; ++i)
	{
		client[i] = -1;
	}//for

	//fd_zero 清空集合。
	FD_ZERO(&allset);
	//fd_set 将描述符加入集合中。
	FD_SET(listenfd , &allset);

	/*(5) 进入服务器接收请求死循环*/
	while(1)
	{
		//rset he allset 两个文件描述符集合，rset为allset的临时存储，allset用于更新。
		rset = allset;
		//select函数 第一个:文件描述符个数 二、三、四:读写异常描述符集合 五:时间结构体
		//返回就绪描述符的个数。
		nready = select(maxfd+1 , &rset , NULL , NULL , NULL);
		
		//检查集合中的文件描述符时候可读写。
		if(FD_ISSET(listenfd , &rset))
		{
			/*接收客户端的请求*/
			clilen = sizeof(cliaddr);

			printf("\naccpet connection~\n");

			if((connfd = accept(listenfd , (struct sockaddr *)&cliaddr , &clilen)) < 0)
			{
				perror("accept error.\n");
				exit(1);
			}//if		

			printf("accpet a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr) , cliaddr.sin_port);

			//维持一个数组，存储链接的套接字描述符。
			/*将客户链接套接字描述符添加到数组*/
			for(i=0 ; i<FD_SETSIZE ; ++i)
			{
				if(client[i] < 0)
				{
					client[i] = connfd;
					break;
				}//if
			}//for

			if(FD_SETSIZE == i)
			{
				perror("too many connection.\n");
				exit(1);
			}//if
			//讲新建的套接字描述符加入集合中。
			FD_SET(connfd , &allset);
			//记录套接字描述符个数。和最大下表maxi
			if(connfd > maxfd)
				maxfd = connfd;
			if(i > maxi)
				maxi = i;

			//记录以处理的个数，小于0即处理完，这循环继续等待可处理描述符。
			//这里不等于0，考虑到监听套接字就绪会建立新的连接套接字，所以还要继续处理。
			if(--nready < 0)
				continue;
		}//if

		//处理可读写的套接字描述符，select只能提示有读写，但并没有给定读写的套接字是哪一个。
		for(i=0; i<=maxi ; ++i)
		{
			//描述符数组可能有空的，即之前的连接关闭了。
			if((sockfd = client[i]) < 0)
				continue;
			if(FD_ISSET(sockfd , &rset))
			{
				/*处理客户请求*/
				printf("\nreading the socket~~~ \n");
				
				bzero(buf , MAX_LINE);
				if((n = read(sockfd , buf , MAX_LINE)) <= 0)
				{
					close(sockfd);
					FD_CLR(sockfd , &allset);
					client[i] = -1;
				}//if
				else{
					printf("clint[%d] send message: %s\n", i , buf);
					if((ret = write(sockfd , buf , n)) != n)	
					{
						printf("error writing to the sockfd!\n");
						break;
					}//if
				}//else
				if(--nready <= 0)
					break;
			}//if
		}//for
	}//while
}
