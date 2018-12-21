// CTaskCommon.h: interface for the CTaskCommon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTASKCOMMON_H__6E344496_4129_4D92_A9B7_351B365F9FB4__INCLUDED_)
#define AFX_CTASKCOMMON_H__6E344496_4129_4D92_A9B7_351B365F9FB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CDBFields.h"

class _declspec(dllexport)CTaskCommon : public CDBFields  
{
public:
	CTaskCommon();
	CTaskCommon(int idbtype,const char *sztablename);
	virtual ~CTaskCommon();
	bool LoadLinkInfo() {return true;};
	void Release() ;
};

#endif // !defined(AFX_CTASKCOMMON_H__6E344496_4129_4D92_A9B7_351B365F9FB4__INCLUDED_)
