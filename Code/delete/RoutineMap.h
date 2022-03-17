#pragma once

//#include <iostream>
#include <string>
#include <windows.h>

class ICommItem;

typedef void(*COMM_HANDLE_ROUTINE)(ICommItem *pCommItem);

extern int RegisterCommRoutine(const std::string& sRoutineName, COMM_HANDLE_ROUTINE pRoutine, const BOOL bReplace = FALSE);
extern COMM_HANDLE_ROUTINE GetCommRoutine(const std::string& sRoutineName);
extern void ClearCommRoutine();