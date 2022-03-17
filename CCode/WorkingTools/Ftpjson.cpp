#include "stdafx.h"
#define CONFIG_PATH "D:\\Models\\%s\\Config\\*.txt"
#define MODEL_PATH "D:\\Models\\*.*"
#define T1 "\t"
#define T2 "\t\t"
#define T3 "\t\t\t"
#define T4 "\t\t\t\t"
#define T5 "\t\t\t\t\t"
#define T6 "\t\t\t\t\t\t"
#define T7 "\t\t\t\t\t\t\t"
#define T8 "\t\t\t\t\t\t\t\t"
void FTPjson()
{
	_finddata_t FindData;
	intptr_t handle = _findfirst(MODEL_PATH, &FindData);
	vector<string> lists;
	fstream Out(FTP_PATH, ios::out);
	do
	{
		if (FindData.attrib == _A_SUBDIR)//是目录
		{
			lists.emplace_back(FindData.name);
		}
	} while (!_findnext(handle, &FindData));

	char cBuffer[64] = { 0 };	
	Out << "\t\t\t\"children\": [" << endl;
	for (auto item = lists.begin(); item != lists.end();item++)
	{

		if (strcmp(item->c_str(), ".") == 0 || strcmp(item->c_str(), "..") == 0 || strcmp(item->c_str(), "Xxx") == 0)
		{
			continue;
		}

		if (strcmp(item->c_str(), "ROP") == 0)
		{
			vector<string> RROP;
			vector<string> FROP;
			sprintf_s(cBuffer, sizeof(cBuffer), "D:\\Models\\ROP\\RROP_Config\\*.txt");
			handle = _findfirst(cBuffer, &FindData);
			if (-1 == handle)
			{
				printf("%s下没有RROP_Config文件夹\n", item->c_str());
				continue;
			}
			string filename = "";
			do
			{
				filename = FindData.name;
				RROP.emplace_back(filename);
			} while (!_findnext(handle, &FindData));

			sprintf_s(cBuffer, sizeof(cBuffer), "D:\\Models\\ROP\\FROP_Config\\*.txt");
			handle = _findfirst(cBuffer, &FindData);
			if (-1 == handle)
			{
				printf("%s下没有FROP_Config文件夹\n", item->c_str());
				continue;
			}
			do
			{
				filename = FindData.name;
				FROP.emplace_back(filename);
			} while (!_findnext(handle, &FindData));
			Out << T4<<"{" << endl;
			Out << T5<<"\"pFile\": []," << endl;
			Out << T5<<"\"pTId\": \"" << getGuid().c_str() << "\"," << endl;
			Out << T5<<"\"pType\": \"" << item->c_str() << "\"," << endl;
			Out << T5<<"\"pPath\": \"%BKMASIC_MODELS%\\\\" << item->c_str() << "\\\\RROP_Config\"," << endl;
			Out << T5<<"\"disPath\": \"%BKMASIC_SYSTEM%\\\\Config\\\\" << item->c_str() << "\\\\RROP_Config\"," << endl;
			Out << T5<<"\"children\": [" << endl;

			Out << T5"{" << endl;
			Out << T6"\"pFile\": [" << endl;
			int num = 1;
			for (auto item_txt = RROP.begin(); item_txt != RROP.end(); item_txt++)
			{
				Out << T7"{" << endl;
				Out << T8"\"pSId\": \"" << num++ << "\"," << endl;
				Out << T8"\"pGId\": \"" << getGuid().c_str() << "\"," << endl;
				Out << T8"\"pfName\": \"" << *item_txt << "\"," << endl;
				Out << T8"\"pfPath\": \"%BKMASIC_MODELS%\\\\" << item->c_str() << "\\\\RROP_Config\"," << endl;
				Out << T8"\"showCfPath\": null," << endl;
				Out << T8"\"showPfPath\": null," << endl;
				Out << T8"\"pfTime\": null," << endl;
				Out << T8"\"copyFPath\": \"%BKMASIC_SYSTEM%\\\\Config\\\\Models\\\\" << item->c_str() << "\\\\RROP_Config\"," << endl;
				Out << T8"\"disTime\": null" << endl;
				if (*item_txt != RROP[RROP.size() - 1])
				{
					Out << T7"}," << endl;
				}
				else
				{
					Out << T7"}" << endl;
				}
			}
			Out << T6"]," << endl;
			Out << T6"\"pTId\": \"" << getGuid().c_str() << "\"," << endl;
			Out << T6"\"pType\": \"RROP\"," << endl;
			Out << T6"\"pPath\": \"%BKMASIC_MODELS%\\\\" << item->c_str() << "\\\\FROP_Config\"," << endl;
			Out << T6"\"disPath\": \"%BKMASIC_SYSTEM%\\\\Config\\\\" << item->c_str() << "\\\\FROP_Config\"," << endl;
			Out << T6"\"children\": []" << endl;
			Out << T5"}," << endl;

			Out << T5"{" << endl;
			Out << T6"\"pFile\": [" << endl;

			num = 1;
			for (auto item_txt = FROP.begin(); item_txt != FROP.end(); item_txt++)
			{
				Out << T7"{" << endl;
				Out << T8"\"pSId\": \"" << num++ << "\"," << endl;
				Out << T8"\"pGId\": \"" << getGuid().c_str() << "\"," << endl;
				Out << T8"\"pfName\": \"" << *item_txt << "\"," << endl;
				Out << T8"\"pfPath\": \"%BKMASIC_MODELS%\\\\" << item->c_str() << "\\\\FROP_Config\"," << endl;
				Out << T8"\"showCfPath\": null," << endl;
				Out << T8"\"showPfPath\": null," << endl;
				Out << T8"\"pfTime\": null," << endl;
				Out << T8"\"copyFPath\": \"%BKMASIC_SYSTEM%\\\\Config\\\\Models\\\\" << item->c_str() << "\\\\FROP_Config\"," << endl;
				Out << T8"\"disTime\": null" << endl;
				if (*item_txt != FROP[FROP.size() - 1])
				{
					Out << T7"}," << endl;
				}
				else
				{
					Out << T7"}" << endl;
				}
			}
			Out << T6"]," << endl;
			Out << T6"\"pTId\": \"" << getGuid().c_str() << "\"," << endl;
			Out << T6"\"pType\": \"FROP\"," << endl;
			Out << T6"\"pPath\": \"%BKMASIC_MODELS%\\\\" << item->c_str() << "\\\\FROP_Config\"," << endl;
			Out << T6"\"disPath\": \"%BKMASIC_SYSTEM%\\\\Config\\\\" << item->c_str() << "\\\\FROP_Config\"," << endl;
			Out << T6"\"children\": []" << endl;
			Out << T5"}" << endl;

			Out << T5"]" << endl;

			if (*item != lists[lists.size() - 1])
			{
				Out << T4"}," << endl;
			}
			else
			{
				Out << T4"}" << endl;
			}
		}
		else if (strcmp(item->c_str(), "Records") == 0)
		{
			sprintf_s(cBuffer, sizeof(cBuffer), CONFIG_PATH, item->c_str());
			handle = _findfirst(cBuffer, &FindData);
			int num = 1;
			if (-1 == handle)
			{
				printf("%s下没有config文件夹\n", item->c_str());
				continue;
			}
			vector<string> iocheck;
			vector<string> config;
			string filename = "";
			do
			{
				filename = FindData.name;
				if (filename.find("iocheck") != -1)
				{
					iocheck.emplace_back(filename);
				}
				else
				{
					config.emplace_back(filename);
				}
			} while (!_findnext(handle, &FindData));
			
			Out << T4"{" << endl;
			Out << T5"\"pFile\": []," << endl;
			Out << T5"\"pTId\": \"" << getGuid().c_str() << "\"," << endl;
			Out << T5"\"pType\": \"" << item->c_str() << "\"," << endl;
			Out << T5"\"pPath\": \"%BKMASIC_MODELS%\\\\" << item->c_str() << "\\\\Config\"," << endl;
			Out << T5"\"disPath\": \"%BKMASIC_SYSTEM%\\\\Config\\\\" << item->c_str() << "\\\\Config\"," << endl;
			Out << T5"\"children\": [" << endl;

			Out << T5"{" << endl;		
			Out << T6"\"pFile\": [" << endl;
			num = 1;
			for (auto item_txt = iocheck.begin(); item_txt != iocheck.end();item_txt++)
			{
				Out << T7"{" << endl;
				Out << T8"\"pSId\": \"" << num++ << "\"," << endl;
				Out << T8"\"pGId\": \"" << getGuid().c_str() << "\"," << endl;
				Out << T8"\"pfName\": \"" << *item_txt << "\"," << endl;
				Out << T8"\"pfPath\": \"%BKMASIC_MODELS%\\\\" << item->c_str() << "\\\\Config\"," << endl;
				Out << T8"\"showCfPath\": null," << endl;
				Out << T8"\"showPfPath\": null," << endl;
				Out << T8"\"pfTime\": null," << endl;
				Out << T8"\"copyFPath\": \"%BKMASIC_SYSTEM%\\\\Config\\\\Models\\\\" << item->c_str() << "\\\\Config\"," << endl;
				Out << T8"\"disTime\": null" << endl;
				if (*item_txt != iocheck[iocheck.size() - 1])
				{
					Out << T7"}," << endl;
				}
				else
				{
					Out << T7"}" << endl;
				}
			}
			Out << T6"]," << endl;
			Out << T6"\"pTId\": \"" << getGuid().c_str() << "\"," << endl;
			Out << T6"\"pType\": \"iocheck\"," << endl;
			Out << T6"\"pPath\": \"%BKMASIC_MODELS%\\\\" << item->c_str() << "\\\\Config\"," << endl;
			Out << T6"\"disPath\": \"%BKMASIC_SYSTEM%\\\\Config\\\\" << item->c_str() << "\\\\Config\"," << endl;
			Out << T6"\"children\": []" << endl;
			Out << T5"}," << endl;

			Out << T5"{" << endl;
			Out << T6"\"pFile\": [" << endl;

			num = 1;
			for (auto item_txt = config.begin(); item_txt != config.end(); item_txt++)
			{
				Out << T7"{" << endl;
				Out << T8"\"pSId\": \"" << num++ << "\"," << endl;
				Out << T8"\"pGId\": \"" << getGuid().c_str() << "\"," << endl;
				Out << T8"\"pfName\": \"" << *item_txt << "\"," << endl;
				Out << T8"\"pfPath\": \"%BKMASIC_MODELS%\\\\" << item->c_str() << "\\\\Config\"," << endl;
				Out << T8"\"showCfPath\": null," << endl;
				Out << T8"\"showPfPath\": null," << endl;
				Out << T8"\"pfTime\": null," << endl;
				Out << T8"\"copyFPath\": \"%BKMASIC_SYSTEM%\\\\Config\\\\Models\\\\" << item->c_str() << "\\\\Config\"," << endl;
				Out << T8"\"disTime\": null" << endl;
				if (*item_txt != config[config.size() - 1])
				{
					Out << T7"}," << endl;
				}
				else
				{
					Out << T7"}" << endl;
				}
			}
			Out << T6"]," << endl;
			Out << T6"\"pTId\": \"" << getGuid().c_str() << "\"," << endl;
			Out << T6"\"pType\": \"config\"," << endl;
			Out << T6"\"pPath\": \"%BKMASIC_MODELS%\\\\" << item->c_str() << "\\\\Config\"," << endl;
			Out << T6"\"disPath\": \"%BKMASIC_SYSTEM%\\\\Config\\\\" << item->c_str() << "\\\\Config\"," << endl;
			Out << T6"\"children\": []" << endl;
			Out << T5"}" << endl;

			Out << T5"]" << endl;

			if (*item != lists[lists.size() - 1])
			{
				Out << T4"}," << endl;
			}
			else
			{
				Out << T4"}" << endl;
			}
		}
		else
		{
			sprintf_s(cBuffer, sizeof(cBuffer), CONFIG_PATH, item->c_str());
			handle = _findfirst(cBuffer, &FindData);
			int num = 1;
			if (-1 == handle)
			{
				printf("%s下没有config文件夹\n", item->c_str());
				continue;
			}
			Out << T4"{" << endl;
			Out << T5"\"pFile\": [" << endl;
begin3:
			Out << T6"{" << endl;
			Out << T7"\"pSId\": \"" << num++ << "\"," << endl;
			Out << T7"\"pGId\": \"" << getGuid().c_str() << "\"," << endl;
			Out << T7"\"pfName\": \"" << FindData.name << "\"," << endl;
			Out << T7"\"pfPath\": \"%BKMASIC_MODELS%\\\\" << item->c_str() << "\\\\Config\"," << endl;
			Out << T7"\"showCfPath\": null," << endl;
			Out << T7"\"showPfPath\": null," << endl;
			Out << T7"\"pfTime\": null," << endl;
			Out << T7"\"copyFPath\": \"%BKMASIC_SYSTEM%\\\\Config\\\\Models\\\\" << item->c_str() << "\\\\Config\"," << endl;
			Out << T7"\"disTime\": null" << endl;
			if (!_findnext(handle, &FindData))
			{
				Out << T6"}," << endl;
				goto begin3;
			}
			else
			{
				Out << T6"}" << endl;
			}

			Out << T5"]," << endl;
			Out << T5"\"pTId\": \"" << getGuid().c_str() << "\"," << endl;
			Out << T5"\"pType\": \"" << item->c_str() << "\"," << endl;
			Out << T5"\"pPath\": \"%BKMASIC_MODELS%\\\\" << item->c_str() << "\\\\Config\"," << endl;
			Out << T5"\"disPath\": \"%BKMASIC_SYSTEM%\\\\Config\\\\" << item->c_str() << "\\\\Config\"," << endl;
			Out << T5"\"children\": []" << endl;
			if (*item != lists[lists.size() - 2])//SSU为倒数第二个,最后一个是Xxx
			{
				Out << T4"}," << endl;
			}
			else
			{
				Out << T4"}" << endl;
			}
		}

	}
	Out << T3"]";
	Out.close();
}

