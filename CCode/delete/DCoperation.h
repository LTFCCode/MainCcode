#pragma once

#import "C:\ProgramFiles\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

class CDBOperation
{
public:
	//��ʼ�����ݿ������Ҫ�Ķ���
	CDBOperation(void);
	~CDBOperation(void);
	//���������ݿ�
	boolConnToDB(char *ConnectionString, char *UserID, char*Password);

	//���ݿ��������
	//��ѯ����ɾ���Լ����
	_RecordsetPtr ExecuteWithResSQL(constchar *);
	//boolExecuteNoResSQL(const char *);//delete and add

private:
	voidPrintErrorInfo(_com_error &);

private:
	//��ʼ�����ݿ����ӡ������¼��
	_ConnectionPtr CreateConnPtr();
	_CommandPtr CreateCommPtr();
	_RecordsetPtr CreateRecsetPtr();

private:
	//���ݿ�������Ҫ�����ӡ������������
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
};