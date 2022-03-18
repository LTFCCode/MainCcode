// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��
#define ANSI0 48;//'0'��Ӧ��ANSI��
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
	int TblNum;//̨����
	int SprNum;//ˮ����
	float DisTbl;//̨�ܼ��
	float DisSpr;//ˮ�����1
	float DisSprDouble;//ˮ�����2
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
//1��������������һ�㺯����ǰ���һ��inline���η���
//2������������ֱ�Ӹ��ơ���Ƕ������������ȥ�ģ����ǽ����������Ĵ���ֱ�ӷ�������������λ����
//����һ�㺯����ͬ���������ڵ���һ�㺯����ʱ����ָ����ת�������ú�������ڵ�ַ��ִ���걻���ú�����ָ������ת���������ϼ���ִ�к���Ĵ��룻
//���������������ǽ������Ĵ���ֱ�ӷ����˺�����λ���ϣ�����û��ָ����ת��ָ�˳��ִ�С�
//3��һ�㺯���Ĵ����ֻ��һ�ݣ������ڴ��е�ĳ��λ���ϣ�������������ǣ�ָ�����ת����������һ�γ���������ǣ�ָ������ת������
//�����������ǳ����е��ü����������������������Ĵ���ͻḴ�Ƽ��ݷ��ڶ�Ӧ��λ����
//4����������һ����ͷ�ļ��ж��壬��һ�㺯����ͷ�ļ�����������cpp�ж��塣
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
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
