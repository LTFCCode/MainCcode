#include "stdafx.h"
int client_num = 0;
datatype *data = new datatype;
LPVOID lpBase;
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
	HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "ShareMemory");

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
				printf("%s 断开连接,其余连接数:%d\n", SysInfo.UserName, result);
				closesocket(socket_client);
				client_num--;
				break;
			}

			break;
		}
		printf("%s\t%d:%d:%d:%d\t%s\n", SysInfo.UserName, SysInfo.sendtime.wHour, SysInfo.sendtime.wMinute, SysInfo.sendtime.wSecond, SysInfo.sendtime.wMilliseconds,
			client_data->s_data);
		GetLocalTime(&SysInfo.revtime);
		send(socket_client, (char *)&SysInfo, sizeof(dSysInfo), 0);
	}
}

void start()
{
	printf("AddSocket线程启动\n");

	// 定义共享数据
	datatype *data = new datatype;
	for (int i = 0; i < 100;i++)
	{
		data->i_data[i] = i;
		data->f_data[i] = 0.1f + i;
	}
	strcpy(data->s_data,"test");

	HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(datatype),"ShareMemory");


	lpBase = MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,sizeof(datatype));


	lpBase = (void*)data;

	HANDLE hMapFile_test = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "ShareMemory");
	if (hMapFile_test) {
		LPVOID client_lpBase = MapViewOfFile(hMapFile_test, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		client_lpBase = (void*)data;
	}


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

	UnmapViewOfFile(lpBase);

	CloseHandle(hMapFile);
}