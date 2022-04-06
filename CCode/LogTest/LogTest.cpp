// LogTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Socket_Tools.h"
#define SERVICE_NAME "LOG"

#define SLEEP_TIME 5000 //���ʱ��

#define FILE_PATH "C:\\log.txt" //��Ϣ����ļ�

bool brun = false;
int Log();
SERVICE_STATUS servicestatus;

SERVICE_STATUS_HANDLE hstatus;

int WriteToLog(char* str);

void WINAPI ServiceMain(int argc, char** argv);

void WINAPI CtrlHandler(DWORD request);

int InitService();

int WriteToLog(char* str)

{
	FILE* pfile;
	fopen_s(&pfile, FILE_PATH, "a+");
	if (pfile == NULL)
	{
		return -1;
	}
	fprintf_s(pfile, "%s\n", str);
	fclose(pfile);
	return 0;
}

void WINAPI ServiceMain(int argc, char** argv)
{
	servicestatus.dwServiceType = SERVICE_WIN32;
	servicestatus.dwCurrentState = SERVICE_START_PENDING;
	servicestatus.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_STOP;//�ڱ�����ֻ����ϵͳ�ػ���ֹͣ�������ֿ�������
	servicestatus.dwWin32ExitCode = 0;
	servicestatus.dwServiceSpecificExitCode = 0;
	servicestatus.dwCheckPoint = 0;
	servicestatus.dwWaitHint = 0;
	hstatus = ::RegisterServiceCtrlHandler(SERVICE_NAME, CtrlHandler);
	if (hstatus == 0)
	{
		WriteToLog("RegisterServiceCtrlHandler failed");
		return;
	}
	WriteToLog("RegisterServiceCtrlHandler success");
	//��SCM ��������״̬
	servicestatus.dwCurrentState = SERVICE_RUNNING;
	SetServiceStatus(hstatus, &servicestatus);	
	Log();
	WriteToLog("service stopped");
}

void WINAPI CtrlHandler(DWORD request)
{

	switch (request)
	{
	case SERVICE_CONTROL_STOP:

		brun = false;

		servicestatus.dwCurrentState = SERVICE_STOPPED;

		break;

	case SERVICE_CONTROL_SHUTDOWN:

		brun = false;

		servicestatus.dwCurrentState = SERVICE_STOPPED;

		break;

	default:

		break;

	}

	SetServiceStatus(hstatus, &servicestatus);
}

void main()
{

	SERVICE_TABLE_ENTRY entrytable[2];

	entrytable[0].lpServiceName = SERVICE_NAME;

	entrytable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;

	entrytable[1].lpServiceName = NULL;

	entrytable[1].lpServiceProc = NULL;

	StartServiceCtrlDispatcher(entrytable);

}
int Log()
{
	WriteToLog("����Log");
	DWORD   dwIndex;
	HANDLE hGetEvent[EVENTSIZE];

	SECURITY_DESCRIPTOR sd;
	::InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	::SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE;
	sa.lpSecurityDescriptor = &sd;

	::CreateEvent(&sa, FALSE, FALSE, "Global\\HF");//������ TRUE�˹���λ��FALSE �ӵ��������Զ���λ
	::CreateEvent(&sa, FALSE, FALSE, "Global\\HS");//������ TRUE ��ʼ����λ  FALSE��ʼ������λ
	::CreateEvent(&sa, FALSE, FALSE, "Global\\Alarm");
	::CreateEvent(&sa, FALSE, FALSE, "Global\\Vector");
	::CreateEvent(&sa, FALSE, FALSE, "Global\\LOG");

	hGetEvent[0] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\HF");
	hGetEvent[1] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\HS");
	hGetEvent[2] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\Alarm");
	hGetEvent[3] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\Vector");
	hGetEvent[4] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\LOG");

	if (::GetFileAttributes(LOGADDRESS) == 0xFFFFFFFF)
	{
		WriteToLog("1������");
		if (!::CreateDirectory(LOGADDRESS, NULL))
		{
		}
		else
		{
			WriteToLog("1�����ɹ�");
		}
	}
	TCHAR AimDir[MAX_PATH];
	SYSTEMTIME FileTime;
	::GetLocalTime(&FileTime);

	_stprintf_s(AimDir, MAX_PATH, _T("%s\\%04d-%02d-%02d.txt"), LOGADDRESS, FileTime.wYear, FileTime.wMonth, FileTime.wDay);
	if (::GetFileAttributes(AimDir) == 0xFFFFFFFF)
	{
		WriteToLog("2������");
		if (!::GetFileAttributes(AimDir))
		{
		}
		else
		{
			WriteToLog("2�����ɹ�");
		}
	}


	HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "LogShareMemory");
	LPVOID client_lpBase;
	FILE* fp = nullptr;

	if (hMapFile)
	{
		WriteToLog("�����ɹ�");
		client_lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (client_lpBase)
		{
			WriteToLog("map�ɹ�");
		}
	}
	else
	{
		WriteToLog((char*)GetLastError());
		WriteToLog("����ʧ��");
	}
	sLOG* test = ((sLOG*)client_lpBase);
	while (true)
	{
		WriteToLog("����ѭ��");
		dwIndex = WaitForMultipleObjects(EVENTSIZE, hGetEvent, FALSE, INFINITE);
		switch (dwIndex)
		{
		case WAIT_TIMEOUT:
			WriteToLog("��ʱ");
			break;
		case WAIT_FAILED:
			WriteToLog((char*)GetLastError());
			break;
		case WAIT_OBJECT_0:
			break;
		case WAIT_OBJECT_0 +1:
			break;
		case WAIT_OBJECT_0 +2:
			break;
		case WAIT_OBJECT_0 +3:
			break;
		case WAIT_OBJECT_0 +4:
			WriteToLog("�ź��崥��");
			_tfopen_s(&fp, AimDir, _T("a+"));
			if (fp != nullptr)
			{
				WriteToLog("����־�ļ��ɹ�");
				_ftprintf_s(fp, "%s\t%d:%d:%d:%d\t%s\n", test->sender, test->sendtime.wHour, test->sendtime.wMinute, test->sendtime.wSecond,
					test->sendtime.wMilliseconds, test->data);
				fclose(fp);
			}
			else
			{
				WriteToLog("����־�ļ�ʧ��");
			}
			break;
		default:
			break;
		}
	}
	fclose(fp);
	return 0;

}

