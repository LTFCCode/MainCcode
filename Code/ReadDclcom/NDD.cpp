#include "stdafx.h"

#include "CPDAcom.h"

string LogAddress = "E:\\CCode\\ServiceDemo\\Code\\ReadDclcom\\GetNDDLog.log";
fstream out(LogAddress, ios::out);
ADODATA ado_model;
std::string strsql("");

map < string, vector <fast_struct*>> map_struct;
map < string, vector <enum_struct*>> map_enum;
map < string, vector <head_struct*>> map_head;
map < string, define_struct*> map_define;

void WriteLog(const char* Log, char* data)
{
	out << Log << data << endl;
}
void WriteLog(const char* Log, string data)
{
	out << Log << data.c_str() << endl;
}
void WriteLog(const char* Log, float data)
{
	out << Log << data << endl;
}
void WriteLog(const char* Log)
{
	out << Log << endl;
}
double elapsedTime(long long time1, long long time2)
{
	return ((double)(time2 - time1)) / 10.0 / 1000.0 / 1000.0;
}

int ConnectNDD()
{
	const char *dbHost = "10.24.10.188";
	const char *dbName = "masic1";
	const char *dbUser = "NDD";
	const char *dbPwd = "NDD";


	if (!SUCCEEDED(ado_model.Initialize(dbHost, dbName, dbUser, dbPwd, ADO_ORACLE)))
	{
		WriteLog("ado_model连接NDD失败");
		return FALSE;
	}
	WriteLog("ado_model连接NDD成功");
	return TRUE;
}

