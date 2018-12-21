// CTaskCommon.cpp: implementation of the CTaskCommon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskManager.h"
#include "CTaskCommon.h"

#include "CDB_Manager.h"
#include "CDBFieldInfo.h"
#include "CDBValue.h"
#include "DB_ResultSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaskCommon::CTaskCommon()
{

}


CTaskCommon::~CTaskCommon()
{

}

void CTaskCommon::Release() 
{
	delete this ;
}

CTaskCommon::CTaskCommon(int idbtype,const char *sztablename)
{
	CDB_Manager::GetDBManagerPtr()->ChooseDB(idbtype) ;
	CString strSQL ;
	strSQL.Format("desc %s",sztablename) ;
	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
	
	if ( pRes == NULL)
	{
		return ;
	}
	int num_rows = pRes->GetResRowCount();
	int num_fields = pRes->GetResFieldCount();

	int icount = 0 ;
	
	CDBFieldInfo *pFieldInfo = NULL ;
	CDBValue *pValue = NULL ;

	for(int r = 0; r < num_rows; r++)
	{
		icount++ ;
		CString strType = pRes->GetResStringValue(r,1) ;
		if ( strType.Find("(") != -1 )
		{
			strType = strType.Left(strType.Find("(")) ;
		}
		int etypes = DBFT_String;
		if ( strType == "bigint")
		{
			etypes = DBFT_Bigint ;
		}
		if ( strType == "int")
		{
			etypes = DBFT_Int ;
		}
		if ( strType == "double")
		{
			etypes = DBFT_Double ;
		}
		
		pFieldInfo = new CDBFieldInfo(pRes->GetResStringValue(r,0),"",etypes) ;
		pFieldInfo->SetFieldType(DB_FIELDTYPE(etypes));//再单独设置一下
		pValue = new CDBValue ;
		this->AddField(pFieldInfo, pValue) ;
		
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
}