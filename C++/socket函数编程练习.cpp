#include<iostream>
#include<winsocks2>
#include<WinSock2.h>
#include<stdlib.h>
#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 100
int main()
{
	WSADATA wasData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	SOCKET sockclient=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	sockaddr_in sockAddr;
	memset(&sockAddr,0,sizeof(sockaddr_in));
	sockAddr.sin_family=PF_INET;
	sockAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	sockAddr.sin_port=htons(1234);
	connet(sockclient,(SOCKADDR*)&sockAddr,sizeof(SOCKADDR));
	char bufsend[BUF_SIZE]={0};
	cout<<"input a string:"<<endl;
	cin>>bufsend;
	send(sockclient,bufsend,strlen(bufsend),0);
	char bufRecv[BUF_SIZE]={0};
	recv(sock,bufRecv,BUF_SIZE,0);
	cout<<"message from server"<<endl;
	closesocket(sockclient);
	WSACleanup();
	system("pause");
	return 0;
}