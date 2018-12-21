// CTaskManager.h: interface for the CTaskManager class.
// 
/*
		���������
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
	//�����ݿ��ȡ����
	//idRoleUser����ǰ��ɫid��idotherRoleUser��������ɫid�����û�������һ�ֽ�ɫid��
	CTask *	GetNextAvailableTaskInfo(  bool bFirstLogin,int nEditType,int idRoleUser,int idotherRoleUser,int iProjectId);
	//�ͷ������ڴ�
	void ReleaseTask();

	void SetTaskType(int type);

	int  GetTaskType();

	//��ȡ��ǰ������
	CTask*  GetCurTask();

	//����������ҵ���Թ�ϵ
	void AddNewTaskLinkFieldData(__int64 shapeid,CTaskLinkFieldData* pFieldData);

	//����������Ƭ��¼��ϵ
	void  AddNewTaskLinkAttach(CTaskLinkAttach* pAttach);

	//��ʱ��ɾ��poi��
	int GetDelDescId(__int64 idbase, __int64 iTaskid, int operatetype);

	bool  CommitTask();

	//��ʱ����
	void SetEditType(int iedittype);

	void SetUserId(int iUserId);

	void SetUseRoleId(int iRoleId);

	int GetRoleuserid(int idRole, int idUser);
	//�½���������
	void AddNewTaskBatch(CTaskBatch* pTaskBatch);

	//��ѯ�������Σ�����Ϊsql��ѯ����������ȷ�������룩
	void GetTaskBatchInfos(CString strCond);
	//�ͷ�TaskBatch
	void ReleaseTaskBatch();
	//��ȡ�׸�taskbachid
	CTaskBatch *GetFirstTaskBatchPtr() ;
	CTaskBatch *GetNextTaskBatchPtr() ;

	CString GetTaskBatchTableName();

	/// �½�����
	bool AddNewTask(CTask *pTask);
	const char* GetReferdataInfo(CTask *pTask) ;

	// �ͷ�TaskPro
	void ReleaseTaskPros() ;	
	//
	bool AddNewLinkInfoByTask(CTask *pTask);

	// �����task.tb_task_changeroadtime
	// �ڵ�·�仯ʱ��α������һ����¼
	bool						AddNewTaskChangeRoadTime( CTaskChangeRoadTime *pTaskChangeRoadTime) ;
	// ����������ѯ��·�仯ʱ���strcond = "where state = 1"
	bool						GetTaskChangeRoadTimeInfos( CString strCond="") ;
	// ѭ����ȡ��ѯ�ļ�¼
	CTaskChangeRoadTime*		GetFirstTaskChangeRoadTimePtr() ;
	CTaskChangeRoadTime*		GetNextTaskChangeRoadTimePtr() ;
	CTaskChangeRoadTime*		GetNextTaskChangeRoadTimePtr(CTaskChangeRoadTime *pTaskChangeRoadTime) ;
	// ����state״̬
	bool						UpdateTaskChangeRoadTimePtr(CTaskChangeRoadTime *pTaskChangeRoadTime) ;			
	// ��ȡ����ʱ��
	SYSTEMTIME					GetNewSystemtimeFromChangeRoadTimeTable() ;

	// �����CTaskBlockDetail
	// ��һ����¼д�����ݿ�
	bool						WriteDBForTaskBlockDetail(CTaskBlockDetail *pTaskBlockDetail) ;
	
	// �����TaskBlock
	/// ע�������ڲ�ѯTaskBlock��ʱ�������Ὣstatus=4/5���رգ���������ȡ����
	// ��һ��taskBlock��¼�������ݿ⣨ֱ�Ӳ�����
	bool						AddTaskBlockToDB( CTaskBlock *pTaskBlock) ;
	// ����һ��taskBlock��¼��ֱ�Ӳ�����
	bool						UpDateBlockToDB( CTaskBlock *pTaskBlock) ;
	// ����status��ֱ�Ӳ�����
	bool						UpDateBlockStatusToDB(CTaskBlock *pTaskBlock, __int64 newblockid) ;
	// ����type	��ֱ�Ӳ�����				
	bool						UpDateBlockTypeToDB(CTaskBlock *pTaskBlock) ;
	// ����envelope��ֱ�Ӳ�����
	bool						UpDateBlockEnvelope(CTaskBlock* pTaskBlock) ;
	// ��һ��block�����Ķ���д�����ݿ⣨ֱ�Ӳ�����
	bool						ADDTaskBlockInfosToDB(CTaskBlock *pTaskBlock) ;
	// ��ѯһ�������Ƿ���Block���У�����ڣ�����Block��ID�б�,size��ʾ����blockID�ĸ���/���ĳblock�Ѿ����Σ����践�أ�ֱ�Ӳ�����
	__int64*					GetBlockIDsForFeatureID(__int64 featureID, int layerid,int &size) ;
	// ����blockid��ȡһ��taskblock��¼��ֱ�Ӵӱ��ж�ȡ��ֱ�Ӳ�����
	CTaskBlock*					GetTaskBlockPtrForBlockID(__int64 blockid) ;
	// ֱ�Ӹ���blockid�ر�һ��block��¼,status=4���رգ���ɣ�5���رգ��ϲ���ֱ�Ӳ�����
	bool						CloseTaskBlockForBlockID(__int64 blockid,int status) ;

	// ˳����ȡ�ǹر�״̬��block,
	// �ͷ�m_mapTaskBlock
	void						ReleaseTaskBlocks() ;
	// �ӱ��м������ڴ��У�����������ȡ�ǹر�״̬��block
	bool						LoadTaskBlock(CString strConfition = "") ;
	// �õ���һ��
	CTaskBlock*					GetFirstTaskBlockPtr() ;
	// �õ���һ��
	CTaskBlock*					GetNextTaskBlockPtr() ;
	CTaskBlock*					GetNextTaskBlockPtr(CTaskBlock *pTaskBlock) ;

	// ����id��ȡ,���Ѿ����ص���������ȡ
	CTaskBlock*					GetTaskBlockByBlockID(__int64 blockid) ;
	// ����ID���ڴ���ȥ��һ��Block
	bool						DeleteTaskBlock(__int64 blockid) ;

public:
	//****** �������� ********/
	// �����ݿ��������
	bool AddQCTask(CQCTask *pQCTask) ;
	// ��������������񼯺�
	bool GetQCTask(CString strCond) ;
	// ��õ�λ����
	CQCTask *GetQCTaskByIndex(int iIndex) ;
	// ����������
	int GetQCTaskCount() ;
	// �ͷ�����ָ��
	void ReleaseQCTask() ;
	// �����������itemset��Ϣ
	void GetItemSetInfo(CString strCond) ;
	// ���itemset����
	int GetItemSetCount() ;
	// ���itemsetinfo
	CTaskLinkItemSet *GetTaskLinkItemSetByIndex(int iIndex) ;
	// �ͷ�ָ��
	void ReleaseItemset() ;

	/// �����ݿ��л�ȡû��ִ�е��ʼ������һ������
	CQCTask *GetLastTask(int itasktype=2001) ;
	/// �����������һ����ִ�е�����������where��ʼ��where process=51 and state=12
	CQCTask *GetLastTask(const char *szcond) ;
	// ��������
	bool UpdataQCTask(CQCTask *pQCTask) ;
	//char*תsystemtime
	SYSTEMTIME Char2Systemtime(char* p);

	//�ж�ĳһ���͵���Ŀ�Ƿ񴴽�������
	CString JudgeProjectHaveCreateTask(__int64 iProjectid, int iTaskType) ;
	//�ж�ĳһ���͵���Ŀ�Ƿ���������������
	CString JudgeProjectHaveDonePTask(__int64 iProjectid, int iProjectType);
	//ͬ������Ϊ"��������"����Ϣ
	void SyncImportTaskInfo(CTask* pTask) ;

	// ת���ֶ����͸�ʽ��mysqltype
	//enum_field_types TransType(int datatype) ;
	// ����������ȡiteminfo��Ϣ
	void GetItemInfos(const char *szcond) ;
	// ���iteminfo��Ϣ
	int GetItemInfoCount() ;
	CDBFields *GetItemInfoByIndex(int index) ;
	// �ͷ�iteminfo��Ϣ
	void ReleaseItemInfo() ;

	// blockʶ��
	// ��ȡ���µ�begintime�ֶ�
	SYSTEMTIME					GetNewSystemtimeFromChangeRoadTimeTableForBeginTime() ;
	// ����һ��taskBlock��¼���ǲ�����status��ֱ�Ӳ�����
	bool						UpDateBlockToDBNoStatus( CTaskBlock *pTaskBlock ) ;
	// ���һ����¼�Ƿ��ڱ����Ѿ�����
	bool						CheckIsHasTaskBlockDetail(__int64 blockid, __int64 featureid, int layerid) ;
	// ��һ��block�����Ķ�����ص��ڴ��У�ֱ�Ӳ�����
	bool						LoadTaskBlockDetailsForBlock(CTaskBlock *pTaskBlock) ;
	// ͨ���������ݿ��ȡblock�е�roadnum
	bool						GetTaskBlockRoadNum() ;
	// ����roadnumʱ������ʱ��
	bool						UpdateTaskBlockRoadNumNoTime(CTaskBlock *pTaskBlock) ;
	// ����roadnumʱ����ʱ��
	bool						UpdateTaskBlockRoadNum(CTaskBlock *pTaskBlock) ;

	void						SetSqlFlag(int flag) ;
	int							GetSqlFlag() ;
	void						SetChoosingTask() ;
	void						SetChoosingError() ;

	// block����
	bool						LoadTaskDetailForNull(std::vector< __int64> &vtblockid, std::vector< int> &vtstatus ) ;
	bool						LoadTaskDetail(std::vector< __int64> &vtblockid,std::vector< int > &vtlayerid, std::vector< __int64 > &vtfeatureid, 
		std::vector< int> &vtstatus,std::vector< _TSGEO::SGeoRect > &vtbound, std::vector< CString > &vtupdatetime,
		std::vector<CString> &vtmanualcheck, std::vector<CString> &vtusername,
								  std::vector<int> &vtblockmanualroadnum, std::vector<CString> &vtblockusername, std::vector<__int64> &vtdetailid,
								  std::vector<int> &vtOwner,std::vector<CString> &vtblockOwner) ;

