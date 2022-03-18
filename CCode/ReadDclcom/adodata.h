#ifndef _ADODATA_
#define _ADODATA_

#include <iostream>
#include <string>
#ifndef _WINDOWS_
#    include <Windows.h>
#endif
//#include "TString.h"

#import "C:\Program Files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

typedef enum DBTypeEnum { ADO_SQL_SERVER, ADO_ORACLE, ADO_ODBC } DB_TYPE;

typedef enum SGPTypeEnum 
{ DQ2J = 1, B210P, SPHC, _380CL, CQ340V, Q235B,Q355B,
Q550D, SPHT2, SAE1026, GL1, X80, SPA_H, QStE500TM, DP590, TRIP590, CCSA,
_510L, Q235B_HW, Q355B_HW, _204, _304, _430, _304_HW, SAPH440
} SGP_TYPE;
#define TString std::string
class ADODATA
{
public:
	ADODATA();
	~ADODATA();

	// 初始化
	HRESULT Initialize();
	// 初始化并连接数据库
	HRESULT Initialize(const TCHAR *szServer, const TCHAR *szDatabase, const TCHAR *szUser, const TCHAR *szPwd, DB_TYPE DBType = ADO_ORACLE);

	HRESULT ReInitialize(const TCHAR *szDataSource, const TCHAR *szUser, const TCHAR *szPwd, DB_TYPE DBType = ADO_ORACLE);

	// 同步连接数据库
	HRESULT Connect(const TCHAR *szServer, const TCHAR *szDatabase, const TCHAR *szUser, const TCHAR *szPwd);
	// 只用于使用连接字符串连接ORACLE数据库
	HRESULT Connect(const TCHAR *szDataSource, const TCHAR *szUser, const TCHAR *szPwd);
	HRESULT Disconnect();
	void Release();

	BOOL VerifyConnection();

	HRESULT BeginTrans();
	HRESULT CommitTrans();
	HRESULT RollbackTrans();

	static void AppendInsertParameter(TString &FieldParam, const TCHAR *szField, TString &ValueParam, _variant_t vtValue);
	static void AppendUpdateParameter(TString &SetParam, const TCHAR *szField, _variant_t vtValue);

	DB_TYPE GetDBType() const;
	void SetDBType(DB_TYPE _DBType);
	//bool GetRecordset(TCHAR *sqlstr);
	//bool GetRecordset(CString sqlstr);
	//bool GetRecordset(BSTR sqlstr);

	bool ExecuteSQL(const TCHAR *szSQL, int *pnRecordAffected = NULL);
	//bool Execute(CString sqlstr);
	//bool Execute(BSTR sqlstr);
	//int GetRecordCount(void);
	//bool ExecProc(void);

	TString GetErrorDescription();

	HRESULT CloseRecordset();
public:
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;
	long m_SqlNativeError;

private:
	//	CString m_serveName,m_databaseName,m_user,m_passWord;
	DB_TYPE m_DBType;
	bool m_bInitialized;
	bool m_bTrans;
};
#endif
