// CTaskLinkFieldData.cpp: implementation of the CTaskLinkFieldData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskManager.h"
#include "CTaskLinkFieldData.h"


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

// CTaskLinkFieldData *NewTaskLinkFieldData()
// {
// 	CTaskLinkFieldData *p = NULL ;
// 	CString strSQL ;
// 	strSQL.Format("desc tb_task_link_fielddata") ;
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
// 	p = new CTaskLinkFieldData ;
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
// }

CTaskLinkFieldData::CTaskLinkFieldData()
{
	m_id = 0;
	m_taskId = 0;
	m_shapeid = 0;
	m_poitempid = 0;
	m_distance = 0;
    m_second = 0;
	m_lroadid = 0;
     m_rroadid = 0;
}

CTaskLinkFieldData::CTaskLinkFieldData(int idbtype,const char *sztablename)
:CTaskCommon(idbtype, sztablename)
{
	m_id = 0;
	m_taskId = 0;
	m_shapeid = 0;
	m_poitempid = 0;
	m_distance = 0;
    m_second = 0;
	m_lroadid = 0;
     m_rroadid = 0;
	 m_layerid = 0;
}

CTaskLinkFieldData::~CTaskLinkFieldData()
{

}

void CTaskLinkFieldData::SetID(__int64 id)
{
	int index = GetIndex("id");
	if(index != -1)
		SetInt64ByIndex(index,id);
}

__int64 CTaskLinkFieldData::GetID()
{
	int index = GetIndex("id");
	if(index != -1)
		return GetInt64ByIndex(index);
	return -1;
}

void CTaskLinkFieldData::SetTaskId(__int64 id)
{
	int index = GetIndex("taskid");
	if(index != -1)
		SetInt64ByIndex(index,id);
}

__int64 CTaskLinkFieldData::GetTaskId()
{
	int index = GetIndex("taskid");
	if(index != -1)
		return GetInt64ByIndex(index);
	return -1;
}

void CTaskLinkFieldData::SetShapeId(__int64 id)
{
	int index = GetIndex("shapeid");
	if(index != -1)
		SetInt64ByIndex(index,id);
}

__int64 CTaskLinkFieldData::GetShapeId()
{
	int index = GetIndex("shapeid");
	if(index != -1)
		return GetInt64ByIndex(index);
	return -1;
}

void CTaskLinkFieldData::SetFeatureId(__int64 id)
{
	int index = GetIndex("featureid");
	if(index != -1)
		SetInt64ByIndex(index,id);

}

__int64 CTaskLinkFieldData::GetFeatureId()
{
	int index = GetIndex("featureid");
	if(index != -1)
		return GetInt64ByIndex(index);
	return -1;
}

void CTaskLinkFieldData::SetDistance(double distance)
{
	m_distance = distance;
}

double CTaskLinkFieldData::GetDistance()
{
	return m_distance;
}

void CTaskLinkFieldData::SetSecond(double second)
{
	m_second = second;
}

double CTaskLinkFieldData::GetSecond()
{
	return m_second;
}

void CTaskLinkFieldData::SetLRoadId(__int64 roadid)
{
	m_lroadid = roadid;
}

__int64 CTaskLinkFieldData::GetLRoadId()
{
	return m_lroadid;
}

void CTaskLinkFieldData::SetRRoadId(__int64 roadid)
{
	m_rroadid = roadid;
}

__int64 CTaskLinkFieldData::GetRRoadId()
{
	return m_rroadid;
}

void CTaskLinkFieldData::SetLayerId(int id)
{
	int index = GetIndex("layerid");
	if(index != -1)
		SetIntByIndex(index,id);

	m_layerid = id;
}

int CTaskLinkFieldData::GetLayerId()
{
	int index = GetIndex("layerid");
	if(index != -1)
		return m_layerid = GetIntByIndex(index);
	return m_layerid;
}
