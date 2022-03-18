#include "stdafx.h"

extern HANDLE hMapLogFile;
extern LPVOID Log_lpBase;
extern HANDLE WaitHandle[5];
extern sLOG *Log;
void writelog(char * data, char* function)
{
	sprintf(Log->sender, function);
	sprintf(Log->data, data);
	GetLocalTime(&Log->sendtime);
	Log_lpBase = (void*)&Log;
	SetEvent(WaitHandle[4]);
}