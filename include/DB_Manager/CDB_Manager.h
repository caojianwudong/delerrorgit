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

class __declspec(dllexport)CDB_Manager  
{
public:
	//CDB_Manager();
	CDB_Manager(bool isAutoConn = true);
	virtual ~CDB_Manager();

	//isAutoConn参数代表是否自动加载链接配置
	//自动加载时，将自动加载dbconfig中配置的链接
	//手动加载时需通过AddOneConnection方法加载
	static CDB_Manager* GetDBManagerPtr(bool isAutoConn = true);
	static void DestroyDBManagerPtr();

	//增加一个链接
	//idbCategory为数据库类别：DB_TYPE_MYSQL为mysql；DB_TYPE_PGSQL为postgres
	void AddOneConnection(int idbCategory,const char* strconname,const char* strservice,const char* strdb,const char* strdba,const char* strport,const char* strdbpw);

	//选择并打开指定数据库链接
	bool ChooseDB(int itype); //通过数据库类型编号打开
	bool ChooseDB(const char* sConnectionname);//通过链接名打开,此接口对应打开AddOneConnection方法增加的链接

	//显式关闭指定数据库链接
	void CloseDB(int itype);//对应关闭ChooseDB(int itype)打开的连接
	void CloseDB(const char* sConnectionname);//对应关闭ChooseDB(const char* sConnectionname)打开的连接

	//执行查询sql语句返回CDB_ResultSet查询结果集对象
	//sResName参数为结果集名称，由用户指定。默认为空，当为空的时候接口将自动按照
	//查询结果集顺序命名，例如当前结果集为第n(n为整数,n>0)次查询的,则名称为"n"
	//注意此处所指的查询结果集顺序针对的是没有释放的查询结果集
	CDB_ResultSet* ExcuteQuerySql(const char* sSql, const char* sResName = "");

	//根据结果集名称返回结果集
	//结果集名称为调用ExcuteQuerySql接口时传入的名称
	CDB_ResultSet* GetResultSetPtrByName(const char* sResName);

	//执行非查询sql
	bool ExcuteSql(const char* sSql,int& iAffect);

	//得到执行sql后的错误信息
	const char* GetErrorMessage();

	//释放所有查询结果集
	void ReleaseAllRes();

	//释放指定查询结果集
	void ReleaseRes(CDB_ResultSet** pDBResultSet);//根据指针释放
	void ReleaseRes(const char* sResName);//根据名称释放

	
};

#endif // !defined(AFX_CDB_MANAGER_H__FD023842_B65A_49CE_9A81_8A2D7022BCBE__INCLUDED_)
