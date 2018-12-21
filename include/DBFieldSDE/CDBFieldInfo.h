// CTSFieldInfo.h: interface for the CTSFieldInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTSFIELDINFO_H__90D5CB33_BAA9_4822_9584_B74E52FE5717__INCLUDED_)
#define AFX_CTSFIELDINFO_H__90D5CB33_BAA9_4822_9584_B74E52FE5717__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;
#include "dbcommondef.h"

class _declspec(dllexport) CDBFieldInfo  
{
public:
	CDBFieldInfo(const char* szName, const char* szCaption, int nFieldType);
	virtual ~CDBFieldInfo();
	void SetFieldName(const char * name);
	void SetFieldType(DB_FIELDTYPE type);
	const char* GetFieldName ();
	const char* GetFieldCaption ();
	void SetFieldCaption (const char* szCaption);
	DB_FIELDTYPE GetFieldType ();
	
private:
	string m_szFieldName;
	string m_szFieldCaption;
	DB_FIELDTYPE m_nFieldType;
};

#endif // !defined(AFX_CTSFIELDINFO_H__90D5CB33_BAA9_4822_9584_B74E52FE5717__INCLUDED_)
