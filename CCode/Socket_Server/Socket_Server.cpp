// Socket_Server.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "Socket_Tools.h"

HANDLE hMapLogFile;
LPVOID Log_lpBase;
HANDLE WaitHandle[5];
sLOG *Log;
int _tmain(int argc, _TCHAR* argv[])
{

	//init_Server();
	//Server();
	SocketText();
	system("pause");
	return 0;
}

