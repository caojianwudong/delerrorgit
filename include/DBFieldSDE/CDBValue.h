// CTSValue.h: interface for the CTSValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTSVALUE_H__F2AAFAFB_58D9_4F6C_80C0_556160855958__INCLUDED_)
#define AFX_CTSVALUE_H__F2AAFAFB_58D9_4F6C_80C0_556160855958__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
using namespace std;

class _declspec(dllexport) CDBValue  
{
public:
	CDBValue();
	virtual ~CDBValue();

	int GetInt();
	void SetInt(int val);
	double GetDouble ();
	void SetDouble(double val);
	const char* GetString();
	void SetString(const char* val);
	__int64 GetInt64();
	void SetInt64(__int64 val);

private:
	string m_szvalue ;

};

#endif // !defined(AFX_CTSVALUE_H__F2AAFAFB_58D9_4F6C_80C0_556160855958__INCLUDED_)