void GetStackType(string type_name, stack<string> *stack_struct)
{
	vector<fast_struct*> vector_Run;
	int DeepIn = FALSE;
	(*stack_struct).push(type_name);
	strsql.clear();
	strsql  = "select e.element_name,e.dimensions,e.dim_1,e.dim_2,e.dim_3,e.comments,e.UNITS,t.type_class,t.type_name from"
		" data_type s"
		" join struct_element e on s.type_id=e.struct_id"
		" join data_type t on e.type_id=t.type_id"
		" where s.type_name='" + type_name + "'"
		" and e.db_use=1"
		" order by e.offset";
	ado_model.ExecuteSQL(strsql.c_str(), NULL);
	
	try
	{
		
		while (!ado_model.m_pRecordset->adoEOF)
		{
			fast_struct* p_Run = new fast_struct;
			p_Run->type_name = (char*)(_bstr_t)ado_model.m_pRecordset->GetCollect("ELEMENT_NAME");
			p_Run->struct_name = (char*)(_bstr_t)ado_model.m_pRecordset->GetCollect("TYPE_NAME");
			if (p_Run->struct_name == "bk_time")
			{
				p_Run->struct_name = "long long";
			}
			p_Run->type_class = (int)ado_model.m_pRecordset->GetCollect("TYPE_CLASS");
			if (p_Run->type_class != 1)
			{
				DeepIn = TRUE;
			}
			auto vtComments = ado_model.m_pRecordset->GetCollect("COMMENTS");
			p_Run->comments = vtComments.vt == VT_NULL ? "" : (char*)(_bstr_t)vtComments;
			auto vtUnits = ado_model.m_pRecordset->GetCollect("UNITS");
			p_Run->units = vtUnits.vt == VT_NULL ? "" : (char*)(_bstr_t)vtUnits;
			p_Run->dimensions = (int)ado_model.m_pRecordset->GetCollect("DIMENSIONS");
			switch (p_Run->dimensions)
			{
			case 3:
				p_Run->dim[2] = (int)ado_model.m_pRecordset->GetCollect("DIM_3");
			case 2:
				p_Run->dim[1] = (int)ado_model.m_pRecordset->GetCollect("DIM_2");
			case 1:
				p_Run->dim[0] = (int)ado_model.m_pRecordset->GetCollect("DIM_1");
				break;
			default:
				break;
			}
			vector_Run.emplace_back(p_Run);
			ado_model.m_pRecordset->MoveNext();
		}
		map_struct.insert({ type_name, vector_Run });
	}
	catch (_com_error e)
	{
		//printf("%s	%s\n", p_Run->type_name.c_str(),e.ErrorMessage());
		WriteLog(e.ErrorMessage());
	}
	for (auto item = vector_Run.begin(); item != vector_Run.end(); item++)
	{
		if ((*item)->type_class != 1)
		{
			auto item1 = map_struct.find((*item)->struct_name);
			if (item1 == map_struct.end()){
				printf("%s开始\n", (*item)->struct_name.c_str());
				GetStackType((*item)->struct_name, stack_struct);
				printf("%s结束\n", (*item)->struct_name.c_str());
			}
			else
			{
				//需要将该结构体挪到栈顶
				printf("%s重复\n", (*item)->struct_name.c_str());
				stack<string> stack_Run;
				if ((*stack_struct).top() == (*item)->struct_name)
				{
					continue;
				}
				else
				{
					while (!(*stack_struct).empty())
					{
						if ((*stack_struct).top() == (*item)->struct_name)
						{
							(*stack_struct).pop();
							break;
						}
						stack_Run.push((*stack_struct).top());
						(*stack_struct).pop();
					}

					while (!stack_Run.empty())
					{
						(*stack_struct).push(stack_Run.top());
						stack_Run.pop();
					}

					(*stack_struct).push((*item)->struct_name);
				}			
			}
		}
	}
}
int GetEnum()
{
	strsql.clear();
	strsql = strsql + "select d.TYPE_NAME,e.ELEMENT_NAME,e.ELEMENT_VALUE from ENUM_ELEMENT e join DATA_TYPE d on d.TYPE_ID = e.ENUM_ID ORDER BY TYPE_NAME, ORDINAL_VALUE";
	ado_model.ExecuteSQL(strsql.c_str(), NULL);

	while (!ado_model.m_pRecordset->adoEOF)
	{
		enum_struct* p_Run = new enum_struct;

		string type_name = (char*)(_bstr_t)ado_model.m_pRecordset->GetCollect("TYPE_NAME");
		p_Run->enum_name = (char*)(_bstr_t)ado_model.m_pRecordset->GetCollect("ELEMENT_NAME");
		p_Run->value = (int)ado_model.m_pRecordset->GetCollect("ELEMENT_VALUE");

		auto item = map_enum.find(type_name);
		if (item != map_enum.end())
		{
			item->second.emplace_back(p_Run);
		}
		else
		{
			vector<enum_struct*> Run;
			map_enum.insert({ type_name, Run });
		}
		ado_model.m_pRecordset->MoveNext();
	}
	return TRUE;
}
void GetDefine()
{
	strsql.clear();
	strsql = strsql + "select HEADER_NAME,FILE_NAME,ELEMENT_TYPE,ELEMENT_NAME,head.ELEMENT_ID,head.COMMENTS,con.CONSTANT_VALUE from HEADERS he join  HEADER_ELEMENT head on head.HEADER_ID = he.HEADER_ID join  CONSTANTS con on con.CONSTANT_NAME = head.ELEMENT_NAME where head.ELEMENT_TYPE = 2";
	ado_model.ExecuteSQL(strsql.c_str(), NULL);

	while (!ado_model.m_pRecordset->adoEOF)
	{
		define_struct* p_Run = new define_struct;

		string type_name = (char*)(_bstr_t)ado_model.m_pRecordset->GetCollect("ELEMENT_NAME");
		p_Run->value = (int)ado_model.m_pRecordset->GetCollect("CONSTANT_VALUE");
		auto vtComments = ado_model.m_pRecordset->GetCollect("COMMENTS");
		p_Run->element = vtComments.vt == VT_NULL ? "" : (char*)(_bstr_t)vtComments;

		map_define.insert({ type_name, p_Run });

		ado_model.m_pRecordset->MoveNext();
	}
}
void GetHead()
{
	strsql.clear();
	strsql = strsql + "select HEADER_NAME,FILE_NAME,ELEMENT_TYPE,ELEMENT_NAME,head.ELEMENT_ID,head.COMMENTS from HEADERS he join  HEADER_ELEMENT head on head.HEADER_ID = he.HEADER_ID order by he.HEADER_NAME ,head.ELEMENT_TYPE";
	ado_model.ExecuteSQL(strsql.c_str(), NULL);

	while (!ado_model.m_pRecordset->adoEOF)
	{
		head_struct* p_Run = new head_struct;

		string file_name = (char*)(_bstr_t)ado_model.m_pRecordset->GetCollect("FILE_NAME");
		//p_Run->element_id = (char*)(_bstr_t)ado_model.m_pRecordset->GetCollect("ELEMENT_ID");
		p_Run->element_name = (char*)(_bstr_t)ado_model.m_pRecordset->GetCollect("ELEMENT_NAME");
		p_Run->element_type = (int)ado_model.m_pRecordset->GetCollect("ELEMENT_TYPE");
		if (p_Run->element_name == "FIO"){
			int i = 0;
		}
		auto item = map_head.find(file_name);
		if (item != map_head.end())
		{
			item->second.emplace_back(p_Run);
		}
		else
		{
			vector<head_struct*> Run;
			Run.emplace_back(p_Run);
			map_head.insert({ file_name, Run });
		}
		ado_model.m_pRecordset->MoveNext();
	}
	return;
}
void WriteEnum(std::fstream* Out, string enum_name)
{
	auto item_enum = map_enum.find(enum_name);
	if (item_enum != map_enum.end())
	{
		*Out << endl;
		*Out <<"typedef enum"<< endl;
		*Out << "{"<<endl;

		for (auto item = item_enum->second.begin(); item != item_enum->second.end();item++)
		{
			*Out << "	"<<(*item)->enum_name << " = " << (*item)->value << endl;
		}
		*Out << "}" << enum_name << ";" << endl;
		*Out << endl;
	}
	else
	{
		printf("未找到枚举:%s\n", enum_name.c_str());
		WriteLog("未找到枚举:", enum_name);
	}
}
void WriteDefine(std::fstream* Out, string define_name)
{
	auto item = map_define.find(define_name);
	if (item != map_define.end())
	{
		*Out << "#define " << define_name << "  " << (item->second)->value << "  //" << (item->second)->element << endl;
	}
	else
	{
		printf("未找到宏:%s\n", define_name.c_str());
		WriteLog("未找到宏:", define_name);
	}
}
void WriteStruct(std::fstream* Out, string struct_name)
{
	stack<string> stack_struct;
	GetStackType(struct_name, &stack_struct);

	auto item1 = map_struct.find(struct_name);
	if (item1 != map_struct.end())
	{
		printf("%s 写入\n", struct_name.c_str());
		WriteLog("写入:", struct_name);
	}
	else
	{
		printf("%s 未找到\n", struct_name.c_str());
		WriteLog("未找到:", struct_name);
	}

	*Out << "typedef struct{" << endl;

	string struct_name_local = "";
	for (auto item = item1->second.begin(); item != item1->second.end(); item++)
	{
		if ((*item)->type_class == 1)
		{
			struct_name_local = (*item)->struct_name;
		}
		else if ((*item)->type_class == 2)
		{
			struct_name_local = (*item)->struct_name + "TYPE";
		}
		else
		{
			continue;
		}
		if ((*item)->dimensions == 0)
		{
			if ((*item)->units == "")
			{
				*Out << "	" << struct_name_local << "  " << (*item)->type_name << ";//" << (*item)->comments << endl;
			}
			else
			{
				*Out << "	" << struct_name_local << "  " << (*item)->type_name << ";//" << (*item)->comments << "[" << (*item)->units << "]" << endl;
			}

		}
		else
		{
			switch ((*item)->dimensions)
			{
			case 1:
			{
				if ((*item)->units == "")
				{
					*Out << "	" << struct_name_local << "  " << (*item)->type_name << "[" << (*item)->dim[0] << "];//" << (*item)->comments << endl;
				}
				else
				{
					*Out << "	" << struct_name_local << "  " << (*item)->type_name << "[" << (*item)->dim[0] << "];//" << (*item)->comments << "[" << (*item)->units << "]" << endl;
				}
				break;
			}
			case 2:
			{
				if ((*item)->units == "")
				{
					*Out << "	" << struct_name_local << "  " << (*item)->type_name << "[" << (*item)->dim[0] << "][" << (*item)->dim[1] << "];//" << (*item)->comments << endl;
				}
				else
				{
					*Out << "	" << struct_name_local << "  " << (*item)->type_name << "[" << (*item)->dim[0] << "][" << (*item)->dim[1] << "];//" << (*item)->comments << "[" << (*item)->units << "]" << endl;
				}
				break;
			}
			case 3:
			{
				if ((*item)->units == "")
				{
					*Out << "	" << struct_name_local << "  " << (*item)->type_name << "[" << (*item)->dim[0] << "][" << (*item)->dim[1] << "][" << (*item)->dim[2] << "];//" << (*item)->comments << endl;
				}
				else
				{
					*Out << "	" << struct_name_local << "  " << (*item)->type_name << "[" << (*item)->dim[0] << "][" << (*item)->dim[1] << "][" << (*item)->dim[2] << "];//" << (*item)->comments << "[" << (*item)->units << "]" << endl;
				}
				break;
			}
			default:
				break;
			}
		}
	}
	*Out << "}" << struct_name << "TYPE;" << endl;

}
void WriteHead(string address, vector <head_struct*> data)
{
	std::fstream HeadOut(HEADADRESS+address, ios::out);
	HeadOut << "#pragma once" << endl;
	HeadOut << endl;
	for (auto item = data.begin(); item != data.end();item++)
	{
		switch ((*item)->element_type)
		{
		case 1:
			HeadOut << "#include \"" + (*item)->element_name + ".h\"" << endl;
			break;
		case 2:
			WriteDefine(&HeadOut, (*item)->element_name);
			break;
		case 3:
			WriteEnum(&HeadOut, (*item)->element_name);
			break;
		case 4:
			WriteStruct(&HeadOut, (*item)->element_name);
			break;
		default:
			break;
		}
	}
	HeadOut << endl;

	HeadOut.close();
}
int WriteCpda(){
	if (ConnectNDD())
	{
		WriteLog("连接NDD成功");
	}
	GetHead();
	GetDefine();
	GetEnum();

	for (auto item = map_head.begin(); item != map_head.end();item++)
	{
		WriteHead(item->first,item->second);
	}

	out.close();

	return TRUE;
}