// CTaskLinkFieldData.h: interface for the CTaskLinkFieldData class.
//任务与外业采集数据关联表
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTASKLINKFIELDDATA_H__475009F4_8F74_4034_8FA4_D3DB6EFB5152__INCLUDED_)
#define AFX_CTASKLINKFIELDDATA_H__475009F4_8F74_4034_8FA4_D3DB6EFB5152__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CTaskCommon.h"

class _declspec(dllexport) CTaskLinkFieldData  :public CTaskCommon
{
public:
	CTaskLinkFieldData();
	CTaskLinkFieldData(int idbtype,const char *sztablename);
	virtual ~CTaskLinkFieldData();

public:
	void	SetID(__int64 id);
	__int64 GetID();

	void    SetTaskId(__int64 id);
	__int64 GetTaskId();

	void    SetShapeId(__int64 id);
	__int64 GetShapeId();

	void    SetFeatureId(__int64 id);
	__int64 GetFeatureId();

	void    SetDistance(double distance);
	double  GetDistance();

	void    SetSecond(double second);
	double  GetSecond();

	void    SetLRoadId(__int64 roadid);
	__int64 GetLRoadId();

	void    SetRRoadId(__int64 roadid);
	__int64 GetRRoadId();

	void SetLayerId(int id);
	int GetLayerId();
private:
	//索引
	__int64  m_id;
	//任务id
	__int64  m_taskId;
	//record_shapeid
	__int64  m_shapeid;
	//关联的poiid
	__int64  m_poitempid;
	//位置
	CPoint  m_location;
	//
	double  m_distance;
	//
	double  m_second;
	//左侧道路id
	__int64  m_lroadid;
	//右侧道路id
	__int64 m_rroadid;

	//图层编号
	int m_layerid;

};

// extern "C"
// {
// 	__declspec(dllexport) CTaskLinkFieldData *NewTaskLinkFieldData() ;
// }
// 

#endif // !defined(AFX_CTASKLINKFIELDDATA_H__475009F4_8F74_4034_8FA4_D3DB6EFB5152__INCLUDED_)
