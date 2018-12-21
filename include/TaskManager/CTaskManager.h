// CTaskManager.h: interface for the CTaskManager class.
// 
/*
		任务管理类
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTASKMANAGER_H__AA17E739_2C09_4C76_B379_2B5C137DE56F__INCLUDED_)
#define AFX_CTASKMANAGER_H__AA17E739_2C09_4C76_B379_2B5C137DE56F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CTaskBlock.h"
#include <vector>
#include <map>

#include "task_definition.h"
using namespace   std;

#pragma warning(disable:4192)


class CTask;
class CTaskLinkFieldData;
class CTaskLinkAttach;
class CTaskBatch;
class CTaskChangeRoadTime ;
class CTaskBlock ;
class CTaskBlockDetail ;
class CQCTask ;
class CTaskLinkItemSet ;
class CDBFields ;

typedef std::vector<CTaskBatch*>		VT_TASK_BATCH ;
typedef std::vector<CTaskChangeRoadTime * > VT_TASK_CHANGEROADTIME ;
typedef std::map< __int64, CTaskBlock * > MAP_TASK_BLOCK ;
typedef std::vector<CQCTask *>			VT_QCTASK ;
typedef std::vector<CTaskLinkItemSet *>	VT_LINKITEMSET ;
typedef std::vector<CDBFields *>		VT_ITEMINFO ;


class _declspec(dllexport) CTaskManager  
{
public:
	CTaskManager();
	virtual ~CTaskManager();
	static CTaskManager*  GetTaskManager();
	static void  DestroyTaskManager();
private:
	static CTaskManager*   m_pManagerPtr;

public:
	//从数据库获取任务
	//idRoleUser：当前角色id；idotherRoleUser：其他角色id（该用户的另外一种角色id）
	CTask *	GetNextAvailableTaskInfo(  bool bFirstLogin,int nEditType,int idRoleUser,int idotherRoleUser,int iProjectId);
	//释放任务内存
	void ReleaseTask();

	void SetTaskType(int type);

	int  GetTaskType();

	//获取当前的任务
	CTask*  GetCurTask();

	//新增任务外业属性关系
	void AddNewTaskLinkFieldData(__int64 shapeid,CTaskLinkFieldData* pFieldData);

	//新增任务照片记录关系
	void  AddNewTaskLinkAttach(CTaskLinkAttach* pAttach);

	//临时给删除poi用
	int GetDelDescId(__int64 idbase, __int64 iTaskid, int operatetype);

	bool  CommitTask();

	//临时函数
	void SetEditType(int iedittype);

	void SetUserId(int iUserId);

	void SetUseRoleId(int iRoleId);

	int GetRoleuserid(int idRole, int idUser);
	//新建任务批次
	void AddNewTaskBatch(CTaskBatch* pTaskBatch);

	//查询任务批次，参数为sql查询条件（需正确完整输入）
	void GetTaskBatchInfos(CString strCond);
	//释放TaskBatch
	void ReleaseTaskBatch();
	//获取首个taskbachid
	CTaskBatch *GetFirstTaskBatchPtr() ;
	CTaskBatch *GetNextTaskBatchPtr() ;

	CString GetTaskBatchTableName();

	/// 新建任务
	bool AddNewTask(CTask *pTask);
	const char* GetReferdataInfo(CTask *pTask) ;

	// 释放TaskPro
	void ReleaseTaskPros() ;	
	//
	bool AddNewLinkInfoByTask(CTask *pTask);

	// 处理表task.tb_task_changeroadtime
	// 在道路变化时间段表中添加一条记录
	bool						AddNewTaskChangeRoadTime( CTaskChangeRoadTime *pTaskChangeRoadTime) ;
	// 根据条件查询道路变化时间表，strcond = "where state = 1"
	bool						GetTaskChangeRoadTimeInfos( CString strCond="") ;
	// 循环获取查询的记录
	CTaskChangeRoadTime*		GetFirstTaskChangeRoadTimePtr() ;
	CTaskChangeRoadTime*		GetNextTaskChangeRoadTimePtr() ;
	CTaskChangeRoadTime*		GetNextTaskChangeRoadTimePtr(CTaskChangeRoadTime *pTaskChangeRoadTime) ;
	// 更新state状态
	bool						UpdateTaskChangeRoadTimePtr(CTaskChangeRoadTime *pTaskChangeRoadTime) ;			
	// 获取最新时间
	SYSTEMTIME					GetNewSystemtimeFromChangeRoadTimeTable() ;

	// 处理表CTaskBlockDetail
	// 将一条记录写入数据库
	bool						WriteDBForTaskBlockDetail(CTaskBlockDetail *pTaskBlockDetail) ;
	
	// 处理表TaskBlock
	/// 注：以下在查询TaskBlock表时，均不会将status=4/5（关闭）的内容提取出来
	// 将一条taskBlock记录吸入数据库（直接操作表）
	bool						AddTaskBlockToDB( CTaskBlock *pTaskBlock) ;
	// 更新一条taskBlock记录（直接操作表）
	bool						UpDateBlockToDB( CTaskBlock *pTaskBlock) ;
	// 更新status（直接操作表）
	bool						UpDateBlockStatusToDB(CTaskBlock *pTaskBlock, __int64 newblockid) ;
	// 更新type	（直接操作表）				
	bool						UpDateBlockTypeToDB(CTaskBlock *pTaskBlock) ;
	// 更新envelope（直接操作表）
	bool						UpDateBlockEnvelope(CTaskBlock* pTaskBlock) ;
	// 将一个block关联的对象都写入数据库（直接操作表）
	bool						ADDTaskBlockInfosToDB(CTaskBlock *pTaskBlock) ;
	// 查询一个对象是否在Block表中，如果在，返回Block的ID列表,size表示包含blockID的个数/如果某block已经屏蔽，不予返回（直接操作表）
	__int64*					GetBlockIDsForFeatureID(__int64 featureID, int layerid,int &size) ;
	// 根据blockid获取一个taskblock记录，直接从表中读取（直接操作表）
	CTaskBlock*					GetTaskBlockPtrForBlockID(__int64 blockid) ;
	// 直接根据blockid关闭一个block记录,status=4：关闭，完成，5：关闭，合并（直接操作表）
	bool						CloseTaskBlockForBlockID(__int64 blockid,int status) ;

	// 顺序提取非关闭状态的block,
	// 释放m_mapTaskBlock
	void						ReleaseTaskBlocks() ;
	// 从表中加载至内存中，根据条件读取非关闭状态的block
	bool						LoadTaskBlock(CString strConfition = "") ;
	// 得到第一个
	CTaskBlock*					GetFirstTaskBlockPtr() ;
	// 得到下一个
	CTaskBlock*					GetNextTaskBlockPtr() ;
	CTaskBlock*					GetNextTaskBlockPtr(CTaskBlock *pTaskBlock) ;

	// 根据id获取,从已经加载的容器里提取
	CTaskBlock*					GetTaskBlockByBlockID(__int64 blockid) ;
	// 根据ID从内存中去掉一个Block
	bool						DeleteTaskBlock(__int64 blockid) ;

public:
	//****** 任务处理部分 ********/
	// 向数据库添加任务
	bool AddQCTask(CQCTask *pQCTask) ;
	// 根据条件获得任务集合
	bool GetQCTask(CString strCond) ;
	// 获得单位任务
	CQCTask *GetQCTaskByIndex(int iIndex) ;
	// 获得任务个数
	int GetQCTaskCount() ;
	// 释放任务指针
	void ReleaseQCTask() ;
	// 根据条件获得itemset信息
	void GetItemSetInfo(CString strCond) ;
	// 获得itemset个数
	int GetItemSetCount() ;
	// 获得itemsetinfo
	CTaskLinkItemSet *GetTaskLinkItemSetByIndex(int iIndex) ;
	// 释放指针
	void ReleaseItemset() ;

	/// 从数据库中获取没有执行的最开始的任务一个任务
	CQCTask *GetLastTask(int itasktype=2001) ;
	/// 根据条件获得一个可执行的任务，条件以where开始：where process=51 and state=12
	CQCTask *GetLastTask(const char *szcond) ;
	// 保存任务
	bool UpdataQCTask(CQCTask *pQCTask) ;
	//char*转systemtime
	SYSTEMTIME Char2Systemtime(char* p);

	//判断某一类型的项目是否创建过任务
	CString JudgeProjectHaveCreateTask(__int64 iProjectid, int iTaskType) ;
	//判断某一类型的项目是否做完了属性任务
	CString JudgeProjectHaveDonePTask(__int64 iProjectid, int iProjectType);
	//同步类型为"导入任务"的信息
	void SyncImportTaskInfo(CTask* pTask) ;

	// 转换字段类型格式到mysqltype
	//enum_field_types TransType(int datatype) ;
	// 根据条件获取iteminfo信息
	void GetItemInfos(const char *szcond) ;
	// 获得iteminfo信息
	int GetItemInfoCount() ;
	CDBFields *GetItemInfoByIndex(int index) ;
	// 释放iteminfo信息
	void ReleaseItemInfo() ;

	// block识别
	// 获取最新的begintime字段
	SYSTEMTIME					GetNewSystemtimeFromChangeRoadTimeTableForBeginTime() ;
	// 更新一条taskBlock记录但是不更新status（直接操作表）
	bool						UpDateBlockToDBNoStatus( CTaskBlock *pTaskBlock ) ;
	// 检查一条记录是否在表中已经存在
	bool						CheckIsHasTaskBlockDetail(__int64 blockid, __int64 featureid, int layerid) ;
	// 将一个block关联的对象加载到内存中（直接操作表）
	bool						LoadTaskBlockDetailsForBlock(CTaskBlock *pTaskBlock) ;
	// 通过遍历数据库获取block中的roadnum
	bool						GetTaskBlockRoadNum() ;
	// 更新roadnum时不更新时间
	bool						UpdateTaskBlockRoadNumNoTime(CTaskBlock *pTaskBlock) ;
	// 更新roadnum时更新时间
	bool						UpdateTaskBlockRoadNum(CTaskBlock *pTaskBlock) ;

	void						SetSqlFlag(int flag) ;
	int							GetSqlFlag() ;
	void						SetChoosingTask() ;
	void						SetChoosingError() ;

	// block更新
	bool						LoadTaskDetailForNull(std::vector< __int64> &vtblockid, std::vector< int> &vtstatus ) ;
	bool						LoadTaskDetail(std::vector< __int64> &vtblockid,std::vector< int > &vtlayerid, std::vector< __int64 > &vtfeatureid, 
		std::vector< int> &vtstatus,std::vector< _TSGEO::SGeoRect > &vtbound, std::vector< CString > &vtupdatetime,
		std::vector<CString> &vtmanualcheck, std::vector<CString> &vtusername,
								  std::vector<int> &vtblockmanualroadnum, std::vector<CString> &vtblockusername, std::vector<__int64> &vtdetailid,
								  std::vector<int> &vtOwner,std::vector<CString> &vtblockOwner) ;

