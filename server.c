#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;
    
    /*struct sockaddr_in{
	sa_family_t   sin_family;   //地址族
	uint16_t      sin_port;     //端口号
	struct in_addr    sin_addr;  //32位IP地址
	char     sin_zero;      //预留未使用
};
struct in_addr{
	In_addr_t  s_addr;    //32位IPv4地址
};*/

    
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;//socklen_t是一种数据类型，和int差不多，在32位机下，size_t和int的长度相同，都是32 bits,但在64位机下，size_t（32bits）和int（64 bits）的长度是不一样的，socket编程中的accept函数的第三个参数的长度必须和int的长度相同。于是有了socklen_t类型。
    char message[] = "Hello World!";

    if(argc != 2)//argc表示接受命令个数，*argv指针数组，用来存放字符串参赛的指针
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
	// 创建套接字socket函数 (协议栈信息, 套接字数据传输类型信息, 计算机间通信的协议信息)
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	
	if(serv_sock == -1)
		error_handling("socket() error");
	// 初始化存有地址信息的结构体变量
	memset(&serv_addr, 0, sizeof(serv_addr));//将某一块内存中的内容全部设置为指定值
	serv_addr.sin_family=AF_INET;//使用 IPv4 进行通信
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);//htonl();将主机数转换成无符号长整型,INADDR_ANY为任意地址0.0.0.0
	serv_addr.sin_port=htons(atoi(argv[1]));//atoi();将字符串转换成整型数
	// bind函数，分配初始化的地址信息 (套接字文件描述符, 存映地址信息的结构体变量, 第二个结构体变量的长度)
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
		error_handling("bind() error");
	// listen函数，进入等待连接请求状态 (套接字文件描述符, 队列长度)
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	clnt_addr_size=sizeof(clnt_addr);
	// accept函数，受理客户端连接请求 (套接字文件描述符, 存有客户端地址信息的变量地址值, 第二个结构体变量的长度)
	clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr, &clnt_addr_size);
	if(clnt_sock==-1)
		error_handling("accept() error");

	write(clnt_sock, message, sizeof(message));
	close(clnt_sock);
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