private:
	VT_ITEMINFO m_vtItemInfo ;
	
protected:	

	//�����������ͻ�ȡϸ������
	CString GetTaskTypeStr(int taskType);

	void GetProjectTaskTypes(__int64 projectid);

	bool IsAvaliableType(int tasktype);

	//������Ŀ���ȼ���ȡ����
	//idRoleUser����ǰ��ɫid��idotherRoleUser��������ɫid�����û�������һ�ֽ�ɫid��
	CTask * GetTask( __int64 nPid, int taskType,int nEditType,int idRoleUser,int idotherRoleUser, bool bFirstLogin=false);

	int GetOccupiedTaskCount( int nEditType);

	CTask* GetTaskInfo(const char *sql);

	//����������־
	void AddTaskLog( __int64 idTask, int state);

	CString GetDllPath();

	//��ȡ��Ŀ����
	bool GetProgress(int nProjectID, int nTaskCount,
		std::pair<int,int> &pairEditProg,
		std::pair<int,int> &pairCheckProg,
		std::pair<int,int> &pairModifyProg,
		std::pair<int,int> &pairConfirmProg,
		std::pair<int,int> &pairOverProg );

	// linestringתsgeorect
	// ��ʽ��LINESTRING(112.23456 39.123456,113.123456 40.123456)��
	_TSGEO::SGeoRect LineString2SGeoRect( CString linestring) ;
	// �и��ַ���
	void SqlitCString(CString strContent,CString ch,vector<CString>& strResultArr); //���������ַ���

	
private:
	//��ǰ����
	CTask* m_pTask;
	//��½ѡ�����������: ���� , ����
	int m_iTaskType;

	//����
	int m_nEditType;

	//�û�Id
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
