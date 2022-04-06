#include "stdafx.h"
#include "Socket_Tools.h"

extern HANDLE hMapLogFile;
extern LPVOID Log_lpBase;
extern HANDLE WaitHandle[5];
extern sLOG *Log;
void init_Server()
{

	WaitHandle[0] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\HF");
	WaitHandle[1] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\HS");
	WaitHandle[2] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\Alarm");
	WaitHandle[3] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\Vector");
	WaitHandle[4] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\LOG");

	CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, SOCKETSHAREMEMORY);
	CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, LOGSHAREMEMORY);
	CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, "VectorShareMemory");

	hMapLogFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, LOGSHAREMEMORY);

	if (hMapLogFile) 
	{
		Log_lpBase = MapViewOfFile(hMapLogFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	}
	else
	{
		printf("Init LOGMEMORY Failed\n");
		//return;
	}
	Log = (sLOG*)Log_lpBase;
	system("pause");
	writelog("��ʼ���ɹ�1",__FUNCTION__);
	system("pause");
	writelog("��ʼ���ɹ�2", __FUNCTION__);
	system("pause");
	writelog("��ʼ���ɹ�3", __FUNCTION__);
	system("pause");
	writelog("��ʼ���ɹ�4", __FUNCTION__);
}