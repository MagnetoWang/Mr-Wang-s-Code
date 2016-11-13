#include<iostream>
#include<winsocks2>
#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 100
int main()
{
	WSADATA wasData;
	WSAStartup (MAKEWORD(2,2),&wasData);
	SOCKET servSock=socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in sockAddr;
	memset(&sockAddr,0,sizeof(sockAddr));
	sockAddr.sin_family=AF_INET;
	sockAddr.sim_addr.s_addr=inet_addr("127.0.0.1");
	sockAddr.sin_port=htons(1234);
	bind(SOCKET servSock,(SOCKADDR*)&sockAddr,sizeof(SOCKADDR));
	listen(servSock,20);
	SOCKADDR clntAddr;
	int nSize=sizeof(SOCKADDR);
	SOCKET clntSock=accept(servSock,(SOCKADDR*)&clntAddr,&nSize);

	char buffer[BUF_SIZE];
	int strlen=recv(clntSock,buffer,BUF_SIZE,0);
	send(clntSock,buffer,strlen,0);
	closesocket(clntSock);
	closesocket(servSock);
	WSACleanup();
	return 0;
}