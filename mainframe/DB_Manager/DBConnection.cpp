// DBConnection.cpp: implementation of the DBConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DB_Manager.h"
#include "DBConnection.h"
#include "..\..\include\mysql\mysql.h"
#include "..\..\include\pq\libpq-fe.h"
#include "Db_Definition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBConnection::DBConnection()
{	
	m_pg = NULL;
	m_mysql = NULL;

	m_sError = "";
}

DBConnection::~DBConnection()
{
	Close();
}

bool DBConnection::Connection()
{
	switch(m_idbnumber)
	{
		case DB_QCTASK_MYSQL : 
		case DB_OKERROR_MYSQL : 
		case DB_LOG_MYSQL :
		case DB_POIEDIT_TASK_MYSQL :
		case DB_FIELDDATA_MYSQL :
		case DB_ERRORLOG_MYSQL :
		case DB_TASK_MYSQL :
		case DB_USR_MYSQL :
		case DB_POIEDIT_PROJECT_MYSQL :
		case DB_EXTEND1_MYSQL:
		case DB_EXTEND2_MYSQL:
		{
			m_iDbType = DB_TYPE_MYSQL;

		
			if( m_mysql != NULL)
			{
				Close();
			}
			
			m_mysql = new MYSQL;
			//初始化
			mysql_init( m_mysql );
			//连接数据库
			if( !mysql_real_connect(m_mysql,m_strdbservice.c_str(),m_strdba.c_str(),m_strdbpw.c_str(),m_strdb.c_str(),atoi(m_strdbport.c_str()),NULL,0))
			{
				//iErrorCode = mysql_errno(m_mysql);
				//strcpy( sErrorInfo,mysql_error(m_mysql));
				m_sError = mysql_error(m_mysql);
				//CString sMess;
				//sMess.Format("ERROR:0\n\n%s",sErrorInfo);
				//MessageBox(NULL,sErrorInfo,"连接失败",MB_ICONERROR);
				if( !mysql_real_connect(m_mysql,m_strdbservice.c_str(),m_strdba.c_str(),m_strdbpw.c_str(),m_strdb.c_str(),atoi(m_strdbport.c_str()),NULL,0))
					return false;
			}

			break;
		}
			
		case DB_QCTASK_PGSQL :
		case DB_OKERROR_PGSQL :
		case DB_LOG_PGSQL :
		case DB_POIEDIT_TASK_PGSQL :
		case DB_FIELDDATA_PGSQL :
		case DB_ERRORLOG_PGSQL :
		case DB_TASK_PGSQL :
		case DB_USR_PGSQL :
		case DB_POIEDIT_PROJECT_PGSQL: 
		case DB_EXTEND1_PGSQL:
		case DB_EXTEND2_PGSQL:
		{
			m_iDbType = DB_TYPE_PGSQL;

			if(m_pg != NULL)
			{
				Close();
			}
			
			char *pgoptions,*pgtty;
			pgoptions=NULL;
			pgtty=NULL;
			
			m_pg=PQsetdbLogin(m_strdbservice.c_str(),m_strdbport.c_str(),pgoptions,pgtty,m_strdb.c_str(),m_strdba.c_str(),m_strdbpw.c_str());
			if(PQstatus(m_pg)==CONNECTION_BAD) // or conn==NULL 
			{
				Close();
				m_pg=PQsetdbLogin(m_strdbservice.c_str(),m_strdbport.c_str(),pgoptions,pgtty,m_strdb.c_str(),m_strdba.c_str(),m_strdbpw.c_str());
				if(PQstatus(m_pg)==CONNECTION_BAD)
				{
					m_sError = PQerrorMessage(m_pg);
					//MessageBox(NULL,sMess,"连接失败",MB_ICONERROR);
					Close();
					return false;
				}
				
			  }

			break;
		}
	}

	return true;
}

bool DBConnection::Connection(int iCatagory)
{
	m_iDbType = iCatagory;

	switch(m_iDbType)
	{
		case DB_TYPE_MYSQL :
		{
			
			if( m_mysql != NULL)
			{
				Close();
			}
			
			m_mysql = new MYSQL;
			//初始化
			mysql_init( m_mysql );
			//连接数据库
			if( !mysql_real_connect(m_mysql,m_strdbservice.c_str(),m_strdba.c_str(),m_strdbpw.c_str(),m_strdb.c_str(),atoi(m_strdbport.c_str()),NULL,0))
			{
				//iErrorCode = mysql_errno(m_mysql);
				//strcpy( sErrorInfo,mysql_error(m_mysql));
				m_sError = mysql_error(m_mysql);
				//CString sMess;
				//sMess.Format("ERROR:0\n\n%s",sErrorInfo);
				//MessageBox(NULL,sErrorInfo,"连接失败",MB_ICONERROR);
				if( !mysql_real_connect(m_mysql,m_strdbservice.c_str(),m_strdba.c_str(),m_strdbpw.c_str(),m_strdb.c_str(),atoi(m_strdbport.c_str()),NULL,0))
					return false;
			}
			
			break;
		}
		case DB_TYPE_PGSQL:
		{
			
			if(m_pg != NULL)
			{
				Close();
			}
			
			char *pgoptions,*pgtty;
			pgoptions=NULL;
			pgtty=NULL;
			
			m_pg=PQsetdbLogin(m_strdbservice.c_str(),m_strdbport.c_str(),pgoptions,pgtty,m_strdb.c_str(),m_strdba.c_str(),m_strdbpw.c_str());
			if(PQstatus(m_pg)==CONNECTION_BAD) // or conn==NULL 
			{
				Close();
				m_pg=PQsetdbLogin(m_strdbservice.c_str(),m_strdbport.c_str(),pgoptions,pgtty,m_strdb.c_str(),m_strdba.c_str(),m_strdbpw.c_str());
				if(PQstatus(m_pg)==CONNECTION_BAD)
				{
					m_sError = PQerrorMessage(m_pg);
					//MessageBox(NULL,sMess,"连接失败",MB_ICONERROR);
					Close();
					return false;
				}
				
			}
			
			break;
		}
	}

	return true;
}

bool DBConnection::Close()
{
	if( m_pg != NULL)
	{
		PQfinish(m_pg);
		//delete m_pg;
		m_pg = NULL;
	}

	if(m_mysql != NULL)
	{
		mysql_close(m_mysql);
		delete m_mysql;
		m_mysql = NULL;
	}

	return true;
}

int DBConnection::GetCurDBType()
{
	return m_iDbType;
}

PGconn* DBConnection::GetCurConn_PGconn()
{
	return m_pg;
}

MYSQL* DBConnection::GetCurConn_MySqlconn()
{
	return m_mysql;
}

const char* DBConnection::GetConnError()
{
	return m_sError.c_str();
}


