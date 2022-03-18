#include "stdafx.h"


TCHAR BaseDir[MAX_PATH] = "E:\\CCode\\ForTest";
TCHAR AimDir[MAX_PATH];

void MakeFile(int DataFileType, TCHAR *FileName, TCHAR *Data){

	SYSTEMTIME stCharge;
	TCHAR StartDir[MAX_PATH];
	TCHAR ResultDir[MAX_PATH];
	TCHAR FileType[MAX_PATH];
	TCHAR DataType[MAX_PATH];

	::GetLocalTime(&stCharge);

	_stprintf_s(StartDir, MAX_PATH, _T("%s"), BaseDir);
	if (::GetFileAttributes(StartDir) == 0xFFFFFFFF)
	{
		printf("%s不存在\n", StartDir);
		if (!::CreateDirectory(StartDir, NULL))
		{
		}
		else
		{
			printf("%s创建成功\n",StartDir);
		}
	}
	SYSTEMTIME FileTime;
	::GetLocalTime(&FileTime);

	_stprintf_s(AimDir, MAX_PATH, _T("%s\\%04d-%02d-%02d"), StartDir, FileTime.wYear, FileTime.wMonth, FileTime.wDay);
	if (::GetFileAttributes(AimDir) == 0xFFFFFFFF)
	{
		printf("%s不存在\n", AimDir);
		if (!::CreateDirectory(AimDir, NULL))
		{
		}
		else
		{
			printf("%s创建成功\n", AimDir);
		}
	}
	switch (DataFileType)
	{
	case MakeDataFile:
		_stprintf_s(FileType, MAX_PATH, _T("Data"));
		_stprintf_s(DataType, MAX_PATH, _T("csv"));
		break;
	case MakeLogFile:
		_stprintf_s(FileType, MAX_PATH, _T("Log"));
		_stprintf_s(DataType, MAX_PATH, _T("txt"));
		break;
	default:
		break;
	}
	_stprintf_s(StartDir, MAX_PATH, _T("%s\\%s"), AimDir, FileType);

	if (::GetFileAttributes(StartDir) == 0xFFFFFFFF)
	{
		printf("%s不存在\n", StartDir);
		if (!::CreateDirectory(StartDir, NULL))
		{
		}
		else
		{
			printf("%s创建成功\n", StartDir);
		}
	}

	_stprintf_s(ResultDir, MAX_PATH, _T("%s\\%s.%s"), StartDir, FileName, DataType);
	if (::GetFileAttributes(ResultDir) != INVALID_FILE_ATTRIBUTES)
	{
	}
	else
	{
		printf("%s不存在\n", ResultDir);
	}
	FILE* fp = NULL;

	_tfopen_s(&fp, ResultDir, _T("a+"));
	//	"r"
	//	打开以进行读取。如果该文件不存在，或无法找到，fopen_s调用失败。
	//	"w"
	//	打开一个空文件以进行写入。如果该文件存在，其内容将被销毁。
	//	"a"
	//	打开以进行写入 （追加） 而不将新数据写入文件之前删除的 EOF 标记文件的末尾。如果它不存在，则创建该文件。
	//	"r+"
	//	将打开并读取和写入。 （该文件必须存在。
	//	"w+"
	//	打开一个空的文件进行读写。如果该文件存在，其内容将被销毁。
	//	"a+"
	//	将打开并读取文件和追加。追加操作包括删除 EOF 标记的新数据写入到文件并在编写完成后还原 EOF 标记之前。如果它不存在，则创建该文件。

	if (fp == NULL)
	{
		printf("打开文件失败%s\n", ResultDir);
	}
	else{
		printf("%s创建成功\n", ResultDir);

	}

	::GetLocalTime(&FileTime);

	_ftprintf_s(fp, _T("Time,%04d,%02d-%02d,%02d:%02d:%02d,\n"),
		FileTime.wYear, FileTime.wMonth, FileTime.wDay, FileTime.wHour, FileTime.wMinute, FileTime.wSecond);

	_ftprintf_s(fp, _T("%s\n"), Data);

	fclose(fp);
	
}