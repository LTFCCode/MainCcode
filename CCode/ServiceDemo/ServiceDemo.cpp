// Service_Demo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

TCHAR InitData[MAX_PATH] = "��ʼ���ɹ�";


HANDLE       dcSeqEvent;
TestStruct Alarm;
int MakeFileInit(){

	MakeFile(MakeDataFile, "Demo", InitData);
	cout << "Data��ʼ���ɹ�" << endl;
	
	MakeFile(MakeLogFile, "Demo", InitData);
	cout << "Log��ʼ���ɹ�" << endl;

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
	//hGetEvent[0] = CreateEvent(NULL, FALSE, FALSE, "Global\\HF");//������ TRUE�˹���λ��FALSE �ӵ��������Զ���λ
	//hGetEvent[1] = CreateEvent(NULL, FALSE, FALSE, "Global\\HS");//������ TRUE ��ʼ����λ  FALSE��ʼ������λ
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
			AlarmLog(ProName, "���󱣳�δ���źŵ�״̬�����涨�ĵȴ���ʱʱ���Ѿ�����", UNSUCCESSED);
			break;
		case WAIT_FAILED:
			AlarmLog(ProName, GetLastError(), UNSUCCESSED);
			break;
		case WAIT_OBJECT_0:

			AlarmLog(ProName, "�ź�һ����", SUCCESSED);
			MakeFileInit();
			break;
		case WAIT_OBJECT_0 + 1:

			AlarmLog(ProName, "�źŶ�����", SUCCESSED);
			SharedMemoryClient();
			break;
		case WAIT_OBJECT_0 + 2:

			AlarmLog(ProName, "�ź�������", SUCCESSED);
			AlarmMemoryClient();
			break;
		case WAIT_OBJECT_0 + 3:

			AlarmLog(ProName, "�ź��Ĵ���", SUCCESSED);
			VectorMemory();
			break;
		case WAIT_OBJECT_0 + 4:

			AlarmLog(ProName, "�ź��崥��", SUCCESSED);
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

