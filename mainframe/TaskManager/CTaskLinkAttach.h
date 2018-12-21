// CTaskLinkAttach.h: interface for the CTaskLinkAttach class.
//任务关联的照片/视频
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
	//索引id
	__int64  m_id;
	//任务id
	__int64  m_taskId;
	//1:照片，2:语音
	int m_recordtype;
	//关联照片的id
	__int64  m_attachid;
	//关联外业资料的id
	__int64  m_shapeid;
	//位置

	//关联poi的唯一标识
	__int64 m_timestamp;
	//时长(秒)
	int  m_length;
	__int64 m_poitempid;
	
	//图层编号
	int m_layerid;


};

#endif // !defined(AFX_CTASKLINKATTACH_H__4B224EE0_B933_4A56_85DC_4FC8FBD9273A__INCLUDED_)
