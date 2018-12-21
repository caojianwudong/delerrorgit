// CObjectOwner.h: interface for the CObjectOwner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COBJECTOWNER_H__AC7CE1FD_0557_4816_886F_E37C62FED136__INCLUDED_)
#define AFX_COBJECTOWNER_H__AC7CE1FD_0557_4816_886F_E37C62FED136__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CObjectOwner  
{
public:
	CObjectOwner();
	virtual ~CObjectOwner();

	void SetOwner(int owner) ;
	int GetOwner() ;

	void SetName(CString strName) ;
	CString GetName() ;

	void SetPy(CString strpy) ;
	CString GetPy() ;

	void SetAreaCode( CString code) ;
	CString GetAreaCode() ;

	void SetFeatCode(int code) ;
	int GetFeatCode() ;

	void SetCityCode(CString code) ;
	CString GetCityCode() ;

	void SetDesc(CString desc) ;
	CString GetDesc() ;
private:
	int m_iowner ;
	CString m_strName ;
	CString m_strPy ;
	CString m_iareacode ;
	int m_ifeatcode ;
	CString m_citycode ;
	CString m_strdesc ;
};

#endif // !defined(AFX_COBJECTOWNER_H__AC7CE1FD_0557_4816_886F_E37C62FED136__INCLUDED_)
