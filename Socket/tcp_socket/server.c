/*
 * server.c为服务器端代码
*/

#include "config.h"

int main(int argc , char **argv)
{
	/*声明服务器地址和客户链接地址*/
	struct sockaddr_in servaddr , cliaddr;

	/*声明服务器监听套接字和客户端链接套接字*/
	int listenfd , connfd;
	pid_t childpid;

	socklen_t clilen;

	/*(1) 初始化监听套接字listenfd*/
	if((listenfd = socket(AF_INET , SOCK_STREAM , 0)) < 0)
	{
		perror("socket error");
		exit(1);
	}//if

	/*(2) 设置服务器sockaddr_in结构*/
	bzero(&servaddr , sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	//host order to network order with int --32bit
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //表明可接受任意IP地址
	//host order to network order with short int -- 16bit
	servaddr.sin_port = htons(PORT);

	/*(3) 绑定套接字和端口*/
	if(bind(listenfd , (struct sockaddr*)&servaddr , sizeof(servaddr)) < 0)
	{
		perror("bind error");
		exit(1);
	}//if

	/*(4) 监听客户请求*/
	if(listen(listenfd , LISTENQ) < 0)
	{
		perror("listen error");
		exit(1);
	}//if

	/*(5) 接受客户请求*/
	for( ; ; )
	{
		clilen = sizeof(cliaddr);
		if((connfd = accept(listenfd , (struct sockaddr *)&cliaddr , &clilen)) < 0 )
		{
			perror("accept error");
			exit(1);
		}//if

		//新建子进程单独处理链接
		//返回0的是子进程，程序通过拷贝父进程放回两次。
		if((childpid = fork()) == 0) 
		{
			//由于拷贝的父进程所有资源，所以要关闭子进程的监听套接字
			close(listenfd);
			//str_echo
			ssize_t n;
			char buff[MAX_LINE];
			while((n = read(connfd , buff , MAX_LINE)) > 0)
			{
				write(connfd , buff , n);
			}
			exit(0);
		}// end if
		//回到父进程的内容，关闭父进程中的连接套接字。
		close(connfd);
	}//end for
	
	/*(6) 关闭监听套接字*/
	close(listenfd);
}
