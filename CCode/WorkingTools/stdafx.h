// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
