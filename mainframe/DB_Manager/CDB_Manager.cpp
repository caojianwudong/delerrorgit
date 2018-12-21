// CDB_Manager.cpp: implementation of the CDB_Manager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DB_Manager.h"
#include "CDB_Manager.h"
#include "DBConnection.h"
#include "..\..\include\pq\libpq-fe.h"
#include "..\db_manager\Db_Definition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void WriteLog(const char* log)
{
	char path[1024] ;
	::GetModuleFileName( NULL, path, 1024) ;
	std::string strAppPath = path ;
	int ipos = strAppPath.rfind('\\') ;
	if ( ipos != -1)
	{
		strAppPath = strAppPath.substr(0,ipos+1) ;
	}
	
	CTime time_current ;
	time_current = CTime::GetCurrentTime() ;
// 	CString strtime = time_current.Format("%Y-%m-%d %H:%M:%S	") ;
	char stime[100] ;
	sprintf(stime, "%d-%d-%d %d-%d-%d	", time_current.GetYear(), time_current.GetMonth(),time_current.GetDay(),time_current.GetHour(),time_current.GetMinute(),time_current.GetSecond()) ;
	strAppPath += "db_manager.log" ;
	
	CStdioFile stfile ;
	if (!stfile.Open( strAppPath.c_str(), CFile::modeCreate |CFile::modeReadWrite|CFile::modeNoTruncate))
	{
		return ;
	}
	stfile.SeekToEnd() ;
	stfile.WriteString( stime) ;
// 	CString strtemp = log ;
	stfile.WriteString( log) ;
	stfile.WriteString("\n") ;
	stfile.Close() ;
	
}
CDB_Manager* CDB_Manager::m_pDBManagerPtr = NULL;
// 
// CDB_Manager::CDB_Manager()
// {
// 
// }

CDB_Manager::CDB_Manager(bool isAutoConn /*= true*/)
{
	m_idbtype = -1;

	if(isAutoConn)
	{
		ReadConfig();
	}
}

CDB_Manager::~CDB_Manager()
{
	CloseAllDB();
	ReleaseAllRes();
}

bool CDB_Manager::ReadConfig()
{
	CString strpath;
	TCHAR cAppPathName[1024];
	int nTempFileLen = 0;
	::GetModuleFileName(NULL,cAppPathName,1024);
	strpath.Format("%s",cAppPathName);	
	nTempFileLen = strpath.ReverseFind ('\\');
	strpath = strpath.Left(nTempFileLen+1);
	CString strtemppath = strpath ;
	strpath = strtemppath + "config\\dbconfig.ini";
	
	
	CStdioFile file,file2;
	if(!file.Open(strpath,CFile::modeRead))
	{
		return false;
	}
	
	CString str;
	
	CString temp ;
	CString strid,strdbname,strusername,strpassword,strhost ,sport,strconname,strschema;
	//if ( streamconfig )
	{
		bool bhas = false ;
		while ( file.ReadString(temp))
		{
			if ( temp.Find("[id]") != -1)
			{
				strid = temp.Mid(4) ;
			}
			if ( temp.Find("[connname]") != -1)
			{
				strconname = temp.Mid(10) ;
			}
			if ( temp.Find("[ip]") != -1)
			{
				strhost = temp.Mid(4) ;
			}
			if ( temp.Find("[dbname]") != -1)
			{
				strdbname = temp.Mid(8) ;
			}
			if ( temp.Find("[schema]") != -1)
			{
				strschema = temp.Mid(8) ;
			}
			if ( temp.Find("[user]") != -1)
			{
				strusername = temp.Mid(6) ;
			}
			if ( temp.Find("[password]") != -1)
			{
				strpassword = temp.Mid(10) ;
			}
			if ( temp.Find("[port]") != -1)
			{
				sport = temp.Mid(6) ;
			}

			if(!strid.IsEmpty() && !strconname.IsEmpty() && !strhost.IsEmpty() 
				&& !strdbname.IsEmpty() && !strusername.IsEmpty() && !strpassword.IsEmpty() && !sport.IsEmpty())
			{
				SetInitDB(strid,strhost,strdbname,strusername,sport,strpassword,strconname,strschema);

				strid = "";
				strconname = "";
				strhost = "";
				strdbname = "";
				strusername = "";
				strpassword = "";
				sport = "";
				strschema = "";
			}
			
		}
		file.Close() ;
	}

	return true;
}

