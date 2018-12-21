// CTaskLinkAttach.h: interface for the CTaskLinkAttach class.
//�����������Ƭ/��Ƶ
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTASKLINKATTACH_H__4B224EE0_B933_4A56_85DC_4FC8FBD9273A__INCLUDED_)
#define AFX_CTASKLINKATTACH_H__4B224EE0_B933_4A56_85DC_4FC8FBD9273A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CTaskCommon.h"

class _declspec(dllexport) CTaskLinkAttach  :public CTaskCommon
{
public:
	CTaskLinkAttach();
	CTaskLinkAttach(int idbtype,const char *sztablename);
	virtual ~CTaskLinkAttach();

public:
	void	SetID(__int64 id);
	__int64 GetID();

	void    SetTaskId(__int64 id);
	__int64 GetTaskId();

	void    SetRecordType(int type);
	int     GetRecordType();

	void    SetAttachId(__int64 id);
	__int64 GetAttachId();

	void    SetShapeId(__int64 id);
	__int64 GetShapeId();

	void    SetTimestamp(__int64 time);
	__int64 GetTimestamp();

	void    SetLength(int length);
	int     GetLength();

	void    SetFeatureid(__int64 poiid);
	__int64 GetFeatureid();

	void SetLayerId(int id);
	int GetLayerId();

private:
	//����id
	__int64  m_id;
	//����id
	__int64  m_taskId;
	//1:��Ƭ��2:����
	int m_recordtype;
	//������Ƭ��id
	__int64  m_attachid;
	//������ҵ���ϵ�id
	__int64  m_shapeid;
	//λ��

	//����poi��Ψһ��ʶ
	__int64 m_timestamp;
	//ʱ��(��)
	int  m_length;
	__int64 m_poitempid;
	
	//ͼ����
	int m_layerid;


};

#endif // !defined(AFX_CTASKLINKATTACH_H__4B224EE0_B933_4A56_85DC_4FC8FBD9273A__INCLUDED_)
