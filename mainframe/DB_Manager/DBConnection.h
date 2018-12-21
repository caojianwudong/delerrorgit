// DBConnection.h: interface for the DBConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBCONNECTION_H__6FF8B6E8_85AF_4098_BE66_A5ACEE84434E__INCLUDED_)
#define AFX_DBCONNECTION_H__6FF8B6E8_85AF_4098_BE66_A5ACEE84434E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\..\include\pq\libpq-fe.h"
#include "..\..\include\mysql\mysql.h"
#include <string>

//���ݿ����ӱ��
// enum DBNUMBER
// {
// 	DB_QCTASK_MYSQL = 1, //�ʼ������
// 	DB_OKERROR_MYSQL = 2 ,            //ok�����
// 	DB_EMP_MYSQL = 3 ,			   // EMP·�����ݿ�
// 	DB_POIEDIT_TASK_MYSQL = 4,       //POI�༭�����
// 	DB_FIELDDATA_MYSQL = 5,		//��ҵ���Ͽ�
// 	DB_ERRORLOG_MYSQL = 6,			//�����
// 	DB_TASK_MYSQL	= 7	,			// �����
// 	DB_USR_MYSQL = 8,				// �û������
// 	DB_POIEDIT_PROJECT_MYSQL = 9,
// 	DB_QCTASK_PGSQL, //�ʼ������
// 	DB_OKERROR_PGSQL ,            //ok�����
// 	DB_EMP_PGSQL ,			   // EMP·�����ݿ�
// 	DB_POIEDIT_TASK_PGSQL,       //POI�༭�����
// 	DB_FIELDDATA_PGSQL,		//��ҵ���Ͽ�
// 	DB_ERRORLOG_PGSQL,			//�����
// 	DB_TASK_PGSQL,			// �����
// 	DB_USR_PGSQL,				// �û������
// 	DB_POIEDIT_PROJECT_PGSQL
// };

//���ݿ�����
// enum DBTYPE
// {
// 	DB_TYPE_MYSQL = 1,//mysql���ݿ�
// 	DB_TYPE_PGSQL//postgres���ݿ�
// };

class DBConnection  
{
public:
	DBConnection();
	virtual ~DBConnection();

	//�������ݿ�
	bool Connection();
	bool Connection(int iCatagory);

	//�ر�����
	bool Close();

	//���ݵ�ǰ���ݿ��ŵõ���ǰ���ݿ�����(mysql ���� postgresql).
	//����ֵ��1Ϊmysql��2Ϊpostgresql
	int GetCurDBType();

	//�õ�postgres���ݿ�����
	PGconn* GetCurConn_PGconn();

	//�õ�mysql���ݿ�����
	MYSQL* GetCurConn_MySqlconn();

	//�õ����Ӵ�����Ϣ
	const char* GetConnError();


private:
	PGconn * m_pg;

	MYSQL* m_mysql;

	int m_iDbType;

	std::string m_sError;

public: 
	int    m_idbnumber;//���ݿ���
	std::string	m_strconname ;//������
	
	std::string       m_strdbservice;//ip
	std::string      m_strdb;//���ݿ�
	std::string       m_strdba;//�û���
	std::string       m_strdbpw;//����
	std::string       m_strdbport;//�˿�
	std::string		  m_strschema;//ģʽ
	std::string       m_strallschemas;//��ǰ���ݿ�ģʽ����·��

};

#endif // !defined(AFX_DBCONNECTION_H__6FF8B6E8_85AF_4098_BE66_A5ACEE84434E__INCLUDED_)
