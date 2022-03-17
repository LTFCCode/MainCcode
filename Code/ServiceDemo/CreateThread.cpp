#include "stdafx.h"

list<TestStruct> TestQueue;
mutex Demomutex;
TCHAR ProName[MAX_PATH];

string DwordToString(DWORD val)
{
	string cur_str = to_string(long long(val));
	return cur_str;
}


DWORD StringToDword(string val)
{
	DWORD cur_dword;
	sscanf(val.c_str(), "%ul", &cur_dword);
	return cur_dword;
}

void write_demo(){
	TestStruct inputdata;
	while (TRUE){
		cout << "请输入Message:" << endl;
		cin >> inputdata.Message;
		GetLocalTime(&inputdata.CreateTime);
		inputdata.DemoCount = 1;
		inputdata.Status = SUCCESSED;
			{
				std::lock_guard<std::mutex> sbguard(Demomutex);
				TestQueue.push_back(inputdata);
				cout << "插入元素\tMessage:" << inputdata.Message << endl;
			}
			Sleep(100);
		}
	}


void read_demo(){
	_stprintf_s(ProName, MAX_PATH, _T("ReadTestThread"));
	while (TRUE)
	{
		{
			std::lock_guard<std::mutex> sbguard(Demomutex);
			if (!TestQueue.empty())
			{
				TestStruct getdata = TestQueue.front();
				cout << "取出元素\tCreateTime:"<<getdata.CreateTime.wMinute << "-" << getdata.CreateTime.wSecond << endl;
				AppDataLog(ProName,getdata);
				TestQueue.pop_front();
			}
			else{					
			}
		}
		Sleep(300);
	}
}




void Thread()
{

	thread ReadThread(write_demo);
	thread WriteThread(read_demo);

	ReadThread.detach();
	WriteThread.detach();
	while (TRUE){
		Sleep(10000);
		cout << "主线程运行中" << endl;
	}
}
