// CTransOwner.cpp: implementation of the CTransOwner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CreateTaskForChangedRoad.h"
#include "CTransOwner.h"

#include "CObjectOwner.h"
#include "EMG_OperateExcel.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransOwner::CTransOwner()
{

}

CTransOwner::~CTransOwner()
{
	if ( !m_mapOwner_Object.empty())
	{
		for ( std::map< int, CObjectOwner*>::iterator it = m_mapOwner_Object.begin(); it != m_mapOwner_Object.end(); it++)
		{
			CObjectOwner *p = it->second ;
			if ( p != NULL)
			{
				delete p ;
				p = NULL ;
			}
		}
		m_mapOwner_Object.clear() ;
	}
}

bool CTransOwner::InitOwnerObject()
{
	char path[1024] ;
	::GetModuleFileName( NULL, path, 1024) ;
	CString strAppPath = path ;
	int ipos = strAppPath.ReverseFind('\\') ;
	if ( ipos != -1)
	{
		strAppPath = strAppPath.Left(ipos+1) ;
	}
	
	CString strConfigPath = strAppPath + "config\\行政区划.xls" ;

	EMG_OperateExcel *pexcel = new EMG_OperateExcel() ;
	if( !pexcel->OpenExcelFile(strConfigPath))
	{
		return false ;
	}
	
	int isheetnum = pexcel->GetSheetsNum() ;
	for ( int i = 1;  i < (isheetnum+1); i++)
	{
		CString sheetname = pexcel->GetSheetNameByNumber(i) ;
		if ( sheetname != "最新行政区划代码")
		{
			continue;
		}
		pexcel->SetOperateSheetByName(sheetname) ;
		
		
		
		int rowcount = pexcel->GetRowsCount() ;
// 		CString column_owner = "A" ;
// 		CString column_name = "B" ;
// 		CString column_py = "C" ;
// 		CString column_area = "D" ;
// 		CString column_feat= "E" ;
// 		CString column_city= "F" ;
// 		CString column_desc="G" ;

		int indexrow = 0 ;
		for (indexrow = 3 ;indexrow< rowcount;indexrow++)
		{
			CString msg ;
			msg.Format("%d", indexrow) ;
			CString indexrowA = "A" + msg ;
			CString indexrowB = "B" + msg ;
			CString indexrowC = "C" + msg ;
			CString indexrowD = "D" + msg ;
			CString indexrowE = "E" + msg ;
			CString indexrowF = "F" + msg ;
			CString indexrowG = "G" + msg ;
			CString strA = pexcel->GetRangeValue(indexrowA) ;
			CString strB = pexcel->GetRangeValue(indexrowB) ;
			CString strC = pexcel->GetRangeValue(indexrowC) ;
			CString strD = pexcel->GetRangeValue(indexrowD) ;
			CString strE = pexcel->GetRangeValue(indexrowE) ;
			CString strF = pexcel->GetRangeValue(indexrowF) ;
			CString strG = pexcel->GetRangeValue(indexrowG) ;
			
			strA.TrimLeft() ;
			strA.TrimRight() ;
			strA.Replace("　","") ;

			strB.TrimLeft() ;
			strB.TrimRight() ;
			strB.Replace("　","") ;
			strB.Replace(" ","") ;

			strC.TrimLeft() ;
			strC.TrimRight() ;
			strC.Replace("　","") ;

			strD.TrimLeft() ;
			strD.TrimRight() ;
			strD.Replace("　","") ;

			strE.TrimLeft() ;
			strE.TrimRight() ;
			strE.Replace("　","") ;

			strF.TrimLeft() ;
			strF.TrimRight() ;
			strF.Replace("　","") ;

			strG.TrimLeft() ;
			strG.TrimRight() ;
			strG.Replace("　","") ;

			int owner = atoi(strA) ;
			int areacode = atoi( strD) ;
			int featcode = atoi(strE) ;
			int citycode = atoi(strF) ;
			if ( owner > 0 && strB.GetLength() > 0 && featcode >0)
			{
				// 这三个字段是必须的，不能为空
				CObjectOwner *pObjectOwner = new CObjectOwner() ;
				pObjectOwner->SetOwner(owner) ;
				pObjectOwner->SetName(strB) ;
				pObjectOwner->SetPy(strC) ;
				pObjectOwner->SetAreaCode(strD) ;
				pObjectOwner->SetFeatCode(featcode) ;
				pObjectOwner->SetCityCode(strF) ;
				pObjectOwner->SetDesc(strG) ;
				m_mapOwner_Object.insert(std::map< int, CObjectOwner*>::value_type( owner, pObjectOwner)) ;
			}
		}
	}
	
	pexcel->CloseExcelFile() ;
	return true ;
}

