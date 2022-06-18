#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len;

	if(argc!=3)
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock=socket(PF_INET, SOCK_STREAM, 0);// 创建套接字socket函数 (协议栈信息, 套接字数据传输类型信息, 计算机间通信的协议信息)
	if(sock == -1)
		error_handling("socket() error");
	// 初始化存有地址信息的结构体变量
	memset(&serv_addr, 0, sizeof(serv_addr));//将某一块内存中的内容全部设置为指定值
	serv_addr.sin_family=AF_INET;//使用 IPv4 进行通信
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);//htonl();将主机数转换成无符号长整型,地址为argv[1]
	serv_addr.sin_port=htons(atoi(argv[2]));//使用 IPv4 进行通信

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		error_handling("connet() error");//connect()用于建立与指定socket的连接。

	str_len=read(sock, message, sizeof(message)-1);
	if(str_len==-1)
		error_handling("read() error");

	printf("Message from server : %s \n", message);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

