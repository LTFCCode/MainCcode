#include "stdafx.h"
#include <iostream>
#include <string>
#include <AtlComTime.h>
#include "AdoData.h"
//#ifndef _WINDOWS_
//#    include <Windows.h>
//#endif

ADODATA::ADODATA() :
m_bInitialized(false)
{
}

ADODATA::~ADODATA()
{
	//Disconnect();
	Release();

	if (m_bInitialized)
	{
		::CoUninitialize();
		m_bInitialized = false;
	}
}

HRESULT ADODATA::Initialize()
{
	HRESULT hr;
	if (SUCCEEDED(hr = ::CoInitialize(NULL)))
	{
		m_bInitialized = true;
	}
	else
	{
		return hr;
	}

	if (!SUCCEEDED(hr = m_pConnection.CreateInstance(_uuidof(Connection))))
	{
		return hr;
	}
	if (!SUCCEEDED(hr = m_pCommand.CreateInstance(_uuidof(Command))))
	{
		return hr;
	}
	if (!SUCCEEDED(hr = m_pRecordset.CreateInstance(_uuidof(Recordset))))
	{
		return hr;
	}

	return hr;
}

HRESULT ADODATA::Initialize(const TCHAR *szServer, const TCHAR *szDatabase, const TCHAR *szUser, const TCHAR *szPwd, DB_TYPE DBType)
{
	HRESULT hr;
	if (SUCCEEDED(hr = ::CoInitialize(NULL)))
	{
		m_bInitialized = true;
	}
	else
	{
		return hr;
	}

	if (!SUCCEEDED(hr = m_pConnection.CreateInstance(_uuidof(Connection))))
	{
		return hr;
	}
	if (!SUCCEEDED(hr = m_pCommand.CreateInstance(_uuidof(Command))))
	{
		return hr;
	}
	if (!SUCCEEDED(hr = m_pRecordset.CreateInstance(_uuidof(Recordset))))
	{
		return hr;
	}
	SetDBType(DBType);

	return Connect(szServer, szDatabase, szUser, szPwd);
}

HRESULT ADODATA::ReInitialize(const TCHAR *szDataSource, const TCHAR *szUser, const TCHAR *szPwd, DB_TYPE DBType)
{
	HRESULT hr;

	if (!m_bInitialized)
	{
		return -1;
	}

	Release();

	if (!SUCCEEDED(hr = m_pConnection.CreateInstance(_uuidof(Connection))))
	{
		return hr;
	}
	if (!SUCCEEDED(hr = m_pCommand.CreateInstance(_uuidof(Command))))
	{
		return hr;
	}
	if (!SUCCEEDED(hr = m_pRecordset.CreateInstance(_uuidof(Recordset))))
	{
		return hr;
	}
	SetDBType(DBType);

	return Connect(szDataSource, szUser, szPwd);
}

DB_TYPE ADODATA::GetDBType() const
{
	return m_DBType;
}

void ADODATA::SetDBType(DB_TYPE _DBType)
{
	m_DBType = _DBType;
}

HRESULT ADODATA::Connect(const TCHAR *szServer, const TCHAR *szDatabase, const TCHAR *szUser, const TCHAR *szPwd)
{
	TCHAR szConnStr[256];
	HRESULT hr = 0;

	if (m_DBType == ADO_SQL_SERVER)
	{
		_stprintf_s(szConnStr, 256, _T("Provider=SQLOLEDB.1;Password=%s;Persist Security Info=True;User ID=%s;")
			_T("Initial Catalog=%s;Data Source=%s"), szPwd, szUser, szDatabase, szServer);
	}
	else if (m_DBType == ADO_ORACLE)
	{
		_stprintf_s(szConnStr, 256, _T("Provider=OraOLEDB.Oracle.1;User ID=%s;Password=%s;")
			_T("Data Source='(DESCRIPTION=(ADDRESS_LIST=(ADDRESS=(PROTOCOL=TCP)")
			_T("(HOST=%s)(PORT=1521)))(CONNECT_DATA=(SID=%s)))'"), szUser, szPwd, szServer, szDatabase);
	}
	else if (m_DBType == ADO_ODBC)
	{
		_stprintf_s(szConnStr, 256, _T("DSN=%s;UID=%s;PWD=%s;"), szServer, szUser, szPwd);
	}
	else
		return -1;

	try
	{
		// 同步打开数据库链接
		hr = m_pConnection->Open((_bstr_t)szConnStr, (_bstr_t)(_T("")), (_bstr_t)(_T("")), adConnectUnspecified);
		if (SUCCEEDED(hr))
		{
			m_pCommand->ActiveConnection = m_pConnection;
		}
	}
	catch (_com_error e)
	{
		OutputDebugString(e.ErrorMessage());
		hr = -1;
	}

	return hr;
}

