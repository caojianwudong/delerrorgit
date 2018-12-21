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

//数据库链接编号
// enum DBNUMBER
// {
// 	DB_QCTASK_MYSQL = 1, //质检任务库
// 	DB_OKERROR_MYSQL = 2 ,            //ok错误库
// 	DB_EMP_MYSQL = 3 ,			   // EMP路径数据库
// 	DB_POIEDIT_TASK_MYSQL = 4,       //POI编辑任务库
// 	DB_FIELDDATA_MYSQL = 5,		//外业资料库
// 	DB_ERRORLOG_MYSQL = 6,			//错误库
// 	DB_TASK_MYSQL	= 7	,			// 任务库
// 	DB_USR_MYSQL = 8,				// 用户管理库
// 	DB_POIEDIT_PROJECT_MYSQL = 9,
// 	DB_QCTASK_PGSQL, //质检任务库
// 	DB_OKERROR_PGSQL ,            //ok错误库
// 	DB_EMP_PGSQL ,			   // EMP路径数据库
// 	DB_POIEDIT_TASK_PGSQL,       //POI编辑任务库
// 	DB_FIELDDATA_PGSQL,		//外业资料库
// 	DB_ERRORLOG_PGSQL,			//错误库
// 	DB_TASK_PGSQL,			// 任务库
// 	DB_USR_PGSQL,				// 用户管理库
// 	DB_POIEDIT_PROJECT_PGSQL
// };

//数据库类型
// enum DBTYPE
// {
// 	DB_TYPE_MYSQL = 1,//mysql数据库
// 	DB_TYPE_PGSQL//postgres数据库
// };

class DBConnection  
{
public:
	DBConnection();
	virtual ~DBConnection();

	//链接数据库
	bool Connection();
	bool Connection(int iCatagory);

	//关闭链接
	bool Close();

	//根据当前数据库编号得到当前数据库类型(mysql 还是 postgresql).
	//返回值：1为mysql；2为postgresql
	int GetCurDBType();

	//得到postgres数据库链接
	PGconn* GetCurConn_PGconn();

	//得到mysql数据库链接
	MYSQL* GetCurConn_MySqlconn();

	//得到连接错误信息
	const char* GetConnError();


private:
	PGconn * m_pg;

	MYSQL* m_mysql;

	int m_iDbType;

	std::string m_sError;

public: 
	int    m_idbnumber;//数据库编号
	std::string	m_strconname ;//链接名
	
	std::string       m_strdbservice;//ip
	std::string      m_strdb;//数据库
	std::string       m_strdba;//用户名
	std::string       m_strdbpw;//密码
	std::string       m_strdbport;//端口
	std::string		  m_strschema;//模式
	std::string       m_strallschemas;//当前数据库模式查找路径

};

#endif // !defined(AFX_DBCONNECTION_H__6FF8B6E8_85AF_4098_BE66_A5ACEE84434E__INCLUDED_)
