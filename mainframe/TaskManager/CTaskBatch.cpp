// TaskBatch.cpp: implementation of the CTaskBatch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskManager.h"
#include "CTaskBatch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaskBatch::CTaskBatch()
{
m_remark = "" ;
m_id = 0 ;
m_projectid = 0 ;
m_systemid = 0 ;
m_uid = 0 ;
m_batchid = 0 ;
m_datasetid = 0 ;
m_datasettype = 0 ;
}

CTaskBatch::~CTaskBatch()
{
int iii = 0 ;
}

void CTaskBatch::SetId(__int64 id)
{
	m_id = id;
}

__int64 CTaskBatch::GetId()
{
	return m_id;
}

void CTaskBatch::SetBatchId(__int64 iBatchId)
{
	m_batchid = iBatchId;
}

__int64 CTaskBatch::GetBatchId()
{
	return m_batchid;
}

void CTaskBatch::SetDataSetId(__int64 iDataSetId)
{
	m_datasetid = iDataSetId;
}

__int64 CTaskBatch::GetDataSetId()
{
	return m_datasetid;
}

void CTaskBatch::SetProjectId(__int64 iProjectId)
{
	m_projectid = iProjectId;
}

__int64 CTaskBatch::GetProjectId()
{
	return m_projectid;
}

void CTaskBatch::SetDataSetType(int iDataSetType)
{
	m_datasettype = iDataSetType;
}

int CTaskBatch::GetDataSetType()
{
	return m_datasettype;
}

void CTaskBatch::SetUID(int iUID)
{
	m_uid = iUID;
}

int CTaskBatch::GetUID()
{
	return m_uid;
}

void CTaskBatch::SetRemark(const char * str)
{
	m_remark = str;
}

const char * CTaskBatch::GetRemark()
{
	return m_remark.c_str();
}

void CTaskBatch::SetCreateTime(SYSTEMTIME tCreateTime)
{
	m_creatime = tCreateTime;
}

SYSTEMTIME CTaskBatch::GetCreateTime()
{
	return m_creatime;
}

void CTaskBatch::SetSystemid( int systemid )
{
	m_systemid = systemid ;
}

int CTaskBatch::GetSystemid()
{
	return m_systemid ;
}