private:
	VT_ITEMINFO m_vtItemInfo ;
	
protected:	

	//根据任务类型获取细分类型
	CString GetTaskTypeStr(int taskType);

	void GetProjectTaskTypes(__int64 projectid);

	bool IsAvaliableType(int tasktype);

	//根据项目优先级获取任务
	//idRoleUser：当前角色id；idotherRoleUser：其他角色id（该用户的另外一种角色id）
	CTask * GetTask( __int64 nPid, int taskType,int nEditType,int idRoleUser,int idotherRoleUser, bool bFirstLogin=false);

	int GetOccupiedTaskCount( int nEditType);

	CTask* GetTaskInfo(const char *sql);

	//增加任务日志
	void AddTaskLog( __int64 idTask, int state);

	CString GetDllPath();

	//获取项目进度
	bool GetProgress(int nProjectID, int nTaskCount,
		std::pair<int,int> &pairEditProg,
		std::pair<int,int> &pairCheckProg,
		std::pair<int,int> &pairModifyProg,
		std::pair<int,int> &pairConfirmProg,
		std::pair<int,int> &pairOverProg );

	// linestring转sgeorect
	// 格式【LINESTRING(112.23456 39.123456,113.123456 40.123456)】
	_TSGEO::SGeoRect LineString2SGeoRect( CString linestring) ;
	// 切割字符串
	void SqlitCString(CString strContent,CString ch,vector<CString>& strResultArr); //不保留空字符串

	
