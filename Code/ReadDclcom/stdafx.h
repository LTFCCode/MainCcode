// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <map>
#include <vector>
#include <stack>
#include <tuple>
using namespace std;
#pragma warning(default:4146)
#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)
#define HEADADRESS "E:\\CCode\\ServiceDemo\\Code\\ReadDclcom\\NDD\\"
#include "adodata.h"

typedef struct{
	string type_name;
	string type_id;
	string struct_name;
	string struct_id;
	int size;
	int type_class;
	int dimensions;
	int dim[3];
	string dim_name[3];
	string comments;
}struct_type;


typedef struct NDD_struct{
	string type_name;//类型
	string struct_name;//结构体名称
	string struct_id;
	string comments;//注释
	string units;
	int size;
	int offset;
	int ordinal_value;
	int element_num;//成员数量
	int type_class;//基本类型为1
	int dimensions;//维度
	int dim[3];//
	string dim_name[3];//维度名称
	NDD_struct* P_pre;
	NDD_struct* P_next;
	NDD_struct* P_inside;
};

typedef struct fast_struct{
	string type_name;//类型
	string struct_name;//结构体名称
	string comments;//注释
	string units;//单位
	int element_num;//成员数量
	int type_class;//基本类型为1
	int dimensions;//维度
	int dim[3];//
};
typedef struct NDD_vector{
	NDD_struct type;
	vector<NDD_struct> inside_vector;
};
typedef struct{
	int value;
	string element;
}define_struct;

typedef struct{
	string element_name;
	int element_type;
}head_struct;
typedef struct{
	int value;
	string enum_name;
}enum_struct;
int ReadDclcom();
int ConnectOracle_Model();
int ConnectOracle_mskorcl();
int ConnectOracle_localhost();
int Connect_Init();
int ReadSteelGradeNo();
int WriteByAdo();
int WriteByAdoNew();
int ReadCpda();
int ReadDclcom();
int CheckParameters(); 
int connectNDD();
int WriteCpda();
void CompareEnumJson();
// TODO:  在此处引用程序需要的其他头文件
