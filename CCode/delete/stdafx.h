// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
#include <fstream>
#include <iostream>
#include <memory>
#include <objbase.h>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <atlbase.h>
#include <atlstr.h>
#include "targetver.h"
#include <map>
#include <vector>
#include <string>
#include <exception>  
#include <string.h>
#include <math.h>
#include <unordered_map>
#include <ctime>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的
#define ANSI0 48;//'0'对应的ANSI码
#define SE_NO_ERROR           0L
#define SE_INIT_FAILED        1L
#define SE_NOT_SPECIFIC_FUNC  2L
#define SE_INVALID_FUNC       3L
#define SE_UNEXPECTED_STOP    4L
#define SE_WAIT_ERROR         5L
#define SE_THREAD_NO_RESPOND  6L
#define _tcscpy_s   strcpy_s

#ifdef _UNICODE
#   define TString std::wstring
#else
#   define TString std::string
#endif
template<class _Ty>
struct StringLess
	: public std::binary_function<_Ty, _Ty, bool>
{	// functor for operator<
	bool operator()(const _Ty& _Left, const _Ty& _Right) const
	{	// apply operator< to operands
		return (_Left.compare(_Right) < 0);
	}
};

class Base{
public:
	virtual void function() = 0;
};

typedef int(*PEXIT_HANDLER)();
typedef std::vector<TString> CmdParamList;
typedef std::map<TString, CmdParamList, StringLess<TString>> OptionMap;
typedef DWORD(WINAPI *PWORK_ROUTINE)(LPVOID lpParameter);


class demo_ptr;

int demo_safe_delete();
void demo_sample_delete();
void demo_heap_stack();
void demo();
void sampe();
void delete_work();
void pass_by_value(int ,int );
void pass_by_reference(int *,int *);
void function_template();
int function_template_work();
int base_work();
void demo_Test();
typedef struct{
	int TblNum;//台架数
	int SprNum;//水阀数
	float DisTbl;//台架间距
	float DisSpr;//水阀间距1
	float DisSprDouble;//水阀间距2
}ZONE;

void time_work();
void demo_time();
void demo_time_test();
double elapsedTime(long long time1, long long time2);
int absoluteTime(long long *PnewTime, float offset);
void DcMRead();
void Demo_get(ZONE &MZONE, ZONE &VZONE, ZONE *FBKZONE);
void Demo_CalSpr();
float Demo_ShowSprDis(ZONE *MZONE, ZONE *VZONE, ZONE *FBKZONE);
void CdbInit();
void Demo_Alarm();
void Demo_calculate();
BOOL IsInstalled();
void demo_service();
BOOL MyService();
void split(string& s, vector<string>&res, string& delema1);
void CalculateSpr();
void demo_try();

void ComVariableScale();
//1）内联含函数比一般函数在前面多一个inline修饰符。
//2）内联函数是直接复制“镶嵌”到主函数中去的，就是将内联函数的代码直接放在内联函数的位置上
//这与一般函数不同，主函数在调用一般函数的时候，是指令跳转到被调用函数的入口地址，执行完被调用函数后，指令再跳转回主函数上继续执行后面的代码；
//而由于内联函数是将函数的代码直接放在了函数的位置上，所以没有指令跳转，指令按顺序执行。
//3）一般函数的代码段只有一份，放在内存中的某个位置上，当程序调用它是，指令就跳转过来；当下一次程序调用它是，指令又跳转过来；
//而内联函数是程序中调用几次内联函数，内联函数的代码就会复制几份放在对应的位置上
//4）内联函数一般在头文件中定义，而一般函数在头文件中声明，在cpp中定义。
inline int demo_inline(){
	int demo = 123;
	string a = to_string(demo);
	cout << sizeof(demo) << endl;

	cout << sizeof(a) << endl;
	return TRUE;
}
void Demo_Hash();
int demo_define();
void Demo_Test();
void Demo_Test2();
void Demo_Test234();
void Demo_Test_char();
void Demo_Test_point();
vector<vector<int>> Demo_Test(int numRows);
// TODO:  在此处引用程序需要的其他头文件