private:
	//当前任务
	CTask* m_pTask;
	//登陆选择的任务类型: 属性 , 几何
	int m_iTaskType;

	//类型
	int m_nEditType;

	//用户Id
	int m_idUser;

	int m_idRoleUser;

	std::map<__int64, std::vector<int> > map_tasktypevt;

	VT_TASK_BATCH m_vtTaskBatchInfos;
	VT_TASK_BATCH::iterator m_itTaskBatch ;
	
	VT_TASK_CHANGEROADTIME				m_vtTaskChangeRoadTime ;
	VT_TASK_CHANGEROADTIME::iterator	m_currentTaskChangRoadTimePtr ;

	MAP_TASK_BLOCK						m_mapTaskBlock ;
	MAP_TASK_BLOCK::iterator			m_currentTaskBlockPtr ;

	VT_QCTASK m_vtqctask ;
	VT_LINKITEMSET m_vtItemset ;

	CString m_csHostIP;
	int m_iHostPort;
	CString m_csHostDBName;
	CString m_csHostUsername;
	CString m_csHostPassword;

	CString m_csHostIP2;
	int m_iHostPort2;
	CString m_csHostDBName2;
	CString m_csHostUsername2;
	CString m_csHostPassword2;

	// tb_blcok
	__int64 m_currentblockid ;

	int m_sqlFlag ;
};

#endif // !defined(AFX_CTASKMANAGER_H__AA17E739_2C09_4C76_B379_2B5C137DE56F__INCLUDED_)
