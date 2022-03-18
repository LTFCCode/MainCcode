// ServiceBase.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
HANDLE	WaitHandle[5];

int WorkInit(){
	WaitHandle[0] = CreateEvent(NULL, FALSE, FALSE, "Global\\HF");//参数二 TRUE人工复位，FALSE 接到触发后自动复位
	WaitHandle[1] = CreateEvent(NULL, FALSE, FALSE, "Global\\HS");//参数三 TRUE 初始化置位  FALSE初始化不置位
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

