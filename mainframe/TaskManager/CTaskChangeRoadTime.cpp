// CTaskChangeRoadTime.cpp: implementation of the CTaskChangeRoadTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskManager.h"
#include "CTaskChangeRoadTime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaskChangeRoadTime::CTaskChangeRoadTime()
{
	m_id = 0 ;
	m_taskid = 0 ;
	m_state = 0 ;// 0开始组织，1组织完毕，2批处理开始，3批处理完毕
}

CTaskChangeRoadTime::~CTaskChangeRoadTime()
{

}

void CTaskChangeRoadTime::SetID( __int64 id )
{
	m_id = id ;
}

__int64 CTaskChangeRoadTime::GetID()
{
	return m_id ;
}

void CTaskChangeRoadTime::SetTaskID( __int64 taskid )
{
	m_taskid = taskid ;
}

__int64 CTaskChangeRoadTime::GetTaskID()
{
	return m_taskid ;
}

void CTaskChangeRoadTime::SetBeginTime( SYSTEMTIME time )
{
	m_begintime = time ;
}

SYSTEMTIME CTaskChangeRoadTime::GetBeginTime()
{
	return m_begintime ;
}

void CTaskChangeRoadTime::SetEndTime( SYSTEMTIME time )
{
	m_endtime = time ;
}

SYSTEMTIME CTaskChangeRoadTime::GetEndTime()
{
	return m_endtime ;
}

void CTaskChangeRoadTime::SetUpdateTime( SYSTEMTIME time )
{
	m_updatetime = time ;
}

SYSTEMTIME CTaskChangeRoadTime::GetUpdateTime()
{
	return m_updatetime ;
}

void CTaskChangeRoadTime::SetState( int istate )
{
	m_state = istate ;
}

int CTaskChangeRoadTime::GetState()
{
	return m_state ;
}
