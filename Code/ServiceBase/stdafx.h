// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "targetver.h"

#include <tchar.h>
#include<sys/types.h>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <thread>
#include<vector>
#include<list>
#include<mutex>

using namespace std;
#define MakeDataFile (1) 
#define MakeLogFile (2) 
#define EMPTY (3579)

#define BUF_SIZE 838860
#define STRUCT_SIZE 100
#define UNINITIALIZED 9999
#define UNSETTLED 8888
#define INITIALIZED 8887
#define SETTLED 8886

#define SUCCESSED 918
#define UNSUCCESSED 919
#ifdef __MAIN__
#    define EXTERNSW
#else
#    define EXTERNSW extern
#endif
typedef struct {
	TCHAR Message[MAX_PATH];
	SYSTEMTIME CreateTime;
	int DemoCount;
	int Status;
}TestStruct;

typedef struct{
	TestStruct Data[STRUCT_SIZE];
	int SharedMemoryStatus;
}MainStruct;

void MakeFile(int FileType = MakeLogFile, TCHAR *FileName = "Demodata", TCHAR *Data = "\n");
void AppLog(TCHAR* ProName, TestStruct AimData);
void AppData(TCHAR* ProName, TestStruct AimData);
void AppDataLog(TCHAR* ProName, TestStruct AimData);
void Thread();

void SharedMemoryClient();

#ifndef _COMM_H__
#define _COMM_H__
#endif

#define PATHNAME "."
#define PROJ_ID 0x6666

int CreateShm(int size);
int DestroyShm(int shmid);
int GetShm(int size);

string DwordToString(DWORD val);
DWORD StringToDword(string val);

void AlarmLog(TCHAR *ProName, char *message, int status);
void AlarmLog(TCHAR *ProName, DWORD message, int status);
#ifndef First
#define First

#endif
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