HRESULT ADODATA::Connect(const TCHAR *szDataSource, const TCHAR *szUser, const TCHAR *szPwd)
{
	TCHAR szConnStr[256];
	HRESULT hr = 0;

	if (m_DBType == ADO_ORACLE)
	{
		_stprintf_s(szConnStr, 256, _T("Provider=OraOLEDB.Oracle.1;User ID=%s;Password=%s;")
			_T("Data Source='%s'"), szUser, szPwd, szDataSource);
	}
	else
	{
		return -1;
	}

	try
	{
		// 同步打开数据库链接
		hr = m_pConnection->Open((_bstr_t)szConnStr, (_bstr_t)(_T("")), (_bstr_t)(_T("")), adConnectUnspecified);
		if (SUCCEEDED(hr))
		{
			m_pCommand->ActiveConnection = m_pConnection;
		}
	}
	catch (_com_error e)
	{
		OutputDebugString(e.ErrorMessage());
		hr = -1;
	}

	return hr;
}

HRESULT ADODATA::Disconnect()
{
	HRESULT hr;
	if (m_pRecordset->State)
	{
		if (!SUCCEEDED(hr = m_pRecordset->Close()))
		{
			return hr;
		}
	}
	try
	{
		if (m_pConnection->State)
		{
			if (!SUCCEEDED(hr = m_pConnection->Close()))
			{
				return hr;
			}
		}
	}
	catch (_com_error e)
	{
		//MessageBox(NULL, e.ErrorMessage(), _T("Disconnect"), MB_OK);
		OutputDebugString(e.ErrorMessage());
	}
	return S_OK;
}

void ADODATA::Release()
{
	if (m_pRecordset != NULL)
	{
		m_pRecordset.Release();
	}
	if (m_pCommand != NULL)
	{
		m_pCommand.Release();
	}
	if (m_pConnection != NULL)
	{
		m_pConnection->Release();
	}
}

BOOL ADODATA::VerifyConnection()
{
	BOOL bOK = FALSE;
	TCHAR szSql[] = _T("select sysdate from dual");
	try
	{
		_variant_t RecordsAffected;
		if (ExecuteSQL(szSql))
		{
			bOK = TRUE;
		}
	}
	catch (_com_error& ex)
	{
		OutputDebugString(ex.Description());
	}
	return bOK;
}

HRESULT ADODATA::BeginTrans()
{
	return m_pConnection->BeginTrans();
	/*DWORD Tried = 0;

	if ((m_pConnection->State & adStateOpen) != adStateOpen)
	{
	throw std::exception("Connection not open");
	}

	do
	{
	++Tried;
	try
	{
	m_SqlNativeError = 0;
	m_pConnection->GetErrors()->Clear();
	return m_pConnection->BeginTrans();
	}
	catch (_com_error e)
	{
	if (e.Error() == XACT_E_XTIONEXISTS && Tried < 2)
	{
	RollbackTrans();
	continue;
	}

	TCHAR szOutStr[256] = _T("Exception in BeginTrans");
	if (m_pConnection->GetErrors()->Count > 0)
	{
	for (long i = 0; i < m_pConnection->GetErrors()->Count; ++i)
	{
	ErrorPtr pError = m_pConnection->GetErrors()->GetItem(_variant_t(i));
	m_SqlNativeError = pError->NativeError;

	_stprintf_s(szOutStr, 256, _T("ADO error, Desc:%s, Native Error:%d"), (TCHAR*)pError->Description, pError->NativeError);
	OutputDebugString(szOutStr);

	}
	//m_pConnection->GetErrors()->Clear();
	}
	throw std::exception(szOutStr);
	}
	} while (true);*/
}

