#include "stdafx.h"

extern HANDLE hMapLogFile;
extern LPVOID Log_lpBase;
extern HANDLE WaitHandle[5];
extern sLOG *Log;

void start()
{
	WSADATA wsaData;
	string IpAddress;
	dSysInfo SysInfo;
	datatype *data = nullptr;
	LPVOID lpBase;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SysInfo.sender = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);                 
	sockaddr_in sockAddr;
	sockAddr.sin_family = PF_INET;

	sockAddr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	sockAddr.sin_port = htons(PORT);
	int LogInStatus = connect(SysInfo.sender, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));                    
	if (LogInStatus == 0)
	{
		printf("���ӳɹ�\n");
	}
	else if (LogInStatus == SOCKET_ERROR){
		printf("����ʧ��\n");
		return;
	}
	printf("Username:");
	scanf("%s", SysInfo.UserName);

	HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, SOCKETSHAREMEMORY);


	if (hMapFile) {
		lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		data = (datatype*)lpBase;
	}
	printf("%s\n",data->s_data);
	while (true)
	{
		GetLocalTime(&SysInfo.sendtime);
		scanf("%s", data->s_data);
		lpBase = (void*)&data;
		send(SysInfo.sender, (char *)&SysInfo, sizeof(dSysInfo), 0);
		recv(SysInfo.sender, (char *)&SysInfo, sizeof(dSysInfo), 0);
		printf("%s\t%d:%d:%d:%d\n", SysInfo.UserName, SysInfo.revtime.wHour, SysInfo.revtime.wMinute, SysInfo.revtime.wSecond, SysInfo.revtime.wMilliseconds);
		system("pause");
	}

	// ����ļ�ӳ��
	UnmapViewOfFile(lpBase);
	// �ر��ڴ�ӳ���ļ�������
	CloseHandle(hMapFile);

	return ;
}