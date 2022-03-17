// ReadExcel.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

extern fstream LogOut;
/**
* @brief 主函数文件
* @details 定义main入口函数
* @author E.Z.
* @date 2022-02-14
* @copyright Copyright (c) 2015-2022 北京北科麦思科自动化工程技术有限公司
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

