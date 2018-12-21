// CTransOwner.h: interface for the CTransOwner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTRANSOWNER_H__DA010D59_ADA0_4F32_B81B_70033C5032CF__INCLUDED_)
#define AFX_CTRANSOWNER_H__DA010D59_ADA0_4F32_B81B_70033C5032CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <vector>
using namespace std ;

class CObjectOwner ;
class CTransOwner  
{
public:
	CTransOwner();
	virtual ~CTransOwner();

	bool InitOwnerObject() ;
	CObjectOwner* GetObjectByOwner(int owner) ;
	CString GetProCityNameByOnwer(int owner) ; // 获取省市级名称（河北省保定市）
	int GetFrontOwner(int owner,int featcode) ; // 获取上一级的owner
	void WriteOwnerNameToLog() ;
private:
	std::map< int, CObjectOwner*> m_mapOwner_Object ;

};

#endif // !defined(AFX_CTRANSOWNER_H__DA010D59_ADA0_4F32_B81B_70033C5032CF__INCLUDED_)
