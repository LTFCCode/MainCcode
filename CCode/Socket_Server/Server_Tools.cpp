#include "stdafx.h"
#include "Socket_Tools.h"


int client_num = 0;
datatype *data = new datatype;
LPVOID lpBase;

extern HANDLE hMapLogFile;
extern LPVOID Log_lpBase;
extern HANDLE WaitHandle[5];
extern sLOG *Log;
const char * inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
	const u_char *p = (const u_char *)addrptr;
	if (family == AF_INET) {
		char temp[INET_ADDRSTRLEN];
		sprintf(temp, "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
		if (strlen(temp) >= len){
			errno = ENOSPC;
			return (NULL);
		}
		strcpy(strptr, temp);
		return (strptr);
	}
	errno = EAFNOSUPPORT;
	return (NULL);
}
void Accpet_Thread(SOCKET socket_client)
{
	dSysInfo SysInfo;
	int result;
	SysInfo.recever = socket_client;
	datatype* client_data = nullptr;
	HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, SOCKETSHAREMEMORY);

	if (hMapFile) {
		LPVOID client_lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		client_data = (datatype*)client_lpBase;
	}
	while (true)
	{
		result = recv(socket_client, (char *)&SysInfo, sizeof(dSysInfo), 0);
		if (result <= 0)
		{
			switch (result)
			{
			case -1:
				printf("%s 断开连接,其余连接数:%d\n", SysInfo.UserName, client_num);
				closesocket(socket_client);
				client_num--;
				break;
			}

			break;
		}
		sprintf(Log->data, "%s\t%d:%d:%d:%d\t%s\n", SysInfo.UserName, SysInfo.sendtime.wHour, SysInfo.sendtime.wMinute, SysInfo.sendtime.wSecond, SysInfo.sendtime.wMilliseconds,
			client_data->s_data);
		printf("%s\n", Log->data);
		writelog(Log->data, __FUNCTION__);
		GetLocalTime(&SysInfo.revtime);
		send(socket_client, (char *)&SysInfo, sizeof(dSysInfo), 0);
	}
}

void Server()
{
	printf("AddSocket线程启动\n");

	WSADATA wsaData;
	char ipClient[16];
	sockaddr_in clientAddr = { 0 };
	int nSize = sizeof(SOCKADDR);

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET socket_server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sockaddr;
	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	sockaddr.sin_port = htons(PORT);
	::bind(socket_server, (SOCKADDR*)&sockaddr, sizeof(sockaddr));
	int rev = listen(socket_server, LISTEN_NUM);
	if (rev == SOCKET_ERROR)
	{
		printf("侦听失败\n");
		closesocket(socket_server);
	}
	while (true)
	{
		SOCKET socket_client = accept(socket_server, (struct sockaddr*)&clientAddr, &nSize);
		if (socket_client == INVALID_SOCKET)
		{
			printf("无效socket\n");
			continue;;
		}
		client_num++;
		inet_ntop(AF_INET, &clientAddr.sin_addr, ipClient, sizeof(ipClient));
		printf("收到%s访问 当前用户数:%d\n", ipClient, client_num);
		thread accept_thread(Accpet_Thread, socket_client);
		accept_thread.detach();
	}

}
void SocketText()
{
	WSADATA wsaData;
	char ipClient[16];
	sockaddr_in clientAddr = { 0 };
	int nSize = sizeof(SOCKADDR);
	int result;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET socket_server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sockaddr;
	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.S_un.S_addr = inet_addr("192.168.22.104");
	sockaddr.sin_port = htons(5432);
	::bind(socket_server, (SOCKADDR*)&sockaddr, sizeof(sockaddr));
	int rev = listen(socket_server, 10);
	if (rev == SOCKET_ERROR)
	{
		printf("侦听失败\n");
		closesocket(socket_server);
	}
	while (true)
	{
		SOCKET socket_client = accept(socket_server, (struct sockaddr*)&clientAddr, &nSize);
		if (socket_client == INVALID_SOCKET)
		{
			printf("无效socket\n");
			continue;;
		}
		inet_ntop(AF_INET, &clientAddr.sin_addr, ipClient, sizeof(ipClient));
		printf("收到%s访问\n", ipClient);

		send(socket_client, "Connect Success\n\r", sizeof("Connect Success\n\r"), 0);

		send(socket_client, "password:", sizeof("password:"), 0);
		char data[24] = "";
		while (true)
		{
			char recev;
			result = recv(socket_client, (char *)&recev, sizeof(recev), 0);
			if (result <= 0)
			{
				switch (result)
				{
				case -1:
					printf("Client Close\n");
					closesocket(socket_client);
					break;
				}

				break;
			}
			if (recev == '\r')
			{
				printf("收到\\r\n");
			}
			else if (recev == '\n')
			{
				printf("收到\\n\n");
				printf("%s/n",data);
				if (strcmp(data,"liu172")==0)
				{
					send(socket_client, "\r\nLoad Success\r\n", sizeof("\r\nLoad Success\r\n"), 0);
				}
				else
				{
					send(socket_client, "\r\nERROR PASSWORD\r\n", sizeof("\r\nERROR PASSWORD\r\n"), 0);
					send(socket_client, "password:", sizeof("password:"), 0);
				}
				sprintf(data, "");
			}
			else
			{
				sprintf(data, "%s%c", data,recev);
			}
		}
	}
}