// CTaskBlockDetail.cpp: implementation of the CTaskBlockDetail class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskManager.h"
#include "CTaskBlockDetail.h"

#include "CDB_Manager.h"
#include "CDBFieldInfo.h"
#include "CDBValue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// CTaskBlockDetail *NewTaskBlockDetail()
// {
// 	CTaskBlockDetail *p = NULL ;
// 	CString strSQL ;
// // 	strSQL.Format("select * from tb_task_blockdetail limit 1") ;
// 	strSQL.Format("desc tb_task_blockdetail") ;
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK);
// 	MYSQL_RES *pRes = CDB_Manager::GetDBManagerPtr()->GetTableBySql(strSQL) ;
// 
// 	if ( pRes == NULL)
// 	{
// 		return false ;
// 	}
// 	int num_rows = mysql_num_rows(pRes);
// 	int num_fields = mysql_num_fields(pRes);
// 	MYSQL_FIELD* pfields;//数组，包含所有field的元数据
// 	pfields = mysql_fetch_fields(pRes);
// 	MYSQL_ROW row ;
// 	int icount = 0 ;
// 
// 	CDBFieldInfo *pFieldInfo = NULL ;
// 	CDBValue *pValue = NULL ;
// 
// 	p = new CTaskBlockDetail ;
// 	while ( (row = mysql_fetch_row( pRes)) != NULL)
// 	{
// 		icount++ ;
// 		CString strType = row[1] ;
// 		if ( strType.Find("(") != -1 )
// 		{
// 			strType = strType.Left(strType.Find("(")) ;
// 		}
// 		enum enum_field_types etypes = MYSQL_TYPE_STRING ;
// 		if ( strType == "bigint")
// 		{
// 			etypes = MYSQL_TYPE_LONGLONG ;
// 		}
// 		if ( strType == "int")
// 		{
// 			etypes = MYSQL_TYPE_LONG ;
// 		}
// 		if ( strType == "double")
// 		{
// 			etypes = MYSQL_TYPE_DOUBLE ;
// 		}
// 		
// 		pFieldInfo = new CDBFieldInfo(row[0],CDB_Manager::GetDBManagerPtr()->GetConnection(DB_TASK)->strdb.c_str(),etypes) ;
// 		pValue = new CDBValue ;
// 		p->AddField(pFieldInfo, pValue) ;
// 		
// 	}
// 	CDB_Manager::GetDBManagerPtr()->FreeRecordSet() ;
// 
// 	return p ;
// 
// // 	while ( (row = mysql_fetch_row( pRes)) != NULL)
// // 	{
// // 		icount++ ;
// // 		p = new CTaskBlockDetail ;
// // 		for ( int i=0; i<num_fields; i++ )
// // 		{
// // 			if ( icount == 1 )
// // 			{
// // 				pFieldInfo = new CDBFieldInfo(pfields[0].name,pfields[0].table,pfields[0].type) ;
// // 				pValue = new CDBValue ;
// // 				p->AddField(pFieldInfo, pValue) ;
// // 			}
// // 		}
// // 	}
// 
// 	
// }

CTaskBlockDetail::CTaskBlockDetail()
{
	m_id = 0 ;
	m_blockid = 0 ;
	m_layerid = 0 ;
	m_featureid = 0 ;
	m_incrementtype = 0;
	m_direction = 0;
	m_desc = "";
	m_bScanf = false;
}

CTaskBlockDetail::CTaskBlockDetail(int idbtype,const char *sztablename)
:CTaskCommon(idbtype, sztablename)
{
	m_id = 0 ;
	m_blockid = 0 ;
	m_layerid = 0 ;
	m_featureid = 0 ;
	m_operatetype = 0;
	m_incrementtype = 0;
	m_direction = 0;
	m_desc = "";
	//默认值
	int index = GetIndex("edittime");
	if( index != -1)
		SetStringByIndex(index,"0000-00-00 00:00:00");
	index = GetIndex("checktime");
	if( index != -1)
		SetStringByIndex(index,"0000-00-00 00:00:00");

	m_bScanf = false;
}

CTaskBlockDetail::~CTaskBlockDetail()
{
	
}

void CTaskBlockDetail::SetID( __int64 id )
{
	int index = GetIndex("id");
	if( index != -1)
		SetInt64ByIndex(index,id);
	m_id = id ;
}

__int64 CTaskBlockDetail::GetID()
{
	int index = GetIndex("id");
	if( index != -1)
		return GetInt64ByIndex(index);
	return m_id;
}

void CTaskBlockDetail::SetBlockID( __int64 blockid )
{
	int index = GetIndex("blockid");
	if( index != -1)
		SetInt64ByIndex(index,blockid);
	m_blockid = blockid ;
}

__int64 CTaskBlockDetail::GetBlockID()
{
	int index = GetIndex("blockid");
	if( index != -1)
		return GetInt64ByIndex(index);
	return m_blockid ;
}

void CTaskBlockDetail::SetLayerID( int layerid )
{
	int index = GetIndex("layerid");
	if( index != -1)
		SetIntByIndex(index,layerid);
	m_layerid = layerid ;
}

int CTaskBlockDetail::GetLayerID()
{
	int index = GetIndex("layerid");
	if( index != -1)
		return GetIntByIndex(index);
	return m_layerid ;
}

void CTaskBlockDetail::SetOperateType( int type )
{
	int index=GetIndex("operatetype");
	if (index != -1 )
		SetIntByIndex(index,type);
	m_operatetype = type ;
}

int CTaskBlockDetail::GetOperateType()
{
	int index=GetIndex("operatetype");
	if (index != -1 )
		return GetIntByIndex(index);
	return m_operatetype;
}

void CTaskBlockDetail::SetDesc( CString strDesc )
{
	int index=GetIndex("desc");
	if (index != -1 )
		SetStringByIndex(index,strDesc);
	m_desc = strDesc ;
}

CString CTaskBlockDetail::GetDesc()
{
	int index=GetIndex("desc");
	if (index != -1 )
		return GetStringByIndex(index);
	return m_desc;
}

void CTaskBlockDetail::SetFeatureID( __int64 featureid )
{
	int index = GetIndex("featureid");
	if( index != -1)
		SetInt64ByIndex(index,featureid);
	m_featureid = featureid ;
}

__int64 CTaskBlockDetail::GetFeatureID()
{
	int index = GetIndex("featureid");
	if( index != -1)
		return GetInt64ByIndex(index);
	return m_featureid;
}

void CTaskBlockDetail::SetCreateTime( SYSTEMTIME time )
{
	m_createtime = time; 
}

SYSTEMTIME CTaskBlockDetail::GetCreateTime()
{
	return m_createtime ;
}

void CTaskBlockDetail::SetIncrementtype( int incrementtype )
{
	int index=GetIndex("incrementtype");
	if (index != -1 )
		SetIntByIndex(index,incrementtype);

	m_incrementtype = incrementtype ;
}

int CTaskBlockDetail::GetIncrementtype()
{
	int index=GetIndex("incrementtype");
	if (index != -1 )
		return GetIntByIndex(index);
	return m_incrementtype;
}

void CTaskBlockDetail::SetDirection( int direction )
{
	int index=GetIndex("direction");
	if (index != -1 )
		SetIntByIndex(index,direction);
	m_direction = direction ;
}

int CTaskBlockDetail::GetDirection()
{
	int index=GetIndex("direction");
	if (index != -1 )
		return GetIntByIndex(index);

	return m_direction;
}

bool CTaskBlockDetail::IsScanf()
{
	return m_bScanf;
}

void CTaskBlockDetail::SetScanf( bool scanf )
{
	m_bScanf = scanf;
}