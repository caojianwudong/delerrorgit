// CTaskLinkPoi.h: interface for the CTaskLinkPoi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTASKLINKPOI_H__C078E447_0DA1_4E1C_8F1E_3CFB1014E588__INCLUDED_)
#define AFX_CTASKLINKPOI_H__C078E447_0DA1_4E1C_8F1E_3CFB1014E588__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class _declspec(dllexport) CTaskLinkPoi  
{
public:
	CTaskLinkPoi();
	virtual ~CTaskLinkPoi();

public:
	void	SetID(__int64 id);
	__int64 GetID();

	void    SetPoitempid(__int64 id);
	__int64 GetPoitempid();

	void    SetTaskId(__int64 id);
	__int64 GetTaskId();

	void    SetOperatetype(int type);
	int     GetOperatetype();

	void    SetSource(int source);
	int     GetSource();

	void    SetManualcheck(bool bCheck);
	bool    GetManualcheck();

	void    SetAutoCheck(bool bCheck);
	bool    GetAutoCheck();

	void    SetEditRoleId(int id);
	int     GetEditRoleId();

	void    SetCheckRoleId(int id);
	int     GetChechRoleId();



private:
	//
	__int64 m_id;
	//Ä¸¿âpoiid
	__int64 m_poitempid;
	//
	__int64 m_taskid;
	//
	int m_operatetype;
	//
	int m_source;
	//
	bool  m_manualcheck;
	//
	bool  m_autocheck;
	//
	int   m_idEditRoleUser;
	//
	int	  m_idCheckRoleUser;



};

#endif // !defined(AFX_CTASKLINKPOI_H__C078E447_0DA1_4E1C_8F1E_3CFB1014E588__INCLUDED_)
