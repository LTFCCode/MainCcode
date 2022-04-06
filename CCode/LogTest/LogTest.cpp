// LogTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Socket_Tools.h"
#define SERVICE_NAME "LOG"

#define SLEEP_TIME 5000 //间隔时间

#define FILE_PATH "C:\\log.txt" //信息输出文件

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
	servicestatus.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_STOP;//在本例中只接受系统关机和停止服务两种控制命令
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
	//向SCM 报告运行状态
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
	WriteToLog("进入Log");
	DWORD   dwIndex;
	HANDLE hGetEvent[EVENTSIZE];

	SECURITY_DESCRIPTOR sd;
	::InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	::SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE;
	sa.lpSecurityDescriptor = &sd;

	::CreateEvent(&sa, FALSE, FALSE, "Global\\HF");//参数二 TRUE人工复位，FALSE 接到触发后自动复位
	::CreateEvent(&sa, FALSE, FALSE, "Global\\HS");//参数三 TRUE 初始化置位  FALSE初始化不置位
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
		WriteToLog("1不存在");
		if (!::CreateDirectory(LOGADDRESS, NULL))
		{
		}
		else
		{
			WriteToLog("1创建成功");
		}
	}
	TCHAR AimDir[MAX_PATH];
	SYSTEMTIME FileTime;
	::GetLocalTime(&FileTime);

	_stprintf_s(AimDir, MAX_PATH, _T("%s\\%04d-%02d-%02d.txt"), LOGADDRESS, FileTime.wYear, FileTime.wMonth, FileTime.wDay);
	if (::GetFileAttributes(AimDir) == 0xFFFFFFFF)
	{
		WriteToLog("2不存在");
		if (!::GetFileAttributes(AimDir))
		{
		}
		else
		{
			WriteToLog("2创建成功");
		}
	}


	HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "LogShareMemory");
	LPVOID client_lpBase;
	FILE* fp = nullptr;

	if (hMapFile)
	{
		WriteToLog("创建成功");
		client_lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (client_lpBase)
		{
			WriteToLog("map成功");
		}
	}
	else
	{
		WriteToLog((char*)GetLastError());
		WriteToLog("创建失败");
	}
	sLOG* test = ((sLOG*)client_lpBase);
	while (true)
	{
		WriteToLog("进入循环");
		dwIndex = WaitForMultipleObjects(EVENTSIZE, hGetEvent, FALSE, INFINITE);
		switch (dwIndex)
		{
		case WAIT_TIMEOUT:
			WriteToLog("超时");
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
			WriteToLog("信号五触发");
			_tfopen_s(&fp, AimDir, _T("a+"));
			if (fp != nullptr)
			{
				WriteToLog("打开日志文件成功");
				_ftprintf_s(fp, "%s\t%d:%d:%d:%d\t%s\n", test->sender, test->sendtime.wHour, test->sendtime.wMinute, test->sendtime.wSecond,
					test->sendtime.wMilliseconds, test->data);
				fclose(fp);
			}
			else
			{
				WriteToLog("打开日志文件失败");
			}
			break;
		default:
			break;
		}
	}
	fclose(fp);
	return 0;

}