HRESULT ADODATA::CommitTrans()
{
	return m_pConnection->CommitTrans();
	/*DWORD Tried = 0;

	if ((m_pConnection->State & adStateOpen) != adStateOpen)
	{
	throw std::exception("Connection not open");
	}
	do
	{
	++Tried;
	try
	{
	m_SqlNativeError = 0;
	m_pConnection->GetErrors()->Clear();
	return m_pConnection->CommitTrans();
	}
	catch (_com_error e)
	{
	if (e.Error() == E_FAIL && Tried < 2)
	{
	// ORA-03114,not connected to oracle
	continue;//retry
	}

	TCHAR szOutStr[256] = _T("Exception in CommitTrans");
	if (m_pConnection->GetErrors()->Count > 0)
	{
	for (long i = 0; i < m_pConnection->GetErrors()->Count; ++i)
	{
	ErrorPtr pError = m_pConnection->GetErrors()->GetItem(_variant_t(i));
	m_SqlNativeError = pError->NativeError;

	_stprintf_s(szOutStr, 256, _T("ADO error, Desc:%s, Native Error:%d"), (TCHAR*)pError->Description, pError->NativeError);
	OutputDebugString(szOutStr);
	}
	//m_pConnection->GetErrors()->Clear();
	}
	throw std::exception(szOutStr);
	}
	} while (true);*/

}

HRESULT ADODATA::RollbackTrans()
{
	return m_pConnection->RollbackTrans();
	/*if ((m_pConnection->State & adStateOpen) != adStateOpen)
	{
	throw std::exception("Connection not open");
	}

	try
	{
	m_SqlNativeError = 0;
	m_pConnection->GetErrors()->Clear();
	return m_pConnection->RollbackTrans();
	}
	catch (_com_error e)
	{
	TCHAR szOutStr[256] = _T("Exception in RollbackTrans");
	if (m_pConnection->GetErrors()->Count > 0)
	{
	for (long i = 0; i < m_pConnection->GetErrors()->Count; ++i)
	{
	ErrorPtr pError = m_pConnection->GetErrors()->GetItem(_variant_t(i));
	m_SqlNativeError = pError->NativeError;

	_stprintf_s(szOutStr, 256, _T("ADO error, Desc:%s, Native Error:%d"), (TCHAR*)pError->Description, pError->NativeError);
	OutputDebugString(szOutStr);
	}
	//m_pConnection->GetErrors()->Clear();
	}
	throw std::exception(szOutStr);
	}*/
}

bool ADODATA::ExecuteSQL(const TCHAR *szSQL, int *pnRecordAffected)
{
	_variant_t RecordsAffected;
	if ((m_pConnection->State & adStateOpen) != adStateOpen)
	{
		OutputDebugString(_T("执行SQL语句前未连接数据库"));
		return false;
	}
	try
	{
		//m_pCommand->CommandText = (_bstr_t)szSQL;
		//m_pRecordset = m_pCommand->Execute(&RecordsAffected, NULL, adCmdText);
		m_SqlNativeError = 0;
		m_pConnection->GetErrors()->Clear();
		m_pRecordset = m_pConnection->Execute((_bstr_t)szSQL, &RecordsAffected, adCmdText);
		if (pnRecordAffected != NULL)
		{
			*pnRecordAffected = (int)RecordsAffected;
		}
	}
	catch (_com_error e)
	{
		if (m_pConnection->GetErrors()->Count > 0)
		{
			for (long i = 0; i < m_pConnection->GetErrors()->Count; ++i)
			{
				ErrorPtr pError = m_pConnection->GetErrors()->GetItem(_variant_t(i));
				m_SqlNativeError = pError->NativeError;
				TCHAR szOutStr[256];
				_stprintf_s(szOutStr, 256, _T("ADO error, Desc:%s, Native Error:%d"), (TCHAR*)pError->Description, pError->NativeError);
				OutputDebugString(szOutStr);
				if (pError->NativeError == 3113 || pError->NativeError == 3114)
				{
					// Not connect to oracle
					if (m_pConnection->State != adStateClosed)
					{
						//m_pConnection->Close();
						Disconnect();
					}
				}
			}
			//m_pConnection->GetErrors()->Clear();
		}
		OutputDebugString(e.ErrorMessage());
		OutputDebugString(szSQL);
		return false;
	}

	return true;
}