CObjectOwner* CTransOwner::GetObjectByOwner( int owner )
{
	std::map<int, CObjectOwner*> ::iterator it = m_mapOwner_Object.find( owner) ;
	if ( it == m_mapOwner_Object.end())
	{
		return NULL ;
	}
	else
	{
		CObjectOwner *pObjectOwner = it->second ;
		return pObjectOwner ;
	}
}

CString CTransOwner::GetProCityNameByOnwer( int owner )
{
	if ( owner < 1)
	{
		return "" ;
	}
	CObjectOwner *pObjectOwner = GetObjectByOwner( owner) ;
	if ( pObjectOwner == NULL)
	{
		return "" ;
	}

	CString strName = "" ;
	if ( pObjectOwner->GetFeatCode() == 1010202)
	{
		strName = pObjectOwner->GetName() ;
	}
	else if ( pObjectOwner->GetFeatCode() == 1010203)
	{
		int proowner = GetFrontOwner( owner, 1010203) ;
		CObjectOwner *pProOwner = GetObjectByOwner( proowner) ;
		if ( pProOwner != NULL)
		{
			strName = pProOwner->GetName() ;
		}
		strName += pObjectOwner->GetName() ;
	}
	else if ( pObjectOwner->GetFeatCode() == 1010204)
	{
		int proowner = GetFrontOwner( owner, 1010203) ;
		int cityowner = GetFrontOwner( owner, 1010204) ;
		CObjectOwner *pProOwner = GetObjectByOwner( proowner) ;
		CObjectOwner *pCityOwner = GetObjectByOwner( cityowner) ;
		if ( pProOwner != NULL)
		{
			strName = pProOwner->GetName() ;
		}
		if ( pCityOwner != NULL)
		{
			strName += pCityOwner->GetName() ;
		}
	}
	return strName ;
}

int CTransOwner::GetFrontOwner( int owner, int featcode )
{
	if ( featcode == 1010204)
	{
		CString msg ;
		msg.Format("%d", owner) ;
		msg = msg.Left(4) ;
		msg += "00" ;
		int temp = atoi(msg) ;
		return temp ;
	}
	else if ( featcode == 1010203)
	{
		CString msg ;
		msg.Format("%d", owner) ;
		msg = msg.Left(2) ;
		msg += "0000" ;
		int temp = atoi(msg) ;
		return temp ;
	}	
	else 
	{
		return owner ;
	}
}

void CTransOwner::WriteOwnerNameToLog()
{
	char path[1024] ;
	::GetModuleFileName( NULL, path, 1024) ;
	CString strAppPath = path ;
	int ipos = strAppPath.ReverseFind('\\') ;
	if ( ipos != -1)
	{
		strAppPath = strAppPath.Left(ipos+1) ;
	}

	strAppPath += "test.csv" ;
	CStdioFile stfile ;
	if ( !stfile.Open(strAppPath, CFile::modeCreate|CFile::modeWrite))
	{
		return ;
	}

	for ( std::map< int, CObjectOwner*>::iterator it = m_mapOwner_Object.begin(); it != m_mapOwner_Object.end(); it++)
	{
		CObjectOwner *p = it->second ;
		CString msg ;
		msg.Format("%d,%s,%s,%s,%d,%s,%s\n",p->GetOwner(),
			p->GetName(),p->GetPy(),p->GetAreaCode(),p->GetFeatCode(),p->GetCityCode(),p->GetDesc()) ;
		stfile.WriteString( msg) ;
	}
	stfile.Close() ;
}