void CDB_Manager::SetInitDB(const char* strid,const char* strservice,const char* strdb,const char* strdba,const char* strport,const char* strdbpw,const char* strconname,const char* strschema)
{
	int id = atoi(strid);

	std::map<int,DBConnection*>::iterator it = m_mapDBConnection.find(id);

	if(it == m_mapDBConnection.end())
	{
		DBConnection* pDBConnection = new DBConnection;
		pDBConnection->m_strconname = strconname;
		pDBConnection->m_strdb = strdb;
		pDBConnection->m_strschema = strschema;
		pDBConnection->m_strdba = strdba;
		pDBConnection->m_strdbport = strport;
		pDBConnection->m_idbnumber = id;
		pDBConnection->m_strdbpw = strdbpw;
		pDBConnection->m_strdbservice = strservice;
		bool bOk = pDBConnection->Connection();

		if(bOk)
		{
			m_mapDBConnection.insert(std::map<int,DBConnection*>::value_type(id,pDBConnection));
		}
		else
		{
			std::string sconnError = pDBConnection->GetConnError();

			delete pDBConnection;
			pDBConnection = NULL;

			m_sError = "连接失败:";
			m_sError += sconnError;
		}
		

	}
}

CDB_Manager* CDB_Manager::GetDBManagerPtr(bool isAutoConn /*= true*/)
{
	if(m_pDBManagerPtr == NULL)
	{
		m_pDBManagerPtr = new CDB_Manager(isAutoConn);
	}

	return m_pDBManagerPtr;
}

void CDB_Manager::DestroyDBManagerPtr()
{
	if(m_pDBManagerPtr != NULL)
	{
		delete m_pDBManagerPtr;

		m_pDBManagerPtr = NULL;
	}
}

bool CDB_Manager::ChooseDB(int itype)
{
	m_sConnectionname = "";//将按链接名的置为空
	m_idbtype = itype;

	
	DBConnection* pDbConnection;
	pDbConnection = GetConnection(m_idbtype);
	if(pDbConnection != NULL && pDbConnection->GetCurDBType() == DB_TYPE_PGSQL)
	{
		if(!pDbConnection->m_strschema.empty())
		{
			PGconn* pgConn = NULL;
			pgConn = pDbConnection->GetCurConn_PGconn();
			if(PQstatus(pgConn)==CONNECTION_BAD || pgConn == NULL) 
			{
				pDbConnection->Connection(pDbConnection->GetCurDBType());
				
				pgConn = pDbConnection->GetCurConn_PGconn();
				if(PQstatus(pgConn)==CONNECTION_BAD || pgConn == NULL)
				{
					pDbConnection->Close();
					
					m_sError = "数据库连接失败";
					return false;
				}
								
			}
			
			std::string str = "set search_path to " + pDbConnection->m_strschema + ",\"$user\",public,topology";
			const char* sSetschemaSql = str.c_str();
			PQexec(pgConn,sSetschemaSql);
		}
		
	}

	

	return true;
}

bool CDB_Manager::ChooseDB(const char* sConnectionname)
{
	m_idbtype = -1;//将按类型的置为-1
	m_sConnectionname = sConnectionname;

	DBConnection* pDbConnection;
	pDbConnection = GetConnection(m_sConnectionname.c_str());

	if(pDbConnection != NULL && pDbConnection->GetCurDBType() == DB_TYPE_PGSQL)
	{		
		if(!pDbConnection->m_strschema.empty())
		{
			PGconn* pgConn = NULL;
			pgConn = pDbConnection->GetCurConn_PGconn();
			if(PQstatus(pgConn)==CONNECTION_BAD || pgConn == NULL) 
			{
				pDbConnection->Connection(pDbConnection->GetCurDBType());
				
				pgConn = pDbConnection->GetCurConn_PGconn();
				if(PQstatus(pgConn)==CONNECTION_BAD || pgConn == NULL)
				{
					pDbConnection->Close();
					
					m_sError = "数据库连接失败";
					return false;
				}
								
			}
			
			std::string str = "set search_path to " + pDbConnection->m_strschema + ",\"$user\",public,topology";
			const char* sSetschemaSql = str.c_str();
			PQexec(pgConn,sSetschemaSql);
		}
	}

	return true;
}