TString ADODATA::GetErrorDescription()
{
	TString sError;
	if (m_pConnection->GetErrors()->GetCount() > 0)
	{
		sError = (LPCTSTR)m_pConnection->GetErrors()->GetItem(_variant_t(0L))->Description;
	}
	return sError;
}

HRESULT ADODATA::CloseRecordset()
{
	if (m_pRecordset != NULL && m_pRecordset->State == 1)
	{
		return m_pRecordset->Close();
	}
	else
	{
		OutputDebugString(_T("未创建Recordset实例或Recordset未打开"));
		return -1;
	}
}

//-----------------------------------------------------------------------------
//+  Module Name:  AppendInsertparameter
//
//+  Description:  This Function append <field,value> to 'Field' and 'Values'
//                 Parameter for Insert SQL command.
//
//+     参数:
//
//          szFieldParam - 字符串.字段参数列表.
//
//          szField  - 字符串.字段名.
//
//          szValueParam - 字符串.值参数列表.
//
//          lpszValue - 字符串.字段值.
//
//+     返回值:
//          无.
//------------------------------------------------------------------------------
void ADODATA::AppendInsertParameter(TString &FieldParam, const TCHAR *szField, TString &ValueParam, _variant_t vtValue)
{
	if (vtValue.vt == VT_NULL || vtValue.vt == VT_EMPTY)
	{
		return;
	}

	TCHAR *lpszValue = NULL;

	switch (vtValue.vt)
	{
	case VT_DATE:
	{
		COleDateTime odt(vtValue.date);
		CString strTime = odt.Format(_T("%Y-%m-%d %H:%M:%S"));
		lpszValue = new TCHAR[64];
		_stprintf_s(lpszValue, 64, _T("to_date('%s', 'yyyy-mm-dd hh24:mi:ss')"), (LPCTSTR)strTime);
		break;
	}
	case VT_BSTR:
	{
		// String
		_bstr_t bstrValue(vtValue);
		int iMaxLen = _tcslen((TCHAR*)bstrValue) + 2 + 1;
		lpszValue = new TCHAR[iMaxLen];
		if (_tcsnicmp((TCHAR*)bstrValue, _T("direct="), _tcslen(_T("direct="))) == 0)
		{
			// direct string,don't put it in ''
			TCHAR* pString = _tcschr((TCHAR*)bstrValue, _T('=')) + 1;
			_tcscpy_s(lpszValue, iMaxLen, pString);
		}
		else
		{
			_stprintf_s(lpszValue, iMaxLen, _T("'%.*s'"), _tcslen((TCHAR*)bstrValue), (TCHAR*)bstrValue);
		}
		break;
	}
	case VT_INT:
	{
		// Int
		lpszValue = new TCHAR[32];
		_stprintf_s(lpszValue, 32, _T("%d"), vtValue.intVal);
		break;
	}
	case VT_UINT:
	{
		// Usigned int
		lpszValue = new TCHAR[32];
		_stprintf_s(lpszValue, 32, _T("%d"), vtValue.uintVal);
		break;
	}
	case VT_I2:
	{
		// Short
		lpszValue = new TCHAR[32];
		_stprintf_s(lpszValue, 32, _T("%d"), vtValue.iVal);
		break;
	}
	case VT_I4:
	{
		// Long
		lpszValue = new TCHAR[32];
		_stprintf_s(lpszValue, 32, _T("%ld"), vtValue.lVal);
		break;
	}
	case VT_I8:
	{
		// FILETIME
		SYSTEMTIME st;
		lpszValue = new TCHAR[64];
		::FileTimeToSystemTime((LPFILETIME)vtValue.llVal, &st);
		_stprintf_s(lpszValue, 64, _T("to_date('%04d-%02d-%02d %02d:%02d:%02d', 'yyyy-mm-dd hh24:mi:ss')"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		break;
	}
	case VT_R4:
	{
		// float
		CString s;
		s.Format(_T("%.3f"), vtValue.fltVal);
		if (s.GetLength() <= 15)
		{
			lpszValue = new TCHAR[s.GetLength() + 1];
			_tcscpy_s(lpszValue, s.GetLength() + 1, (LPCTSTR)s);
			//sprintf(lpszValue, "%.3f", vtValue.fltVal);
		}
		else
		{
			lpszValue = new TCHAR[8];
			_tcscpy_s(lpszValue, 8, _T("0.0"));
		}
		break;
	}
	case VT_R8:
	{
		// double
		CString s;
		s.Format(_T("%.3f"), vtValue.dblVal);
		if (s.GetLength() <= 15)
		{
			lpszValue = new TCHAR[s.GetLength() + 1];
			_tcscpy_s(lpszValue, s.GetLength() + 1, (LPCTSTR)s);
			//sprintf(lpszValue, "%.3f", vtValue.dblVal);
		}
		else
		{
			lpszValue = new TCHAR[8];
			_tcscpy_s(lpszValue, 8, _T("0.0"));
		}
		break;
	}
	default:
		return;
	}

	if (FieldParam.empty() || ValueParam.empty())
	{
		// 第一次添加参数
		FieldParam = szField;
		ValueParam = lpszValue;
	}
	else
	{
		// 在参数列表尾部追加参数
		FieldParam = FieldParam + _T(",") + szField;
		ValueParam = ValueParam + _T(",") + lpszValue;
	}

	if (lpszValue != NULL)
	{
		delete[] lpszValue;
		lpszValue = NULL;
	}

	return;
}

//-----------------------------------------------------------------------
//+  Module Name:  AppendUpdateParameter
//
//+  Description:  This Function append <field,value> to 'Set'
//                 Parameter for Update SQL command.
//
//+     参数:
//
//          szSetParam - 字符串.Set参数字符串，在此字符串尾部添加参数.
//
//          szField  - 字符串.字段名
//
//          szValue - 字符串.字段值
//
//+     返回值:
//          无.
//------------------------------------------------------------------------
void ADODATA::AppendUpdateParameter(TString &SetParam, const TCHAR *szField, _variant_t vtValue)
{
	if (vtValue.vt == VT_NULL || vtValue.vt == VT_EMPTY)
	{
		return;
	}

	TCHAR *lpszValue = NULL;
	switch (vtValue.vt)
	{
	case VT_DATE:
	{
		COleDateTime odt(vtValue.date);
		CString strTime = odt.Format(_T("%Y-%m-%d %H:%M:%S"));
		lpszValue = new TCHAR[64];
		_stprintf_s(lpszValue, 64, _T("to_date('%s', 'yyyy-mm-dd hh24:mi:ss')"), (LPCTSTR)strTime);
		break;
	}
	case VT_BSTR:
	{
		// String
		_bstr_t bstrValue(vtValue);
		int iMaxLen = _tcslen((TCHAR*)bstrValue) + 2 + 1;
		lpszValue = new TCHAR[iMaxLen];
		if (_tcsnicmp((TCHAR*)bstrValue, _T("direct="), _tcslen(_T("direct="))) == 0)
		{
			// direct string,don't put it in ''
			TCHAR* pString = _tcschr((TCHAR*)bstrValue, _T('=')) + 1;
			_tcscpy_s(lpszValue, iMaxLen, pString);
		}
		else
		{
			_stprintf_s(lpszValue, iMaxLen, _T("'%.*s'"), _tcslen((TCHAR*)bstrValue), (TCHAR*)bstrValue);
		}
		break;
	}
	case VT_INT:
	{
		// Int
		lpszValue = new TCHAR[32];
		_stprintf_s(lpszValue, 32, _T("%d"), vtValue.intVal);
		break;
	}
	case VT_UINT:
	{
		// Usigned int
		lpszValue = new TCHAR[32];
		_stprintf_s(lpszValue, 32, _T("%d"), vtValue.uintVal);
		break;
	}
	case VT_I2:
	{
		// Short
		lpszValue = new TCHAR[32];
		_stprintf_s(lpszValue, 32, _T("%d"), vtValue.iVal);
		break;
	}
	case VT_I4:
	{
		// Long
		lpszValue = new TCHAR[32];
		_stprintf_s(lpszValue, 32, _T("%ld"), vtValue.lVal);
		break;
	}
	case VT_I8:
	{
		// FILETIME
		SYSTEMTIME st;
		lpszValue = new TCHAR[64];
		::FileTimeToSystemTime((LPFILETIME)vtValue.llVal, &st);
		_stprintf_s(lpszValue, 64, _T("to_date('%04d-%02d-%02d %02d:%02d:%02d', 'yyyy-mm-dd hh24:mi:ss')"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		break;
	}
	case VT_R4:
	{
		// float
		CString s;
		s.Format(_T("%.3f"), vtValue.fltVal);
		lpszValue = new TCHAR[s.GetLength() + 1];
		_tcscpy_s(lpszValue, s.GetLength() + 1, (LPCTSTR)s);
		//sprintf(lpszValue, "%.3f", vtValue.fltVal);
		break;
	}
	case VT_R8:
	{
		// double
		CString s;
		s.Format(_T("%.3f"), vtValue.dblVal);
		lpszValue = new TCHAR[s.GetLength() + 1];
		_tcscpy_s(lpszValue, s.GetLength() + 1, (LPCTSTR)s);
		//sprintf(lpszValue, "%.3f", vtValue.dblVal);
		break;
	}
	default:
		return;
	}

	if (SetParam.empty())
	{
		// 第一次添加参数
		SetParam = SetParam + szField + _T("=") + lpszValue;
	}
	else
	{
		// 在参数列表尾部追加参数
		SetParam = SetParam + _T(",") + szField + _T("=") + lpszValue;
	}

	if (lpszValue != NULL)
	{
		delete[] lpszValue;
		lpszValue = NULL;
	}

	return;
}

//bool ADODATA::GetRecordset(TCHAR *sqlstr)
//{
//  CString m_sqlStr;
//  BSTR m_bstrSqlStr;
//
//  m_sqlStr=sqlstr;
//  m_bstrSqlStr=m_sqlStr.AllocSysString();
//  if(m_pRecordset->State==1)
//      m_pRecordset->Close();
//  try
//  {
//      m_pRecordset->Open(m_bstrSqlStr,(IDispatch*)m_pConnection,adOpenDynamic,adLockOptimistic,adCmdText);
//  }
//  catch(_com_error e)
//  {
//#ifdef _DEBUG
//      CString errorMessage;
//      errorMessage.Format("%s",(LPTSTR)e.Description());
//      //      AfxMessageBox(errorMessage);
//#endif
//      return false;
//  }
//  return true;
//}
//bool ADODATA::GetRecordset(CString sqlstr)
//{
//  CString m_sqlStr;
//  BSTR m_bstrSqlStr;
//
//  m_sqlStr=sqlstr;
//  m_bstrSqlStr=m_sqlStr.AllocSysString();
//  if(m_pRecordset->State==1)
//      m_pRecordset->Close();
//  try
//  {
//      m_pRecordset->Open(m_bstrSqlStr,(IDispatch*)m_pConnection,adOpenDynamic,adLockOptimistic,adCmdText);
//  }
//  catch(_com_error e)
//  {
//#ifdef _DEBUG
//      CString errorMessage;
//      errorMessage.Format("%s",(LPTSTR)e.Description());
//      //      AfxMessageBox(errorMessage);
//#endif
//      return false;
//  }
//  return true;
//}
//bool ADODATA::GetRecordset(BSTR sqlstr)
//{
//  CString m_sqlStr;
//  BSTR m_bstrSqlStr;
//
//  m_sqlStr=sqlstr;
//  m_bstrSqlStr=m_sqlStr.AllocSysString();
//  if(m_pRecordset->State==1)
//      m_pRecordset->Close();
//  try
//  {
//      m_pRecordset->Open(m_bstrSqlStr,(IDispatch*)m_pConnection,adOpenDynamic,adLockOptimistic,adCmdText);
//  }
//  catch(_com_error e)
//  {
//#ifdef _DEBUG
//      CString errorMessage;
//      errorMessage.Format("%s",(LPTSTR)e.Description());
//      //      AfxMessageBox(errorMessage);
//#endif
//      return false;
//  }
//  return true;
//}
//

//bool ADODATA::Execute(CString sqlstr)
//{
//  CString m_sqlStr;
//  BSTR m_bstrSqlStr;
//  _variant_t RecordsAffected;
//
//  m_sqlStr=sqlstr;
//  m_bstrSqlStr=m_sqlStr.AllocSysString();
//  if(m_pConnection->State!=1)
//      return false;
//  try
//  {
//      m_pConnection->BeginTrans();
//      m_pConnection->Execute(m_bstrSqlStr,&RecordsAffected,adCmdText);
//      m_pConnection->CommitTrans();
//  }
//  catch(_com_error e)
//  {
//      m_pConnection->RollbackTrans();
//#ifdef _DEBUG
//      CString errorMessage;
//      errorMessage.Format("%s",(LPTSTR)e.Description());
//      //      AfxMessageBox(errorMessage);
//#endif
//      return false;
//  }
//
//  return true;
//}
//bool ADODATA::Execute(BSTR sqlstr)
//{
//  CString m_sqlStr;
//  BSTR m_bstrSqlStr;
//  _variant_t RecordsAffected;
//
//  m_sqlStr=sqlstr;
//  m_bstrSqlStr=m_sqlStr.AllocSysString();
//  if(m_pConnection->State!=1)
//      return false;
//  try
//  {
//      m_pConnection->BeginTrans();
//      m_pConnection->Execute(m_bstrSqlStr,&RecordsAffected,adCmdText);
//      m_pConnection->CommitTrans();
//  }
//  catch(_com_error e)
//  {
//      m_pConnection->RollbackTrans();
//#ifdef _DEBUG
//      CString errorMessage;
//      errorMessage.Format("%s",(LPTSTR)e.Description());
//      //      AfxMessageBox(errorMessage);
//#endif
//      return false;
//  }
//
//  return true;
//}
//
//int ADODATA::GetRecordCount(void)
//{
//  int n=0;
//  try
//  {
//      if(m_pRecordset->adoEOF)
//          return 0;
//      m_pRecordset->MoveFirst();
//      while(!m_pRecordset->adoEOF)
//      {
//          n++;
//          m_pRecordset->MoveNext();
//      }
//      m_pRecordset->MoveFirst();
//      return n;
//  }
//  catch(_com_error e)
//  {
//#ifdef _DEBUG
//      CString errorMessage;
//      errorMessage.Format("%s",(LPTSTR)e.Description());
//      //      AfxMessageBox(errorMessage);
//#endif
//      return -1;
//  }
//}
//
//bool ADODATA::ExecProc(void)
//{
//  _ParameterPtr m_pParameter1;
//  _ParameterPtr m_pParameter2;
//  _ParameterPtr m_pParameter3;
//  m_pParameter1.CreateInstance("ADODB.Parameter");
//  m_pParameter2.CreateInstance("ADODB.Parameter");
//  m_pParameter3.CreateInstance("ADODB.Parameter");
//
//  _CommandPtr m_pCommand1;
//  m_pCommand1.CreateInstance(_uuidof(Command));
//
//  CString mystr="addNum";
//
//  if(m_pConnection->State!=1)
//      return false;
//  try
//  {
//      m_pParameter1->Name="n1";
//      m_pParameter1->Type=adSingle;
//      m_pParameter1->Size=4;
//      m_pParameter1->Direction=adParamInput;
//      m_pParameter1->Value=_variant_t(10.0);
//      m_pCommand1->Parameters->Append(m_pParameter1);
//
//      m_pParameter2->Name="n2";
//      m_pParameter2->Type=adSingle;
//      m_pParameter2->Size=4;
//      m_pParameter2->Direction=adParamInput;
//      m_pParameter2->Value=_variant_t(20.0);
//      m_pCommand1->Parameters->Append(m_pParameter2);
//
//      m_pParameter3->Name="result";
//      m_pParameter3->Type=adSingle;
//      m_pParameter3->Size=4;
//      m_pParameter3->Direction=adParamOutput;
//      m_pCommand1->Parameters->Append(m_pParameter3);
//
//      m_pCommand1->ActiveConnection=m_pConnection;
//      m_pCommand1->CommandText=mystr.GetBuffer(0);
//      m_pCommand1->CommandType=adCmdStoredProc;
//      m_pCommand1->Execute(NULL, NULL, adCmdStoredProc);
//
//      float result=(float)(m_pParameter3->Value);
//
//      m_pParameter1.Release();
//      m_pParameter2.Release();
//      m_pParameter3.Release();
//      m_pCommand1.Release();
//  }
//  catch(_com_error e)
//  {
//#ifdef _DEBUG
//      CString errorMessage;
//      errorMessage.Format("%s",(LPTSTR)e.Description());
//      //      AfxMessageBox(errorMessage);
//#endif
//      m_pParameter1.Release();
//      m_pParameter2.Release();
//      m_pParameter3.Release();
//      m_pCommand1.Release();
//
//      return false;
//  }
//
//  return true;
//}