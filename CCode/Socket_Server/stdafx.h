// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include "targetver.h"

#include "Socket_Tools.h"

void init_Server();
void Server();
void SocketText();
// TODO:  在此处引用程序需要的其他头文件
