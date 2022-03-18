#include "stdafx.h"
#define MODEL_PATH "D:\\Models\\*.*"
#define TEXT_PATH "E:\\CCode\\ServiceDemo\\ReadExcel\\CTC\\*.*"
bool validFileName(string FileName)
{
	if (FileName.find(".cxx") != -1 || FileName.find(".txt") != -1 || FileName.find(".h") != -1)
	{
		return true;
	}
	return false;
}
int getLastEnter(string *data, int end)
{
	string run = data->substr(0, end);
	return	run.find_last_of("\n");
}
int getNextEnter(string *data,int start)
{	
	string run = data->substr(start,data->size());
	int line = run.find("!!-------------------");
	if (line == -1)
	{
		line = run.find("//-------------------");
	}
	string test = run.substr(line, run.size());
	int address = test.find("\n");

	return start + line + address;
}
void deleteTM()
{
	_finddata_t FindData;
	intptr_t handle = _findfirst(MODEL_PATH, &FindData);
	vector<string> list;
	
	do
	{
		if (FindData.attrib == _A_SUBDIR )
		{
			if (strcmp(FindData.name, ".") == 0 || strcmp(FindData.name, "..") == 0 )
			{
				continue;
			}
			char cBuffer[256] = { 0 };
			sprintf_s(cBuffer, sizeof(cBuffer), "D:\\Models\\%s\\*.*", FindData.name);
			_finddata_t FindData_inside;
			intptr_t handle_inside = _findfirst(cBuffer, &FindData_inside);
			do
			{
				if (FindData_inside.attrib == _A_SUBDIR)
				{
					if (strcmp(FindData_inside.name, ".") == 0 || strcmp(FindData_inside.name, "..") == 0)
					{
						continue;
					}
					char cBuffer_inside[256] = { 0 };
					sprintf_s(cBuffer_inside, sizeof(cBuffer_inside), "D:\\Models\\%s\\%s", FindData.name, FindData_inside.name);
					list.emplace_back(cBuffer_inside);
				}
			} while (!_findnext(handle_inside, &FindData_inside));
		}
	} while (!_findnext(handle, &FindData));

	for (auto address : list)
	{
		printf("%s\n",address.c_str());
		string file_name = "";
		string addr = address + "\\*.*";
		intptr_t handle = _findfirst(addr.c_str(), &FindData);
		do
		{
			file_name = FindData.name;
			if (validFileName(file_name))
			{
				char cBuffer[256] = { 0 };
				sprintf_s(cBuffer, sizeof(cBuffer), "%s\\%s", address.c_str(),file_name.c_str());
				ifstream in(cBuffer, ios::in);
				istreambuf_iterator<char> beg(in), end;
				string data(beg, end);
				int aim = data.find("REVISIONS:");
				in.close();
				if (aim != -1)
				{
					int start = getLastEnter(&data, aim);
					int end = getNextEnter(&data, aim);
					data.erase(start, end - start);
					fstream out(cBuffer, ios::out);
					out << data;
					out.close();
				}
				else
				{
					
				}
			}
		} while (!_findnext(handle, &FindData));
	}

}