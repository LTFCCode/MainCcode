// LogTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Socket_Tools.h"

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD   dwIndex;
	HANDLE	WaitHandle[EVENTSIZE];
	HANDLE hGetEvent[EVENTSIZE];

	WaitHandle[0] = CreateEvent(NULL, FALSE, FALSE, "Global\\HF");//参数二 TRUE人工复位，FALSE 接到触发后自动复位
	WaitHandle[1] = CreateEvent(NULL, FALSE, FALSE, "Global\\HS");//参数三 TRUE 初始化置位  FALSE初始化不置位
	WaitHandle[2] = CreateEvent(NULL, FALSE, FALSE, "Global\\Alarm");
	WaitHandle[3] = CreateEvent(NULL, FALSE, FALSE, "Global\\Vector");
	WaitHandle[4] = CreateEvent(NULL, FALSE, FALSE, "Global\\LOG");

	hGetEvent[0] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\HF");
	hGetEvent[1] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\HS");
	hGetEvent[2] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\Alarm");
	hGetEvent[3] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\Vector");
	hGetEvent[4] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\LOG");

	CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, SOCKETSHAREMEMORY);
	CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, LOGSHAREMEMORY);
	CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, "VectorShareMemory");

	HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, LOGSHAREMEMORY);
	LPVOID client_lpBase;


	if (::GetFileAttributes(LOGADDRESS) == 0xFFFFFFFF)
	{
		printf("%s不存在\n", LOGADDRESS);
		if (!::CreateDirectory(LOGADDRESS, NULL))
		{
		}
		else
		{
			printf("%s创建成功\n", LOGADDRESS);
		}
	}
	TCHAR AimDir[MAX_PATH];
	SYSTEMTIME FileTime;
	::GetLocalTime(&FileTime);

	_stprintf_s(AimDir, MAX_PATH, _T("%s\\%04d-%02d-%02d.txt"), LOGADDRESS, FileTime.wYear, FileTime.wMonth, FileTime.wDay);
	if (::GetFileAttributes(AimDir) == 0xFFFFFFFF)
	{
		printf("%s不存在\n", AimDir);
		if (!::GetFileAttributes(AimDir))
		{
		}
		else
		{
			printf("%s创建成功\n", AimDir);
		}
	}

	FILE* fp = nullptr;

	if (hMapFile)
	{
		client_lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	}
	sLOG* test = ((sLOG*)client_lpBase);
	while (true)
	{
		dwIndex = WaitForMultipleObjects(EVENTSIZE, WaitHandle, FALSE, INFINITE);
		switch (dwIndex)
		{
		case WAIT_TIMEOUT:
			printf("对象保持未发信号的状态，但规定的等待超时时间已经超过\n");
			break;
		case WAIT_FAILED:
			printf("%s\n",GetLastError());
			break;
		case WAIT_OBJECT_0:
			printf("信号一触发\n");
			printf("%s\t%s\n", test->sender, test->data);
			break;
		case WAIT_OBJECT_0 +1:
			printf("信号二触发\n");
			printf("%s\t%s\n", test->sender, test->data);
			break;
		case WAIT_OBJECT_0 +2:
			printf("信号三触发\n");
			printf("%s\t%s\n", test->sender, test->data);
			break;
		case WAIT_OBJECT_0 +3:
			printf("信号四触发\n");
			printf("%s\t%s\n", test->sender, test->data);
			break;
		case WAIT_OBJECT_0 +4:
			printf("信号五触发\n");
			printf("%s\t%d:%d:%d:%d\t%s\n", test->sender, test->sendtime.wHour, test->sendtime.wMinute, test->sendtime.wSecond, 
				test->sendtime.wMilliseconds,test->data);
			_tfopen_s(&fp, AimDir, _T("a+"));
			if (fp != nullptr)
			{
				_ftprintf_s(fp, "%s\t%d:%d:%d:%d\t%s\n", test->sender, test->sendtime.wHour, test->sendtime.wMinute, test->sendtime.wSecond,
					test->sendtime.wMilliseconds, test->data);
				fclose(fp);
			}
			else
			{
				printf("打开日志文件失败 %s\n",AimDir);
			}
			break;
		default:
			break;
		}
	}
	fclose(fp);
	system("pause");
	return 0;
}

