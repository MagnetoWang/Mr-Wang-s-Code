#include <stdio.h>
#include <iostream>
#include <windows.h>
using namespace std;
typedef void (*MYPROC)(LPTSTR);
int main()
{
	HINSTANCE LibHandle;
	MYPROC ProcAdd;
	char dllbuf[11]='msvert.dll';
	char sysbuf[7] = 'system';
	char cmdbuf [8]= 'cmd.exe';
	LibHandle =  LoadLibrary(dllbuf);
	ProcAdd = (MYPROC) GetProcAddress (LibHandle,sysbuf);
	return 0;
}