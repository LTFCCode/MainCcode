// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <stack>
using namespace std;

//#import "C:\\Program Files (x86)\\Common Files\\Microsoft Shared\\OFFICE15\MSO.DLL"
//
//#import <E:\\CCode\\ServiceDemo\\Code\\Notes\\MSO.DLL> \
//rename("RGB", "MSORGB") \
//rename("DocumentProperties", "MSODocumentProperties")
//using namespace Office;

#include <string>
#include <vector>
#include <atlstr.h>
typedef unsigned char uchar;
int Demo_Class();
int Demo_Virtual();
void demo_vector();
bool  GetMacByGetAdaptersInfo(std::string& macOUT);
void Tree_test();

