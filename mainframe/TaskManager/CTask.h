// CTask.h: interface for the CTask class.
/*
	1.0 外业资料记录是指fielddata表记录
	2.0 外业资料是指fielddata表记录的shapeid对应的外业点
	3.0 外业资料驱动是按照整理好的外业资料id容器顺序驱动
	4.0 任务关联fielddata、attach、block信息，其中block代替之前的linkpoi信息。
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTASK_H__FA1FB987_3AB8_4335_9B06_58D076878A37__INCLUDED_)
#define AFX_CTASK_H__FA1FB987_3AB8_4335_9B06_58D076878A37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "video_definition.h"

#include <vector>
#include <map>

#include "task_definition.h"

struct vtDef
{
	std::vector<__int64> vt;
};

enum RECORDTYPE
{
	RECORDTYPE_PHOTO = 1,//照片
	RECORDTYPE_SOUND = 2//语音
};

class CTaskLinkAttach;
class CTaskLinkFieldData;
class CTaskBlock ;

typedef   std::pair<CString,CString>  VALUEPAIR;  
typedef std::multimap<CString, VALUEPAIR> MAP_STRINGPAIR;

// shapeid -- fielddata
typedef    std::multimap<__int64 ,CTaskLinkFieldData* >  MAP_SHAPEID_FIELDDATA;

#include "CTaskCommon.h"

struct FieldRefer 
{
	string strname ;
	__int64 batchid ;
	_TSGEO::SGeoRect bound ;
};

struct EditRefer 
{
	string strname ;
	_TSGEO::SGeoRect bound ;
};

typedef std::vector<FieldRefer>			VT_FieldRefer ;
typedef std::vector<EditRefer>			VT_EditRefer ;

class _declspec(dllexport) CTask  :public CTaskCommon
{
public:
	CTask();
	virtual ~CTask();

	__int64  GetID();
	void     SetID(__int64 id);
	int      GetTaskType();
	void     SetTaskType(int tasktype);
	int      GetState();
	void     SetState(int state);
	void     SetProcess(int process );
	int		 GetProcess();
	int      GetRoleId();
	void     SetRoleId(int roleid);
	void     SetEditRoleId(int iEditRoleId);
	int      GetEditRoleId();
	void     SetCheckRoleId(int idCheckRole);
	int      GetCheckRoleId();
	__int64       GetProjectId();
	void     SetProjectId(__int64);
	double   GetLastExit();
	void     SetLastExit(double lastexit);
	void     SetPriority(int priority);
	void     SetProjectName(CString sProjectName);
	CString  GetProjectName();

	__int64  GetBatchId();
	void     SetBatchId(__int64 batchid );

	CString  GetTaskName();

	void SetTaskBlock(CTaskBlock *pTaskBlock) ;
	CTaskBlock *GetTaskBlock() ;

	bool LoadLinkInfo()  ;


	//释放任务内存
	void	ReleaseTask();
	//清空任务信息
	void Clear();

	// 参考的区域
	_TSGEO::SGeoRect GetQCBound() ;
	void SetQCBound(_TSGEO::SGeoRect bound) ;
	_TSGEO::SGeoRect GetToolBound() ;
	void SetToolBound(_TSGEO::SGeoRect bound) ;
	// qc批处理的图层
	const char *GetQCLayerNameByIndex(int index) ;
	const char *GetToolLayerNameByIndex(int index) ;
	void SetQCReferLayerName(const char* szLayername) ;
	void SetToolReferLayerName(const char *szLayername) ;
	// 获得参考图层的个数
	int GetQCReferLayerCount() ;
	int GetToolReferLayerCount() ;
	int GetEditReferLayerCount() ;
	int GetFieldReferLayerCount() ;
	// 获取参考图层信息
	FieldRefer GetFieldReferIndex(int iIndex) ;
	void SetFieldRefer(FieldRefer fieldrefer) ;

	EditRefer GetEditReferIndex(int iIndex) ;
	void SetEditRefer(EditRefer editrefer) ;

	// 根据关键字获得referdata的jsonb,此方法用于已经加载过task语句以后（LoadLinkInfo）
	void GetReferdataByKey(const char *szkey) ;
private:
	bool LoadLinkAttach() ;
	bool LoadLinkFielddata() ;

	//====================外业资料DB======================================//
public:
	//
	void  AddTaskLinkFieldData(__int64 shapeid,CTaskLinkFieldData* pFieldData);

	void  AddTaskLinkAttach(CTaskLinkAttach* pAttach);
	
	//获取数据表中外业资料记录数
	int GetLinkDbFieldDataCount();

	//根据索引获取数据表中外业资料
	CTaskLinkFieldData*  GetLinkFieldDataByIndex(int index);

	//根据外业资料id获取对应的poiid
	bool  GetPoiIdByShapeid(__int64 shapeid,vtDef* pvtDef);

	//根据外业资料id获取对应的piciid
	bool  GetPicIdByShapeid(__int64 shapeid ,vtDef* pvtdef);

	//根据poiid获取对应的piciid
	bool  GetPicIdByPoiid(__int64 poiid, vtDef* pvtdef);

	//=====================照片/视频=====================================//
public:
	//获取数据表中照片的记录数
	int  GetLinkAttachCount();
	//根据索引获取数据表的照片数据
	CTaskLinkAttach*  GetLinkAttachByIndex(int index);

	//根据picid获取poi集合
	bool GetPoiIdByPicid(__int64 picid, vtDef* pvtdef);

	//=======================poi=====================================//
public:

	//获取疑问信息
	int GetInfoType(__int64 poiid);

	//获取浏览标识
	bool bScan(__int64 poiid);

protected:

	//任务关联的外业资料，用map存储，shapeid当索引是为了方便查找
	//< shapeid , fileddata* >
	MAP_SHAPEID_FIELDDATA  map_taskLinkFieldData;
	//任务关联的照片
	std::vector<CTaskLinkAttach* > vt_taskLinkAttach;

	//任务关联的处理逻辑集合
	std::vector<__int64> m_vtTaskLinkItemset;

private:
	//任务id
	__int64 m_id;
	//任务类型：1:视频，20:步调普通任务，21:步调外业新增POI任务，22：步调外业新增门址点任务，23：步调外业修改POI任务，24：步调外业修改门址点任务)
	int m_iTaskType;
	//流程类型:1:制作流程，2:抽检流程，3:综合检查流程
	int m_iFlowType;
	//任务状态：0未占用（默认），1占用，2提交，3任务完成
	int m_iState;
	//角色名称
	int m_iRoleId;
	//编辑人员最后一次操作视频时的角色用户id，制作修改为同一人
	int m_idEditRoleUser;
	//校验人员最后一次操作视频时的角色户用id：校正验证为同一人
	int m_idCheckRoleUser;
	//任务所属的项目id
	__int64 m_idProject;
	// 任务进度 照片:POI索引 视频:
	double m_dLastExit;
	//优先级 优先安排数字小的任务
	int  m_iPriority;
	//参考图层数据
	char* m_szReferData;
	//项目名称
	CString m_sProName;
	//任务POI 类型 0: 初始值 1 :普通POI 2:vip poi(校正筛选的时候才会修改这个值)
	int m_taskpoitype;
	//参考数据
	CString m_strRefer;
	__int64 m_batchid;

	

public:
	//初始化任务数据
	bool  InitData();
  
	//是否允许提交任务
	bool  bAlloCommitTask();


	//====================外业资料================================
public:
	
	//设置当前操作的外业资料
	void SetCurrentShapeIndex(int index);
	
    //获取当前外业资料的索引
	int  GetCurrentShapeIndex();
	//获取外业资料记录索引
	int  GetShapeIndexByShapeid(__int64 shapeid);
	
	//获取当前操作的外业资料
	CTaskLinkFieldData* GetCurrentFieldData();
	
	//获取当前外业资料的id
	__int64  GetCurrentShapeId();
	
	//获取外业资料个数
	int   GetFieldDataCount();
	//获取外业资料id
	__int64  GetShapeIdByIndex(int index);
	
	//根据poiid获取外业资料id
	__int64  GetShapeIdByFeatureId(int poiid);

	//获取下一个外业资料索引
	__int64  GetNextShapeIndex();

	//获取上一个外业资料索引
	__int64  GetPreShapeIndex();

	//新增任务外业记录关系
	void  AddNewTaskLinkFieldData(__int64 shapeid,CTaskLinkFieldData* pFieldData);

	//新增任务照片记录关系
	void  AddNewTaskLinkAttach(CTaskLinkAttach* pAttach);
	
	//======================照片/视频===========================
public:
	//根据外业资料id获取照片集合
	bool   GetPicByShapeId(__int64 shapeid,vtDef* pvtDef);
	
	
	bool   GetPoiByPicId(__int64 pic,std::vector<__int64> &vt);
	
	//根据照片索引获取路径
	CString  GetPicPathByPicid(__int64 picid);

	//根据照片名称获取picid
	__int64 CTask::GetPicIdByPath(CString strPicName);
	
	void     AddPicPath(__int64 picid,CString strPath);
	
	
	//=======================poi===================================
public:

	//获取从属poi集(必须在sde加载poi后才能调用)
	void        GetPoiLinkPoi();

	bool        GetPoiLinkPoiByShapeId(__int64 shapeid,vtDef* pvtDef);

	//  
	void       AddDelDesc(CString ske,CString ikey,CString svalue);
	//获取第一个删除的描述信息
	int		   GetDelDescCount();

	bool       GetDelDescByIndex(int index,CString& ivalue ,CString& svalue);

	CString    GetErrorTypeName(CString sErrtype);

	CString    GetErrorTypeNameByIndex(int index);

	CString    GetErrorTypeByName(CString stypeanme);

	int		   GetErrorCount();

    int        GetQuestionDescCount();
	void       GetQuestionDescByIndex(int index,CString &sKey,CString& sValue);


	//by ycf 20170306 需要提供一个函数判断这个任务中的POi的那些字段有编辑的权限，那些poi有移动的权限
	bool         bAllow(){return true;}

	void SetReferData(CString strRefer);

	CString GetReferData();
	//增加任务关联的处理逻辑集合
	void AddTaskLinkItemset(__int64 itemsetid);
	int GetTaskLinkItemsetCount();
	__int64 GetTaskLinkItemsetByIndex(int index);
private:
	

	//设置当前操作的外业资料索引
	int     m_ShapeIndex ;
	
	//外业资料shapeid
	std::vector<__int64 > vt_shape_id;
	//shapeid,poiid
	std::map<__int64 ,std::vector<__int64> > map_shapeid_poiid;
	//shapeid,poi,poi （外业资料关联的Poi，poi关联的Poi ) 用于关联poi列表
	std::map<__int64 ,std::vector<__int64> > map_shapeid_poiid_poiid;
	//shapeid,picid
	std::map<__int64 ,std::vector<__int64> > map_shapeid_picid;
	//pic,poiid
	std::map<__int64,std::vector<__int64> > map_picid_poiid;
	//poiid,picid
	std::map<__int64,std::vector<__int64> > map_poiid_picid;
	//pic ,path
	std::map<__int64,CString > map_pic_path;

	//数据库配置信息
	MAP_STRINGPAIR    map_DBconfig;

	CTaskBlock *m_pBlock ;

	_TSGEO::SGeoRect m_sqcBound ;
	VT_CHAR m_vtqcLayerName ;
	_TSGEO::SGeoRect m_stoolBound ;
	VT_CHAR m_vttoolLayerName ;
	
	VT_EditRefer m_vtEditRefer ;
	VT_FieldRefer m_vtFieldRefer ;
	
};

#endif // !defined(AFX_CTASK_H__FA1FB987_3AB8_4335_9B06_58D076878A37__INCLUDED_)
