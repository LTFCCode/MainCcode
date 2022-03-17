#pragma once

#import "C:\ProgramFiles\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

class CDBOperation
{
public:
	//初始化数据库操作需要的对象
	CDBOperation(void);
	~CDBOperation(void);
	//连接至数据库
	boolConnToDB(char *ConnectionString, char *UserID, char*Password);

	//数据库操作函数
	//查询操作删除以及添加
	_RecordsetPtr ExecuteWithResSQL(constchar *);
	//boolExecuteNoResSQL(const char *);//delete and add

private:
	voidPrintErrorInfo(_com_error &);

private:
	//初始化数据库连接、命令、记录集
	_ConnectionPtr CreateConnPtr();
	_CommandPtr CreateCommPtr();
	_RecordsetPtr CreateRecsetPtr();

private:
	//数据库连接需要的连接、命令操作对象
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
};