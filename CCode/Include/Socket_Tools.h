#pragma once
#include <stdio.h>
#include <tchar.h>
#include <WS2tcpip.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <process.h>
#include <WinSock2.h>
#include <thread>
#include <mutex>
#include <string.h>
#include <cstring>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <list>
#include <sys/types.h>
#include <io.h>
#include <random>
#include <algorithm> //sort
using namespace std;
#pragma comment(lib,"ws2_32.lib")
#define SERVER_IP "192.168.100.80"
#define PORT 4119
#define LISTEN_NUM 10
#define NAMESIZE 24
#define BUF_SIZE 838860
#define SOCKETSHAREMEMORY "SocketShareMemory"
#define LOGSHAREMEMORY "LogShareMemory"
#define LOGADDRESS "E:\\CCodeSSH\\Log"
#define EVENTSIZE 5

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
typedef struct
{
	char sender[48];
	char data[256];
	SYSTEMTIME sendtime;
}sLOG;
void writelog(char * data, char* function);