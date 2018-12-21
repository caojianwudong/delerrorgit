// CPOIUserDB.h: interface for the POIUserDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPOIUSERDB_H__7789E0FD_6C53_419D_B651_08C0628AA2D4__INCLUDED_)
#define AFX_CPOIUSERDB_H__7789E0FD_6C53_419D_B651_08C0628AA2D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <string>
#include <vector>

#include "winsock.h" 
#include "mysql.h" 

using namespace std;

class POIUserDB  
{
public:
	string GetRealName();
	bool GetUserInfoById(int id, string &sUserName, string &sRealName);
	POIUserDB();
	virtual ~POIUserDB();
	
	bool DBQueryCheckUser(string sDBSql);
	bool DBQueryCheckUserEdit(int nEdit);	//判断编辑类型
	bool DBQueryGetPost(string sDBSql, std::vector< std::pair<int,std::string> > &vecPost);

	string GetNameC(){return m_sUserNameCInDB;}
	
	int GetSelectResultCount(string sDBSql);
	CString  GetDllPath();
private:
	bool GetAllUserName();
	void ReadConfig();
	void InitMysql();
	
	
	void print_error(MYSQL *conn, const char *title);
	
	// 多字节编码转为UTF8编码  
	bool UTF8ToMB(std::vector<char>& pmb, const char* pu8, int utf8Len);
	
	CString m_strdllPath; 

	std::string m_sMysqlAddr;
	std::string m_sMysqlUser;
	std::string m_sMysqlPass;
	std::string m_sMysqlDB;
	int m_nMysqlPort;

	std::string m_sUserNameInDB;
	std::string m_sUserPassInDB;
	std::string m_sUserNameCInDB;
	int m_nUserPostInDB;
	int m_nUserIDInDB;

	std::map<std::string, std::string> m_mapMysqlInfo;
	
	MYSQL *m_pMysql;
	MYSQL_RES *m_pMysqlRes;
	MYSQL_ROW m_pMysqlRow;

	//用户id，真实姓名，用户名
	std::map<int, std::pair<std::string,std::string> > m_mapUserInfo;
	
};

#endif // !defined(AFX_CPOIUSERDB_H__7789E0FD_6C53_419D_B651_08C0628AA2D4__INCLUDED_)
