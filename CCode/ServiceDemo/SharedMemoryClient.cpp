#include "stdafx.h"

HANDLE hMapFile;
extern TestStruct Alarm;
void SharedMemoryClient(){
	MainStruct *lpBase = new MainStruct;
	//TCHAR ProName[MAX_PATH];
	//_stprintf_s(ProName, MAX_PATH, __FUNCTION__);//_T("SharedMemoryClient")
	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "DemoShareMemory");
		if (hMapFile) {
			lpBase = (MainStruct*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			lpBase->SharedMemoryStatus = INITIALIZED;
			for (int point = 1; point < STRUCT_SIZE; point++){
				if (lpBase->Data[point].Status == UNSETTLED){

					cout << "Message:" << lpBase->Data[point].Message << endl;
					printf("Time:%2d:%2d\tDemoCount:%d\n", lpBase->Data[point].CreateTime.wMinute, lpBase->Data[point].CreateTime.wSecond, lpBase->Data[point].DemoCount);
					printf("Status:%d\n", lpBase->Data[point].Status);

					AppDataLog(__FUNCTION__, lpBase->Data[point]);

					lpBase->Data[point].Status = SETTLED;
					printf("Status:%d\n", lpBase->Data[point].Status);		
					//break;
				}
			}
			

			UnmapViewOfFile(lpBase);

			CloseHandle(hMapFile);

		}
		else {
			AlarmLog(__FUNCTION__, GetLastError(), UNSUCCESSED);
			AlarmLog(__FUNCTION__, "´ò¿ª¹²ÏíÊ§°Ü", UNSUCCESSED);

		}

	
}