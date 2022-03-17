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
		printf("%s������\n", StartDir);
		if (!::CreateDirectory(StartDir, NULL))
		{
		}
		else
		{
			printf("%s�����ɹ�\n",StartDir);
		}
	}
	SYSTEMTIME FileTime;
	::GetLocalTime(&FileTime);

	_stprintf_s(AimDir, MAX_PATH, _T("%s\\%04d-%02d-%02d"), StartDir, FileTime.wYear, FileTime.wMonth, FileTime.wDay);
	if (::GetFileAttributes(AimDir) == 0xFFFFFFFF)
	{
		printf("%s������\n", AimDir);
		if (!::CreateDirectory(AimDir, NULL))
		{
		}
		else
		{
			printf("%s�����ɹ�\n", AimDir);
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
		printf("%s������\n", StartDir);
		if (!::CreateDirectory(StartDir, NULL))
		{
		}
		else
		{
			printf("%s�����ɹ�\n", StartDir);
		}
	}

	_stprintf_s(ResultDir, MAX_PATH, _T("%s\\%s.%s"), StartDir, FileName, DataType);
	if (::GetFileAttributes(ResultDir) != INVALID_FILE_ATTRIBUTES)
	{
	}
	else
	{
		printf("%s������\n", ResultDir);
	}
	FILE* fp = NULL;

	_tfopen_s(&fp, ResultDir, _T("a+"));
	//	"r"
	//	���Խ��ж�ȡ��������ļ������ڣ����޷��ҵ���fopen_s����ʧ�ܡ�
	//	"w"
	//	��һ�����ļ��Խ���д�롣������ļ����ڣ������ݽ������١�
	//	"a"
	//	���Խ���д�� ��׷�ӣ� ������������д���ļ�֮ǰɾ���� EOF ����ļ���ĩβ������������ڣ��򴴽����ļ���
	//	"r+"
	//	���򿪲���ȡ��д�롣 �����ļ�������ڡ�
	//	"w+"
	//	��һ���յ��ļ����ж�д��������ļ����ڣ������ݽ������١�
	//	"a+"
	//	���򿪲���ȡ�ļ���׷�ӡ�׷�Ӳ�������ɾ�� EOF ��ǵ�������д�뵽�ļ����ڱ�д��ɺ�ԭ EOF ���֮ǰ������������ڣ��򴴽����ļ���

	if (fp == NULL)
	{
		printf("���ļ�ʧ��%s\n", ResultDir);
	}
	else{
		printf("%s�����ɹ�\n", ResultDir);

	}

	::GetLocalTime(&FileTime);

	_ftprintf_s(fp, _T("Time,%04d,%02d-%02d,%02d:%02d:%02d,\n"),
		FileTime.wYear, FileTime.wMonth, FileTime.wDay, FileTime.wHour, FileTime.wMinute, FileTime.wSecond);

	_ftprintf_s(fp, _T("%s\n"), Data);

	fclose(fp);
	
}