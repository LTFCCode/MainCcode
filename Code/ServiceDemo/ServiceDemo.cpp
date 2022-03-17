// Service_Demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

TCHAR InitData[MAX_PATH] = "初始化成功";


HANDLE       dcSeqEvent;
TestStruct Alarm;
int MakeFileInit(){

	MakeFile(MakeDataFile, "Demo", InitData);
	cout << "Data初始化成功" << endl;
	
	MakeFile(MakeLogFile, "Demo", InitData);
	cout << "Log初始化成功" << endl;

	return TRUE;
}
void SharedMain(){
	DWORD   dwIndex;
	HANDLE hGetEvent[EVENTSIZE];
	hGetEvent[0] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\HF");
	hGetEvent[1] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\HS");
	hGetEvent[2] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\Alarm");
	hGetEvent[3] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\Vector");
	hGetEvent[4] = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\MFC");
	//hGetEvent[0] = CreateEvent(NULL, FALSE, FALSE, "Global\\HF");//参数二 TRUE人工复位，FALSE 接到触发后自动复位
	//hGetEvent[1] = CreateEvent(NULL, FALSE, FALSE, "Global\\HS");//参数三 TRUE 初始化置位  FALSE初始化不置位
	TCHAR ProName[MAX_PATH];
	_stprintf_s(ProName, MAX_PATH, _T("MainThread"));
	int status = MakeFileInit();
	VectorInit();
	while (status==TRUE)
	{
		dwIndex = WaitForMultipleObjects(EVENTSIZE, hGetEvent, FALSE, INFINITE);//INFINITE;
		switch (dwIndex)
		{
		case WAIT_TIMEOUT:
			AlarmLog(ProName, "对象保持未发信号的状态，但规定的等待超时时间已经超过", UNSUCCESSED);
			break;
		case WAIT_FAILED:
			AlarmLog(ProName, GetLastError(), UNSUCCESSED);
			break;
		case WAIT_OBJECT_0:

			AlarmLog(ProName, "信号一触发", SUCCESSED);
			MakeFileInit();
			break;
		case WAIT_OBJECT_0 + 1:

			AlarmLog(ProName, "信号二触发", SUCCESSED);
			SharedMemoryClient();
			break;
		case WAIT_OBJECT_0 + 2:

			AlarmLog(ProName, "信号三触发", SUCCESSED);
			AlarmMemoryClient();
			break;
		case WAIT_OBJECT_0 + 3:

			AlarmLog(ProName, "信号四触发", SUCCESSED);
			VectorMemory();
			break;
		case WAIT_OBJECT_0 + 4:

			AlarmLog(ProName, "信号五触发", SUCCESSED);
			MFCWork();
			break;
		default:
			break;
		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	//MakeFileInit();
	SharedMain();
	///Thread();
	//Demo_Printf();

	return 0;
}

