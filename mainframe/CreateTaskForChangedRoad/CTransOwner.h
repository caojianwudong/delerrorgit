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
	CString GetProCityNameByOnwer(int owner) ; // ��ȡʡ�м����ƣ��ӱ�ʡ�����У�
	int GetFrontOwner(int owner,int featcode) ; // ��ȡ��һ����owner
	void WriteOwnerNameToLog() ;
private:
	std::map< int, CObjectOwner*> m_mapOwner_Object ;

};

#endif // !defined(AFX_CTRANSOWNER_H__DA010D59_ADA0_4F32_B81B_70033C5032CF__INCLUDED_)