CDB_ResultSet* CDB_Manager::ExcuteQuerySql(const char* sSql, const char* sResName /*= ""*/)
{
	m_sError = "";//置空

	DBConnection* pDbConnection; 
	if(m_idbtype > 0 && m_sConnectionname.empty())
	{
		pDbConnection = GetConnection(m_idbtype);
	}
	else if(!m_sConnectionname.empty() && m_idbtype < 0)
	{
		pDbConnection = GetConnection(m_sConnectionname.c_str());
	}
	else return NULL;

	if(pDbConnection == NULL)
	{
		if(m_sError.empty())
			m_sError = "无效的数据库连接";
		//MessageBox(NULL,"无效的数据库","错误",MB_ICONERROR);
		return NULL;
	}

	int iCurDbType = pDbConnection->GetCurDBType();

	if(iCurDbType == 1)
	{
		MYSQL* pMySql = NULL;
		pMySql = pDbConnection->GetCurConn_MySqlconn();
		
		mysql_set_character_set(pMySql,"GBK");
		
		if ( mysql_query(pMySql,sSql) )
		{
			int iError = mysql_errno(pMySql);
			if ( iError == 2013 || iError == 2006)
			{
				if( pDbConnection->Connection(iCurDbType))
				{
					pMySql = pDbConnection->GetCurConn_MySqlconn();
					
					mysql_set_character_set(pMySql,"GBK");
					//strcpy(szSql,sSql);
					if ( mysql_query(pMySql,sSql) )
					{
						//iError = mysql_errno(pMySql);
						//strcpy( szErrorInfo,mysql_error(pMySql));
						m_sError = mysql_error(pMySql);
// 						CString sMess;
// 						sMess.Format("ERROR:11\n\n%s",szErrorInfo);
// 						MessageBox(NULL,sMess,"二次连接错误",MB_ICONERROR);
						return NULL;
					}
				}
			} 
			else
			{
// 				iError = mysql_errno(pMySql);
// 				strcpy( szErrorInfo,mysql_error(pMySql));
// 				CString sMess;
// 				sMess.Format("ERROR:11\n\n%s",szErrorInfo);
// 				MessageBox(NULL,sMess,"错误",MB_ICONERROR);
				m_sError = mysql_error(pMySql);
				return NULL;
			}
		}

		MYSQL_RES* pRes = NULL;
		pRes = mysql_use_result(pMySql);

		CDB_ResultSet* pDBRes = new CDB_ResultSet;
		//m_vtRes.push_back(pDBRes);
		std::string strResName = sResName;
		if(!strResName.empty())
		{
			m_mapRes.insert(std::map<std::string,CDB_ResultSet*>::value_type(strResName,pDBRes));
		}
		else
		{
			int isize = m_mapRes.size();

			char c[4];
			sprintf(c,"%d",++isize);
			strResName = c;
			m_mapRes.insert(std::map<std::string,CDB_ResultSet*>::value_type(strResName,pDBRes));
		}

		int iCount = pRes->field_count;
		
		for ( int i = 0 ; i< iCount ; i++)
		{
			MYSQL_FIELD sql_field = pRes->fields[i];

			pDBRes->SetFieldName(sql_field.name);
			
			switch(sql_field.type)
			{
				case MYSQL_TYPE_DECIMAL:
				case MYSQL_TYPE_TINY:
				case MYSQL_TYPE_FLOAT:
				case MYSQL_TYPE_DOUBLE:
				{
					pDBRes->SetFieldType(DBFT_Double);
					break;
				}
				case MYSQL_TYPE_LONG:
				case MYSQL_TYPE_SHORT:
				case MYSQL_TYPE_INT24:
				{
					pDBRes->SetFieldType(DBFT_Int);
					break;
				}
				//	case MYSQL_TYPE_LONG:
				case MYSQL_TYPE_LONGLONG:
				{
					pDBRes->SetFieldType(DBFT_Bigint);
					break;
				}
				default:
				{
					pDBRes->SetFieldType(DBFT_String);
					break;
				}
			}
			
		}
		
		MYSQL_ROW  row;
		while(  row = mysql_fetch_row( pRes))
		{
			std::vector<std::string> vt;
			for ( int i = 0 ; i< iCount ; i++)
			{
				char* p = row[i];
				if(p == NULL)
				{
					p = "";
				}
				vt.push_back(p);
			}

			pDBRes->SetResValue(vt);
		}

		if(pRes != NULL)
		{
			mysql_free_result(pRes);
		}
		
		
		return pDBRes;
	}
	else if(iCurDbType == 2)
	{
		PGconn* pgConn = NULL;
		pgConn = pDbConnection->GetCurConn_PGconn();
		if(PQstatus(pgConn)==CONNECTION_BAD || pgConn == NULL) 
		{
			pDbConnection->Connection(iCurDbType);
			
			pgConn = pDbConnection->GetCurConn_PGconn();
			if(PQstatus(pgConn)==CONNECTION_BAD || pgConn == NULL)
			{
				pDbConnection->Close();

				m_sError = "数据库连接失败";
				WriteLog("数据库连接失败") ;
				return NULL;
			}

			if(!pDbConnection->m_strschema.empty())
			{//如果配置了schema就设置
				std::string str = "set search_path to " + pDbConnection->m_strschema + ",\"$user\",public,topology";
				const char* sSetschemaSql = str.c_str();
				PQexec(pgConn,sSetschemaSql);
			}

		}
		//else
		{
// 			if(!pDbConnection->m_strschema.empty())
// 			{//如果配置了schema就设置
// 				std::string str = "set search_path to " + pDbConnection->m_strschema + ",\"$user\",public,topology";
// 				const char* sSetschemaSql = str.c_str();
// 				PQexec(pgConn,sSetschemaSql);
// 			}

			PQsetClientEncoding(pgConn,"gbk");

			PGresult* pgresult =PQexec(pgConn,sSql);
			
			m_sError = PQresultErrorMessage(pgresult);
			if(!m_sError.empty())
			{
				//MessageBox(NULL,strError,"执行失败",MB_ICONERROR);
				WriteLog( m_sError.c_str()) ;
				WriteLog( sSql) ;
				return NULL;
			}

			CDB_ResultSet* pDBRes = new CDB_ResultSet;
			//m_vtRes.push_back(pDBRes);
			std::string strResName = sResName;
			if(!strResName.empty())
			{
				m_mapRes.insert(std::map<std::string,CDB_ResultSet*>::value_type(strResName,pDBRes));
			}
			else
			{
				int isize = m_mapRes.size();
				
				char c[4];
				sprintf(c,"%d",++isize);
				strResName = c;
				m_mapRes.insert(std::map<std::string,CDB_ResultSet*>::value_type(strResName,pDBRes));
			}

			int field_num=PQnfields(pgresult);//
			for(int f = 0; f < field_num; f++)
			{
				std::string strName = PQfname(pgresult,f);
				
				pDBRes->SetFieldName(strName.c_str());

				Oid itype = PQftype(pgresult,f);
				switch(itype)
				{
					case 16:
					case 21:
					case 23:
					{
						pDBRes->SetFieldType(DBFT_Int);
						break;
					}
					case 20:
					{
						pDBRes->SetFieldType(DBFT_Bigint);
						break;
					}
					case 700:
					case 701:
					{
						pDBRes->SetFieldType(DBFT_Double);
						break;
					}
					default:
					{
						pDBRes->SetFieldType(DBFT_String);
						break;
					}
				}
			}
			int tuple_num=PQntuples(pgresult);

			for(int row = 0; row < tuple_num; row++)
			{
				std::vector<std::string> vt;
				for(int col = 0; col < field_num; col++)
				{
					vt.push_back(PQgetvalue(pgresult,row,col));
				}

				pDBRes->SetResValue(vt);
			}
			
			PQclear(pgresult);

			return pDBRes;
			
		}
	}
	else
	{
		m_sError = "无效的数据库类型";
		return NULL;
	}
}

