#include <WS2tcpip.h>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
//#include "afxwin.h"
#include <string.h>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <process.h>
#include <WinSock2.h>
#include <thread>
#include <mutex>
#include <map>

#pragma comment(lib,"ws2_32.lib")
#define SERVER_IP "192.168.100.80"
#define PORT 4119
#define LISTEN_NUM 10
#define NAMESIZE 24
typedef struct
{
	int i_data[100];
	float f_data[100];
	char s_data[256];
}datatype;
typedef struct MyStruct                                           //SysInfo结构体声明
{
	int WrongTime;
	int LogInStatus;
	int SendMessageStatus;
	SYSTEMTIME sendtime;
	SYSTEMTIME revtime;
	SOCKET sender;
	SOCKET recever;
	char UserName[NAMESIZE];
	char Password[NAMESIZE];
	char AimUser[NAMESIZE];
	char FeedbackMessage[256];
	char SendToServer[256];
	char OnLine_User[256];
}dSysInfo;