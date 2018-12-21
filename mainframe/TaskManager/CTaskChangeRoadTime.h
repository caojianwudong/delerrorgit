// CTaskChangeRoadTime.h: interface for the CTaskChangeRoadTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTASKCHANGEROADTIME_H__F63A14AE_B4BD_4F6C_85E5_1FC554AC2F3B__INCLUDED_)
#define AFX_CTASKCHANGEROADTIME_H__F63A14AE_B4BD_4F6C_85E5_1FC554AC2F3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CDBFields.h"

class __declspec(dllexport) CTaskChangeRoadTime : public CDBFields 
{
public:
	CTaskChangeRoadTime();
	virtual ~CTaskChangeRoadTime();

	void			SetID(__int64 id) ;
	__int64			GetID() ;

	void			SetTaskID(__int64 taskid) ;
	__int64			GetTaskID() ;


	void			SetBeginTime(SYSTEMTIME time) ;
	SYSTEMTIME		GetBeginTime() ;

	void			SetEndTime(SYSTEMTIME time) ;
	SYSTEMTIME		GetEndTime() ;

	void			SetUpdateTime(SYSTEMTIME time) ;
	SYSTEMTIME		GetUpdateTime() ;

	void			SetState(int istate) ;
	int				GetState() ;

private:
	__int64				m_id ;
	__int64				m_taskid ;
	SYSTEMTIME			m_begintime ;
	SYSTEMTIME			m_endtime ;
	SYSTEMTIME			m_updatetime ;
	int					m_state ;// 0开始组织，1组织完毕，2批处理开始，3批处理完毕
};

#endif // !defined(AFX_CTASKCHANGEROADTIME_H__F63A14AE_B4BD_4F6C_85E5_1FC554AC2F3B__INCLUDED_)
