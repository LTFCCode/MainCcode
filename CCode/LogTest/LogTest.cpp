// LogTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Socket_Tools.h"

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD   dwIndex;
	HANDLE	WaitHandle[EVENTSIZE];
	HANDLE hGetEvent[EVENTSIZE];

	WaitHandle[0] = CreateEvent(NULL, FALSE, FALSE, "Global\\HF");//������ TRUE�˹���λ��FALSE �ӵ��������Զ���λ
	WaitHandle[1] = CreateEvent(NULL, FALSE, FALSE, "Global\\HS");//������ TRUE ��ʼ����λ  FALSE��ʼ������λ
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
		printf("%s������\n", LOGADDRESS);
		if (!::CreateDirectory(LOGADDRESS, NULL))
		{
		}
		else
		{
			printf("%s�����ɹ�\n", LOGADDRESS);
		}
	}
	TCHAR AimDir[MAX_PATH];
	SYSTEMTIME FileTime;
	::GetLocalTime(&FileTime);

	_stprintf_s(AimDir, MAX_PATH, _T("%s\\%04d-%02d-%02d.txt"), LOGADDRESS, FileTime.wYear, FileTime.wMonth, FileTime.wDay);
	if (::GetFileAttributes(AimDir) == 0xFFFFFFFF)
	{
		printf("%s������\n", AimDir);
		if (!::GetFileAttributes(AimDir))
		{
		}
		else
		{
			printf("%s�����ɹ�\n", AimDir);
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
			printf("���󱣳�δ���źŵ�״̬�����涨�ĵȴ���ʱʱ���Ѿ�����\n");
			break;
		case WAIT_FAILED:
			printf("%s\n",GetLastError());
			break;
		case WAIT_OBJECT_0:
			printf("�ź�һ����\n");
			printf("%s\t%s\n", test->sender, test->data);
			break;
		case WAIT_OBJECT_0 +1:
			printf("�źŶ�����\n");
			printf("%s\t%s\n", test->sender, test->data);
			break;
		case WAIT_OBJECT_0 +2:
			printf("�ź�������\n");
			printf("%s\t%s\n", test->sender, test->data);
			break;
		case WAIT_OBJECT_0 +3:
			printf("�ź��Ĵ���\n");
			printf("%s\t%s\n", test->sender, test->data);
			break;
		case WAIT_OBJECT_0 +4:
			printf("�ź��崥��\n");
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
				printf("����־�ļ�ʧ�� %s\n",AimDir);
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

