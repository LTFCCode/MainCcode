#include "stdafx.h"

extern TCHAR AimDir[MAX_PATH];
extern TCHAR InitData[MAX_PATH];
char ErrorList[10][MAX_PATH] = {"�����ɹ����","���ܴ���","ϵͳ�Ҳ���ָ�����ļ�","ϵͳ�Ҳ���ָ����·��",
	"ϵͳ�޷����ļ�","�ܾ�����","�����Ч","�洢���ƿ鱻��",
	"�洢�ռ䲻�㣬�޷����������","�洢���ƿ��ַ��Ч"};

void AppData(TCHAR *ProName,TestStruct AimData){

	TCHAR ResultDir[MAX_PATH];
	TCHAR DataType[MAX_PATH] = "csv";
	FILE* fp = NULL;
	int FileExistFlag = TRUE;

	_stprintf_s(ResultDir, MAX_PATH, _T("%s\\Data\\%s.%s"), AimDir, ProName, DataType);

	if (::GetFileAttributes(ResultDir) != INVALID_FILE_ATTRIBUTES)
	{
	}
	else
	{
		FileExistFlag = FALSE;
		printf("%s������\n", ResultDir);
		MakeFile(MakeDataFile, ProName, ResultDir);
		cout << "Data��ʼ���ɹ�" << endl;
		MakeFile(MakeLogFile, ProName, ResultDir);
		cout << "Log��ʼ���ɹ�" << endl;
	}

restart:
	_tfopen_s(&fp, ResultDir, _T("a+"));

	if (fp == NULL)
	{
		printf("AppData���ļ�ʧ��%s,ProName:%s\n", ResultDir, ProName);
		Sleep(3000);
		goto restart;
	}
	else if (FileExistFlag == FALSE){
		printf("%s�����ɹ�\n", ResultDir);
		FileExistFlag = TRUE;

	}

	_ftprintf_s(fp, _T("CreateTime,%04d,%02d-%02d,%02d:%02d:%02d,\n"),
		AimData.CreateTime.wYear, AimData.CreateTime.wMonth, AimData.CreateTime.wDay, 
		AimData.CreateTime.wHour, AimData.CreateTime.wMinute, AimData.CreateTime.wSecond);

	_ftprintf_s(fp, _T("Message,%s\n"),AimData.Message);
	_ftprintf_s(fp, _T("DemoCount,%d\n"), AimData.DemoCount);

	fclose(fp);
}
void AppLog(TCHAR *ProName,TestStruct AimData){

	TCHAR ResultDir[MAX_PATH];
	TCHAR LogType[MAX_PATH] = "txt";
	FILE* fp = NULL;
	int FileExistFlag=TRUE;

	_stprintf_s(ResultDir, MAX_PATH, _T("%s\\Log\\%s.%s"), AimDir, ProName, LogType);

	if (::GetFileAttributes(ResultDir) != INVALID_FILE_ATTRIBUTES)
	{
	}
	else
	{
		FileExistFlag =FALSE;
		printf("%s������\n", ResultDir);
		MakeFile(MakeDataFile, ProName, ResultDir);
		cout << "Data��ʼ���ɹ�" << endl;
		MakeFile(MakeLogFile, ProName, ResultDir);
		cout << "Log��ʼ���ɹ�" << endl;
	}
	_tfopen_s(&fp, ResultDir, _T("a+"));

	if (fp == NULL)
	{
		printf("AppLog���ļ�ʧ��%s,ProName:%s\n", ResultDir, ProName);
	}
	else if (FileExistFlag == FALSE){
		printf("%s�����ɹ�\n", ResultDir);
		FileExistFlag = TRUE;

	}

	_ftprintf_s(fp, _T("Time\t%04d-%02d-%02d\t%02d:%02d:%02d\n"),
		AimData.CreateTime.wYear, AimData.CreateTime.wMonth, AimData.CreateTime.wDay,
		AimData.CreateTime.wHour, AimData.CreateTime.wMinute, AimData.CreateTime.wSecond);

	_ftprintf_s(fp, _T("Message:\t%s\tDemoCount:%d\n"), AimData.Message,AimData.DemoCount);

	fclose(fp);
}
void AppDataLog(TCHAR* ProName,TestStruct AimData){
	AppLog(ProName, AimData);
	AppData(ProName,AimData);
}
void AlarmLog(TCHAR *ProName, char *message,int status){
	TestStruct Alarm;
	_stprintf_s(Alarm.Message, MAX_PATH, message);
	GetLocalTime(&Alarm.CreateTime);
	Alarm.DemoCount = status;
	Alarm.Status = status;
	AppLog(ProName, Alarm);
}
void AlarmLog(TCHAR *ProName, DWORD message, int status){
	TestStruct Alarm;


	if (message<=9 &&message>=0){
		_stprintf_s(Alarm.Message, MAX_PATH, ErrorList[message]);
	}
	else
	{
		_stprintf_s(Alarm.Message, MAX_PATH, "LastError:");
		_stprintf_s(Alarm.Message, MAX_PATH, (DwordToString(message)).c_str());
	}
	

	GetLocalTime(&Alarm.CreateTime);
	Alarm.DemoCount = status;
	Alarm.Status = status;
	AppLog(ProName, Alarm);
}