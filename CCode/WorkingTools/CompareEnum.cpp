#include "stdafx.h"
typedef struct 
{
	string event;
	int enumNo;
	map<string, string> SenderListener;
}JsonItem;

int getlinecounter(string address)
{
	string test;
	int n = 0;
	fstream in(address, ios::in);
	while (getline(in, test))
	{
		n++;
	}
	in.close();
	return n;
}
void CompareEvent()
{
	string JsonAddress = "E:\\CCode\\ServiceDemo\\ReadExcel\\Tools\\pbEvent.json";
	fstream Jsonin(JsonAddress, ios::in);
	string APPAddress = "E:\\CCode\\ServiceDemo\\ReadExcel\\Tools\\app.json";
	fstream AppOut(APPAddress, ios::out);
	string MillAddress = "E:\\CCode\\ServiceDemo\\ReadExcel\\Tools\\millparam.h";
	fstream Millin(MillAddress, ios::in);
	string CsvAddress = "E:\\CCode\\ServiceDemo\\ReadExcel\\Tools\\S220121141937.csv";
	fstream Csvin(CsvAddress, ios::in);
	
	string data;
	int result = 0;

	vector<string> UneventVector;//csv中有但Json中没有的事件名称

	map<string, JsonItem> JsonMap;//pbEvent.json
	map<string, map<string, int>> MillMap;//millparam.h
	map<string, JsonItem> csvMap;//csv文件
	//pbevents
	//l2ProcessEnum
	//l2EventResultEnum

	while (getline(Millin, data))
	{
		int i = data.find("{");
		if (i != -1 )
		{
			map<string, int> EnumMap;
			while (getline(Millin, data))
			{
				deletestring(&data, "\t");
				deletestring(&data, " ");
				int h = data.find_first_of("=");
				int j = data.find_first_of(",");

				if (h < j && h > 0)
				{
					string key = data.substr(0, h);
					string value = data.substr(h + 1, j - 1);
					EnumMap[key] = atoi(value.c_str());
				}
				int result = data.find("}");

				if (result != -1)
				{
					deletestring(&data, " ");
					deletestring(&data, "}");
					deletestring(&data, ";");
					MillMap[data] = EnumMap;
					break;
				}
			}
		}
	}

	while (getline(Jsonin, data))
	{
		result = data.find("EventName");
		if (result > 0)
		{
			JsonItem jsonitem;
			jsonitem.event = getJsonValue(data);
			
			getline(Jsonin, data);
			jsonitem.enumNo  = atoi(getJsonValue(data).c_str());

			getline(Jsonin, data);
			getline(Jsonin, data);
			getline(Jsonin, data);
			getline(Jsonin, data);
			getline(Jsonin, data);

			string sender = getJsonValue(data);
			getline(Jsonin, data);
			string listener = getJsonValue(data);

			jsonitem.SenderListener[sender] = listener;

			if (MillMap["pbevents"].find(jsonitem.event) != MillMap["pbevents"].end())
			{
				if (MillMap["pbevents"][jsonitem.event] != jsonitem.enumNo)
				{
					Log(__FUNCTION__, "%s value error :%d  %d \n", jsonitem.event.c_str(), MillMap["pbevents"][jsonitem.event], jsonitem.enumNo);
				}
			}
			else
			{
				Log(__FUNCTION__, "未找到:%s", jsonitem.event.c_str());
			}

			if (JsonMap.find(jsonitem.event) != JsonMap.end())
			{
				Log(__FUNCTION__, "%s重复", jsonitem.event.c_str());
			}
			else
			{
				JsonMap[jsonitem.event] = jsonitem;
			}
		}
	}



	while (getline(Csvin, data))
	{
		JsonItem csvitem;
		stack<string> result(split(&data,","));
		result.pop();
		result.pop();

		string result_status = result.top();
		result.pop();

		int result_num = atoi(result.top().c_str());
		result.pop();

		string listener = result.top();
		result.pop();

		int listener_num = atoi(result.top().c_str());
		result.pop();

		string sender = result.top();
		result.pop();

		int sender_num = atoi(result.top().c_str());
		result.pop();

		csvitem.event = result.top();
		result.pop();

		csvitem.enumNo = atoi(result.top().c_str());

		csvitem.SenderListener[sender] = listener;

		if (JsonMap.find(csvitem.event) != JsonMap.end())
		{

		}
		else
		{
			Log(__FUNCTION__, "csv中的事件在json中不存在:event:%s enum:%d sender:%s listener:%s", csvitem.event.c_str(), csvitem.enumNo, sender.c_str(), listener.c_str());
			UneventVector.emplace_back(csvitem.event);
			JsonMap[csvitem.event] = csvitem;
		}
		if (csvMap.find(csvitem.event)!= csvMap.end())
		{
			if (csvMap[csvitem.event].enumNo == csvitem.enumNo && csvMap[csvitem.event].event == csvitem.event)
			{
				csvMap[csvitem.event].SenderListener[sender] = listener;
			}
			else
			{
				Log("csv事件不相同 csvMap %s(%d) csvitem %s(%d)", csvMap[csvitem.event].event, csvMap[csvitem.event].enumNo, csvitem.event, csvitem.enumNo);
			}
		}
		else
		{
			csvMap[csvitem.event] = csvitem;
		}
		
	}


	if (UneventVector.size()>0)
	{
		for (auto item = UneventVector.begin(); item != UneventVector.end();item++)
		{
			if (csvMap.find(*item) != csvMap.end())
			{
				string sender = "";
				string listener = "";
				if (csvMap[*item].SenderListener.size() > 0)
				{
					if (csvMap[*item].SenderListener.size() == 1)
					{
						for (auto send_item = csvMap[*item].SenderListener.begin(); send_item != csvMap[*item].SenderListener.end(); send_item++)
						{
							sender = send_item->first;
							listener = send_item->second;
						}
					}
					else
					{
						for (auto send_item = csvMap[*item].SenderListener.begin(); send_item != csvMap[*item].SenderListener.end(); send_item++)
						{
							sender = sender + send_item->first + ",";
							listener = listener + send_item->second + ",";
						}
					}
				}
				else
				{
					Log(__FUNCTION__, "csvMap中%s事件的收发者为空",item->c_str());
					break;
				}
				
				AppOut << "\t\t" << "{" << endl;
				AppOut << "\t\t\t" << "\"EventName\": \"" << csvMap[*item].event.c_str() << "\"," << endl;
				AppOut << "\t\t\t" << "\"EventEnum\": \"" << csvMap[*item].enumNo << "\"," << endl;
				AppOut << "\t\t\t" << "\"Zone\": \"" << sender << "\"," << endl;
				AppOut << "\t\t\t" << "\"Comment\": \"\"," << endl;
				AppOut << "\t\t\t" << "\"Enable\": true," << endl;
				AppOut << "\t\t\t" << "\"EventType\": \"PickUp\"," << endl;
				AppOut << "\t\t\t" << "\"Senders\": [ \"" << sender << "\" ]," << endl;
				AppOut << "\t\t\t" << "\"Listeners\": [ \"" << listener << "\" ]," << endl;
				AppOut << "\t\t\t" << "\"ResultReq\": false," << endl;
				AppOut << "\t\t\t" << "\"SPARE_1\":  \"\"," << endl;
				AppOut << "\t\t\t" << "\"SPARE_2\":  \"\"" << endl;
				AppOut << "\t\t" << "}," << endl;
			}
			else
			{
				Log(__FUNCTION__,"UneventVector中的事件在csvMap中不存在:%s",item->c_str());
			}
		}
	}

	AppOut.close();
}