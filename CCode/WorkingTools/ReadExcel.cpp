// ReadExcel.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"

extern fstream LogOut;
/**
* @brief �������ļ�
* @details ����main��ں���
* @author E.Z.
* @date 2022-02-14
* @copyright Copyright (c) 2015-2022 ����������˼���Զ������̼������޹�˾
*/
int _tmain(int argc, _TCHAR* argv[])
{

	Log(__FUNCTION__, "start");

	//LoadConfig();
	//CompareEvent();
	//GetOracle();
	//CallPython(2);
	//CompareEvent();
	//getPond();
	//forsg();
	//NineQueenQues();
	//FTPjson();
	//testreturn();
	//HanoiTower();
	//deleteTM();
	MinRoad();
	Log(__FUNCTION__, "end");

	LogOut.close();
	system("pause");
	return 0;
}

