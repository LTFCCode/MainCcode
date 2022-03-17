// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once



#include "ToolsLib.h"




int LoadConfig();
void findsuccess(intptr_t handle, _finddata_t FindData);
void CompareEvent();
void GetOracle();
void CallPython(int aimfunction);
void getPond();
void NineQueenQues();
void FTPjson();
void HanoiTower();
int testreturn();
void deleteTM();
void MinRoad();
//update DCRCOF_1D set B_CONTROLWRAPROLLSTEP = 1 where DCRCOF_1D.DCRCOF_ID IN (select DCRCOF.DCRCOF_ID from DCRCOF WHERE  I_GRTIDX > 13) and DCRCOF_1D.idx_1 BETWEEN 0 and 2;
// TODO:  在此处引用程序需要的其他头文件
