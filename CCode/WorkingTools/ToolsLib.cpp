#include "stdafx.h"


string HoolString = "sdft%\t";
char s = HoolString[0];
char d = HoolString[1];
char f = HoolString[2];
char t = HoolString[3];
char ASD = HoolString[4];
char T = HoolString[5];
fstream LogOut(Log_PATH, ios::out);

double elapsedTime(long long time1, long long time2)
{
	return ((double)(time2 - time1)) / 10.0 / 1000.0 / 1000.0;
}

void printSystemTime(char* log, SYSTEMTIME time)
{
	printf("%s%d:%d:%d - %d:%d:%d\n", log, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
}

string Upper(string data)
{
	string result = data;
	transform(result.begin(), result.end(), result.begin(), toupper);
	return result;
}
string Lower(string data)
{
	string result = data;
	transform(result.begin(), result.end(), result.begin(), tolower);
	return result;
}
SYSTEMTIME OnTime64toSystemTime(__time64_t& itime)
{
	tm *temptm = new tm;
	_localtime64_s(temptm, &itime);
	SYSTEMTIME st = { 1900 + temptm->tm_year,
		1 + temptm->tm_mon,
		temptm->tm_wday,
		temptm->tm_mday,
		temptm->tm_hour,
		temptm->tm_min,
		temptm->tm_sec,
		0 };
	return st;
}

//删除data中aim返回aim出现的次数
int deletestring(string *data, string aim)
{
	size_t result = data->find(aim);
	if (result != -1)
	{
		data->erase(result, aim.length());
		return deletestring(data, aim) + 1;
	}
	else
	{
		return 0;
	}
}

stack<string> split(string *data, string aim)
{
	stack<string> result;
	int address[20] = {0};
	int time = getString(*data,aim,&address[1]);
	for (int i = 0; i < time;i++)
	{
		int start = address[i];
		int end = address[i + 1] - address[i]-1;
		string test = data->substr(start, end);
		deletestring(&test," ");
		result.push(test);
	}
	return result;
}
string getJsonValue(string data)
{

	size_t i = data.find_first_of(":");
	size_t h = data.find_last_of(",");
	if (i < h && i > 0)
	{
		string aim = data.substr(i, h);
		deletestring(&aim, "\"");
		deletestring(&aim, " ");
		deletestring(&aim, "[");
		deletestring(&aim, "]");
		deletestring(&aim, ",");
		deletestring(&aim, ":");
		return aim;
	}
	else
	{
		return "";
	}

}
double GetEndTime(SYSTEMTIME startpoint)
{
	SYSTEMTIME endpoint;
	GetLocalTime(&endpoint);
	LPFILETIME ft_start_point, ft_end_point;
	SystemTimeToFileTime(&startpoint, (LPFILETIME)&ft_start_point);
	SystemTimeToFileTime(&endpoint, (LPFILETIME)&ft_end_point);
	return ((double)(ft_end_point - ft_start_point))/ 1000.0 / 1000.0;;
}
//判断data中aim出现的次数及位置 sum应为数组下标1且sum[-1] = 0
int getString(string data,string aim,int *sum,int num)
{
	int address = data.find(aim);
	if (address != -1)
	{
		*sum++ = address + sum[-1] +1;
		num = getString(data.substr(data.find(aim) + 1, data.length()), aim, sum, ++num);
	}
	return num;
}
void Log(char *function_name,string log,...)
{
	va_list p;
	va_start(p, log);
	
	SYSTEMTIME stLocal;
	GetLocalTime(&stLocal);	
	if (stLocal.wMilliseconds < 100)
	{
		if (stLocal.wMilliseconds < 10)
		{
			LogOut << stLocal.wHour << ":" << stLocal.wMinute << ":" << stLocal.wSecond << ":00" << stLocal.wMilliseconds << "\t";
		}
		else
		{
			LogOut << stLocal.wHour << ":" << stLocal.wMinute << ":" << stLocal.wSecond << ":0" << stLocal.wMilliseconds << "\t";
		}
	}
	else
	{
		LogOut << stLocal.wHour << ":" << stLocal.wMinute << ":" << stLocal.wSecond << ":" << stLocal.wMilliseconds << "\t";
	}
	LogOut << function_name << "\t";

	for (int i = 0; i < log.length(); i++)
	{
		if (log[i] == ASD)
		{
			if (log[i+1] == s)
			{
				string data = va_arg(p, char*);
				LogOut << data.c_str();
			}
			if (log[i + 1] == d)
			{
				int data = va_arg(p, int);
				LogOut << data;
			}
			if (log[i + 1] == f)
			{
				double data = va_arg(p, double);
				LogOut << data;
			}
			if (log[i + 1] == t)
			{
				SYSTEMTIME data = va_arg(p, SYSTEMTIME);
				LogOut << "开始时间:" << data.wHour << ":" << data.wMinute << ":" << data.wSecond << ":" << data.wMilliseconds << "\t" << "使用时间:" << GetEndTime(data)<<"s";
			}
			if (i<log.length()-1)
			{
				i++;
			}
			else
			{
				LogOut << "%";
				break;
			}
		}
		else
		{
			LogOut << log[i];
		}
	}
	LogOut << endl;
	va_end(p);
}
string getGuid()
{
	GUID guid;
	CoCreateGuid(&guid);
	char cBuffer[64] = { 0 };
	sprintf_s(cBuffer, sizeof(cBuffer),
		"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2,
		guid.Data3, guid.Data4[0],
		guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4],
		guid.Data4[5], guid.Data4[6],
		guid.Data4[7]);
	return string(cBuffer);
}
