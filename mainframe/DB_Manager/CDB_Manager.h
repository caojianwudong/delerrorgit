// CDB_Manager.h: interface for the CDB_Manager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDB_MANAGER_H__FD023842_B65A_49CE_9A81_8A2D7022BCBE__INCLUDED_)
#define AFX_CDB_MANAGER_H__FD023842_B65A_49CE_9A81_8A2D7022BCBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DB_ResultSet.h"
#include <MAP>

using namespace std;

class DBConnection;
class __declspec(dllexport)CDB_Manager  
{
public:
	//CDB_Manager();
	CDB_Manager(bool isAutoConn = true);
	virtual ~CDB_Manager();

	//isAutoConn���������Ƿ��Զ�������������
	//�Զ�����ʱ�����Զ�����dbconfig�����õ�����
	//�ֶ�����ʱ��ͨ��AddOneConnection��������
	static CDB_Manager* GetDBManagerPtr(bool isAutoConn = true);
	static void DestroyDBManagerPtr();

	//����һ������
	//idbCategoryΪ���ݿ����DB_TYPE_MYSQLΪmysql��DB_TYPE_PGSQLΪpostgres
	void AddOneConnection(int idbCategory,const char* strconname,const char* strservice,const char* strdb,const char* strschema,const char* strdba,const char* strport,const char* strdbpw);

	//ѡ�񲢴�ָ�����ݿ�����
	bool ChooseDB(int itype); //ͨ�����ݿ����ͱ�Ŵ�
	bool ChooseDB(const char* sConnectionname);//ͨ����������,�˽ӿڶ�Ӧ��AddOneConnection�������ӵ�����

	//��ʽ�ر�ָ�����ݿ�����
	void CloseDB(int itype);//��Ӧ�ر�ChooseDB(int itype)�򿪵�����
	void CloseDB(const char* sConnectionname);//��Ӧ�ر�ChooseDB(const char* sConnectionname)�򿪵�����

	//ִ�в�ѯsql��䷵��CDB_ResultSet��ѯ���������
	//sResName����Ϊ��������ƣ����û�ָ����Ĭ��Ϊ�գ���Ϊ�յ�ʱ��ӿڽ��Զ�����
	//��ѯ�����˳�����������統ǰ�����Ϊ��n(nΪ����,n>0)�β�ѯ��,������Ϊ"n"��
	//ע��˴���ָ�Ĳ�ѯ�����˳����Ե���û���ͷŵĲ�ѯ�����
	CDB_ResultSet* ExcuteQuerySql(const char* sSql, const char* sResName = "");

	//���ݽ�������Ʒ��ؽ����
	//���������Ϊ����ExcuteQuerySql�ӿ�ʱ���������
	CDB_ResultSet* GetResultSetPtrByName(const char* sResName);

	//ִ�зǲ�ѯsql
	bool ExcuteSql(const char* sSql,int& iAffect);

	//�õ�ִ��sql��Ĵ�����Ϣ
	const char* GetErrorMessage();

	//�ͷ����в�ѯ�����
	void ReleaseAllRes();

	//�ͷ�ָ����ѯ�����
	void ReleaseRes(CDB_ResultSet** pDBResultSet);//����ָ���ͷ�
	void ReleaseRes(const char* sResName);//���������ͷ�


private:
	static CDB_Manager* m_pDBManagerPtr;
	
	//��ǰʵ���µ�����δ�ͷŵĽ����
	std::map<std::string,CDB_ResultSet*> m_mapRes;

	//����
	std::string m_sError;

	//���ݿ���
	int  m_idbtype;
	std::string m_sConnectionname;

	std::map<int,DBConnection*> m_mapDBConnection;
	std::vector<DBConnection*> m_vtDBConnection;
	

private:
	//�ر��������ݿ�����
	void CloseAllDB();

	//�õ���ǰ����
	DBConnection* GetConnection(int itype);
	DBConnection* GetConnection(const char* sConnectionname);

	bool ReadConfig();
	void SetInitDB(const char* strid,const char* strservice,const char* strdb,const char* strdba,const char* strport,const char* strdbpw,const char* strconname,const char* strschema);
	
};

#endif // !defined(AFX_CDB_MANAGER_H__FD023842_B65A_49CE_9A81_8A2D7022BCBE__INCLUDED_)
