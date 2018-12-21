// CTSFields.h: interface for the CTSFields class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTSFIELDS_H__9B578E4A_EA82_4F6A_BB83_AEB173EBA259__INCLUDED_)
#define AFX_CTSFIELDS_H__9B578E4A_EA82_4F6A_BB83_AEB173EBA259__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
using namespace std;

#include "dbcommondef.h"

#include "CDBFieldInfo.h"
#include "CDBValue.h"

typedef std::vector<CDBFieldInfo *>			Vector_FieldInfo ;
typedef std::vector<CDBValue *>				Vector_Value ;

class _declspec(dllexport) CDBFields  
{
public:
	CDBFields();
	virtual ~CDBFields();

	int GetIndex(const char* szFieldName) ;
	void SetIntByIndex(int iIndex,int val) ;
	int GetIntByIndex(int iIndex) ;
	void SetDoubleByIndex(int iIndex, double val) ;
	double GetDoubleByIndex(int iIndex) ;
	void SetStringByIndex(int iIndex,const char *val);
	const char *GetStringByIndex(int iIndex) ;
	__int64 GetInt64ByIndex(int iIndex) ;
	void SetInt64ByIndex(int iIndex, __int64 val) ;
	void AddField(CDBFieldInfo *pFieldInfo,CDBValue *pValue) ;
	DB_FIELDTYPE GetFieldTypeByIndex(int iIndex) ;
	int Size() ;

	CDBFieldInfo *GetFieldInfoByIndex(int iIndex) ;
	// 	template<class T>
	// 	T GetValByIndex(int iIndex) ;
	// 	template<class T>
	// 	void SetValByIndex(int iIndex, T val);
	

private:
	Vector_FieldInfo m_vtFieldsInfo ;
	Vector_Value m_vtValue ;
	
};

#endif // !defined(AFX_CTSFIELDS_H__9B578E4A_EA82_4F6A_BB83_AEB173EBA259__INCLUDED_)
