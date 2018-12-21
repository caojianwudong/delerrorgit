// CTaskLinkAttach.cpp: implementation of the CTaskLinkAttach class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskManager.h"
#include "CTaskLinkAttach.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaskLinkAttach::CTaskLinkAttach()
{
	 m_id = 0;
	m_taskId = 0;
	m_recordtype = 0;
	m_attachid = 0;
	m_shapeid = 0;
	//Œª÷√
	
    m_timestamp = 0;
	m_length = 0;
	m_layerid = 0;
}

CTaskLinkAttach::CTaskLinkAttach(int idbtype,const char *sztablename)
:CTaskCommon(idbtype, sztablename)
{
	m_id = 0;
	m_taskId = 0;
	m_recordtype = 0;
	m_attachid = 0;
	m_shapeid = 0;
	//Œª÷√
	
    m_timestamp = 0;
	m_length = 0;
	m_layerid = 0;
}

CTaskLinkAttach::~CTaskLinkAttach()
{

}

void CTaskLinkAttach::SetID(__int64 id)
{
	int index = GetIndex("id");
	if( index != -1)
		 SetInt64ByIndex(index,id);
}

__int64 CTaskLinkAttach::GetID()
{
	int index = GetIndex("id");
	if( index != -1)
		return GetInt64ByIndex(index);
	return -1;
}

void CTaskLinkAttach::SetTaskId(__int64 id)
{
	int index = GetIndex("taskid");
	if( index != -1)
		 SetInt64ByIndex(index,id);
}

__int64 CTaskLinkAttach::GetTaskId()
{
	int index = GetIndex("taskid");
	if( index != -1)
		return GetInt64ByIndex(index);
	return -1;
}

void CTaskLinkAttach::SetAttachId(__int64 id)
{
	int index = GetIndex("attachid");
	if( index != -1)
		SetInt64ByIndex(index,id);
}

__int64 CTaskLinkAttach::GetAttachId()
{
	int index = GetIndex("attachid");
	if( index != -1)
		return m_attachid = GetInt64ByIndex(index);
	return -1;
}

void CTaskLinkAttach::SetRecordType(int type)
{
	int index = GetIndex("recordtype");
	if( index != -1)
		SetIntByIndex(index,type);
}

int CTaskLinkAttach::GetRecordType()
{
	int index = GetIndex("recordtype");
	if( index != -1)
		return GetIntByIndex(index);
	return -1;
}

void CTaskLinkAttach::SetShapeId(__int64 id)
{
	int index = GetIndex("shapeid");
	if( index != -1)
		SetInt64ByIndex(index,id);
}

__int64 CTaskLinkAttach::GetShapeId()
{
	int index = GetIndex("shapeid");
	if( index != -1)
		return GetInt64ByIndex(index);
	return -1;
}

void CTaskLinkAttach::SetTimestamp(__int64 time)
{
	m_timestamp = time;
}

__int64 CTaskLinkAttach::GetTimestamp()
{
	return m_timestamp;
}

void CTaskLinkAttach::SetLength(int length)
{
	m_length = length;
}

int  CTaskLinkAttach::GetLength()
{
	return m_length;
}

void CTaskLinkAttach::SetFeatureid(__int64 poiid)
{
	int index = GetIndex("featureid");
	if( index != -1)
		SetInt64ByIndex(index , poiid);
}

__int64 CTaskLinkAttach::GetFeatureid()
{
	int index = GetIndex("featureid");
	if( index != -1)
		return GetInt64ByIndex(index);
	return -1;
}

void CTaskLinkAttach::SetLayerId(int id)
{
	int index = GetIndex("layerid");
	if( index != -1)
		SetIntByIndex(index,id);

	m_layerid = id;
}

int CTaskLinkAttach::GetLayerId()
{
	int index = GetIndex("layerid");
	if( index != -1)
		return m_layerid = GetIntByIndex(index);

	return m_layerid;
}