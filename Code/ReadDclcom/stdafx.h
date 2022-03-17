// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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
	string type_name;//����
	string struct_name;//�ṹ������
	string struct_id;
	string comments;//ע��
	string units;
	int size;
	int offset;
	int ordinal_value;
	int element_num;//��Ա����
	int type_class;//��������Ϊ1
	int dimensions;//ά��
	int dim[3];//
	string dim_name[3];//ά������
	NDD_struct* P_pre;
	NDD_struct* P_next;
	NDD_struct* P_inside;
};

typedef struct fast_struct{
	string type_name;//����
	string struct_name;//�ṹ������
	string comments;//ע��
	string units;//��λ
	int element_num;//��Ա����
	int type_class;//��������Ϊ1
	int dimensions;//ά��
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
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
