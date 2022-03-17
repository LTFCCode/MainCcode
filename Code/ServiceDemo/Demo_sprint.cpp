#include "stdafx.h"

int MyPrintf(char* Message, ...){

	va_list argp;
	SYSTEMTIME InputTime;
	TestStruct InputStruct;
	const int MessageLength = strlen(Message);//若直接用strlen(Message)做循环条件,Message++会减少strlen(Message)
	//strlen计算从当前指针至'\0'字符串长度,移动Message会影响返回的字符串长度
	int length = 0;
	va_start(argp, Message);
	while (*Message != '\0' ){
		switch (*Message){
		case '\n':
			cout << endl;
			break;
		case '\t':
			cout << "\t";
			break;
		case '\\':
			cout << "\\";
			break;
		case '%':
			Message++;
			length++;
			switch (*Message)
			{
			case 'F':
			case 'f':
				cout << va_arg(argp, double);
				break;

			case 'S'://Struct 传入结构体
				InputStruct = va_arg(argp,TestStruct);
				MyPrintf("\n--------Struct-------\nDemoCount:%d\tStatus:%d\tMessage:%s\tCreateTime:%t\n",
					InputStruct.DemoCount,InputStruct.Status,InputStruct.Message,InputStruct.CreateTime);
				break;
			case 's':
				cout << va_arg(argp, char*);
				break;

			case 'D':
			case 'd':
				cout << va_arg(argp, int);
				break;
			case 'T':
			case 't':
				InputTime = va_arg(argp, SYSTEMTIME);
				MyPrintf("%d-%d,%d:%d\n", InputTime.wMonth, InputTime.wDay, InputTime.wHour, InputTime.wMinute);
				break;
			case '%'://"%%"=="%"	"%%d"=="%d"	"%%%d"=="%数字值"
				cout << "%";
				break;
			default:
				cout << *Message;
				break;
			}
			break;
		default:
			cout << *Message;
			break;
		}
		
		Message++;
		length++;

	}
	va_end(argp);

	return TRUE;
}

int Demo_Printf(){
	int demo_i = 45746;
	double demo_f = 0.1;
	char  demo_c[10] = "TestChar";
	char* demo_message = "Test:\nint:%d\tdouble:%f\tchar:%s\tTime:%t\t%S\n";

	SYSTEMTIME demo_time;
	GetLocalTime(&demo_time);

	TestStruct demo_struct;
	demo_struct.DemoCount = 234345;
	demo_struct.Status = SETTLED;
	_stprintf_s(demo_struct.Message, MAX_PATH, _T("TestStrcut"));
	GetLocalTime(&demo_struct.CreateTime);

	printf(demo_message, demo_i, demo_f, demo_c);

	MyPrintf(demo_message, demo_i, demo_f, demo_c, demo_time, demo_struct);

	system("pause");
	return TRUE;
}

