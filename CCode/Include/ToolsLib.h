#pragma once
using namespace std;
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <tchar.h>
#include <map>
#include <vector>
#include <stack>
#include <tuple>
#include <string>
#include <windows.h>
#include <thread>
#include "io.h"
#include "ObjBase.h"
#include <direct.h>
#include <time.h>
#include <utility>
#include <ctime>
#include <random>
#include <stdarg.h>

#include <cctype>//toupper/tolower
#include <algorithm>//transform

#define _CRT_SECURE_NO_WARNINGS

#define TString std::string
#define EXCEL_PATH "E:\\CCode\\Tools\\TestExcel\\*.xlsx"
#define EXCEL_PATH_UP "E:\\CCode\\Tools\\TestExcel\\"
#define LOCAL_TOOLS "E:\\CCode\\ServiceDemo\\ReadExcel\\Tools\\"
#define Log_PATH  "E:\\CCode\\ServiceDemo\\ReadExcel\\Log.log"
#define FTP_PATH  "E:\\CCode\\ServiceDemo\\ReadExcel\\Tools\\FTP.json"




typedef long long Time;

string getJsonValue(string data);
stack<string> split(string *data, string aim);
int deletestring(string *data, string aim);
int getString(string data, string aim, int *sum, int num = 1);
double elapsedTime(long long time1, long long time2);
void printSystemTime(char* log, SYSTEMTIME time);
SYSTEMTIME OnTime64toSystemTime(__time64_t& itime);
double GetEndTime(SYSTEMTIME startpoint);
void Log(char *function_name, string log, ...);
string Upper(string data);
string Lower(string data);
string getGuid();

