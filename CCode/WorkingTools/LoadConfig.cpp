#include "stdafx.h"

vector<intptr_t> vector_handle;
vector<_finddata_t> vector_finddata;
vector<TString> vector_path;



int LoadConfig(){
	_finddata_t FindData;
	intptr_t handle = _findfirst(EXCEL_PATH, &FindData);
	if (handle == -1)
	{
		printf("����ʧ��:%d\n", handle);
	}
	else
	{
		findsuccess(handle, FindData);
	}
	
	while (!_findnext(handle, &FindData))
	{		
		findsuccess(handle, FindData);
	}
	return 1;

}
void findsuccess(intptr_t handle, _finddata_t FindData)
{
	printf("name:%s\n", FindData.name);
	printf("attrib:%d\n", FindData.attrib);
	printf("size:%d\n", FindData.size);
	printSystemTime("��ʱ��", OnTime64toSystemTime(FindData.time_access));
	printSystemTime("����ʱ��", OnTime64toSystemTime(FindData.time_create));
	printSystemTime("�޸�ʱ��", OnTime64toSystemTime(FindData.time_write));
	vector_handle.push_back(handle);
	vector_finddata.push_back(FindData);
	TString path = EXCEL_PATH_UP;
	path += FindData.name;
	vector_path.push_back(path);
}


