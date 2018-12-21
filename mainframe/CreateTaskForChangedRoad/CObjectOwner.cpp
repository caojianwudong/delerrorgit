// CObjectOwner.cpp: implementation of the CObjectOwner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CreateTaskForChangedRoad.h"
#include "CObjectOwner.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CObjectOwner::CObjectOwner()
{
	m_iowner = 0 ;
	m_strName = "";
	m_strPy = "" ;
	m_iareacode = "" ;
	m_ifeatcode =0;
	m_citycode ="";
	m_strdesc ="";
}

CObjectOwner::~CObjectOwner()
{

}

void CObjectOwner::SetOwner( int owner )
{
	m_iowner = owner ;
}

int CObjectOwner::GetOwner()
{
	return m_iowner ;
}

void CObjectOwner::SetName( CString strName )
{
	m_strName = strName ;
}

CString CObjectOwner::GetName()
{
	return m_strName ;
}

void CObjectOwner::SetPy( CString strpy )
{
	m_strPy = strpy ;
}

CString CObjectOwner::GetPy()
{
	return m_strPy ;
}

void CObjectOwner::SetAreaCode( CString code )
{
	m_iareacode = code ;
}

CString CObjectOwner::GetAreaCode()
{
	return m_iareacode ;
}

void CObjectOwner::SetFeatCode( int code )
{
	m_ifeatcode = code ;
}

int CObjectOwner::GetFeatCode()
{
	return m_ifeatcode ;
}

void CObjectOwner::SetCityCode( CString code )
{
	m_citycode = code ;
}

CString CObjectOwner::GetCityCode()
{
	return m_citycode ;
}

void CObjectOwner::SetDesc( CString desc )
{
	m_strdesc = desc ;
}

CString CObjectOwner::GetDesc()
{
	return m_strdesc ;
}