DBConnection* CDB_Manager::GetConnection(int itype)
{
	std::map<int,DBConnection*>::iterator it = m_mapDBConnection.find(itype);

	if(it != m_mapDBConnection.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

DBConnection* CDB_Manager::GetConnection(const char* sConnectionname)
{
	vector<DBConnection* > ::iterator iter = m_vtDBConnection.begin();
	for ( ; iter != m_vtDBConnection.end(); iter++ )
	{
		DBConnection* pCon = *iter;
		if( pCon == NULL)
			continue;
		
		if ( strcmp(pCon->m_strconname.c_str(),sConnectionname)== 0 )
		{
			return pCon;
		}
	}
	
	return NULL;
}

void CDB_Manager::AddOneConnection(int idbCategory,const char* strconname,const char* strservice,const char* strdb,const char* strschema,const char* strdba,const char* strport,const char* strdbpw)
{
	vector<DBConnection* > ::iterator iter = m_vtDBConnection.begin();
	for ( ;  iter != m_vtDBConnection.end(); iter++ )
	{
		DBConnection* pCon = *iter;
		if( pCon == NULL)
			continue;
		
		if ( strcmp(pCon->m_strconname.c_str(),strconname) == 0 )
		{
			return ;
		}
	}
	DBConnection* pCon = new DBConnection;
	pCon->m_strconname = strconname;
	pCon->m_strdb = strdb;
	pCon->m_strschema = strschema;
	pCon->m_strdba = strdba;
	pCon->m_strdbport = strport;
	pCon->m_strdbpw = strdbpw;
	pCon->m_strdbservice = strservice;
	bool bOk = pCon->Connection(idbCategory);
	
	if(bOk)
	{
		m_vtDBConnection.push_back(pCon);
	}
	else
	{
		std::string sconnError = pCon->GetConnError();
		delete pCon;
		pCon = NULL;

		m_sError = "连接失败:";
		m_sError += sconnError;
	}
}

bool CDB_Manager::ExcuteSql(const char* sSql,int& iAffect)
{
	m_sError = "";//置空

	DBConnection* pDbConnection; 
	if(m_idbtype > 0 && m_sConnectionname.empty())
		pDbConnection = GetConnection(m_idbtype);
	else if(!m_sConnectionname.empty() && m_idbtype < 0)
		pDbConnection = GetConnection(m_sConnectionname.c_str());
	else return false;

	if(pDbConnection == NULL)
	{
		if(m_sError.empty())
			m_sError = "无效的数据库连接";
		//MessageBox(NULL,"无效的数据库","错误",MB_ICONERROR);
		return false;
	}

	int iCurDbType = pDbConnection->GetCurDBType();

	if(iCurDbType == 1)
	{
		MYSQL* pMySql = NULL;
		pMySql = pDbConnection->GetCurConn_MySqlconn();
		
		mysql_set_character_set(pMySql,"GBK");
		
		if ( mysql_query(pMySql,sSql) )
		{
			int iError = mysql_errno(pMySql);
			if ( iError == 2013 || iError == 2006)
			{
				if( pDbConnection->Connection(iCurDbType))
				{
					pMySql = pDbConnection->GetCurConn_MySqlconn();
					
					mysql_set_character_set(pMySql,"GBK");
					//strcpy(szSql,sSql);
					if ( mysql_query(pMySql,sSql) )
					{
						//iError = mysql_errno(pMySql);
						//strcpy( szErrorInfo,mysql_error(pMySql));
						m_sError = mysql_error(pMySql);
// 						CString sMess;
// 						sMess.Format("ERROR:11\n\n%s",szErrorInfo);
// 						MessageBox(NULL,sMess,"二次连接错误",MB_ICONERROR);
						return false;
					}
				}
			} 
			else
			{
// 				iError = mysql_errno(pMySql);
// 				strcpy( szErrorInfo,mysql_error(pMySql));
// 				CString sMess;
// 				sMess.Format("ERROR:11\n\n%s",szErrorInfo);
// 				MessageBox(NULL,sMess,"错误",MB_ICONERROR);
				m_sError = mysql_error(pMySql);
				return false;
			}
		}

		iAffect = mysql_affected_rows(pMySql);
		

	}
	else if(iCurDbType == 2)
	{
		PGconn* pgConn = NULL;
		pgConn = pDbConnection->GetCurConn_PGconn();
		if(PQstatus(pgConn)==CONNECTION_BAD || pgConn == NULL) 
		{
			pDbConnection->Connection(iCurDbType);
			
			pgConn = pDbConnection->GetCurConn_PGconn();
			if(PQstatus(pgConn)==CONNECTION_BAD || pgConn == NULL)
			{
				pDbConnection->Close();

				m_sError = "数据库连接失败";
				WriteLog( m_sError.c_str()) ;
				return false;
			}

			if(!pDbConnection->m_strschema.empty())
			{//如果配置了schema就设置
				std::string str = "set search_path to " + pDbConnection->m_strschema + ",\"$user\",public,topology";
				const char* sSetschemaSql = str.c_str();
				PQexec(pgConn,sSetschemaSql);
			}

		}
		//else
		{
// 			if(!pDbConnection->m_strschema.empty())
// 			{//如果配置了schema就设置
// 				std::string str = "set search_path to " + pDbConnection->m_strschema + ",\"$user\",public,topology";
// 				const char* sSetschemaSql = str.c_str();
// 				PQexec(pgConn,sSetschemaSql);
// 			}

			PQsetClientEncoding(pgConn,"gbk");

			PGresult* pgresult =PQexec(pgConn,sSql);
			
			m_sError = PQresultErrorMessage(pgresult);
			if(!m_sError.empty())
			{
				//MessageBox(NULL,strError,"执行失败",MB_ICONERROR);
				WriteLog( m_sError.c_str()) ;
				WriteLog(sSql) ;
				return false;
			}

			char* p = PQcmdTuples(pgresult);
			iAffect = atoi(p);
			PQclear(pgresult);

			return true;

		}
	}
	else
	{
		m_sError = "无效的数据库类型";
		return FALSE;
	}

	return true;
}

const char* CDB_Manager::GetErrorMessage()
{
	return m_sError.c_str();
}

void CDB_Manager::ReleaseRes(CDB_ResultSet** pDBResultSet)
{
	if(pDBResultSet != NULL)
	{
		std::map<std::string,CDB_ResultSet*>::iterator it;
		for(it = m_mapRes.begin(); it != m_mapRes.end(); it++)
		{
			std::string strName = it->first;
			CDB_ResultSet* ptr = it->second;

			if(ptr == *pDBResultSet)
			{
				m_mapRes.erase(it);

				delete ptr;
				
				ptr = NULL;
				*pDBResultSet = NULL;

				break;;
			}
		}
	
		
	}
}

void CDB_Manager::ReleaseRes(const char* sResName)
{
	if(sResName != "")
	{
		std::map<std::string,CDB_ResultSet*>::iterator it;
		for(it = m_mapRes.begin(); it != m_mapRes.end(); it++)
		{
			std::string strName = it->first;
			CDB_ResultSet* ptr = it->second;
			
			if(strName == sResName)
			{
				m_mapRes.erase(it);
				
				delete ptr;
				
				ptr = NULL;
				
				break;;
			}
		}
		
		
	}
}

void CDB_Manager::ReleaseAllRes()
{
	std::map<std::string,CDB_ResultSet*>::iterator it;
	for(it = m_mapRes.begin(); it != m_mapRes.end(); it++)
	{
		CDB_ResultSet* ptr = it->second;
		
		delete ptr;

		ptr = NULL;
	}

	m_mapRes.clear();
}

//DEL int CDB_Manager::GetResCount()
//DEL {
//DEL 	return m_vtRes.size();
//DEL }

void CDB_Manager::CloseAllDB()
{
	std::map<int,DBConnection*>::iterator it = m_mapDBConnection.begin();
	for(it; it != m_mapDBConnection.end(); it++)
	{
		DBConnection* pConn = it->second;
		if(pConn != NULL)
		{
			//pConn->Close();
			delete pConn;
			pConn = NULL;
		}
	}

	m_mapDBConnection.clear();

	int isize = m_vtDBConnection.size();
	for(int i = 0; i < isize; i++)
	{
		DBConnection* pConn = m_vtDBConnection.at(i);
		if(pConn != NULL)
		{
			//pConn->Close();
			delete pConn;
			pConn = NULL;
		}
	}

	m_vtDBConnection.clear();
}

void CDB_Manager::CloseDB(int itype)
{
	std::map<int,DBConnection*>::iterator it = m_mapDBConnection.find(itype);
	
	if(it != m_mapDBConnection.end())
	{
		DBConnection* pConn = it->second;
		//pConn->Close();
		delete pConn;
		pConn = NULL;

		m_mapDBConnection.erase(it);
	}
}

void CDB_Manager::CloseDB(const char* sConnectionname)
{
	vector<DBConnection* > ::iterator iter = m_vtDBConnection.begin();
	for ( ; iter != m_vtDBConnection.end(); iter++ )
	{
		DBConnection* pCon = *iter;
		if( pCon == NULL)
			continue;
		
		if ( strcmp(pCon->m_strconname.c_str(),sConnectionname)== 0 )
		{
			//pCon->Close();
			delete pCon;
			pCon = NULL;

			m_vtDBConnection.erase(iter);
		}
	}
}

CDB_ResultSet* CDB_Manager::GetResultSetPtrByName(const char* sResName)
{
	std::map<std::string,CDB_ResultSet*>::iterator it = m_mapRes.find(sResName);

	if(it != m_mapRes.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}
