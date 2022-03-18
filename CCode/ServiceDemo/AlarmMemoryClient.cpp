#include "stdafx.h"


void AlarmMemoryClient(){

	HANDLE hMapFile;
	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "LogShareMemory");
	
	AlarmStruct *SMvector = (AlarmStruct*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	AppDataLog(SMvector->ProName, SMvector->Data);

	cout << "Message:" << SMvector->Data.Message << endl;
	printf("Time:%2d:%2d\tDemoCount:%d\n", SMvector->Data.CreateTime.wMinute, SMvector->Data.CreateTime.wSecond, SMvector->Data.DemoCount);
	printf("Status:%d\n", SMvector->Data.Status);

	SMvector->Data.Status = SETTLED;
		printf("Status:%d\n", SMvector->Data.Status);


	UnmapViewOfFile(SMvector);

	CloseHandle(hMapFile);

}
HANDLE hMapVector;
vector<AlarmStruct> *SMvector;
void VectorInit(){
	
	hMapVector = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, "VectorShareMemory");
	SMvector = (vector<AlarmStruct> *)MapViewOfFile(hMapVector, FILE_MAP_ALL_ACCESS, 0, 0, 0);

}
void End(){
	UnmapViewOfFile(SMvector);

	CloseHandle(hMapVector);
}
void VectorMemory(){
	cout << "ÐÅºÅËÄ´¥·¢"<< endl;

	cout <<"VectorSize:"<< SMvector->size() << endl;

	//for (auto iter = SMvector->begin(); iter < SMvector->end(); iter++){
	//	cout << "Message:" << (iter)->Data.Message << endl;
	//}
	for (auto iter = (*SMvector).begin(); iter < (*SMvector).end(); iter++){

		//cout << "iterSize:" << sizeof(iter) << endl;
		//cout << "DemoCount:" << iter->Data.DemoCount << endl;
		//cout << "Address:" << &iter << endl;
		//cout << "Address:" << iter->Data.DemoCount << endl;
	}
}