// CTaskLinkItemSet.h: interface for the CTaskLinkItemSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTASKLINKITEMSET_H__05373A79_DE72_481B_B0DC_E7133DAD4265__INCLUDED_)
#define AFX_CTASKLINKITEMSET_H__05373A79_DE72_481B_B0DC_E7133DAD4265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CTaskCommon.h"

typedef std::vector<CDBFields *>		Vector_Fields ;

class _declspec(dllexport)CTaskLinkItemSet : public CTaskCommon  
{
public:
	CTaskLinkItemSet();
	virtual ~CTaskLinkItemSet();
	bool LoadLinkInfo() ;

	void SetItemSetID(__int64 iId) ;
	__int64 GetItemSetID() ;
	
	int GetItemCount() ;
	CDBFields *GetFieldsByIndex(int iIndex);

	void SetType(int type) ;
	int GetType() ;

private:
	__int64 m_iID ;
	int m_itype ;
	Vector_Fields m_vtItemdetail ;
};

extern "C"
{
	__declspec(dllexport) CTaskLinkItemSet *CreateLinkItemSet(__int64 iID) ;
}

#endif // !defined(AFX_CTASKLINKITEMSET_H__05373A79_DE72_481B_B0DC_E7133DAD4265__INCLUDED_)
