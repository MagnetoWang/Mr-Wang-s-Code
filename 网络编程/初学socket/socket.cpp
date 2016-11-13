#include<iostream>
#include<Windows.h>
#include<winsocks2.h>
#pragma comment(lib,"ws_32.lib")
using namespace std;
int main()
{
	WSADATA wasData;
	WSAStartup (MAKEWORD(2,2),&wasData);
	cout<<"wVersion:"<<LOBYTE(wasData.wVersion)<<HIBYTE(wasData.wHighVersion)<<endl;
	cout<<"wHighVersion:"<<LOBYTE(wasData.wHighVersion)<<HIBYTE(wasData.wHighVersion)<<endl;
	cout<<wasData.szDescription<<endl<<wasData.szSystemStatus<<endl;
	SOCKET socket(int af,int type,int protocol);//地址，传输方式，传输协议
	int bind(SOCKET sock,const struct sockaddr *addr,int addrlen);
	int serv_sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	struct sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;//IPV4 address
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//address exactly
	serv_addr.sin_port=htons(1234);
	bind(SOCKET serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));//将sockaddr_in强制转化sockaddr结构体
	int connect(SOCKET sock,const struct sockaddr * serv_addr,int addrlen);
	int listen(SOCKET sock,int backlog);
	SOCKET accept(SOCKET sock,struct sockaddr *addr,int *addrlen);
	 ssize_t write(int fd,const void*buf,size_t nbytes);
	 //fd 为文件名，buf为数据的地址，nbytes 写入数据的大小
	 int send(SOCKET sock,const char *buf,int len, int flags);//服务器端
	 int recv(SOCKET sock,char *buf,int len,int flags);//客服端


}
#include<iostream>
#include<winsocks2>
#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 100
int main()
{
	WSADATA wasData;
	WSAStartup (MAKEWORD(2,2),&wasData);
	SOCKET servSock=socket
}