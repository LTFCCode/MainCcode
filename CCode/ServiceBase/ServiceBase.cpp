// ServiceBase.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
HANDLE	WaitHandle[5];

int WorkInit(){
	WaitHandle[0] = CreateEvent(NULL, FALSE, FALSE, "Global\\HF");//������ TRUE�˹���λ��FALSE �ӵ��������Զ���λ
	WaitHandle[1] = CreateEvent(NULL, FALSE, FALSE, "Global\\HS");//������ TRUE ��ʼ����λ  FALSE��ʼ������λ
	WaitHandle[2] = CreateEvent(NULL, FALSE, FALSE, "Global\\Alarm");
	WaitHandle[3] = CreateEvent(NULL, FALSE, FALSE, "Global\\Vector");
	WaitHandle[4] = CreateEvent(NULL, FALSE, FALSE, "Global\\MFC");
	CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, "DemoShareMemory");
	CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, "LogShareMemory");
	CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, "VectorShareMemory");
	return TRUE;
}
int _tmain(int argc, _TCHAR* argv[])
{	
	WorkInit();
	system("pause");
	return 0;
}

