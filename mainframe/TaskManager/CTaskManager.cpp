// CTaskManager.cpp: implementation of the CTaskManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskManager.h"
#include "CTaskManager.h"
#include "task_definition.h"
//#include "CTaskProject.h"
#include "CTaskBatch.h"

#include "CConvertTool.h"
#include <algorithm>
#include "CTask.h"
#include "CTaskLinkAttach.h"
#include "CTaskLinkFieldData.h"
//#include "CTaskLinkPoi.h"
#include "task_definition.h"
///----------db
#include "CDB_Manager.h"
//#include "CTaskProject.h"
#include "CTaskBatch.h"


#include "CTaskChangeRoadTime.h"
#include "CTaskBlock.h"
#include "CTaskBlockDetail.h"
#include "CTaskLinkItemSet.h"

#include "CDBFields.h"
#include "CQCTask.h"
#include "Db_Definition.h"
#include "DB_ResultSet.h"

const int MYSQL_RUNING = 1001 ;
const int POSTGRES_RUNNING = 1002 ;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaskManager* CTaskManager::m_pManagerPtr = NULL;

CTaskManager::CTaskManager()
{
	m_pTask = NULL;
	m_sqlFlag = POSTGRES_RUNNING ;
// 	OpenDataBase();
}

CTaskManager::~CTaskManager()
{
	ReleaseTask();
	CDB_Manager::DestroyDBManagerPtr();
}


CTaskManager* CTaskManager::GetTaskManager()
{
	if ( m_pManagerPtr == NULL)
	{
		m_pManagerPtr = new CTaskManager;
	}
	return m_pManagerPtr;
}

void CTaskManager::DestroyTaskManager()
{
	if( m_pManagerPtr != NULL)
	{
		delete m_pManagerPtr;
		m_pManagerPtr = NULL;
	}
}

CTask *CTaskManager::GetNextAvailableTaskInfo(  bool bFirstLogin,int nEditType,int idRoleUser,int idotherRoleUser,int iProjectId)
{
	int taskType = m_iTaskType;
// 	int	nEditType = POIUserManager::GetPOIUserManagerPtr()->GetEditType();
// 	int	idUser = POIUserManager::GetPOIUserManagerPtr()->GetUserID();
// 	int	idRoleUser = POIUserManager::GetPOIUserManagerPtr()->GetRoleUserId();
	//若刚登录，则先释放所有项目中被自己占用过的未释放的任务，这种任务一般是平台崩溃造成的
	CString sql;
	int iAffectCount = 0;
	CString sUser = "";
	if ( bFirstLogin)
	{
	
		if ( EDITTYPE_EDIT == nEditType )
		{
			sUser = "editid";
		}
		else if ( EDITTYPE_CHECK == nEditType )
		{
			sUser = "checkid";
		}
	
	}

	std::map<__int64,CString> mapProIdName;
	std::map<__int64,CString>::iterator miter;

	//根据项目优先级获取任务
	CTask *pTaskInfo = NULL;

	GetProjectTaskTypes(iProjectId);

	std::map<__int64 ,std::vector<int> >::iterator iter = map_tasktypevt.find( iProjectId );
	if( iter != map_tasktypevt.end() )
	{
		std::vector<int> vttasktype = iter->second;
		int iSize = vttasktype.size();
		for ( int i = 0 ; i < iSize ; i++ )
		{
			taskType = vttasktype.at(i);
			if( !IsAvaliableType(taskType))
				continue;
			// if( taskType != TASKTYPE_FOOT_PRORERTYERROR )continue;
			if (bFirstLogin && !sUser.IsEmpty())
			{
				sql.Format("update tb_task set state=%d where %s=%d and state=%d and process=%d and tasktype  =%d and projectid = %I64d ;",
					STATE_UNKNOW, sUser, idRoleUser, STATE_OCCUPY, nEditType, taskType ,iProjectId);
				CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
				char szSql[1024];
				
				sprintf(szSql,"%s",sql);
				CDB_Manager::GetDBManagerPtr()->ExcuteSql(szSql,iAffectCount);
				
			}
			
			pTaskInfo = GetTask(iter->first, taskType, nEditType, idRoleUser, idotherRoleUser,bFirstLogin);
			if ( NULL != pTaskInfo)
			{
				break;
			}
		}
	}

	if( pTaskInfo == NULL)
		return NULL;

// 	LoadTaskData();
	pTaskInfo->LoadLinkInfo() ;
	pTaskInfo->InitData();

	return pTaskInfo;
}

bool CTaskManager::IsAvaliableType(int tasktype)
{
	//属性任务
	if( m_iTaskType == TASK_TYPE_ATTR )
	{
		 //平板步调属性任务
		if ( tasktype == TASKTYPE_FOOT_PRORERTY)
		{
			return true;
		}
		//平板属性改错任务
		if ( tasktype == TASKTYPE_FOOT_PRORERTYERROR)
		{
			return true;
		}
		//车调属性任务
		if ( tasktype == TASKTYPE_CAR_PRORERTY)
		{
			return true;
		}
		//车调属性改错任务
		if ( tasktype == TASKTYPE_CAR_PRORERTYERROR)
		{
			return true;
		}
		//非实测属性任务
		if ( tasktype == TASKTYPE_NET_PRORERTY )
		{
			return true;
		}
		//非实测属性改错任务
		if ( tasktype == TASKTYPE_NET_PRORERTYERROR)
		{
			return true;
		}
		//客投属性任务
		if ( tasktype == TASKTYPE_COMPLANIT_PRORERTY)
		{
			return true;
		}
		//客投属性改错任务
		if ( tasktype == TASKTYPE_COMPLANIT_PRORERTYERROR )
		{
			return true;
		}
		//平板属性新增任务
		if ( tasktype == TASKTYPE_FOOT_PRORERTYNEWADD  )
		{
			return true;
		}
		//平板属性新增门址任务
		if ( tasktype == TASKTYPE_FOOT_PRORERTYNEWADDDOOR  )
		{
			return true;
		}
		//平板属性修改任务
		if ( tasktype == TASKTYPE_FOOT_PRORERTYMODIFY  )
		{
			return true;
		}
		//平板属性修改门址任务
		if ( tasktype == TASKTYPE_FOOT_PRORERTYMODIFYDOOR  )
		{
			return true;
		}
		//众包属性任务
		if ( tasktype == TASKTYPE_CROW_PRORERTY   )
		{
			return true;
		}
		//众包属性改错任务
		if ( tasktype == TASKTYPE_CROW_PRORERTYERROR   )
		{
			return true;
		}

		return false;
	}//几何任务
    else if( m_iTaskType == TASK_TYPE_XY )
	{
		//平板步调几何任务
		if( tasktype ==TASKTYPE_FOOT_GEOMETRY )
			return true;
		//车调几何改错任务
		if( tasktype == TASKTYPE_FOOT_GEOMETRYERROR)
			return true;
		//车调几何任务
		if( tasktype == TASKTYPE_CAR_GEOMETRY)
		  return true;
		//车调几何改错任务
		if( tasktype == TASKTYPE_CAR_GEOMETRYERROR)
		  return true;
		//非实测几何任务
		if( tasktype ==  TASKTYPE_NET_GEOMETRY )
			return true;
		//非实测几何改错任务
		if( tasktype == TASKTYPE_NET_GEOMETRYERROR)
		  return true;
		//客投几何任务
		 if(tasktype ==  TASKTYPE_COMPLANIT_GEOMETRY )
		 return true;
		 //客投几何改错任务
		 if( tasktype == TASKTYPE_COMPLANIT_GEOMETRYERROR )
			 return true;
		 //众包几何任务
		 if( tasktype == TASKTYPE_CROW_GEOMETRY  )
			 return true;
		 //道路变化任务
		 if( tasktype == TASKTYPE_ROADCHANGE_GEOMETRY )
			 return true;
	}
	return false;
}

void CTaskManager::GetProjectTaskTypes(__int64 projectid)
{
	CString sql;
	std::map<__int64,std::vector<int> >::iterator  iter  = map_tasktypevt.find(projectid);
	if( iter != map_tasktypevt.end() )
		return;
	sql.Format("select tasktype from tb_task where projectid = %I64d group by tasktype;",projectid);
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	char szSql[1024];
	int iAffectCount = 0;
	sprintf(szSql,"%s",sql);
	CDB_ResultSet* pRes = NULL;

	std::vector<int> vttasktype;
	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);
	if( pRes == NULL)
		return ;

	int rowcount = pRes->GetResRowCount();

	for(int r = 0; r < rowcount; r++)
	{
		int tasktype = pRes->GetResIntValue(r,0);
		vttasktype.push_back( tasktype);
	}
	map_tasktypevt.insert(std::make_pair(projectid,vttasktype));

	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes);
}

void CTaskManager::ReleaseTask()
{
	ReleaseTaskBlocks();
	if( m_pTask != NULL)
	{
		delete m_pTask;
		m_pTask = NULL;
	}
	

}

CTask* CTaskManager::GetCurTask()
{
	return m_pTask;
}

CString CTaskManager::GetTaskTypeStr(int taskType)
{
	CString sTaskType = "";
	sTaskType.Format("%d", taskType);
	if ( TASK_TYPE_ATTR == taskType)
	{
		sTaskType.Format("%d,%d,%d,%d,%d",20,21,22,23,24);
	}
	return sTaskType;
}

// 
// //获取分配给用户的项目优先级和ID
// bool CTaskManager::GetProAndPri(std::map<int, CString> &mapProIdName, bool nAssi)
// { 
// 	CString sql;
// 	int	nEditType = POIUserManager::GetPOIUserManagerPtr()->GetEditType();
// 	int	idUser = POIUserManager::GetPOIUserManagerPtr()->GetUserID();
// 	std::vector<int> vecID;//保存分配给用户的项目ID	
// 	//查找分配给用户的项目ID
// 	int relatedrole = 0;
// 	if ( EDITTYPE_MODIFY == nEditType || EDITTYPE_EDIT == nEditType)
// 	{
// 		relatedrole = 5; //项目管理系统中的作业权限id
// 	}
// 	else if ( EDITTYPE_CONFIRM == nEditType || EDITTYPE_CHECK == nEditType)
// 	{
// 		relatedrole = 6; //项目管理系统中的校验权限id
// 	}
// 	//获取分配给用的项目
// 	sql.Format(_T("select pid from tb_task_project_user where workeruid=%d and relatedrole=%d order by pid;"), idUser, relatedrole);
// 	char szSql[1024];
// 	CDB_ResultSet* pRes = NULL;
// 	MYSQL_ROW row;
// 	char* p = NULL;
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_POIEDIT_TASK);
// 	sprintf(szSql,"%s",sql);
// 	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);
// 	if ( pRes  == NULL)
// 	{
// 		return false;
// 	}
// 	int nVID = 0;
// 	while ( row = mysql_fetch_row( pRes))
// 	{
// 		for ( int i = 0 ; i < pRes->field_count; i++)
// 		{
// 			p = row[i];
// 			if( p == NULL)
// 				continue;
// 			CString strFieldName =  pRes->fields[i].name;
// 			if ( strFieldName.Compare("pid") == 0)
// 			{
// 				nVID = atoi(p);
// 				vecID.push_back(nVID);
// 			}
// 		}
// 	}
// 	CDB_Manager::GetDBManagerPtr()->CloseMySql();
// 	//////////////////////////////////////////////////////////////////////////
// 	//根据角色查询所有相关项目的优先级
// 	if (EDITTYPE_CONFIRM == nEditType)
// 	{
// 		sql.Format(_T("select id,priority,name from tb_task_project where confirmstate=%d order by priority,priorityflag;"), PROJECT_STATE_START);
// 	}else if (EDITTYPE_MODIFY == nEditType)
// 	{
// 		sql.Format(_T("select id,priority,name from tb_task_project where modifystate=%d order by priority,priorityflag;"), PROJECT_STATE_START);
// 	}else if (EDITTYPE_CHECK == nEditType)
// 	{
// 		sql.Format(_T("select id,priority,name from tb_task_project where checkstate=%d order by priority,priorityflag;"), PROJECT_STATE_START);
// 	}else if (EDITTYPE_EDIT == nEditType)
// 	{
// 		sql.Format(_T("select id,priority,name from tb_task_project where state=%d order by priority,priorityflag;"), PROJECT_STATE_START);
// 	}
// 
//     sprintf(szSql,"%s",sql);
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
// 	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);
// 	if ( pRes == NULL)
// 	{
// 		return false;
// 	}
// 	if ( pRes->eof )
// 	{//表示该阶段的项目都已经做完了
// 		return true;
// 	}
// 	
// 	int nPid = 0;
// 	int nPriority = 0;
// 	int sizeVec = vecID.size();
// 	std::multimap<int, std::pair<int,CString> > mapInt;
// 	std::multimap<int, std::pair<int,CString> > mapIntTemp;
// 	std::pair<int,CString> pairProIdName;
// 	CString sProName = "";
// 	while ( row = mysql_fetch_row( pRes))
// 	{
// 		for ( int i = 0 ; i < pRes->field_count; i++)
// 		{
// 			p = row[i];
// 			if( p == NULL )
// 				continue; 
// 			CString strFieldName = pRes->fields[i].name;
// 			if ( strFieldName.Compare("id") == 0)
// 			{
// 				nPid = atoi( p );
// 			}
// 			else if ( strFieldName.Compare("priority") == 0 )
// 			{
// 				nPriority = atoi( p );
// 			}
// 			else if ( strFieldName.Compare("name") == 0 )
// 			{
// 				sProName = p;
// 			}	
// 		}
// 		pairProIdName.first = nPid;
// 		pairProIdName.second = sProName;
// 		if ( std::find( vecID.begin(), vecID.end(), nPid) != vecID.end())
// 		{//按优先级保存分配给用户的项目id
// 			mapInt.insert(std::make_pair(nPriority, pairProIdName));
// 		}
// 		//暂存该阶段没有完成的项目
// 		mapIntTemp.insert(std::make_pair(nPriority, pairProIdName));
// 		//for test
// 		int isize = mapIntTemp.size();
// 	}
// 	std::multimap<int, std::pair<int,CString> >::iterator iter;
// 	//先存分配给用户的按项目优先级排序的项目
// 	for ( iter=mapInt.begin(); iter != mapInt.end(); ++iter)
// 	{
// 		mapProIdName.insert( std::make_pair(iter->second.first, iter->second.second));
// 	}
// 	//后存没有分配给用户的按项目优先级排序的项目
// 	for ( iter=mapIntTemp.begin(); iter != mapIntTemp.end(); ++iter)
// 	{
// 		mapProIdName.insert( std::make_pair(iter->second.first, iter->second.second));
// 	}
// 	
// 	return true;
// }


/* note 根据项目id获取任务
   nPid :项目id
   taskType : 照片类型任务 / 视频类型任务
   由于照片类型又有了细分(21,22,23...)，所以不能直接用taskType进行任务的查询
*/
CTask * CTaskManager::GetTask( __int64 nPid, int taskType,int nEditType,int idRoleUser,int idotherRoleUser, bool bFirstLogin/*=false*/ )
{
	m_idRoleUser = idRoleUser;
	CString sql;
	__int64 idTask = 0;
	int itasktype2 = 0;
	double dLastExitDistance = 0;
	int idEditRoleUser = 0;
// 	int countTaskOccupied = GetOccupiedTaskCount(nEditType);
// 	if ( countTaskOccupied >= 2)
// 	{//一个人同时最多只能占用2个任务
// 		return NULL;
// 	}
	if( m_pTask != NULL)
	{
		delete m_pTask;
		m_pTask = NULL;
	}

	// 首先锁表
	int iaffact = 0;
	CDB_Manager::GetDBManagerPtr()->ExcuteSql("begin;lock table tb_task  in ACCESS EXCLUSIVE MODE;",iaffact) ;
	if (EDITTYPE_CHECK == nEditType) //校正，获取二种状态的任务：2.编辑+完成状态，1.中途退出的任务
	{   
		//优先获取上次中途退出的
		sql.Format(_T("select * from tb_task where tasktype = %d and checkid=%d and   state=%d  and process=%d and projectid=%I64d limit 1;"), 
			taskType, idRoleUser, STATE_OCCUPY, EDITTYPE_CHECK, nPid);
		m_pTask = GetTaskInfo(sql);

		if( !m_pTask )
		{
			//优先获取属于用户的任务
			sql.Format(_T("select * from tb_task where tasktype = %d and checkid=%d and   state=%d  and process=%d and projectid=%I64d limit 1;"), 
			taskType, idRoleUser, STATE_UNKNOW, EDITTYPE_CHECK, nPid);
			m_pTask = GetTaskInfo(sql);
		}

		if ( !m_pTask)
		{
			//再获取制作已提交的且不是自己制作的任务，且任务状态是编辑+完成
			sql.Format(_T("select * from tb_task where tasktype =%d and state=%d and process=%d and editid!=%d and ( checkid = 0 or checkid = %d ) and projectid=%I64d limit 1;"),
				taskType, STATE_OVER, EDITTYPE_EDIT, idotherRoleUser ,idRoleUser, nPid);
			m_pTask = GetTaskInfo(sql) ;
		}
	}
	else if (EDITTYPE_EDIT == nEditType)
	{// 编辑，获取四种状态的任务：4.初始状态，3.质检+提交状态，2.矫正+提交状态，1.中途退出的任务

		//优先获取上次中途退出的
		sql.Format(_T("select * from tb_task where tasktype = %d and editid=%d and state=%d and process=%d and projectid=%I64d limit 1;"), 
			taskType, idRoleUser, STATE_OCCUPY, EDITTYPE_EDIT, nPid);
		m_pTask = GetTaskInfo(sql) ;

		if( !m_pTask )
		{
			//优先获取属于用户的任务
			sql.Format(_T("select * from tb_task where tasktype = %d and editid=%d and   state=%d  and process=%d and projectid=%I64d limit 1;"), 
				taskType, idRoleUser, STATE_UNKNOW, EDITTYPE_EDIT, nPid);
			m_pTask = GetTaskInfo(sql);
		}

		if ( m_pTask == NULL )
		{// 矫正+提交状态
			sql.Format(_T("select * from tb_task where tasktype = %d and editid=%d and state=%d and process=%d and projectid=%I64d limit 1;"), 
				taskType, idRoleUser, STATE_COMMIT, EDITTYPE_CHECK, nPid);
			m_pTask = GetTaskInfo(sql) ;
			if ( !m_pTask )
			{// 质检+提交
				sql.Format(_T("select * from tb_task where tasktype = %d and editid=%d and state=%d and process=%d and projectid=%I64d limit 1;"), 
					taskType, idRoleUser, STATE_COMMIT, EDITTYPE_QCTOOL, nPid);
				m_pTask = GetTaskInfo(sql) ;
			}
		}
		if ( !m_pTask )
		{
			//未制作
			sql.Format(_T("select * from tb_task where tasktype = %d and state=%d and process=%d and editid = 0 and projectid=%I64d limit 1;"), 
				taskType, STATE_UNKNOW, 0, nPid);
			m_pTask = GetTaskInfo(sql);
		}
	}
	if ( m_pTask == NULL )
	{
		CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
		// 解锁
		int iaffact = 0;
		CDB_Manager::GetDBManagerPtr()->ExcuteSql("end;",iaffact) ;
		return NULL ;
	}
	idTask = m_pTask->GetID();
	//获取到任务后马上更新其状态，以防被他人占用
	//用锁也可以，不过不好控制，有可能死锁
	//一旦选择出来，必须马上更新占用状态，多个用户可能同时选择出了这一视频，但是只可能有一个人更新成功，谁更新成功，这个视频就是谁的
	if (EDITTYPE_CHECK == nEditType )
	{
		sql.Format(_T("update tb_task set state=%d,process=%d,checkid=%d where id=%I64d;"), //,operateTime=\"%s\"
			STATE_OCCUPY, nEditType, idRoleUser, idTask);  //, GetCurTime()
	}
	else if ( EDITTYPE_EDIT == nEditType )
	{
		sql.Format(_T("update tb_task set state=%d,process=%d,editid=%d where id=%I64d;"), //,operateTime=\"%s\"
			STATE_OCCUPY, nEditType, idRoleUser, idTask);  //, GetCurTime()
	}
	int iAffectCount = 0;
	char szSql[1024];
	sprintf(szSql,"%s",sql);
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);

	bool bUpdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(szSql,iaffact);
	// 解锁
	CDB_Manager::GetDBManagerPtr()->ExcuteSql("end;",iaffact) ;
	if ( bUpdate) 
	{//表明更新成功,由于更新语句在同一时间只能被执行一次

		m_pTask->SetRoleId(idRoleUser);
		//插入任务日志表
// 		AddTaskLog( idTask, STATE_OCCUPY);
	}
		
	return m_pTask;
}


int CTaskManager::GetOccupiedTaskCount(int nEditType)
{
	CString sql; 
	int	idRoleUser = m_idRoleUser;
	if ( EDITTYPE_EDIT == nEditType )
	{
		sql.Format("select count(id) from tb_task where editid=%d and state=%d and process=%d and tasktype = %d;",
			idRoleUser, STATE_OCCUPY, nEditType,m_iTaskType);
	}
	else if( EDITTYPE_CHECK == nEditType )
	{
		sql.Format("select count(id) from tb_task where checkid=%d and state=%d and process=%d and tasktype = %d;",
			idRoleUser, STATE_OCCUPY, nEditType ,m_iTaskType);
	}
	
	int count = 0;

	CDB_ResultSet* pRes = NULL;

	char szSql[1024];
	sprintf(szSql,"%s",sql);
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);

	int rowcount = pRes->GetResRowCount();
	for(int r = 0; r < rowcount; r++)
	{
		count = pRes->GetResIntValue(r,0);
	}
	
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	return count;
}

void CTaskManager::SetTaskType(int type)
{
	m_iTaskType = type;
}

int CTaskManager::GetTaskType()
{
	return m_iTaskType;
}


CTask* CTaskManager::GetTaskInfo(const char *sql)
{
	__int64 idTask = 0;
	double dLastExitDistance;
	int idEditRoleUser = 0;
	int itasktype = 0;
	int iProjectId = 0;
	CTask* pTask = NULL;

	dLastExitDistance = 0;

	CDB_ResultSet* pRes;
	
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
    pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(sql);
	if ( pRes == NULL )
	{
		return NULL ;
	}
	int num_rows = pRes->GetResRowCount();
	int num_fields = pRes->GetResFieldCount();
	
	std::vector<Field_DB> vtFields ;
	
	MAP_RES mapres ;
	int icount = 0 ;
	for(int r = 0; r < num_rows; r++)
	{
		icount++ ;
		VT_RES vtRes ;
		for ( int i=0; i<num_fields; i++ )
		{
			int ftype = pRes->GetFieldType(i);
			if ( icount == 1 )
			{
				Field_DB field ;
				field.name = pRes->GetFieldName(i) ;
				field.table = "" ;
				field.type = ftype ;
				vtFields.push_back(field) ;	
			}
			
			CString strval;
			
			switch(ftype)
			{
			case DBFT_Int:
				{
					strval.Format("%d",pRes->GetResIntValue(r,i));
					break;
				}
			case DBFT_Double:
				{
					strval.Format("%f",pRes->GetResDoubleValue(r,i));
					break;
				}
			case DBFT_Bigint:
				{
					strval.Format("%I64d",pRes->GetResBigIntValue(r,i));
					break;
				}
			case DBFT_String:
				{
					strval.Format("%s",pRes->GetResStringValue(r,i));
					break;
				}
			}
			
			vtRes.push_back(strval.GetBuffer(0)) ;
		}
		mapres.insert(MAP_RES::value_type(icount,vtRes)) ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	
	if ( mapres.empty() )
	{
		return NULL;
	}
	if( icount > 1)
	{
		AfxMessageBox("警告: 获取多个任务");
	}

	CDBFieldInfo *pFieldInfo = NULL ;
	CDBValue *pValue = NULL ;
	MAP_RES::iterator it ;
	
	for ( it=mapres.begin(); it!=mapres.end(); it++ )
	{
		pTask = new CTask() ;
		VT_RES vtres = it->second ;
		for ( int i=0; i<num_fields; i++ )
		{
			int mysqltype = vtFields.at(i).type ;
			pFieldInfo = new CDBFieldInfo(vtFields[i].name,vtFields[i].table,mysqltype) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(mysqltype));//再单独设置一下
			pValue = new CDBValue ;
			pTask->AddField(pFieldInfo, pValue) ;
			CString strval = vtres.at(i).c_str() ;
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pTask->SetIntByIndex(i,atoi(strval) ) ;
				break;
			case DBFT_Bigint:
				pTask->SetInt64ByIndex(i,_atoi64(strval) ) ;
				break;
			case DBFT_Double:
				pTask->SetDoubleByIndex(i, atof(strval) ) ;
				break;
			case DBFT_String:
				pTask->SetStringByIndex(i,strval) ;
				break;
			}
		}
	
		pTask->SetID(pTask->GetInt64ByIndex(pTask->GetIndex("id")));
		pTask->SetLastExit(pTask->GetDoubleByIndex(pTask->GetIndex("lastexitposition")) );
		pTask->SetEditRoleId(pTask->GetIntByIndex(pTask->GetIndex("editid")));
		pTask->SetTaskType( pTask->GetIntByIndex(pTask->GetIndex("tasktype")));
		pTask->SetProjectId(pTask->GetInt64ByIndex(pTask->GetIndex("projectid")) );
		pTask->SetReferData( pTask->GetStringByIndex(pTask->GetIndex("referdata")) );

//在这里执行就要锁住用到的所有表		pTask->LoadLinkInfo() ;

	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	//可以暂时先不关闭
//	bool bClose = CDB_Manager::GetDBManagerPtr()->CloseMySql();
	return pTask;
}
// ***WHAT***
void CTaskManager::AddTaskLog(__int64 idTask, int state)
{
	CString sql;
	int idRoleUser = m_pTask->GetRoleId();
	sql.Format("insert into tb_task_log(taskid,roleid,state) values(%I64d,%d,%d);",
		idTask, idRoleUser, state/*, GetCurTime()*/);
	char szSql[1024];
	sprintf(szSql,"%s",sql);
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	int iaffact = 0;
	CDB_Manager::GetDBManagerPtr()->ExcuteSql(szSql,iaffact);
}


// bool CTaskManager::OpenDataBase()
// {
// 	CString strPath;
// 	TCHAR cAppPathName[1024];
// 	int nTempFileLen = 0;
// 	::GetModuleFileName(NULL,cAppPathName,1024);
// 	strPath.Format("%s",cAppPathName);	
// 	nTempFileLen = strPath.ReverseFind ('\\');
// 	strPath = strPath.Left(nTempFileLen+1);
// 	CString csIniFilePath = strPath + "config\\dbconfig.ini";
// 	CString strInfoPath = strPath + "config\\dbinfo.ini" ;
// 	// 读配置文件，获取数据库链接信息
// 	CStdioFile stFile ;
// 	if ( !stFile.Open( csIniFilePath, CFile::modeReadWrite ) )
// 	{
// 		AfxMessageBox("请查看是否存在【dbconfig.ini】文件") ;
// 		return false;
// 	}
// 	
// 	CString strString ;
// 	CString strconname = "" ;
// 	CString strdbname = "" ;
// 	CString strip = "" ;
// 	CString strport = "" ;
// 	CString struser = "" ;
// 	CString strpassword = "" ;
// 	while ( stFile.GetLength() != stFile.GetPosition() )
// 	{
// 		stFile.ReadString( strString ) ;
// 		strString.TrimLeft() ;
// 		strString.TrimRight() ;
// 		
// 		if ( strString.GetLength() == 0 || strString.Left(2) == "//" )
// 		{
// 			continue;
// 		}
// 		int ipos = strString.Find("[connname]");
// 		if (ipos != -1)
// 		{
// 			ipos = strString.Find("]");
// 			strconname = strString.Right(strString.GetLength()-ipos-1);
// 		}
// 		ipos = strString.Find("[ip]") ;
// 		if ( ipos != -1 )
// 		{
// 			ipos = strString.Find("]") ;
// 			strip = strString.Right(strString.GetLength() - ipos -1 ) ;
// 		}
// 		ipos = strString.Find("[dbname]") ;
// 		if ( ipos != -1 )
// 		{
// 			ipos = strString.Find("]") ;
// 			strdbname = strString.Right(strString.GetLength() - ipos -1 ) ;
// 		}
// 		ipos = strString.Find("[user]") ;
// 		if ( ipos != -1 )
// 		{
// 			ipos = strString.Find("]") ;
// 			struser = strString.Right(strString.GetLength() - ipos -1 ) ;
// 		}
// 		ipos = strString.Find("[password]") ;
// 		if ( ipos != -1 )
// 		{
// 			ipos = strString.Find("]") ;
// 			strpassword = strString.Right(strString.GetLength() - ipos -1 ) ;
// 		}
// 		ipos = strString.Find("[port]") ;
// 		if ( ipos != -1 )
// 		{
// 			ipos = strString.Find("]") ;
// 			strport = strString.Right(strString.GetLength() - ipos -1 ) ;
// 			CDB_Manager::GetDBManagerPtr()->SetInitMySql(strip.GetBuffer(0),strdbname.GetBuffer(0),
// 				struser.GetBuffer(0),strpassword.GetBuffer(0),strconname.GetBuffer(0));
// 		}
// 		
// 	}
// 	stFile.Close() ;
// 
// 	////////////////////////////mysqldb//////////////////////////////////////////////
// 	if ( !stFile.Open( strInfoPath, CFile::modeReadWrite ) )
// 	{
// 		AfxMessageBox("请查看是否存在【dbinfo.ini】文件") ;
// 		return false;
// 	}
// 	
// 	CString strtype = "" ;
// 	while ( stFile.GetLength() != stFile.GetPosition() )
// 	{
// 		stFile.ReadString( strString ) ;
// 		strString.TrimLeft() ;
// 		strString.TrimRight() ;
// 		
// 		if ( strString.GetLength() == 0 || strString.Left(2) == "//" )
// 		{
// 			continue;
// 		}
// 		int ipos = strString.Find(":");
// 		
// 		strconname = strString.Left(ipos);
// 		strString = strString.Right(strString.GetLength()-ipos-1);
// 
// 		ipos = strString.Find(",") ;
// 		strdbname = strString.Left(ipos) ;
// 		strString = strString.Right(strString.GetLength() - ipos -1 ) ;
// 
// 		strtype = strString ;
// 		CDB_Manager::GetDBManagerPtr()->AddDBConfig(strconname.GetBuffer(0), strdbname.GetBuffer(0),atoi(strtype)) ;
// 		
// 	}
// 	stFile.Close() ;
// 	
// 	return true;
// }


// bool CTaskManager::GetServerInfo( std::map<CString, std::pair<CString,CString> > &mapDbServer)
// {
// 	CString strPath;
// 	TCHAR cAppPathName[1024];
// 	int nTempFileLen = 0;
// 	::GetModuleFileName(NULL,cAppPathName,1024);
// 	strPath.Format("%s",cAppPathName);	
// 	nTempFileLen = strPath.ReverseFind ('\\');
// 	strPath = strPath.Left(nTempFileLen+1);
// 	CString csIniFilePath = strPath + "DBConfig.ini";
// 	
// 	char strL[128];
// 	//poi库
// 	::GetPrivateProfileString("IMPORT_TASK", "DB_IP", "192.168.0.170", strL, 128, csIniFilePath);
// 	m_csHostIP = strL;
// 	::GetPrivateProfileString("IMPORT_TASK", "DB_PORT", "3306", strL, 128, csIniFilePath);
// 	m_iHostPort = atoi(strL);
// 	::GetPrivateProfileString("IMPORT_TASK", "DB_NAME", "task_tl", strL, 128, csIniFilePath);
// 	m_csHostDBName = strL;
// 	::GetPrivateProfileString("IMPORT_TASK", "DB_USERNAME", "root", strL, 128, csIniFilePath);
// 	m_csHostUsername = strL;
// 	::GetPrivateProfileString("IMPORT_TASK", "DB_PASSWORD", "superroot", strL, 128, csIniFilePath);
// 	m_csHostPassword = strL;
// 
// 	//poi库
// 	::GetPrivateProfileString("IMPORT_PROJECT", "DB_IP", "192.168.0.170", strL, 128, csIniFilePath);
// 	m_csHostIP2 = strL;
// 	::GetPrivateProfileString("IMPORT_PROJECT", "DB_PORT", "3306", strL, 128, csIniFilePath);
// 	m_iHostPort2 = atoi(strL);
// 	::GetPrivateProfileString("IMPORT_PROJECT", "DB_NAME", "task_tl", strL, 128, csIniFilePath);
// 	m_csHostDBName2 = strL;
// 	::GetPrivateProfileString("IMPORT_PROJECT", "DB_USERNAME", "root", strL, 128, csIniFilePath);
// 	m_csHostUsername2 = strL;
// 	::GetPrivateProfileString("IMPORT_PROJECT", "DB_PASSWORD", "superroot", strL, 128, csIniFilePath);
// 	m_csHostPassword2 = strL;
// 	
// 	
// 	return true;
// }


CString CTaskManager::GetDllPath()
{
	CString strExe; 
    TCHAR cAppPathName[1024];
    int nTempFileLen = 0;
    ::GetModuleFileName(NULL,cAppPathName,1024);
    strExe.Format("%s",cAppPathName);	
    nTempFileLen = strExe.ReverseFind ('\\');
    strExe = strExe.Left(nTempFileLen+1);
	return strExe;
}

// void CTaskManager::GetUserRoleInProjectDb()
// {
// 	POIUserManager::GetPOIUserManagerPtr()->SetCheckUserRoleFlag(true);
// 	int idUser = 0, idRole = 0;
// 	CString sql;
// 	sql.Format("select uid,rid from tb_user_roles;");
// 
// 	CDB_ResultSet* pRes = NULL;
// 	MYSQL_ROW  row;
// 	char* p = NULL;
// 	char szSql[1024];
// 	sprintf(szSql,"%s",sql);
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_POIEDIT_PROJECT);
// 	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);
// 	while( row = mysql_fetch_row( pRes))
// 	{
// 		int iCount = pRes->field_count;
// 		CTaskLinkFieldData* pFieldData = new CTaskLinkFieldData();
// 		for ( int i = 0 ; i< iCount ; i++)
// 		{
// 			p = row[i];
// 			if( p == NULL)
// 				continue;
// 			CString  strFiledName = pRes->fields[i].name;
// 			if ( strFiledName.Compare("uid") == 0)
// 			{
// 				idUser = atoi( p);
// 			}
// 			else if( strFiledName.Compare("rid") == 0)
// 			{
// 				idRole = atoi(p);
// 			}
// 		}
// 		POIUserManager::GetPOIUserManagerPtr()->AddUserRole( idUser, idRole);
// 	}
// }

// void CTaskManager::AddRoleUser(int idRoleUser)
// {
// 	if ( idRoleUser <= 0)
// 	{
// 		return;
// 	}
// //	CDatabaseCtrl::GetDatabaseCtrlPtr()->SetRoleUserId( idRoleUser);
// }

// 
// bool CTaskManager::GetLinkFieldDataFromDb()
// {
// 	CString sql;
// 	int iAffectCount = 0;
// 	sql.Format("select * from tb_task_link_fielddata where taskid = %I64d",m_pTask->GetID());
//     CDB_ResultSet* pRes = NULL;
// 	MYSQL_ROW  row;
// 	char* p = NULL;
// 	char szSql[1024];
// 	sprintf(szSql,"%s",sql);
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
// 	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);
// 	while( row = mysql_fetch_row( pRes))
// 	{
// 		int iCount = pRes->field_count;
// 		CTaskLinkFieldData* pFieldData = new CTaskLinkFieldData();
// 		for ( int i = 0 ; i< iCount ; i++)
// 		{
// 			p = row[i];
// 			if( p == NULL)
// 				continue;
// 			CString  strFiledName = pRes->fields[i].name;
// 			if ( strFiledName.Compare("id") == 0)
// 			{
// 				pFieldData->SetID( _atoi64(p) );
// 			}
// 			else if ( strFiledName.Compare("taskid") == 0)
// 			{
// 				pFieldData->SetTaskId(  _atoi64(p));
// 			}
// 			else if ( strFiledName.Compare("shapeid") == 0)
// 			{
// 				pFieldData->SetShapeId(  _atoi64(p));
// 			}
// 			else if ( strFiledName.Compare("poitempid") == 0)
// 			{
// 				pFieldData->SetPoitempId( _atoi64(p));
// 			}
// 			else if ( strFiledName.Compare("distance") == 0)
// 			{
// 				pFieldData->SetDistance(atof( p));
// 			}
// 			else if ( strFiledName.Compare("second") == 0)
// 			{
// 				pFieldData->SetSecond(atof(p));
// 			}
// 			else if ( strFiledName.Compare("lroadid") == 0)
// 			{
// 				pFieldData->SetLRoadId( _atoi64(p));
// 			}
// 			else if ( strFiledName.Compare("rroadid") == 0)
// 			{
// 				pFieldData->SetRRoadId( _atoi64(p));
// 			}
// 		}
// 		m_pTask->AddTaskLinkFieldData(pFieldData->GetShapeId(),pFieldData) ;
// 		
// 	}
// 
// 	return true;
// 	
// }
// 
// 
// 
// bool CTaskManager::GetLinkAttachFromDb()
// {
// 	CString sql;
// 	int iAffectCount = 0;
// 	sql.Format("select * from tb_task_link_attach where taskid = %I64d",m_pTask->GetID());
// 	CDB_ResultSet* pRes = NULL;
// 	MYSQL_ROW  row;
// 	char* p = NULL;
//     char szSql[1024];
// 	sprintf(szSql,"%s",sql);
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
// 	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);
// 	while(  row = mysql_fetch_row( pRes))
// 	{
// 		int iCount = pRes->field_count;
// 		CTaskLinkAttach* pAttach = new CTaskLinkAttach();
// 		for ( int i = 0 ; i< iCount ; i++)
// 		{
// 			p = row[i];
// 			if( p == NULL)
// 				continue;
// 			CString  strFiledName = pRes->fields[i].name;
// 			if ( strFiledName.Compare("id") == 0)
// 			{
// 				pAttach->SetID( _atoi64( p ) );
// 			}
// 			else if ( strFiledName.Compare("taskid") == 0)
// 			{
// 				pAttach->SetTaskId(_atoi64( p ));
// 			}
// 			else if ( strFiledName.Compare("shapeid") == 0)
// 			{
// 				pAttach->SetShapeId( _atoi64( p ));
// 			}
// 			else if ( strFiledName.Compare("timestamp") == 0)
// 			{
// 				pAttach->SetTimestamp( _atoi64( p ));
// 			}
// 			else if ( strFiledName.Compare("poitempid") == 0)
// 			{
// 				pAttach->SetPoitempid( _atoi64( p ));
// 			}
// 			else if ( strFiledName.Compare("recordtype") == 0)
// 			{
// 				pAttach->SetRecordType( atoi(p));
// 			}
// 			else if ( strFiledName.Compare("attachid") == 0)
// 			{
// 				pAttach->SetAttachId( _atoi64( p ));
// 			}
// 			else if ( strFiledName.Compare("length") == 0)
// 			{
// 				pAttach->SetLength( atoi(p));
// 			}
// 		}
// 		m_pTask->AddTaskLinkAttach(pAttach) ;
// 	}
// 
// 	return true;
// }
// 
// 
// int CTaskManager::LoadTaskData()
// {
// 	bool bGetFieldData = GetLinkFieldDataFromDb();
// 	bool bGetAttach    = GetLinkAttachFromDb();
// 	
// // 	bool bGetDbconfig  = GetTaskDBConfigInfo();
// 	//获取外业资料信息
// 	if ( bGetFieldData)
// 	{
// 		
// 	}
// 	//获取照片信息
// 	if ( bGetAttach)
// 	{
// 		
// 	}
// 	//获取POI信息
// // 	if ( bGetLinkPoi)
// // 	{
// // 	}
// 	
// 	return 0;
// }
// 

void CTaskManager::AddNewTaskLinkFieldData(__int64 shapeid,CTaskLinkFieldData* pFieldData)
{
	if ( m_pTask == NULL)
		return ;
	if( pFieldData == NULL)
		return ;
	if( m_iTaskType == TASK_TYPE_ATTR ||
		m_iTaskType == TASK_TYPE_XY
		)
	{
		//数据库保存
		CString sql;
		sql.Format("insert into  tb_task_link_fielddata (taskid,shapeid,layerid,featureid, updatetime ) values (%I64d, %I64d,%d, %I64d, %s) ",
			pFieldData->GetTaskId(),pFieldData->GetShapeId(),pFieldData->GetLayerId(),pFieldData->GetFeatureId(),"NOW()");
		int iAffectCount = 0;
		char szSql[1024];
		sprintf(szSql,"%s",sql);
		CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
		int iaffact = 0;
		bool bUpDate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(szSql,iaffact);
	
// 		if( iAffectCount != 1)
// 			return ;
	
		sql.Format("select max(id) from tb_task_link_fielddata");
		sprintf(szSql,"%s",sql);
		CDB_ResultSet* pRes = NULL;
	
		pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);
		int rowcount = pRes->GetResRowCount();
		for(int r = 0; r < rowcount; r++)
		{
			__int64 id = pRes->GetResBigIntValue(r,0);
			pFieldData->SetID( id );
		}
		
		m_pTask->AddNewTaskLinkFieldData(shapeid,pFieldData);

		CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes);
	}
}


void CTaskManager::AddNewTaskLinkAttach(CTaskLinkAttach* pAttach )
{
	if ( m_pTask == NULL)
		return ;
	if( pAttach == NULL)
		return ;
	if( m_iTaskType == TASK_TYPE_ATTR || m_iTaskType == TASK_TYPE_XY	)
	{
		//数据库保存
		CString sql;
		sql.Format("insert into tb_task_link_attach (taskid,recordtype,attachid,shapeid,layerid,featureid,updatetime) values ( %I64d, %d,%I64d,%I64d,%d, %I64d,%s) ",
			pAttach->GetTaskId(),pAttach->GetRecordType(),pAttach->GetAttachId(),pAttach->GetShapeId(),pAttach->GetLayerId(),pAttach->GetFeatureid(),"NOW()");
		int iAffectCount = 0;
		
// 		if( iAffectCount != 1)
// 			return ;
		char szSql[1024];
		sprintf(szSql,"%s",sql);
		CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
		int iaffact = 0;
		bool bUpdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(szSql,iaffact);
		
		
		sql.Format("select max(id) from tb_task_link_attach");
		sprintf(szSql,"%s",sql);
		CDB_ResultSet* pRes = NULL;
	
		pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);
		int rowcount = pRes->GetResRowCount();
		for(int r = 0; r < rowcount; r++)
		{
			__int64 id = pRes->GetResBigIntValue(r,0);
			pAttach->SetID( id );	
		
		}
		m_pTask->AddNewTaskLinkAttach(pAttach);

		CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes);
	}
}


// bool CTaskManager::GetTaskDBConfigInfo()
// {
// 	int id = 0;
// 	CString sql;
// 	sql.Format("select tb_metadata.key, tb_metadata.value, tb_metadata.desc from tb_metadata ;");
// 
// 	char szSql[1024];
// 	sprintf(szSql,"%s",sql);
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
// 	CDB_ResultSet* pRes = NULL;
// 	MYSQL_ROW row;
// 	char* p = NULL;
// 	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);
// 	while( row = mysql_fetch_row( pRes))
// 	{
// 		CString skey;
// 		VALUEPAIR pairType;
// 		for ( int i = 0 ; i < pRes->field_count; i++)
// 		{
// 			p = row[i];
// 			if( p == NULL )
// 				continue;
// 			CString strFieldName = pRes->fields[i].name;
// 			if ( strFieldName.Compare("key") ==0 )
// 			{
// 				skey = p;
// 			}
// 			else if ( strFieldName.Compare("value") == 0)
// 			{
// 				pairType.first =  p;
// 			}
// 			else if ( strFieldName.Compare("desc") == 0)
// 			{
// 				pairType.second = p;
// 			}
// 		}
// 		m_pTask->AddDelDesc(skey,pairType.first,pairType.second);
// 	}
// 	return true;
// }

int CTaskManager::GetDelDescId(__int64 idbase, __int64 iTaskid, int operatetype)
{
	return 1;
}

bool CTaskManager::CommitTask()
{
	if( m_pTask == NULL)
		return false;
	CString sql;
	sql.Format("update tb_task set state=%d,lastexitposition=0 ,batchid = %I64d where id=%I64d;", 
		m_pTask->GetIntByIndex(m_pTask->GetIndex("state")),m_pTask->GetBatchId(), m_pTask->GetInt64ByIndex(m_pTask->GetIndex("id")) /*GetID()*/);
	int iAffectCount = 0;

	char szSql[1024];
	sprintf(szSql,"%s",sql);
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	bool bUpdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(szSql,iAffectCount);
	return bUpdate;
}
void CTaskManager::SetEditType(int iedittype)
{
	m_nEditType = iedittype;
}

void CTaskManager::SetUserId(int iUserId)
{
	m_idUser = iUserId;
}

void CTaskManager::SetUseRoleId(int iRoleId)
{
	m_idRoleUser = iRoleId;
}

// bool CTaskManager::CheckAndModiProjectState( )
// {
// 	if( m_pTask == NULL )
// 		return false;
// 	int nProjectID = m_pTask->GetProjectId();
// 	CString sql = "", csState = "", csProgess = "";
// 	//////////获取项目上视频总数量
// 	sql.Format("select tasknum,state,checkstate,modifystate,confirmstate from tb_task_project where id=%d", nProjectID);
// 
// 
// 	int nTaskCount =0;
// 	int state = 0;
// 	int checkstate = 0;
// 	int modifystate = 0;
// 	int confirmstate = 0;
// 
// 	CDB_ResultSet* pRes = NULL;
// 	MYSQL_ROW  row;
// 	char* p = NULL;
// 	char szSql[1024];
// 	sprintf(szSql,"%s",sql);
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_POIEDIT_TASK);
// 	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);
// 	while( row = mysql_fetch_row( pRes))
// 	{
// 		for ( int i = 0 ; i< pRes->field_count ; i++)
// 		{
// 			p = row[i];
// 			if( p == NULL)
// 				continue;
// 			CString strFieldName = pRes->fields[i].name;
// 			if ( strFieldName.Compare("tasknum") == 0)
// 			{
// 				nTaskCount = atoi( p );
// 			}
// 			else if ( strFieldName.Compare("state") == 0)
// 			{
// 				state = atoi( p );
// 			}
// 			else if ( strFieldName.Compare("checkstate") == 0)
// 			{
// 				checkstate = atoi( p );
// 			}
// 			else if ( strFieldName.Compare("modifystate") == 0)
// 			{
// 				modifystate = atoi( p );
// 			}
// 			else if ( strFieldName.Compare("confirmstate") == 0)
// 			{
// 				confirmstate = atoi( p );
// 			}
// 		}
// 	}
// 	//////////////////////////////////////////
// 	
// 	//统计各个阶段进度
// 	std::pair<int,int> pairEditProg(nTaskCount,nTaskCount); //制作阶段
// 	std::pair<int,int> pairCheckProg(0,0); //校正阶段
// 	std::pair<int,int> pairModifyProg(0,0); //修改阶段
// 	std::pair<int,int> pairConfirmProg(0,0); //验证阶段
// 	std::pair<int,int> pairOverProg(0,nTaskCount); //完成进度
// 	GetProgress( nProjectID, nTaskCount, pairEditProg, pairCheckProg, pairModifyProg, pairConfirmProg, pairOverProg);
// 	
// 	//////////////////////////////////////////////////////////////////////////
// 	//判断各个阶段的任务是否已完成
// 	if ( EDITTYPE_EDIT == m_nEditType && pairEditProg.first == nTaskCount)
// 	{
// 		state = PROJECT_STATE_OK;
// 	}
// 	else if ( EDITTYPE_CHECK == m_nEditType && pairCheckProg.first == pairCheckProg.second && pairCheckProg.first > 0)
// 	{
// 		checkstate = PROJECT_STATE_OK;
// 	}
// 	else if ( EDITTYPE_MODIFY == m_nEditType && pairModifyProg.first == pairModifyProg.second && pairModifyProg.first > 0)
// 	{
// 		modifystate = PROJECT_STATE_OK;
// 	}
// 	else if ( EDITTYPE_CONFIRM == m_nEditType && pairConfirmProg.first == pairConfirmProg.second && pairConfirmProg.first > 0)
// 	{
// 		confirmstate = PROJECT_STATE_OK;
// 	}
// 	
// 	//设置阶段自动开始
// 	if ( EDITTYPE_EDIT == m_nEditType && 
// 		( pairEditProg.first > 0 && checkstate == PROJECT_STATE_UNSTART || pairCheckProg.first < pairCheckProg.second && checkstate == PROJECT_STATE_OK) )
// 	{//有制作完成的且校正未开始时，或又有需要校正的且校正任务已完成的，自动开始校正
// 		checkstate = PROJECT_STATE_START;
// 	}
// 	else if ( EDITTYPE_CHECK == m_nEditType && 
// 		(pairCheckProg.first > 0 && modifystate == PROJECT_STATE_UNSTART || pairModifyProg.first < pairModifyProg.second && modifystate == PROJECT_STATE_OK) )
// 	{//有校正完成的且修改未开始的，或又有需要修改的且修改任务已完成的，自动开始修改
// 		modifystate = PROJECT_STATE_START;
// 	}
// 	else if ( EDITTYPE_MODIFY == m_nEditType &&
// 		(pairModifyProg.first > 0 && confirmstate == PROJECT_STATE_UNSTART || pairConfirmProg.first < pairConfirmProg.second && confirmstate == PROJECT_STATE_OK))
// 	{//有修改完成的且验证未开始的，或又有需要验证的且验证任务已完成的，自动开始验证
// 		confirmstate = PROJECT_STATE_START;
// 	}
// 	else if ( EDITTYPE_CONFIRM == m_nEditType &&
// 		(pairConfirmProg.first > 0 && modifystate == PROJECT_STATE_UNSTART || pairModifyProg.first < pairModifyProg.second && modifystate == PROJECT_STATE_OK) )
// 	{
// 		modifystate = PROJECT_STATE_START;
// 	}
// 	
// 	////////////更新项目进度和状态
// 	sql.Format("update tb_task_project set progress=\'%d/%d\', checkprogress=\'%d/%d\',modifyprogress=\'%d/%d\',confirmprogress=\'%d/%d\',overprogress=\'%d/%d\',"
// 		"state=%d,checkstate=%d,modifystate=%d,confirmstate=%d where id=%d",
// 		pairEditProg.first, pairEditProg.second,
// 		pairCheckProg.first, pairCheckProg.second,
// 		pairModifyProg.first, pairModifyProg.second,
// 		pairConfirmProg.first, pairConfirmProg.second,
// 		pairOverProg.first, pairOverProg.second,
// 		state,checkstate,modifystate,confirmstate,
// 		nProjectID);
// 	int iAffectCount = 0;
// 
// 	
// 
// 	sprintf(szSql,"%s",sql);
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_POIEDIT_TASK);
// 	CDB_Manager::GetDBManagerPtr()->ExcuteSql(szSql);
// 	return true;
// }


bool CTaskManager::GetProgress(int nProjectID, int nTaskCount,
								   std::pair<int,int> &pairEditProg,
								   std::pair<int,int> &pairCheckProg, 
								   std::pair<int,int> &pairModifyProg,
								   std::pair<int,int> &pairConfirmProg,
								   std::pair<int,int> &pairOverProg )
{

	CString sql;
	sql.Format("select state,process,checkid from tb_task where projectid=%d;",
		nProjectID, STATE_UNKNOW, 0);
	char szSql[1024];
	sprintf(szSql,"%s",sql);
	CDB_ResultSet* pRes = NULL;
	
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	pRes  = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);
	if ( pRes == NULL)
	{
		return false;
	}
// 	if (pRes->eof)  
// 	{
// 		return false;
// 	}
	int iState = 0, iRoleType=0, idCheckRoleUser = 0 , iCheckRoleType = 0;
	/*
	项目阶段 | 状态 | 进度含义| 进度
	制作阶段 | state      |  已制作/总任务数      | 总任务数-新任务-制作占用-制作未占用=B / 总任务数=C

	校正阶段 | checkstate |  已校正/已校正+应校正 | (校正提交+校正完成+修改占用+修改未占用+修改提交+修改完成+验证占用+验证未占用+验证提交+验证完成 =
		B-制作提交-校正占用-校正未占用=E) / (E+制作提交+校正占用+校正未占用=B)

	修改阶段 | modifystate|  已修改/已修改+应修改 | 修改提交+修改完成+验证占用+验证未占用+验证完成=H / H+校正提交+修改占用+修改未占用+验证提交

	验证阶段 |confirmstate|  已验证/已验证+应验证 | 修改（验证）占用+修改（验证）未占用+修改（验证）完成+验证提交+验证完成=K / K+修改提交+验证占用+验证未占用完成进度
    已完成/总任务数校正完成+修改完成+验证完成=完成/总任务数
	*/
	int rowcount = pRes->GetResRowCount();
	for(int r = 0; r < rowcount; r++)
	{
		iState = pRes->GetResIntValue(r,0);
		iRoleType = pRes->GetResIntValue(r,1);
		idCheckRoleUser = pRes->GetResIntValue(r,2); //最后一次校验人
	
		CString strcheckroleuser ;
		strcheckroleuser.Format("%d", idCheckRoleUser) ;
		iCheckRoleType = atoi(strcheckroleuser.Left(1))/*POIUserManager::GetPOIUserManagerPtr()->GetRoleIdByRoleuserid(idCheckRoleUser)*/; //EDITTYPE_CHECK * 100000 + m_idUser //最后一次校验人身份

		if ( EDITTYPE_UNKNOW == iRoleType && STATE_UNKNOW == iState) //新任务
		{
			pairEditProg.first--;
		}
		else if (EDITTYPE_EDIT == iRoleType && STATE_OCCUPY == iState) //制作占用
		{
			pairEditProg.first--;
		}
		else if (EDITTYPE_EDIT == iRoleType && STATE_UNKNOW == iState) //制作未占用
		{
			pairEditProg.first--;
		}
		else if ( EDITTYPE_EDIT == iRoleType && STATE_COMMIT == iState) //制作提交
		{
			pairCheckProg.first++;
		}
		else if ( EDITTYPE_CHECK == iRoleType && STATE_OCCUPY == iState) //校正占用
		{
			pairCheckProg.first++;
		}
		else if ( EDITTYPE_CHECK == iRoleType && STATE_UNKNOW == iState) //校正未占用
		{
			pairCheckProg.first++;
		}
		else if ( EDITTYPE_MODIFY == iRoleType && STATE_COMMIT == iState) //修改提交
		{
			pairModifyProg.first++;
			pairConfirmProg.second++;
		}
		else if ( EDITTYPE_MODIFY == iRoleType && STATE_OVER == iState) //修改完成
		{
			pairModifyProg.first++;
			if ( iCheckRoleType == EDITTYPE_CONFIRM)
			{
				pairConfirmProg.first++;
			}
		}
		else if ( EDITTYPE_CONFIRM == iRoleType && STATE_OCCUPY == iState) //验证占用
		{
			pairModifyProg.first++;
			pairConfirmProg.second++;
		}
		else if ( EDITTYPE_CONFIRM == iRoleType && STATE_UNKNOW == iState) //验证未占用
		{
			pairModifyProg.first++;
			pairConfirmProg.second++;
		}
		else if ( EDITTYPE_CONFIRM == iRoleType && STATE_OVER == iState) //验证完成
		{
			pairModifyProg.first++;
			pairConfirmProg.first++;
		}
		else if ( EDITTYPE_CHECK == iRoleType && STATE_COMMIT == iState) //校正提交
		{
			pairModifyProg.second++;
		}
		else if ( EDITTYPE_MODIFY == iRoleType && STATE_OCCUPY == iState) //修改占用
		{
			pairModifyProg.second++;
			if ( iCheckRoleType == EDITTYPE_CONFIRM)
			{
				pairConfirmProg.first++;
			}
		}
		else if ( EDITTYPE_MODIFY == iRoleType && STATE_UNKNOW == iState) //修改未占用
		{
			pairModifyProg.second++;
			if ( iCheckRoleType == EDITTYPE_CONFIRM)
			{
				pairConfirmProg.first++;
			}
		}
		else if ( EDITTYPE_CONFIRM == iRoleType && STATE_COMMIT == iState) //验证提交
		{
			pairModifyProg.second++;
			pairConfirmProg.first++;
		}
		if ( STATE_OVER == iState)
		{
			pairOverProg.first++;
		}
	}

	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes);

	pairCheckProg.first =  pairEditProg.first - pairCheckProg.first; 
	pairCheckProg.second = pairEditProg.first;
	pairModifyProg.second += pairModifyProg.first; 
	pairConfirmProg.second += pairConfirmProg.first;
	return true;
}

void CTaskManager::ReleaseTaskBatch()
{
	int isize = m_vtTaskBatchInfos.size();

	for(int i = 0; i < isize; i++)
	{
		CTaskBatch* pTaskBatch = m_vtTaskBatchInfos[i];

		if(pTaskBatch != NULL)
		{
			delete pTaskBatch;
			pTaskBatch = NULL;
		}
	}

	m_vtTaskBatchInfos.clear();
}

void CTaskManager::GetTaskBatchInfos(CString strCond)
{
	char szSql[1024];
	CString sql;
	//sql.Format("select id,datasetid,projectid,batchid,datasettype,uid,updatetime,`desc` from tb_task_batch where %s",strCond);
	//postgresql
	sql.Format("select id,datasetid,projectid,batchid,datasettype,uid,updatetime,\"desc\" from tb_task_batch where %s",strCond);
	
	sprintf(szSql,"%s",sql);
	CDB_ResultSet* pRes = NULL;
	char* p = NULL;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	
	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);

	if ( pRes == NULL)
	{
		return ;
	}
	int num_rows = pRes->GetResRowCount();
	int num_fields = pRes->GetResFieldCount();
	
	std::vector<Field_DB> vtFields ;
	
	MAP_RES mapres ;
	int icount = 0 ;
	for(int r = 0; r < num_rows; r++)
	{
		icount++ ;
		VT_RES vtRes ;
		for ( int i=0; i<num_fields; i++ )
		{
			int ftype = pRes->GetFieldType(i);
			if ( icount == 1 )
			{
				Field_DB field ;
				field.name = pRes->GetFieldName(i) ;
				field.table = "" ;
				field.type = ftype ;
				vtFields.push_back(field) ;	
			}
			
			CString strval;
			
			switch(ftype)
			{
			case DBFT_Int:
				{
					strval.Format("%d",pRes->GetResIntValue(r,i));
					break;
				}
			case DBFT_Double:
				{
					strval.Format("%f",pRes->GetResDoubleValue(r,i));
					break;
				}
			case DBFT_Bigint:
				{
					strval.Format("%I64d",pRes->GetResBigIntValue(r,i));
					break;
				}
			case DBFT_String:
				{
					strval.Format("%s",pRes->GetResStringValue(r,i));
					break;
				}
			}
			
			vtRes.push_back(strval.GetBuffer(0)) ;
		}
		mapres.insert(MAP_RES::value_type(icount,vtRes)) ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	
	if ( mapres.empty() )
	{
		return ;
	}
	
	CDBFieldInfo *pFieldInfo = NULL ;
	CDBValue *pValue = NULL ;
	MAP_RES::iterator it ;
	for ( it=mapres.begin(); it!=mapres.end(); it++ )
	{
		CTaskBatch* pTaskBatch = new CTaskBatch;
		VT_RES vtres = it->second ;
		for ( int i=0; i<num_fields; i++ )
		{
			int mysqltype = vtFields.at(i).type ;
			pFieldInfo = new CDBFieldInfo(vtFields[i].name,vtFields[i].table,mysqltype) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(mysqltype));//再单独设置一下
			pValue = new CDBValue ;
			pTaskBatch->AddField(pFieldInfo, pValue) ;
			CString strval = vtres.at(i).c_str() ;
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pTaskBatch->SetIntByIndex(i,atoi(strval) ) ;
				break;
			case DBFT_Bigint:
				pTaskBatch->SetInt64ByIndex(i,_atoi64(strval) ) ;
				break;
			case DBFT_Double:
				pTaskBatch->SetDoubleByIndex(i, atof(strval) ) ;
				break;
			case DBFT_String:
				pTaskBatch->SetStringByIndex(i,strval) ;
				break;
			}

			int iIndex = pTaskBatch->GetIndex("id") ;
			pTaskBatch->SetId(pTaskBatch->GetInt64ByIndex(iIndex)) ;

			iIndex = pTaskBatch->GetIndex("datasetid") ;
			pTaskBatch->SetDataSetId(pTaskBatch->GetInt64ByIndex(iIndex)) ;
			
			iIndex = pTaskBatch->GetIndex("projectid") ;
			pTaskBatch->SetProjectId(pTaskBatch->GetInt64ByIndex(iIndex)) ;
			
			iIndex = pTaskBatch->GetIndex("batchid") ;
			pTaskBatch->SetBatchId(pTaskBatch->GetInt64ByIndex(iIndex)) ;
			
			iIndex = pTaskBatch->GetIndex("datasettype") ;
			pTaskBatch->SetDataSetType(pTaskBatch->GetIntByIndex(iIndex)) ;
			
			iIndex = pTaskBatch->GetIndex("uid") ;
			pTaskBatch->SetUID(pTaskBatch->GetIntByIndex(iIndex)) ;
			
			iIndex = pTaskBatch->GetIndex("updatetime") ;
			CString strtime = pTaskBatch->GetStringByIndex(iIndex) ;
			pTaskBatch->SetCreateTime(Char2Systemtime((LPSTR)(LPCSTR)strtime)) ;
			
			iIndex = pTaskBatch->GetIndex("desc") ;
			pTaskBatch->SetRemark(pTaskBatch->GetStringByIndex(iIndex)) ;
			
		}
		m_vtTaskBatchInfos.push_back(pTaskBatch);
	}
}

SYSTEMTIME CTaskManager::Char2Systemtime(char* p)
{
	SYSTEMTIME time;
	
	CString  str = p;
	
	int         nYear   = 0;
    int         nMonth  = 0;
    int         nDay    = 0;
    int         nHour   = 0;
    int         nSecond = 0;
    int         nMinute = 0;
	
    _stscanf(str, _T("%d-%d-%d %d:%d:%d"), &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
	
    if (nMonth==0 || nDay==0)
    {
        _stscanf(str, _T("%d/%d/%d %d:%d:%d"), &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
    }
	
    time.wYear   = nYear;
    time.wMonth  = nMonth;
    time.wDay    = nDay;
    time.wHour   = nHour;
    time.wSecond = nSecond;
    time.wMinute = nMinute;
	
	
	return time;
}

void CTaskManager::AddNewTaskBatch(CTaskBatch* pTaskBatch)
{
	__int64 iBatchid = pTaskBatch->GetBatchId();
	__int64 iDataSetid = pTaskBatch->GetDataSetId();
	int iDataSetType = pTaskBatch->GetDataSetType();
	__int64 iProjectid = pTaskBatch->GetProjectId();
	CString strRemark = pTaskBatch->GetRemark();
	int iUid = pTaskBatch->GetUID();
	int sysytemid = pTaskBatch->GetSystemid() ;
	
	//插入项目数据
	char szSql[1024];
	CString sql;
	
	CDB_ResultSet* pRes = NULL;
	char* p = NULL;
	
// 	sql.Format("insert into tb_task_batch(datasettype,datasetid,projectid,uid,batchid,systemid,`desc`) "
// 		"values(%d,%I64d,%I64d, %d,%I64d,%d,'%s');",
// 		iDataSetType,iDataSetid, iProjectid,iUid,iBatchid, sysytemid,strRemark);

	//postgresql
	sql.Format("insert into tb_task_batch(datasettype,datasetid,projectid,uid,batchid,systemid,\"desc\") "
		"values(%d,%I64d,%I64d, %d,%I64d,%d,'%s');",
		iDataSetType,iDataSetid, iProjectid,iUid,iBatchid, sysytemid,strRemark);
	CString strHead = "insert into tb_task_batch(" ;
	CString strBody = "values(";
	for ( int i=0; i<pTaskBatch->Size(); i++ )
	{
		CString strfieldname = pTaskBatch->GetFieldInfoByIndex(i)->GetFieldName() ;
		DB_FIELDTYPE etype = pTaskBatch->GetFieldTypeByIndex(i) ;
		CString val = "" ;
		switch ( etype )
		{
		case DBFT_Int:
			val.Format("%d",pTaskBatch->GetIntByIndex(i)) ;
			break;
		case DBFT_Bigint:
			val.Format("%I64d",pTaskBatch->GetInt64ByIndex(i)) ;
			break;
		case DBFT_Double:
			val.Format("%f",pTaskBatch->GetDoubleByIndex(i)) ;
			break;
		case DBFT_String:
			val.Format("'%s'",pTaskBatch->GetStringByIndex(i)) ;
			break;
		}
		if ( i==0 )
		{
			strHead += strfieldname ;
			strBody += val ;
		}
		else
		{
			strHead += "," ;
			strBody += "," ;
			strHead += strfieldname ;
			strBody += val ;
		}
	}
	if ( pTaskBatch->Size() >0 )
	{
		strHead += ")" ;
		strBody += ")" ;
		strHead = strHead + strBody ;
		sprintf(szSql,"%s", strHead) ;
	}
	else
	{
		sprintf(szSql,"%s",sql);
	}

	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	
	int iaffact = 0;
	bool bUpdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(szSql,iaffact);


	//增加完批次后 增加对应的task
}


CString CTaskManager::GetTaskBatchTableName()
{
	return "tb_task_batch";
}

CTaskBatch *CTaskManager::GetFirstTaskBatchPtr()
{
	if ( m_vtTaskBatchInfos.empty() )
	{
		return NULL ;
	}
	m_itTaskBatch = m_vtTaskBatchInfos.begin() ;
	return *m_itTaskBatch ;
}

CTaskBatch *CTaskManager::GetNextTaskBatchPtr()
{
	if ( m_vtTaskBatchInfos.empty() )
	{
		return NULL ;
	}
	m_itTaskBatch++ ;
	if ( m_itTaskBatch != m_vtTaskBatchInfos.end() )
	{
		return *m_itTaskBatch ;
	}
	
	return NULL ;
}


bool CTaskManager::AddNewTask(CTask *pTask)
{
	if(pTask == NULL) return false;
	CString sql;
	
	CDB_ResultSet* pRes = NULL;

	char* p = NULL;
	CString strReferdata = GetReferdataInfo(pTask) ;
	if ( strReferdata != "" )
	{
		sql.Format("insert into tb_task(tasktype,state,projectid,referdata) "
			"values(%d,%d,%I64d,'%s');",
			pTask->GetTaskType(),pTask->GetState(),pTask->GetProjectId(),strReferdata); 
	}
	else
	{
		sql.Format("insert into tb_task(tasktype,state,projectid) "
			"values(%d,%d,%I64d);",
			pTask->GetTaskType(),pTask->GetState(),pTask->GetProjectId()); 
	}
		
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	
	int iaffact = 0;
	bool bUpdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql,iaffact);

	sql.Format("select max(id) from tb_task");
	__int64 idTask = -1;
	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(sql);
	int rowcount = pRes->GetResRowCount();
	for(int r = 0; r < rowcount; r++)
	{
		idTask = pRes->GetResBigIntValue(r,0);
		
		pTask->SetID(idTask);
		CDBFieldInfo *pFieldInfo = new CDBFieldInfo("tashid","tb_task",DBFT_Bigint) ;
		pFieldInfo->SetFieldType(DB_FIELDTYPE(DBFT_Bigint));//再单独设置一下
		CDBValue *pValue = new CDBValue ;
		pTask->AddField(pFieldInfo, pValue) ;
		pTask->SetInt64ByIndex(pTask->GetIndex("tashid"), idTask) ;
		
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;

	return true;
}


bool CTaskManager::AddNewLinkInfoByTask(CTask *pTask)
{
	if ( pTask == NULL )
	{
		return false ;
	}
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	
	//----------fielddata--------------------------------------------------------
	int ilinkfielddataNum = pTask->GetLinkDbFieldDataCount() ;
	if ( ilinkfielddataNum > 0 )
	{
		CString strCond ;
		strCond.Format("insert into tb_task_link_fielddata (taskid,shapeid,poitempid,distance,second,lroadid,rroadid) values ") ;
		CString strbody = "" ;
		for ( int i=0; i<ilinkfielddataNum; i++ )
		{
			CTaskLinkFieldData *pLinkFielddata = pTask->GetLinkFieldDataByIndex(i) ;
			if ( pLinkFielddata == NULL )
			{
				continue;
			}
			CString strpoi ;
			strpoi.Format("(%I64d,%I64d,%I64d,%f,%f,%I64d,%I64d)",
				pLinkFielddata->GetTaskId(),pLinkFielddata->GetShapeId(),
				pLinkFielddata->GetFeatureId(),pLinkFielddata->GetDistance(),
				pLinkFielddata->GetLRoadId(),pLinkFielddata->GetRRoadId()) ;
			if ( strbody == "" )
			{
				strbody += strpoi ;
			}
			else
			{
				strbody += "," ;
				strbody += strpoi ;
			}
		}
		if ( strbody != "" )
		{
			strCond += strbody ;
			int iaffact = 0;
			bool bUpdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(strCond,iaffact);
			if ( !bUpdate )
			{/// 插入失败，需不需要保存日志到本地
			}
		}
	}
	
	//----------------attach---------------------------------------------------
	int ilinkattachNum = pTask->GetLinkAttachCount() ;
	if ( ilinkattachNum > 0 )
	{
		CString strCond ;
		strCond.Format("insert into tb_task_link_attach (taskid,recordtype,attachid,shapeid,length,layerid,featureid) values ") ;
		CString strbody = "" ;
		for ( int i=0; i<ilinkattachNum; i++ )
		{
			CTaskLinkAttach *pLinkAtt = pTask->GetLinkAttachByIndex(i) ;
			if ( pLinkAtt == NULL )
			{
				continue;
			}
			CString strpoi ;
			strpoi.Format("(%I64d,%d,%I64d,%I64d,%d,%d,%I64d)",
				pLinkAtt->GetTaskId(),pLinkAtt->GetRecordType(),
				pLinkAtt->GetAttachId(),pLinkAtt->GetShapeId(),
				pLinkAtt->GetLength(),pLinkAtt->GetLayerId(),pLinkAtt->GetFeatureid()) ;
			if ( strbody == "" )
			{
				strbody += strpoi ;
			}
			else
			{
				strbody += "," ;
				strbody += strpoi ;
			}
		}
		if ( strbody != "" )
		{
			strCond += strbody ;
			int iaffact = 0;
			bool bUpdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(strCond,iaffact);
			if ( !bUpdate )
			{/// 插入失败，需不需要保存日志到本地
			}
		}
	}

	//-------------------itemset-----------------------------------------------
	int ilinkitemsetNum = pTask->GetTaskLinkItemsetCount() ;
	if ( ilinkitemsetNum > 0 )
	{
		CString strCond ;
		strCond.Format("insert into tb_task_link_itemset (taskid,itemsetid) values ") ;
		CString strbody = "" ;
		for ( int i=0; i<ilinkitemsetNum; i++ )
		{
			__int64 itemsetid = pTask->GetTaskLinkItemsetByIndex(i) ;
			if ( itemsetid < 0 )
			{
				continue;
			}
			CString strpoi ;
			strpoi.Format("(%I64d,%I64d)",
				pTask->GetID(),itemsetid) ;
			if ( strbody == "" )
			{
				strbody += strpoi ;
			}
			else
			{
				strbody += "," ;
				strbody += strpoi ;
			}
		}
		if ( strbody != "" )
		{
			strCond += strbody ;
			int iaffact = 0;
			bool bUpdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(strCond,iaffact);
			if ( !bUpdate )
			{/// 插入失败，需不需要保存日志到本地
			}
		}
	}


	//----------------block---------------------------------------------------
	if ( pTask->GetTaskBlock() != NULL )
	{
		CTaskBlock *pBlock = pTask->GetTaskBlock() ;
// 		AddTaskBlockToDB(pBlock) ;
		ADDTaskBlockInfosToDB(pBlock) ;
	}
	return true ;
}

bool CTaskManager::AddNewTaskChangeRoadTime( CTaskChangeRoadTime *pTaskChangeRoadTime )
{
	if ( pTaskChangeRoadTime == NULL)
	{
		return false ;
	}


	__int64 itaskid = pTaskChangeRoadTime->GetTaskID() ;
	SYSTEMTIME	begintime = pTaskChangeRoadTime->GetBeginTime() ;
	SYSTEMTIME endtime = pTaskChangeRoadTime->GetEndTime() ;
	int istate = pTaskChangeRoadTime->GetState() ;

	CString sbtime ,setime ;
	sbtime.Format("%d-%d-%d %d:%d:%d", begintime.wYear,begintime.wMonth,begintime.wDay,begintime.wHour,begintime.wMinute,begintime.wSecond) ;
	setime.Format("%d-%d-%d %d:%d:%d", endtime.wYear,endtime.wMonth,endtime.wDay,endtime.wHour,endtime.wMinute,endtime.wSecond) ;
	CString sql = "" ;
	sql.Format("insert into tb_task_changeroad_time(begintime,endtime) values('%s','%s')", sbtime,setime) ;
	
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	SetChoosingTask() ;

	
	int iaffact = 0;
	bool bUpdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql,iaffact);
	return bUpdate ;
}

CTaskChangeRoadTime* CTaskManager::GetFirstTaskChangeRoadTimePtr()
{
	CTaskChangeRoadTime *p = NULL ;
	m_currentTaskChangRoadTimePtr = m_vtTaskChangeRoadTime.begin() ;
	if( m_currentTaskChangRoadTimePtr != m_vtTaskChangeRoadTime.end() ) 
	{
		
		p = *m_currentTaskChangRoadTimePtr ;
		m_currentTaskChangRoadTimePtr++ ;
		return p ;
	}
	else
	{
		return NULL ;
	}
}

bool CTaskManager::GetTaskChangeRoadTimeInfos( CString strCond/*=""*/ )
{
	char szSql[1024];
	CString sql;
	sql.Format("select id,taskid,begintime,endtime,state,updatetime from tb_task_changeroad_time %s",strCond);
	
	sprintf(szSql,"%s",sql);
	CDB_ResultSet* pRes = NULL;

	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	
	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);
	if ( pRes == NULL)
	{
		return false ;
	}

	int rowcount = pRes->GetResRowCount();
	for(int r = 0; r < rowcount; r++)
	{
		CTaskChangeRoadTime* pTaskChangeRoadTime = new CTaskChangeRoadTime;

		pTaskChangeRoadTime->SetID(pRes->GetResBigIntValue(r,0));
		pTaskChangeRoadTime->SetTaskID(pRes->GetResBigIntValue(r,1)) ;
		pTaskChangeRoadTime->SetBeginTime(Char2Systemtime( const_cast<char*>(pRes->GetResStringValue(r,2) ))) ;
		pTaskChangeRoadTime->SetEndTime(Char2Systemtime( const_cast<char*>(pRes->GetResStringValue(r,3) ))) ;
		pTaskChangeRoadTime->SetState(pRes->GetResIntValue(r,4)) ;
		pTaskChangeRoadTime->SetUpdateTime(Char2Systemtime(const_cast<char*>(pRes->GetResStringValue(r,5) ))) ;
		
		
		
		m_vtTaskChangeRoadTime.push_back(pTaskChangeRoadTime);
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	return true ;
}

CTaskChangeRoadTime* CTaskManager::GetNextTaskChangeRoadTimePtr()
{
	CTaskChangeRoadTime *p = NULL ;
	if ( m_currentTaskChangRoadTimePtr != m_vtTaskChangeRoadTime.end())
	{
		p = *m_currentTaskChangRoadTimePtr ;
		m_currentTaskChangRoadTimePtr++ ;
		return p ;
	}	
	else
	{
		return NULL ;
	}
}

CTaskChangeRoadTime* CTaskManager::GetNextTaskChangeRoadTimePtr( CTaskChangeRoadTime *pTaskChangeRoadTime )
{
	VT_TASK_CHANGEROADTIME::iterator change_iterator ;
	for ( change_iterator = m_vtTaskChangeRoadTime.begin(); change_iterator != m_vtTaskChangeRoadTime.end(); change_iterator++)
	{
		CTaskChangeRoadTime *p = *change_iterator ;
		if ( p == pTaskChangeRoadTime)
		{
			change_iterator++ ;
			if ( change_iterator != m_vtTaskChangeRoadTime.end())
			{
				p = *change_iterator ;
				return p ;
			}
		}
	}
	return NULL ;
}

SYSTEMTIME CTaskManager::GetNewSystemtimeFromChangeRoadTimeTable()
{
	CString sql = "" ;
	sql.Format("select max(endtime) from tb_task_changeroad_time") ;

// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	SetChoosingTask() ;



	SYSTEMTIME newtime;
	newtime.wYear = 0 ;
	newtime.wMonth = 0 ;
	newtime.wDay = 0 ;
	newtime.wHour = 0 ;
	newtime.wMinute = 0 ;
	newtime.wSecond = 0 ;

	CDB_ResultSet *result = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(sql) ;
	if ( result == NULL)
	{
		return newtime ;	
	}

	newtime = Char2Systemtime(const_cast<char*>(result->GetResStringValue(0,0))) ;

	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&result) ;
	return newtime ;
}

bool CTaskManager::UpdateTaskChangeRoadTimePtr( CTaskChangeRoadTime *pTaskChangeRoadTime )
{
	if ( pTaskChangeRoadTime == NULL)
	{
		return false ;
	}

	CString sql = "" ;
	sql.Format("update tb_task_changeroad_time set state=%d where taskid=%I64d", pTaskChangeRoadTime->GetState(), pTaskChangeRoadTime->GetTaskID()) ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	int iaffact = 0;
	bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql( sql,iaffact) ;
	return bupdate ;
}

bool CTaskManager::WriteDBForTaskBlockDetail( CTaskBlockDetail *pTaskBlockDetail )
{
	if ( pTaskBlockDetail == NULL)
	{
		return false ;
	}

	CString sql = "" ;
// 	sql.Format("insert into tb_task_blockdetail(blockid,layerid,featureid) values(%I64d,%d,%I64d)", pTaskBlockDetail->GetBlockID(), pTaskBlockDetail->GetLayerID(), pTaskBlockDetail->GetFeatureID()) ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	CString strHead = "insert into tb_task_blockdetail(" ;
	CString strMid = "" ;
	CString strMid1= "" ;
	int size = pTaskBlockDetail->Size();
	for ( int i=0; i<size; i++ )
	{
		CString strFieldname = pTaskBlockDetail->GetFieldInfoByIndex(i)->GetFieldName() ;
		if ( strFieldname == "id")
		{
			continue;
		}
		if( strFieldname == "updatetime")
		{
			continue;
		}
		if ( strMid != "")
		{
			strMid += "," ;
		}
		if ( strFieldname == "desc")
		{
			strFieldname = "`desc`";
		}
		strMid += strFieldname ;
		DB_FIELDTYPE etype = pTaskBlockDetail->GetFieldInfoByIndex(i)->GetFieldType() ;
		CString strValue = "" ;
		switch (etype)
		{
		case DBFT_Bigint:
			strValue.Format("%I64d",pTaskBlockDetail->GetInt64ByIndex(i)) ;
			break;
		case DBFT_Int:
			strValue.Format("%d",pTaskBlockDetail->GetIntByIndex(i)) ;
			break;
		case DBFT_Double:
			strValue.Format("%f",pTaskBlockDetail->GetDoubleByIndex(i)) ;
			break;
		case DBFT_String:
			strValue.Format("'%s'",pTaskBlockDetail->GetStringByIndex(i)) ;
			break;
		}
		if ( strMid1 != "")
		{
			strMid1 += "," ;
		}
		strMid1 += strValue ;
	}
	if ( strMid != "")
	{
		strMid += ") values (" ;
	}
	if ( strMid1 != "")
	{
		strMid1 = strMid + strMid1 +")" ;
		strHead = strHead + strMid1 ;
		int iaffact = 0;
		bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(strHead,iaffact) ;
		if ( bupdate )
		{
			sql = "" ;
			sql.Format("select LAST_INSERT_ID() as maxid ") ;
			CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(sql) ;
			if ( pRes == NULL)
			{
				return false;
			}
		
			__int64 iID = pRes->GetResBigIntValue(0,0) ;
		
			pTaskBlockDetail->SetID(iID) ;
			CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
		}
		return bupdate ;
	}
	
	return false ;
}

bool CTaskManager::AddTaskBlockToDB( CTaskBlock *pTaskBlock )
{
	if ( pTaskBlock == NULL)
	{
		return false ;
	}

	CString sql = "" ;
	CTaskManager::GetTaskManager()->SetChoosingTask() ;
	sql.Format("insert into tb_task_block(type,status,envelope) values(%d,%d,st_geometryfromtext('LINESTRING(%f %f,%f %f)'))",pTaskBlock->GetType(), pTaskBlock->GetStatus(),
		pTaskBlock->GetBound().x_min,pTaskBlock->GetBound().y_min, pTaskBlock->GetBound().x_max, pTaskBlock->GetBound().y_max) ;

	int iaffact = 0;
	bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql,iaffact) ;
	if ( !bupdate)
	{
		return false;
	}

	// 获取刚插入的ID
// 	sql.Format("select max(id) from tb_task_block where type=%d and status = %d and st_contains(envelope,st_geometryfromtext('LINESTRING(%f %f,%f %f)'))  and status not in(5,6)",
// 				pTaskBlock->GetType(), pTaskBlock->GetStatus(),	pTaskBlock->GetBound().x_min,pTaskBlock->GetBound().y_min, pTaskBlock->GetBound().x_max, pTaskBlock->GetBound().y_max) ;
	sql.Format("select max(id) from tb_task_block where type=%d and status = %d and status not in(5,6)",
					pTaskBlock->GetType(), pTaskBlock->GetStatus()) ;

// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	CDB_ResultSet *result = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(sql) ;
	if ( result == NULL)
	{
		return false ;
	}

	pTaskBlock->SetID(result->GetResBigIntValue(0,0)) ; 

	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&result) ;
	return true ;
}

bool CTaskManager::ADDTaskBlockInfosToDB( CTaskBlock *pTaskBlock )
{
	if ( pTaskBlock == NULL)
	{
		return false ;
	}
	
	CTaskManager::GetTaskManager()->SetChoosingTask() ;
	int iCount = pTaskBlock->GetTaskBlockDetailCount() ;
	int iIndex = 0 ;
	CTaskBlockDetail *pTaskBlockDetail = pTaskBlock->GetFirstTaskBlockDetailPtr() ;
	/*CString sqlfront = "insert into tb_task_blockdetail(blockid,layerid,featureid,operatetype,`desc`,incrementtype,direction) " ;*/
	//postgresql
	CString sqlfront = "insert into tb_task_blockdetail(blockid,layerid,featureid,operatetype,\"desc\",incrementtype,direction) " ;
	CString sqlend = "values(" ;
	CString temp = "" ;
	CString msg = "" ;
	CString sql = "" ;
	bool bupdate = true ;
	while ( pTaskBlockDetail)
	{
		iIndex++ ;
		temp = "" ;
		msg.Format("%I64d", pTaskBlockDetail->GetBlockID()) ;
		temp += msg + "," ;
		msg.Format("%d", pTaskBlockDetail->GetLayerID()) ;
		temp += msg + "," ;
		msg.Format("%I64d", pTaskBlockDetail->GetFeatureID()) ;
		temp += msg + "," ;
		msg.Format("%d", pTaskBlockDetail->GetOperateType()) ;
		temp += msg + "," ;
		msg.Format("'%s'", pTaskBlockDetail->GetDesc()) ;
		temp += msg + "," ;
		msg.Format("%d", pTaskBlockDetail->GetIncrementtype()) ;
		temp += msg + "," ;
		msg.Format("%d", pTaskBlockDetail->GetDirection()) ;
		temp += msg + "),(" ;
		sqlend += temp ;
		if ( iIndex % 1000 == 0)
		{
			if ( sqlend.Right(2) == ",(")
			{
				sqlend = sqlend.Left(sqlend.GetLength()-2) ;
				sql = sqlfront + sqlend ;
// 				CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
				int iaffact = 0;
				bool binsert = CDB_Manager::GetDBManagerPtr()->ExcuteSql( sql,iaffact) ;
				if ( bupdate && !binsert)
				{
					bupdate = false ;
				}
				sqlend = "values(" ;
			}
		}
		pTaskBlockDetail = pTaskBlock->GetNextTaskBlockDetailPtr() ;
	}
	if ( sqlend.Right(2) == ",(")
	{
		sqlend = sqlend.Left(sqlend.GetLength()-2) ;
		sql = sqlfront + sqlend ;
// 		CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
		int iaffact = 0;
		bool binsert = CDB_Manager::GetDBManagerPtr()->ExcuteSql( sql,iaffact) ;
		if ( bupdate && !binsert)
		{
			bupdate = false ;
		}
		
	}
	return bupdate ;
}

bool CTaskManager::UpDateBlockToDB( CTaskBlock *pTaskBlock )
{
	if ( pTaskBlock == NULL)
	{
		return false ;
	}

	CString sql = "" ;
	sql.Format("update tb_task_block set type=%d,status=%d,envelope=st_geometryfromtext('LINESTRING(%f %f,%f %f)') where id=%I64d",pTaskBlock->GetType(), pTaskBlock->GetStatus(),
		pTaskBlock->GetBound().x_min,pTaskBlock->GetBound().y_min, pTaskBlock->GetBound().x_max, pTaskBlock->GetBound().y_max,pTaskBlock->GetID()) ;
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	CTaskManager::GetTaskManager()->SetChoosingTask() ;
	int iaffact = 0;
	bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql,iaffact) ;
	return bupdate ;
}

bool CTaskManager::UpDateBlockStatusToDB( CTaskBlock *pTaskBlock , __int64 newblockid)
{
	if ( pTaskBlock == NULL)
	{
		return false ;
	}
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	CTaskManager::GetTaskManager()->SetChoosingTask() ;
	CString sql = "" ;
	sql.Format("update tb_task_block set status=%d where id=%I64d",pTaskBlock->GetStatus(),pTaskBlock->GetID()) ;
	int iaffact = 0;
	bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql, iaffact) ;
	
	if ( bupdate == true && pTaskBlock->GetStatus() == 6)
	{
		// need change tb_error.blockid
// 		CDB_Manager::GetDBManagerPtr()->ChooseDB( DB_ERRORLOG_PGSQL) ;
		CTaskManager::GetTaskManager()->SetChoosingError() ;
		
		CString errorids = "" ;
		sql.Format("select id from tb_error where blockid = %I64d", pTaskBlock->GetID()) ;
		
		CDB_ResultSet *pRes= CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(sql) ;
		if ( pRes == NULL)
		{
			return false ;
		}

		int rowcount = pRes->GetResRowCount() ;
		for ( int index = 0; index < rowcount; index++)
		{
			errorids += pRes->GetResStringValue(index,0) ;
			errorids += "," ;
		}

		CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;

		if ( errorids.Find(",") != -1)
		{
			errorids = errorids.Left(errorids.GetLength()-1) ;
			sql.Format("update tb_error set blockid = %I64d where id in (%s)", newblockid, errorids) ;
			int iaffact2 = 0 ;
			bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql, iaffact2) ;
		}
	}
	
	return bupdate ;
}

bool CTaskManager::UpDateBlockTypeToDB( CTaskBlock *pTaskBlock )
{
	if ( pTaskBlock == NULL)
	{
		return false ;
	}
	
	CString sql = "" ;
	sql.Format("update tb_task_block set type=%d where id=%I64d",pTaskBlock->GetType(),pTaskBlock->GetID()) ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	int iaffact = 0;
	bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql,iaffact) ;
	return bupdate ;
}

bool CTaskManager::UpDateBlockEnvelope( CTaskBlock* pTaskBlock )
{
	if ( pTaskBlock == NULL)
	{
		return false ;
	}
	
	CString sql = "" ;
	sql.Format("update tb_task_block set envelope=st_geometryfromtext('LINESTRING(%f %f,%f %f)') where id=%I64d",
		pTaskBlock->GetBound().x_min,pTaskBlock->GetBound().y_min, pTaskBlock->GetBound().x_max, pTaskBlock->GetBound().y_max,pTaskBlock->GetID()) ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	int iaffact = 0;
	bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql,iaffact) ;
	return bupdate ;
}

CTaskBlock* CTaskManager::GetFirstTaskBlockPtr()
{
	CTaskBlock * pTaskBlock = NULL ;
	m_currentTaskBlockPtr = m_mapTaskBlock.begin() ;
	if ( m_currentTaskBlockPtr != m_mapTaskBlock.end())
	{
		pTaskBlock= m_currentTaskBlockPtr->second ;
		m_currentTaskBlockPtr++ ;
		return pTaskBlock ;
	}
	return NULL ;
}


// 写个字符串
void CTaskManager::SqlitCString(CString strContent,CString ch,vector<CString>& strResultArr) //不保留空字符串
{
	int npos;
	CString strResult;
	strResultArr.clear();
	
	npos=strContent.Find(ch);
	if (npos==-1)
	{
		strResultArr.push_back(strContent);
		return;
	}
	
	while (npos!=-1)
	{
		strResult=strContent.Left(npos);
		if(strResult!="")
			strResultArr.push_back(strResult);
		if(npos+1>strContent.GetLength()-ch.GetLength())
			break;
		strContent=strContent.Mid(npos+ch.GetLength());
		npos=strContent.Find(ch);
		if (npos==-1)
			strResultArr.push_back(strContent);
	}
}

_TSGEO::SGeoRect CTaskManager::LineString2SGeoRect( CString linestring )
{
	// 【x_min y_min,x_max y_max】
	// 格式【LINESTRING(112.23456 39.123456,113.123456 40.123456)】
	CString temp = linestring ;
	_TSGEO::SGeoRect rect ;
	temp.Replace("LINESTRING(","") ;// 112.23456 39.123456,113.123456 40.123456)
	temp.Replace(")","") ;//112.23456 39.123456,113.123456 40.123456
	CString msg ;
	vector< CString > vttemp ;
	SqlitCString( temp, ",", vttemp); 
	if ( vttemp.size() != 2)
	{
		return rect ;
	}
	for ( int i = 0; i < vttemp.size(); i++)
	{
		CString str = vttemp[i] ;
		vector< CString> vtxy ;
		SqlitCString( str, " ", vtxy) ;
		if ( vtxy.size() != 2)
		{
			return rect ;
		}
		if ( i == 0)
		{
			rect.x_min = atof(vtxy[0]) ;
			rect.y_min = atof(vtxy[1]) ;
		}
		else
		{
			rect.x_max = atof(vtxy[0]) ;
			rect.y_max = atof( vtxy[1]) ;
		}
	}
	return rect ;

}

__int64* CTaskManager::GetBlockIDsForFeatureID( __int64 featureID, int layerid,int &size )
{
	__int64 *p = NULL ;
	CString sql = "" ;
// 	sql.Format("select count(*) from tb_task_blockdetail left join tb_task_block on tb_task_block.id = tb_task_blockdetail.blockid "
// 		"where tb_task_blockdetail.featureid = %I64d and tb_task_blockdetail.layerid = %d and tb_task_block.`status` not in (5,6)",featureID, layerid) ;
	//postgresql
	sql.Format("select count(*) from tb_task_blockdetail left join tb_task_block on tb_task_block.id = tb_task_blockdetail.blockid "
		"where tb_task_blockdetail.featureid = %I64d and tb_task_blockdetail.layerid = %d and tb_task_block.\"status\" not in (5,6)",featureID, layerid) ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	CDB_ResultSet *result = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql( sql) ;
	if ( result == NULL)
	{
		return p ;
	}

	size = result->GetResIntValue(0,0) ;
	
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&result) ;

	
	if ( size > 0)
	{
// 		sql.Format("select blockid from tb_task_blockdetail left join tb_task_block on tb_task_block.id = tb_task_blockdetail.blockid "
// 			"where tb_task_blockdetail.featureid = %I64d and tb_task_blockdetail.layerid = %d and tb_task_block.`status` not in (5,6)",featureID, layerid) ;

		//postgresql
		sql.Format("select blockid from tb_task_blockdetail left join tb_task_block on tb_task_block.id = tb_task_blockdetail.blockid "
			"where tb_task_blockdetail.featureid = %I64d and tb_task_blockdetail.layerid = %d and tb_task_block.\"status\" not in (5,6)",featureID, layerid) ;
		result = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql( sql) ;
		if ( result == NULL)
		{
			return p ;
		}
		
		p = new __int64[size] ;
		int index = 0 ;
		int rowcount = result->GetResRowCount();
		for(int r = 0; r < rowcount; r++)
		{
			p[index] = result->GetResBigIntValue(r,0) ;
			index++ ;
		}
		CDB_Manager::GetDBManagerPtr()->ReleaseRes(&result) ;
	}
	return p ;
}

CTaskBlock* CTaskManager::GetTaskBlockPtrForBlockID( __int64 blockid )
{
	CString sql ;
	//sql.Format("select id,`type`,`status`,AsText(envelope) as envelope,updatetime from tb_task_block where id=%I64d and status not in(5,6)", blockid) ;
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	if ( GetSqlFlag() == MYSQL_RUNING)
	{
		sql.Format("select id,`type`,`status`,AsText(envelope) as envelope,updatetime from tb_task_block where id=%I64d and status not in(5,6)", blockid) ;
	}
	else if ( GetSqlFlag() == POSTGRES_RUNNING)
	{
		sql.Format("select id,\"type\",\"status\",st_AsText(envelope) as envelope,updatetime from tb_task_block where id=%I64d and status not in(5,6)", blockid) ;
	}
	CTaskManager::GetTaskManager()->SetChoosingTask() ;
	CDB_ResultSet *result = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(sql) ;
	if ( result == NULL)
	{
		return NULL ;
	}
	int num_rows = result->GetResRowCount();
	int num_fields = result->GetResFieldCount();
	
	std::vector<Field_DB> vtFields ;
	
	MAP_RES mapres ;
	int icount = 0 ;
	for(int r = 0; r < num_rows; r++)
	{
		icount++ ;
		VT_RES vtRes ;
		for ( int i=0; i<num_fields; i++ )
		{
			int ftype = result->GetFieldType(i);
			if ( icount == 1 )
			{
				Field_DB field ;
				field.name = result->GetFieldName(i) ;
				field.table = "" ;
				field.type = ftype ;
				vtFields.push_back(field) ;	
			}
			
			CString strval;
			
			switch(ftype)
			{
			case DBFT_Int:
				{
					strval.Format("%d",result->GetResIntValue(r,i));
					break;
				}
			case DBFT_Double:
				{
					strval.Format("%f",result->GetResDoubleValue(r,i));
					break;
				}
			case DBFT_Bigint:
				{
					strval.Format("%I64d",result->GetResBigIntValue(r,i));
					break;
				}
			case DBFT_String:
				{
					strval.Format("%s",result->GetResStringValue(r,i));
					break;
				}
			}
			
			vtRes.push_back(strval.GetBuffer(0)) ;
		}
		mapres.insert(MAP_RES::value_type(icount,vtRes)) ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&result) ;
	
	if ( mapres.empty() )
	{
		return false ;
	}

	CDBFieldInfo *pFieldInfo = NULL ;
	CDBValue *pValue = NULL ;
	MAP_RES::iterator it ;
	CTaskBlock *pTask = new CTaskBlock() ;
	for ( it=mapres.begin(); it!=mapres.end(); it++ )
	{
		VT_RES vtres = it->second ;
		for ( int i=0; i<num_fields; i++ )
		{
			int mysqltype = vtFields.at(i).type ;
			pFieldInfo = new CDBFieldInfo(vtFields[i].name,vtFields[i].table,mysqltype) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(mysqltype));//再单独设置一下
			pValue = new CDBValue ;
			pTask->AddField(pFieldInfo, pValue) ;
			CString strval = vtres.at(i).c_str() ;
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pTask->SetIntByIndex(i,atoi(strval) ) ;
				break;
			case DBFT_Bigint:
				pTask->SetInt64ByIndex(i,_atoi64(strval) ) ;
				break;
			case DBFT_Double:
				pTask->SetDoubleByIndex(i, atof(strval) ) ;
				break;
			case DBFT_String:
				pTask->SetStringByIndex(i,strval) ;
				break;
			}
		}
		int iIndex = pTask->GetIndex("id") ;
		pTask->SetID(pTask->GetInt64ByIndex(iIndex)) ;
		iIndex = pTask->GetIndex("type") ;
		pTask->SetType(pTask->GetIntByIndex(iIndex)) ;
		iIndex = pTask->GetIndex("status") ;
		pTask->SetStatus(pTask->GetIntByIndex(iIndex)) ;
		iIndex = pTask->GetIndex("updatetime") ;
		CString strtime = pTask->GetStringByIndex(iIndex) ;
		pTask->SetUpdateTime(Char2Systemtime(strtime.GetBuffer(0))) ;
		iIndex = pTask->GetIndex("envelope") ;
		
		CString strbound = pTask->GetStringByIndex(iIndex) ;
		pTask->SetBound(LineString2SGeoRect(strbound)) ;
		pTask->LoadLinkInfo() ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseAllRes() ;
	return pTask ;
}

bool CTaskManager::CloseTaskBlockForBlockID( __int64 blockid,int status )
{
	CString sql = "" ;
	sql.Format("update tb_task_block set status=%d where id=%I64d",status, blockid) ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	int iaffact = 0;
	bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql,iaffact) ;
	return bupdate ;
}

bool CTaskManager::LoadTaskBlock( CString strConfition /*= ""*/ )
{
	// 将以前的内容释放掉
	ReleaseTaskBlocks() ;
	CString sql ;
	/*sql.Format("select id,`type`,`status`,AsText(envelope) as envelope,updatetime from tb_task_block %s", strConfition) ;*/
	//postgresql
	if ( GetSqlFlag() == MYSQL_RUNING)
	{
		sql.Format("select id,`type`,`status`,AsText(envelope) as envelope,updatetime from tb_task_block %s", strConfition) ;
	}
	else if ( GetSqlFlag() == POSTGRES_RUNNING)
	{
		sql.Format("select id,\"type\",\"status\",st_AsText(envelope) as envelope,updatetime from tb_task_block %s", strConfition) ;
	}
	
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	SetChoosingTask() ;

	CDB_ResultSet *pTaskBlockRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(sql) ;
	if ( pTaskBlockRes == NULL)
	{
		return false ;
	}
	int num_rows = pTaskBlockRes->GetResRowCount();
	int num_fields = pTaskBlockRes->GetResFieldCount();
	
	std::vector<Field_DB> vtFields ;
	
	MAP_RES mapres ;
	int icount = 0 ;
	for(int r = 0; r < num_rows; r++)
	{
		icount++ ;
		VT_RES vtRes ;
		for ( int i=0; i<num_fields; i++ )
		{
			int ftype = pTaskBlockRes->GetFieldType(i);
			if ( icount == 1 )
			{
				Field_DB field ;
				field.name = pTaskBlockRes->GetFieldName(i) ;
				field.table = "" ;
				field.type = ftype ;
				vtFields.push_back(field) ;	
			}
			
			CString strval;
			
			switch(ftype)
			{
			case DBFT_Int:
				{
					strval.Format("%d",pTaskBlockRes->GetResIntValue(r,i));
					break;
				}
			case DBFT_Double:
				{
					strval.Format("%f",pTaskBlockRes->GetResDoubleValue(r,i));
					break;
				}
			case DBFT_Bigint:
				{
					strval.Format("%I64d",pTaskBlockRes->GetResBigIntValue(r,i));
					break;
				}
			case DBFT_String:
				{
					strval.Format("%s",pTaskBlockRes->GetResStringValue(r,i));
					break;
				}
			}
			
			vtRes.push_back(strval.GetBuffer(0)) ;
		}
		mapres.insert(MAP_RES::value_type(icount,vtRes)) ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pTaskBlockRes) ;
	
	if ( mapres.empty() )
	{
		return false;
	}

	CDBFieldInfo *pFieldInfo = NULL ;
	CDBValue *pValue = NULL ;
	MAP_RES::iterator it ;
	
	for ( it=mapres.begin(); it!=mapres.end(); it++ )
	{
		CTaskBlock *pTaskBlock = new CTaskBlock() ;
		VT_RES vtres = it->second ;
		for ( int i=0; i<num_fields; i++ )
		{
			int mysqltype = vtFields.at(i).type ;
			pFieldInfo = new CDBFieldInfo(vtFields[i].name,vtFields[i].table,mysqltype) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(mysqltype));//再单独设置一下
			pValue = new CDBValue ;
			string sss = vtFields[i].name ;
			pTaskBlock->AddField(pFieldInfo, pValue) ;
			CString strval = vtres.at(i).c_str() ;
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pTaskBlock->SetIntByIndex(i,atoi(strval) ) ;
				break;
			case DBFT_Bigint:
				pTaskBlock->SetInt64ByIndex(i,_atoi64(strval) ) ;
				break;
			case DBFT_Double:
				pTaskBlock->SetDoubleByIndex(i, atof(strval) ) ;
				break;
			case DBFT_String:
				pTaskBlock->SetStringByIndex(i,strval) ;
				break;
			}
		}
		int iIndex = pTaskBlock->GetIndex("id") ;
		if ( iIndex != -1 )
		{
			pTaskBlock->SetID(pTaskBlock->GetInt64ByIndex(iIndex)) ;
		}
		iIndex = pTaskBlock->GetIndex("type") ;
		if ( iIndex != -1 )
		{
			pTaskBlock->SetType(pTaskBlock->GetIntByIndex(iIndex)) ;
		}
		iIndex = pTaskBlock->GetIndex("status") ;
		if ( iIndex != -1 )
		{
			pTaskBlock->SetStatus(pTaskBlock->GetIntByIndex(iIndex)) ;
		}
		iIndex = pTaskBlock->GetIndex("updatetime") ;
		if ( iIndex != -1 )
		{
			CString strtime = pTaskBlock->GetStringByIndex(iIndex) ;
			pTaskBlock->SetUpdateTime(Char2Systemtime(strtime.GetBuffer(0))) ;
		}
		iIndex = pTaskBlock->GetIndex("envelope") ;
		if ( iIndex != -1 )
		{
			CString strbound = pTaskBlock->GetStringByIndex(iIndex) ;
			pTaskBlock->SetBound(LineString2SGeoRect(strbound)) ;
		}
		pTaskBlock->LoadLinkInfo() ;
		if ( m_pTask != NULL )
		{
			m_pTask->SetTaskBlock( pTaskBlock);
		}
		else
		{
			m_mapTaskBlock.insert(MAP_TASK_BLOCK::value_type( pTaskBlock->GetID(), pTaskBlock)) ;
		}
	}
	return true ;
}

void CTaskManager::ReleaseTaskBlocks()
{
	if ( !m_mapTaskBlock.empty())
	{
		MAP_TASK_BLOCK::iterator block_iterator ;
		for ( block_iterator = m_mapTaskBlock.begin(); block_iterator != m_mapTaskBlock.end(); block_iterator++)
		{
			CTaskBlock *pTaskBlock = block_iterator->second ;
			if ( pTaskBlock != NULL)
			{
				delete pTaskBlock ;
				pTaskBlock = NULL ;
			}
		}
		m_mapTaskBlock.clear() ;
	}
}

CTaskBlock* CTaskManager::GetNextTaskBlockPtr()
{
	if ( m_mapTaskBlock.empty())
	{
		return NULL ;
	}
	if ( m_currentTaskBlockPtr == m_mapTaskBlock.end())
	{
		return NULL ;
	}
	CTaskBlock *p = m_currentTaskBlockPtr->second ;
	m_currentTaskBlockPtr++ ;
	return p ;
}

CTaskBlock* CTaskManager::GetNextTaskBlockPtr( CTaskBlock *pTaskBlock )
{
	if ( m_mapTaskBlock.empty())
	{
		return NULL ;
	}
	if ( pTaskBlock == NULL)
	{
		return NULL ;
	}
	MAP_TASK_BLOCK::iterator block_iterator ;
	block_iterator = m_mapTaskBlock.find( pTaskBlock->GetID()) ;
	if ( block_iterator == m_mapTaskBlock.end())
	{
		return NULL ;
	}
	else
	{
		block_iterator++ ;
		if ( block_iterator == m_mapTaskBlock.end())
		{
			return NULL ;
		}
		else
		{
			return block_iterator->second ;
		}
	}
	return block_iterator->second ;
}

CTaskBlock* CTaskManager::GetTaskBlockByBlockID( __int64 blockid )
{
	MAP_TASK_BLOCK::iterator block_iterator ;
	block_iterator = m_mapTaskBlock.find( blockid) ;
	if ( block_iterator == m_mapTaskBlock.end())
	{
		return NULL ;
	}
	return block_iterator->second ;
}

bool CTaskManager::DeleteTaskBlock( __int64 blockid )
{
	MAP_TASK_BLOCK::iterator block_iterator ;
	block_iterator = m_mapTaskBlock.find( blockid) ;
	if ( block_iterator == m_mapTaskBlock.end())
	{
		return NULL ;
	}
	if ( block_iterator == m_currentTaskBlockPtr)
	{
		m_currentTaskBlockPtr++ ;
	}
	CTaskBlock *ptaskBlock = block_iterator->second ;
	m_mapTaskBlock.erase( block_iterator);	// 从内存中删除一条block
	if ( ptaskBlock != NULL)
	{
		delete ptaskBlock ;
		ptaskBlock = NULL ;
	}
	return true ;
}

// 向数据库添加任务
bool CTaskManager::AddQCTask(CQCTask *pQCTask)
{
	if ( pQCTask == NULL )
	{
		return false;
	}
	CTaskLinkItemSet * pItemSet = pQCTask->GetLinkItemSet() ;
	if (pItemSet == NULL )
	{
		return false;
	}
	int iIndex = pQCTask->GetIndex("blockid") ;
	__int64 iblockid = pQCTask->GetInt64ByIndex(iIndex) ;
	iIndex = pQCTask->GetIndex("name") ;
	CString strname = pQCTask->GetStringByIndex(iIndex) ;
	iIndex = pQCTask->GetIndex("tasktype") ;
	int itasktype = pQCTask->GetIntByIndex(iIndex) ;
	iIndex = pQCTask->GetIndex("state") ;
	int istate = pQCTask->GetIntByIndex(iIndex) ;
	iIndex = pQCTask->GetIndex("referdata") ;
	CString strreferdata = pQCTask->GetStringByIndex(iIndex) ;
	iIndex = pQCTask->GetIndex("batchid") ;
	__int64 ibatchid = pQCTask->GetInt64ByIndex(iIndex) ;
	iIndex = pQCTask->GetIndex("systype") ;
	int isystype = pQCTask->GetIntByIndex(iIndex) ;
	// 设置jsonb
	_TSGEO::SGeoRect bound = pQCTask->GetBound() ;
	_TSGEO::SGeoRect b = _TSGEO::SGeoRect(0,0,0,0) ;
	CString strbound = "" ;
	if ( !(bound == b ))
	{
		strbound.Format("\"bound\":[%f,%f,%f,%f]",bound.x_min,bound.y_min,bound.x_max,bound.y_max) ;
	}
	CString strLayerNames = "" ;
	if ( pQCTask->GetReferLayerCount() > 0)
	{
		strLayerNames = "\"layer\":[" ;
		CString strMid = "" ;
		for (int i=0; i<pQCTask->GetReferLayerCount(); i++ )
		{
			CString strName = pQCTask->GetLayerNameByIndex(i) ;
			if (strName == "")
			{
				continue;
			}
			strName = "\"" + strName + "\"" ;
			if ( strMid != "" )
			{
				strMid += "," ;
			}
			strMid += strName ;
		}
		if ( strMid != "" )
		{
			strMid += "]" ;
			strLayerNames += strMid ;
		}
		else
		{
			strLayerNames = "" ;
		}
	}
	if (strbound != "" && strLayerNames)
	{
		strLayerNames += "," ;
		strLayerNames += strbound ;
		strreferdata = strLayerNames ;
		if ( itasktype == 2002 )
		{
			strreferdata = "{\"tool\":{" + strreferdata + "}}" ;
		}
		else
		{
			strreferdata = "{\"qc\":{" + strreferdata + "}}" ;
		}
	}
	else
	{
		strreferdata = "" ;
	}
	// jsonb设置完毕
	
	CString strSQL ;
	// 先向数据库中添加一条任务记录
	strSQL.Format("insert into tb_task " 
		"(blockid,name,tasktype,state,referdata,batchid,systype) "
		"values(%I64d,'%s',%d,%d,'%s',%I64d,%d)",
		iblockid,strname,itasktype,istate,strreferdata,ibatchid,isystype) ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	int iaffact = 0;
	bool bIssucess = CDB_Manager::GetDBManagerPtr()->ExcuteSql(strSQL,iaffact) ;
	if ( !bIssucess )
	{// 添加失败
		return false;
	}

	// 获得添加的任务编号
	strSQL.Format("select LAST_INSERT_ID() as maxid ") ;
	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
	if ( pRes == NULL)
	{
		return false;
	}

	__int64 iTaskid = pRes->GetResBigIntValue(0,0) ;

	CDB_Manager::GetDBManagerPtr()->ReleaseAllRes() ;
	if ( iTaskid == 0 )
	{
		return false;
	}
	
	// 添加一条link_itemset记录
	strSQL.Format("insert into tb_task_link_itemset (taskid,itemsetid) values(%I64d,%I64d)",
		iTaskid,pItemSet->GetItemSetID()) ;
	
	bIssucess = CDB_Manager::GetDBManagerPtr()->ExcuteSql(strSQL,iaffact) ; 
	return bIssucess ;
}
// 根据条件获得任务集合
bool CTaskManager::GetQCTask(CString strCond)
{
	CString strSql ;
	strSql.Format("select * from tb_task %s", strCond) ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSql) ;
	if ( pRes == NULL)
	{
		return false ;
	}
	int num_rows = pRes->GetResRowCount();
	int num_fields = pRes->GetResFieldCount();
	
	std::vector<Field_DB> vtFields ;
	
	MAP_RES mapres ;
	int icount = 0 ;
	for(int r = 0; r < num_rows; r++)
	{
		icount++ ;
		VT_RES vtRes ;
		for ( int i=0; i<num_fields; i++ )
		{
			int ftype = pRes->GetFieldType(i);
			if ( icount == 1 )
			{
				Field_DB field ;
				field.name = pRes->GetFieldName(i) ;
				field.table = "" ;
				field.type = ftype ;
				vtFields.push_back(field) ;	
			}
			
			CString strval;
			
			switch(ftype)
			{
			case DBFT_Int:
				{
					strval.Format("%d",pRes->GetResIntValue(r,i));
					break;
				}
			case DBFT_Double:
				{
					strval.Format("%f",pRes->GetResDoubleValue(r,i));
					break;
				}
			case DBFT_Bigint:
				{
					strval.Format("%I64d",pRes->GetResBigIntValue(r,i));
					break;
				}
			case DBFT_String:
				{
					strval.Format("%s",pRes->GetResStringValue(r,i));
					break;
				}
			}
			
			vtRes.push_back(strval.GetBuffer(0)) ;
		}
		mapres.insert(MAP_RES::value_type(icount,vtRes)) ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	
	if ( mapres.empty() )
	{
		return false;
	}

	
	
	CDBFieldInfo *pFieldInfo = NULL ;
	CDBValue *pValue = NULL ;
	MAP_RES::iterator it ;
	
	for ( it=mapres.begin(); it!=mapres.end(); it++ )
	{
		CQCTask *pTask = new CQCTask() ;
		VT_RES vtres = it->second ;
		for ( int i=0; i<num_fields; i++ )
		{
			int mysqltype = vtFields.at(i).type ;
			pFieldInfo = new CDBFieldInfo(vtFields[i].name,vtFields[i].table,mysqltype) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(mysqltype));//再单独设置一下
			pValue = new CDBValue ;
			pTask->AddField(pFieldInfo, pValue) ;
			CString strval = vtres.at(i).c_str() ;
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pTask->SetIntByIndex(i,atoi(strval) ) ;
				break;
			case DBFT_Bigint:
				pTask->SetInt64ByIndex(i,_atoi64(strval) ) ;
				break;
			case DBFT_Double:
				pTask->SetDoubleByIndex(i, atof(strval) ) ;
				break;
			case DBFT_String:
				pTask->SetStringByIndex(i,strval) ;
				break;
			}
		}
		int iIndex = pTask->GetIndex("blockid") ;
		__int64 iblockid = pTask->GetInt64ByIndex(iIndex) ;
		if ( iblockid > 0 )
		{
			CTaskBlock *pBlock = CreateTaskBlock(iblockid);
			pTask->SetTaskBlock(pBlock) ;
		}
		pTask->LoadLinkInfo() ;
		m_vtqctask.push_back(pTask) ;
	}
	return true ;

}
// 获得单位任务
CQCTask *CTaskManager::GetQCTaskByIndex(int iIndex) 
{
	if ( iIndex <0 || iIndex >GetQCTaskCount() )
	{
		return NULL ;
	}
	return m_vtqctask.at(iIndex) ;
}
// 获得任务个数
int CTaskManager::GetQCTaskCount() 
{
	return m_vtqctask.size() ;
}
// 释放任务指针
void CTaskManager::ReleaseQCTask()
{
	for ( int i=0; i<GetQCTaskCount(); i++ )
	{
		CQCTask *p = m_vtqctask.at(i) ;
		if ( p != NULL )
		{
			delete p ;
			p = NULL ;
		}
	}
	m_vtqctask.clear() ;
}

void CTaskManager::GetItemSetInfo(CString strCond)
{
	CString strSQL ;
	strSQL.Format("select * from tb_itemset %s",strCond) ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
	if ( pRes == NULL )
	{
		return ;
	}
	int num_rows = pRes->GetResRowCount();
	int num_fields = pRes->GetResFieldCount();
	
	std::vector<Field_DB> vtFields ;
	
	MAP_RES mapres ;
	int icount = 0 ;
	for(int r = 0; r < num_rows; r++)
	{
		icount++ ;
		VT_RES vtRes ;
		for ( int i=0; i<num_fields; i++ )
		{
			int ftype = pRes->GetFieldType(i);
			if ( icount == 1 )
			{
				Field_DB field ;
				field.name = pRes->GetFieldName(i) ;
				field.table = "" ;
				field.type = ftype ;
				vtFields.push_back(field) ;	
			}
			
			CString strval;
			
			switch(ftype)
			{
			case DBFT_Int:
				{
					strval.Format("%d",pRes->GetResIntValue(r,i));
					break;
				}
			case DBFT_Double:
				{
					strval.Format("%f",pRes->GetResDoubleValue(r,i));
					break;
				}
			case DBFT_Bigint:
				{
					strval.Format("%I64d",pRes->GetResBigIntValue(r,i));
					break;
				}
			case DBFT_String:
				{
					strval.Format("%s",pRes->GetResStringValue(r,i));
					break;
				}
			}
			
			vtRes.push_back(strval.GetBuffer(0)) ;
		}
		mapres.insert(MAP_RES::value_type(icount,vtRes)) ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	

	if ( mapres.empty() )
	{
		return ;
	}

	
	CDBFieldInfo *pFieldInfo = NULL ;
	CDBValue *pValue = NULL ;
	MAP_RES::iterator it ;
// 	while ( (row = mysql_fetch_row( &pTempRes)) != NULL)
	for ( it=mapres.begin(); it!=mapres.end(); it++ )
	{
		CTaskLinkItemSet *pItemSet = new CTaskLinkItemSet() ;
		VT_RES vtres = it->second ;
		for ( int i=0; i<num_fields; i++ )
		{
			int mysqltype = vtFields.at(i).type ;
			pFieldInfo = new CDBFieldInfo(vtFields[i].name,vtFields[i].table,mysqltype) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(mysqltype));//再单独设置一下
			pValue = new CDBValue ;
			pItemSet->AddField(pFieldInfo, pValue) ;
			CString strval = /*row[i]*/vtres.at(i).c_str() ;
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pItemSet->SetIntByIndex(i,atoi(strval) ) ;
				break;
			case DBFT_Bigint:
				pItemSet->SetInt64ByIndex(i,_atoi64(strval) ) ;
				break;
			case DBFT_Double:
				pItemSet->SetDoubleByIndex(i, atof(strval) ) ;
				break;
			case DBFT_String:
				pItemSet->SetStringByIndex(i,strval) ;
				break;
			}
		}
		int iIndex = pItemSet->GetIndex("id") ;
		__int64 iitemsetid = pItemSet->GetInt64ByIndex(iIndex) ;
		pItemSet->SetItemSetID(iitemsetid);
		pItemSet->LoadLinkInfo() ;

		m_vtItemset.push_back(pItemSet) ;
	}
	
}

void CTaskManager::ReleaseItemset()
{
	for ( int i=0; i<GetItemSetCount(); i++ )
	{
		CTaskLinkItemSet *p = m_vtItemset.at(i) ;
		if ( p!= NULL )
		{
			delete p ;
			p = NULL ;
		}
	}
	m_vtItemset.clear() ;
}

int CTaskManager::GetItemSetCount()
{
	return m_vtItemset.size() ;
}

CTaskLinkItemSet *CTaskManager::GetTaskLinkItemSetByIndex(int iIndex)
{
	if ( iIndex < 0 || iIndex > GetItemSetCount() )
	{
		return NULL ;
	}
	return m_vtItemset.at(iIndex) ;
}

/// 从数据库中获取没有执行的最开始的任务一个任务
CQCTask *CTaskManager::GetLastTask(int itasktype) 
{
	SYSTEMTIME st;
	CString strTime;
	GetLocalTime(&st);
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	
	CString strSql ;
	strSql.Format("begin;lock table tb_task in ACCESS EXCLUSIVE MODE") ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	int iaffact = 0;
	CDB_Manager::GetDBManagerPtr()->ExcuteSql(strSql,iaffact) ;
	strSql.Format("select *,json_extract(referdata,'$.qc') as 'qc',json_extract(referdata,'$.field') as 'field',"
		"json_extract(referdata,'$.tool') as 'tool',json_extract(referdata,'$.edit') as 'edit'"
		"from tb_task where tasktype=%d and state=10 order by id asc limit 1", itasktype) ;
	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSql) ;
	if ( pRes == NULL)
	{
		strSql.Format("end;") ;
		CDB_Manager::GetDBManagerPtr()->ExcuteSql(strSql,iaffact) ;
		return NULL ;
	}
	int num_rows = pRes->GetResRowCount();
	int num_fields = pRes->GetResFieldCount();
	
	std::vector<Field_DB> vtFields ;
	
	MAP_RES mapres ;
	int icount = 0 ;
	for(int r = 0; r < num_rows; r++)
	{
		icount++ ;
		VT_RES vtRes ;
		for ( int i=0; i<num_fields; i++ )
		{
			int ftype = pRes->GetFieldType(i);
			if ( icount == 1 )
			{
				Field_DB field ;
				field.name = pRes->GetFieldName(i) ;
				field.table = "" ;
				field.type = ftype ;
				vtFields.push_back(field) ;	
			}
			
			CString strval;
			
			switch(ftype)
			{
			case DBFT_Int:
				{
					strval.Format("%d",pRes->GetResIntValue(r,i));
					break;
				}
			case DBFT_Double:
				{
					strval.Format("%f",pRes->GetResDoubleValue(r,i));
					break;
				}
			case DBFT_Bigint:
				{
					strval.Format("%I64d",pRes->GetResBigIntValue(r,i));
					break;
				}
			case DBFT_String:
				{
					strval.Format("%s",pRes->GetResStringValue(r,i));
					break;
				}
			}
			
			vtRes.push_back(strval.GetBuffer(0)) ;
		}
		mapres.insert(MAP_RES::value_type(icount,vtRes)) ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	
	if ( mapres.empty() )
	{
		strSql.Format("end;") ;
		int iaffact = 0;
		CDB_Manager::GetDBManagerPtr()->ExcuteSql(strSql,iaffact) ;
		return NULL;
	}
		
	CDBFieldInfo *pFieldInfo = NULL ;
	CDBValue *pValue = NULL ;
	MAP_RES::iterator it ;
	CQCTask *pTask = new CQCTask() ;
	for ( it=mapres.begin(); it!=mapres.end(); it++ )
	{
		VT_RES vtres = it->second ;
		for ( int i=0; i<num_fields; i++ )
		{
			int mysqltype = vtFields.at(i).type ;
			pFieldInfo = new CDBFieldInfo(vtFields[i].name,vtFields[i].table,mysqltype) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(mysqltype));//再单独设置一下
			pValue = new CDBValue ;
			pTask->AddField(pFieldInfo, pValue) ;
			CString strval = vtres.at(i).c_str() ;
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pTask->SetIntByIndex(i,atoi(strval) ) ;
				break;
			case DBFT_Bigint:
				pTask->SetInt64ByIndex(i,_atoi64(strval) ) ;
				break;
			case DBFT_Double:
				pTask->SetDoubleByIndex(i, atof(strval) ) ;
				break;
			case DBFT_String:
				pTask->SetStringByIndex(i,strval) ;
				break;
			}
		}
		int iIndex = pTask->GetIndex("blockid") ;
		__int64 iblockid = pTask->GetInt64ByIndex(iIndex) ;
		iIndex = pTask->GetIndex("state") ;
		int state = pTask->GetIntByIndex(iIndex) ;
		pTask->SetIntByIndex(iIndex,11) ;
		iIndex = pTask->GetIndex("starttime") ;
		pTask->SetStringByIndex(iIndex,strTime) ;
		if ( pTask->GetIntByIndex(pTask->GetIndex("process")) == 5 )
		{
			pTask->SetIntByIndex(pTask->GetIndex("process"), 51) ;
		}
		else if ( pTask->GetIntByIndex(pTask->GetIndex("process")) == 51 )
		{
			pTask->SetIntByIndex(pTask->GetIndex("process"), 52) ;
		}
		UpdataQCTask(pTask) ;
		strSql.Format("end;") ;
		int iaffact = 0;
		CDB_Manager::GetDBManagerPtr()->ExcuteSql(strSql,iaffact) ;

		if ( iblockid > 0 )
		{
			CTaskBlock *pBlock = CreateTaskBlock(iblockid);
			pTask->SetTaskBlock(pBlock) ;
		}
		pTask->LoadLinkInfo() ;
	}
	return pTask ;
}

CQCTask *CTaskManager::GetLastTask(const char *szcond) 
{
	SYSTEMTIME st;
	CString strTime;
	GetLocalTime(&st);
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	
	CString strSql ;
	//strSql.Format("lock table tb_task write") ;
	strSql.Format("BEGIN;lock table tb_task in ACCESS EXCLUSIVE MODE;") ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	int iaffact = 0;
	CDB_Manager::GetDBManagerPtr()->ExcuteSql(strSql,iaffact) ;
// 	strSql.Format("select * from tb_task %s order by id asc limit 1", szcond) ;
	strSql.Format("select * from tb_task %s limit 1", szcond) ;
	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSql) ;
	if ( pRes == NULL)
	{
		strSql.Format("END;") ;
		int iaffact = 0;
		CDB_Manager::GetDBManagerPtr()->ExcuteSql(strSql,iaffact) ;
		return NULL ;
	}
	int num_rows = pRes->GetResRowCount();
	int num_fields = pRes->GetResFieldCount();
	
	std::vector<Field_DB> vtFields ;
	
	MAP_RES mapres ;
	int icount = 0 ;
	for(int r = 0; r < num_rows; r++)
	{
		icount++ ;
		VT_RES vtRes ;
		for ( int i=0; i<num_fields; i++ )
		{
			int ftype = pRes->GetFieldType(i);
			if ( icount == 1 )
			{
				Field_DB field ;
				field.name = pRes->GetFieldName(i) ;
				field.table = "" ;
				field.type = ftype ;
				vtFields.push_back(field) ;	
			}
			
			CString strval;
			
			switch(ftype)
			{
			case DBFT_Int:
				{
					strval.Format("%d",pRes->GetResIntValue(r,i));
					break;
				}
			case DBFT_Double:
				{
					strval.Format("%f",pRes->GetResDoubleValue(r,i));
					break;
				}
			case DBFT_Bigint:
				{
					strval.Format("%I64d",pRes->GetResBigIntValue(r,i));
					break;
				}
			case DBFT_String:
				{
					strval.Format("%s",pRes->GetResStringValue(r,i));
					break;
				}
			}
			
			vtRes.push_back(strval.GetBuffer(0)) ;
		}
		mapres.insert(MAP_RES::value_type(icount,vtRes)) ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	
	if ( mapres.empty() )
	{
		strSql.Format("END;") ;
		int iaffact = 0;
		CDB_Manager::GetDBManagerPtr()->ExcuteSql(strSql,iaffact) ;
		return NULL;
	}
		
	CDBFieldInfo *pFieldInfo = NULL ;
	CDBValue *pValue = NULL ;
	MAP_RES::iterator it ;
	CQCTask *pTask = new CQCTask() ;
	for ( it=mapres.begin(); it!=mapres.end(); it++ )
	{
		VT_RES vtres = it->second ;
		for ( int i=0; i<num_fields; i++ )
		{
			int mysqltype = vtFields.at(i).type ;
			pFieldInfo = new CDBFieldInfo(vtFields[i].name,vtFields[i].table,mysqltype) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(mysqltype));//再单独设置一下
			pValue = new CDBValue ;
			pTask->AddField(pFieldInfo, pValue) ;
			CString strval = vtres.at(i).c_str() ;
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pTask->SetIntByIndex(i,atoi(strval) ) ;
				break;
			case DBFT_Bigint:
				pTask->SetInt64ByIndex(i,_atoi64(strval) ) ;
				break;
			case DBFT_Double:
				pTask->SetDoubleByIndex(i, atof(strval) ) ;
				break;
			case DBFT_String:
				pTask->SetStringByIndex(i,strval) ;
				break;
			}
		}
		int iIndex = pTask->GetIndex("blockid") ;
		__int64 iblockid = pTask->GetInt64ByIndex(iIndex) ;
		iIndex = pTask->GetIndex("state") ;
		int state = pTask->GetIntByIndex(iIndex) ;
		pTask->SetIntByIndex(iIndex,11) ;
		iIndex = pTask->GetIndex("starttime") ;
		pTask->SetStringByIndex(iIndex,strTime) ;
		int process = pTask->GetIntByIndex(pTask->GetIndex("process")) ;
		if ( process == 5 )
		{
			pTask->SetIntByIndex(pTask->GetIndex("process"), 51) ;
		}
		else if ( process == 51 )
		{
			pTask->SetIntByIndex(pTask->GetIndex("process"), 52) ;
		}

		UpdataQCTask(pTask) ;
		strSql.Format("END;") ;
		int iaffact = 0;
		CDB_Manager::GetDBManagerPtr()->ExcuteSql(strSql,iaffact) ;
		if ( iblockid > 0 )
		{
			CTaskBlock *pBlock = CreateTaskBlock(iblockid);
			pTask->SetTaskBlock(pBlock) ;
			
		}
		pTask->LoadLinkInfo() ;
	}

	return pTask ;
}

// 保存任务
bool CTaskManager::UpdataQCTask( CQCTask *pQCTask )
{
	if ( pQCTask == NULL)
	{
		return false ;
	}

	int state = pQCTask->GetIntByIndex(pQCTask->GetIndex("state")) ;
	int process = pQCTask->GetIntByIndex(pQCTask->GetIndex("process")) ;
	CString starttime = pQCTask->GetStringByIndex(pQCTask->GetIndex("starttime")) ;
	CString endtime = pQCTask->GetStringByIndex(pQCTask->GetIndex("endtime")) ;
	CString time = pQCTask->GetStringByIndex(pQCTask->GetIndex("time")) ;
	CString ip = pQCTask->GetStringByIndex(pQCTask->GetIndex("ip")) ;
	__int64 id = pQCTask->GetInt64ByIndex(pQCTask->GetIndex("id")) ;

	CString sql = "" ;
	if ( endtime != "")
	{
		sql.Format("update tb_task set state=%d,process=%d,starttime='%s',endtime='%s',time='%s',ip='%s' where id=%I64d",
			state, process, starttime, endtime, time, ip,id) ;
	}
	else if( starttime != "")
	{
		sql.Format("update tb_task set state=%d,process=%d,starttime='%s',time='%s',ip='%s' where id=%I64d",
			state, process, starttime, time, ip,id) ;
	}
	else
	{
		sql.Format("update tb_task set state=%d,process=%d,time='%s',ip='%s' where id=%I64d",
			state, process, time, ip,id) ;
	}
	CDB_Manager::GetDBManagerPtr()->ChooseDB( DB_TASK_PGSQL) ;
	int iaffact = 0;
	return CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql,iaffact) ;
}

//判断某一类型的项目是否创建过任务
CString CTaskManager::JudgeProjectHaveCreateTask(__int64 iProjectid, int iTaskType)
{
	
	CString str = "";
	
	CString sql;
	sql.Format("select * from tb_task where projectid=%I64d and tasktype=%d",iProjectid,iTaskType);
	
	
	CDB_ResultSet* pRes = NULL;

	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	
	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(sql);
	if(pRes != NULL && pRes->GetResRowCount() > 0)
	{
		str.Format("此项目此类型的任务已经创建过了不能再创建了");
		
		CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
		return str;
		
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;

	return str;
}

//同步类型为"导入任务"的信息
void CTaskManager::SyncImportTaskInfo(CTask* pTask)
{
	if(!pTask) return;
	
	CString strPoiids;
	CTaskBlock *pBlock = pTask->GetTaskBlock() ;
	if ( pBlock == NULL )
	{
		return ;
	}
	int count = pBlock->GetTaskBlockDetailCount() ;
	CTaskBlockDetail *pDetail = pBlock->GetFirstTaskBlockDetailPtr() ;
	while ( pDetail != NULL )
	{
		int iIndex = pDetail->GetIndex("featureid") ;
		__int64 id = pDetail->GetInt64ByIndex(iIndex) ;
		CString str;
		str.Format("%I64d,",id);
		
		strPoiids += str;
	}
	
	if(strPoiids.Right(1) == ",")
	{
		strPoiids = strPoiids.Left(strPoiids.GetLength()-1);
	}
	
	if(strPoiids.IsEmpty()) strPoiids = "-1";
	
	CString sql;
	sql.Format("insert into tb_task_link_fielddata(taskid,shapeid,poitempid,distance,lroadid,rroadid) select %I64d,shapeid,poitempid,0,0,0 from tb_task_link_fielddata "
		"inner join tb_task on tb_task.id=tb_task_link_fielddata.taskid where tb_task.projectid=%I64d and tb_task.tasktype=%d and tb_task_link_fielddata.poitempid in(%s);",pTask->GetID(),pTask->GetProjectId(),TASKTYPE_IMPORT,strPoiids);
	
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	int iaffact = 0;
	CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql,iaffact);
	
	sql.Format("insert into tb_task_link_attach(taskid,attachid,shapeid,poitempid) select %I64d,attachid,shapeid,poitempid from tb_task_link_attach "
		"inner join tb_task on tb_task.id=tb_task_link_attach.taskid where tb_task.projectid=%I64d and tb_task.tasktype=%d and tb_task_link_attach.poitempid in(%s);",pTask->GetID(),pTask->GetProjectId(),TASKTYPE_IMPORT,strPoiids);
	CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql,iaffact);
}

CString CTaskManager::JudgeProjectHaveDonePTask(__int64 iProjectid, int iProjectType)
{
	CString str = "";
	
// 	CString sql;
// 	sql.Format("select * from tb_task where projectid=%I64d and tasktype in(%d,%d,%d,%d) and state=3",iProjectid,
// 		TASKTYPE_FOOT_PRORERTYNEWADD,//平板属性新增任务
// 		TASKTYPE_FOOT_PRORERTYNEWADDDOOR,//平板属性新增门址任务
// 		TASKTYPE_FOOT_PRORERTYMODIFY,//平板属性修改任务
// 		TASKTYPE_FOOT_PRORERTYMODIFYDOOR//平板属性修改门址任务
// 		);
// 	
// 	
// 	CDB_ResultSet* pRes = NULL;
// 	MYSQL_ROW row;
// 	char* p = NULL;
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_POIEDIT_TASK);
// 	
// 	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(sql);
// 	while( row = mysql_fetch_row( pRes))
// 	{
// 		str.Format("此项目此类型的任务已经编辑玩了");
// 		
// 		return str;
// 		
// 	}
	
	return str;
}

/*
enum_field_types CTaskManager::TransType(int datatype)
{
	enum_field_types field_type = MYSQL_TYPE_STRING ;
	switch ( datatype )
	{
	case DBFT_Int:
		field_type = MYSQL_TYPE_LONG ;
		break;
	case DBFT_Bigint:
		field_type = MYSQL_TYPE_LONGLONG ;
		break;
	case DBFT_Double:
		field_type = MYSQL_TYPE_DOUBLE ;
		break;
	case DBFT_String:
		field_type = MYSQL_TYPE_STRING ;
		break;
	}

	return field_type ;
}
*/

const char* CTaskManager::GetReferdataInfo(CTask *pTask)
{
	if ( pTask == NULL )
	{
		return "" ;
	}
	int iIndex = pTask->GetIndex("id") ;
	if ( iIndex == -1)
	{
		return "" ;
	}
	__int64 iId = pTask->GetInt64ByIndex(iIndex) ;
	if ( iId < 0 )
	{
		return "" ;
	}
	CString strReferdata = "" ;
//////////////////////////////////////////////////////////////////////////
	// 设置qc jsonb
	CString strQCRefer = "" ;
	_TSGEO::SGeoRect bound = pTask->GetQCBound() ;
	_TSGEO::SGeoRect b = _TSGEO::SGeoRect(0,0,0,0) ;
	CString strbound = "" ;
	if ( !(bound == b ))
	{
		strbound.Format("\"bound\":[%f,%f,%f,%f]",bound.x_min,bound.y_min,bound.x_max,bound.y_max) ;
	}
	CString strLayerNames = "" ;
	if ( pTask->GetQCReferLayerCount() > 0)
	{
		strLayerNames = "\"layer\":[" ;
		CString strMid = "" ;
		for (int i=0; i<pTask->GetQCReferLayerCount(); i++ )
		{
			CString strName = pTask->GetQCLayerNameByIndex(i) ;
			if (strName == "")
			{
				continue;
			}
			strName = "\"" + strName + "\"" ;
			if ( strMid != "" )
			{
				strMid += "," ;
			}
			strMid += strName ;
		}
		if ( strMid != "" )
		{
			strMid += "]" ;
			strLayerNames += strMid ;
		}
		else
		{
			strLayerNames = "" ;
		}
	}
	if (strbound != "" && strLayerNames)
	{
		strLayerNames += "," ;
		strLayerNames += strbound ;
		strQCRefer = "\"qc\":{" + strLayerNames + "}" ;
	}
	else
	{
		strQCRefer = "" ;
	}
	strReferdata += strQCRefer ;
	//////////////////////////////////////////////////////////////////////////
	// 设置tool jsonb
	CString strToolRefer = "" ;
	bound = pTask->GetToolBound() ;
	b = _TSGEO::SGeoRect(0,0,0,0) ;
	strbound = "" ;
	if ( !(bound == b ))
	{
		strbound.Format("\"bound\":[%f,%f,%f,%f]",bound.x_min,bound.y_min,bound.x_max,bound.y_max) ;
	}
	strLayerNames = "" ;
	if ( pTask->GetToolReferLayerCount() > 0)
	{
		strLayerNames = "\"layer\":[" ;
		CString strMid = "" ;
		for (int i=0; i<pTask->GetToolReferLayerCount(); i++ )
		{
			CString strName = pTask->GetToolLayerNameByIndex(i) ;
			if (strName == "")
			{
				continue;
			}
			strName = "\"" + strName + "\"" ;
			if ( strMid != "" )
			{
				strMid += "," ;
			}
			strMid += strName ;
		}
		if ( strMid != "" )
		{
			strMid += "]" ;
			strLayerNames += strMid ;
		}
		else
		{
			strLayerNames = "" ;
		}
	}
	if (strbound != "" && strLayerNames)
	{
		strLayerNames += "," ;
		strLayerNames += strbound ;
		strToolRefer = "\"tool\":{" + strLayerNames + "}" ;
		if ( strReferdata != "" )
		{
			strReferdata += "," ;
		}
		strReferdata += strToolRefer ;
	}
	else
	{
		strToolRefer = "" ;
	}
	//////////////////////////////////////////////////////////////////////////
	// 设置edit json
	CString streditrefer = "" ;
	int icount = pTask->GetEditReferLayerCount() ;
	for ( int i=0; i<icount; i++ )
	{
		EditRefer editRefer = pTask->GetEditReferIndex(i);
		_TSGEO::SGeoRect bound = editRefer.bound ;
		b = _TSGEO::SGeoRect(0,0,0,0) ;
		strbound = "" ;
		if ( !(bound == b ))
		{
			strbound.Format("\"bound\":[%f,%f,%f,%f]",bound.x_min,bound.y_min,bound.x_max,bound.y_max) ;
		}
		CString strTem ;
		strTem.Format("{\"layer\":\"%s\",%s}",editRefer.strname.c_str(), strbound) ;
		if ( streditrefer != "")
		{
			streditrefer += "," ;
		}
		streditrefer += strTem ;
	}
	if ( streditrefer != "" )
	{
		streditrefer = "\"edit\":["+streditrefer+"]" ;
		if ( strReferdata != "")
		{
			strReferdata += "," ;
		}
		strReferdata += streditrefer ;
	}
	//////////////////////////////////////////////////////////////////////////
	// 设置field json
	CString strfieldrefer = "" ;
	icount = pTask->GetFieldReferLayerCount() ;
	for ( i=0; i<icount; i++ )
	{
		FieldRefer fieldRefer = pTask->GetFieldReferIndex(i);
		_TSGEO::SGeoRect bound = fieldRefer.bound ;
		b = _TSGEO::SGeoRect(0,0,0,0) ;
		strbound = "" ;
		if ( !(bound == b ))
		{
			strbound.Format("\"bound\":[%f,%f,%f,%f]",bound.x_min,bound.y_min,bound.x_max,bound.y_max) ;
		}
		CString strTem ;
		strTem.Format("{\"layer\":\"%s\",%s,\"batchid\":%I64d}",fieldRefer.strname.c_str(), strbound,fieldRefer.batchid) ;
		if ( strfieldrefer != "")
		{
			strfieldrefer += "," ;
		}
		strfieldrefer += strTem ;
	}
	if ( strfieldrefer != "" )
	{
		strfieldrefer = "\"field\":["+strfieldrefer+"]" ;
		if ( strReferdata != "")
		{
			strReferdata += "," ;
		}
		strReferdata += strfieldrefer ;
	}

	if ( strReferdata != "" )
	{
		strReferdata = "{" + strReferdata + "}" ;
	}
	return strReferdata ;
}

// 根据条件获取iteminfo信息
void CTaskManager::GetItemInfos(const char *szcond) 
{
	CString strSQL ;
	strSQL.Format("select * from tb_iteminfo %s",szcond) ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	CDB_ResultSet* res = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
	if ( res == NULL)
	{
		return ;
	}
	int num_rows = res->GetResRowCount();
	int num_fields = res->GetResFieldCount();
	
	std::vector<Field_DB> vtFields ;
	
	MAP_RES mapres ;
	int icount = 0 ;
	CDBFields *pFields = NULL ;
	for(int r = 0; r < num_rows; r++)
	{
		pFields = new CDBFields() ;
		for ( int i=0; i<num_fields; i++ )
		{
			CDBFieldInfo *pFieldInfo = new CDBFieldInfo(res->GetFieldName(i),"",res->GetFieldType(i)) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(res->GetFieldType(i)));//再单独设置一下
			CDBValue *pValue = new CDBValue ;
			pFields->AddField(pFieldInfo, pValue) ;
	
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pFields->SetIntByIndex(i,res->GetResIntValue(r,i) ) ;
				break;
			case DBFT_Bigint:
				pFields->SetInt64ByIndex(i,res->GetResBigIntValue(r,i) ) ;
				break;
			case DBFT_Double:
				pFields->SetDoubleByIndex(i, res->GetResDoubleValue(r,i) ) ;
				break;
			case DBFT_String:
				pFields->SetStringByIndex(i,res->GetResStringValue(r,i)) ;
				break;
			}
		}
		m_vtItemInfo.push_back(pFields) ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&res) ;
}
// 获得iteminfo信息
int CTaskManager::GetItemInfoCount()
{
	return m_vtItemInfo.size() ;
}
CDBFields *CTaskManager::GetItemInfoByIndex(int index) 
{
	if ( index<0 || index>m_vtItemInfo.size() )
	{
		return NULL ;
	}
	return m_vtItemInfo.at(index) ;
}

void CTaskManager::ReleaseItemInfo()
{
	if ( m_vtItemInfo.size() > 0)
	{
		for ( int i=0; i<m_vtItemInfo.size(); i++ )
		{
			CDBFields *pFields = m_vtItemInfo.at(i) ;
			if ( pFields != NULL )
			{
				delete m_vtItemInfo.at(i) ;
				m_vtItemInfo.at(i) = NULL ;
				pFields = NULL ;
			}
		}
		m_vtItemInfo.clear() ;
	}
}

SYSTEMTIME CTaskManager::GetNewSystemtimeFromChangeRoadTimeTableForBeginTime()
{
	CString sql = "" ;
		
	
	SYSTEMTIME newtime;
	newtime.wYear = 0 ;
	newtime.wMonth = 0 ;
	newtime.wDay = 0 ;
	newtime.wHour = 0 ;
	newtime.wMinute = 0 ;
	newtime.wSecond = 0 ;
	
	sql.Format("select max(begintime) from tb_task_changeroad_time") ;
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	SetChoosingTask() ;
	char szSql[1024];
	int iAffectCount = 0;
	sprintf(szSql,"%s",sql);
	CDB_ResultSet* pRes = NULL;
	
	std::vector<int> vttasktype;
	pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(szSql);
	if( pRes == NULL)
		return newtime;
	
	int rowcount = pRes->GetResRowCount();
	
	if ( rowcount == 0)
	{
		return newtime ;
	}
	CString strmaxtime = pRes->GetResStringValue(0,0) ;
	char stime[1024] ;
	strcpy( stime, strmaxtime) ;
	newtime = Char2Systemtime( stime) ;
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes);

	return newtime ;
}

bool CTaskManager::UpDateBlockToDBNoStatus( CTaskBlock *pTaskBlock )
{
	if ( pTaskBlock == NULL)
	{
		return false ;
	}
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	SetChoosingTask() ;

	CString sql = "" ;
	CTime time = CTime::GetCurrentTime() ;
	CString strtime = time.Format("%Y-%m-%d %H:%M:%S") ;
	
	sql.Format("update tb_task_block set type=%d,envelope=LINESTRINGFROMTEXT('LINESTRING(%f %f,%f %f)'),updatetime='%s',roadnum=%d,errorcount=%d where id=%I64d",pTaskBlock->GetType(),
		pTaskBlock->GetBound().x_min,pTaskBlock->GetBound().y_min, pTaskBlock->GetBound().x_max, pTaskBlock->GetBound().y_max,strtime,pTaskBlock->GetRoadNum(),pTaskBlock->GetErrorCount(),pTaskBlock->GetID()) ;
	int iaffact = 0 ;
	bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql,iaffact) ;
	return bupdate ;
}

bool CTaskManager::CheckIsHasTaskBlockDetail( __int64 blockid, __int64 featureid, int layerid )
{
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	SetChoosingTask() ;

	
	// 检查tb_task_blockdetail表中的一个block是否已经记录了某个对象
	CString sql = "" ;
	sql.Format("select id from tb_task_blockdetail where blockid=%I64d and featureid = %I64d and layerid = %d",blockid, featureid, layerid) ;
	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(sql) ;
	if ( pRes== NULL)
	{
		return false ;
	}
	int rowcount = pRes->GetResRowCount() ;
	bool bexist = false ;
	if ( rowcount > 0)
	{
		bexist = true ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;

	return bexist ;
}

bool CTaskManager::LoadTaskBlockDetailsForBlock( CTaskBlock *pTaskBlock )
{
	if ( pTaskBlock == NULL)
	{
		return false ;
	}
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	SetChoosingTask() ;

	CString sql = "" ;
	sql.Format("select id,blockid,layerid,featureid,updatetime from tb_task_blockdetail where blockid = %I64d", pTaskBlock->GetID()) ;
	
	CDB_ResultSet *pRes =CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(sql) ;
	if ( pRes == NULL)
	{
		return false ;
	}

	int rowcount = pRes->GetResRowCount() ;
	for ( int index = 0; index < rowcount;index ++)
	{
		CTaskBlockDetail *ptaskBlockdetail = new CTaskBlockDetail() ;
		ptaskBlockdetail->SetID(pRes->GetResBigIntValue(index,0)) ;
		ptaskBlockdetail->SetBlockID(pRes->GetResBigIntValue(index,1)) ;
		ptaskBlockdetail->SetLayerID(pRes->GetResIntValue(index,2)) ;
		ptaskBlockdetail->SetFeatureID(pRes->GetResBigIntValue(index,3)) ;
		char stime[100] ;
		strcpy(stime, pRes->GetResStringValue(index,4)) ;
		ptaskBlockdetail->SetCreateTime(Char2Systemtime(stime)) ;
		pTaskBlock->AddTaskBlockDetail( ptaskBlockdetail) ;

	}

	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	
	return true ;
}

bool CTaskManager::GetTaskBlockRoadNum()
{
	// 将以前的内容释放掉
	if ( m_mapTaskBlock.size() == 0)
	{
		return true ;
	}
	CString sql ;
	CString strConfition = "" ;
	MAP_TASK_BLOCK::iterator itblock ;
	CString msg ;
	for ( itblock = m_mapTaskBlock.begin(); itblock != m_mapTaskBlock.end(); itblock++)
	{
		__int64 blockid = itblock->first ;
		msg.Format("%I64d,",blockid) ;
		strConfition += msg ;
	}
	if ( strConfition.Right(1).Compare(",") == 0)
	{
		strConfition = strConfition.Left(strConfition.GetLength()-1) ;
	}
	sql.Format("select blockid,count(*) as roadnum from tb_task_blockdetail where blockid in (%s) and layerid = 1 group by blockid", strConfition) ;
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	SetChoosingTask() ;

	
	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(sql) ;
	if ( pRes == NULL)
	{
		return false ;
	}
	
	int rowcount = pRes->GetResRowCount() ;
	for ( int indexrow = 0; indexrow < rowcount; indexrow++)
	{
		__int64 blockid =  pRes->GetResBigIntValue(indexrow, 0);
		int roadnum =  pRes->GetResIntValue( indexrow, 1);
		itblock = m_mapTaskBlock.find( blockid) ;
		if ( itblock != m_mapTaskBlock.end())
		{
			CTaskBlock *pTaskBlock = itblock->second ;
			if ( pTaskBlock != NULL)
			{
				pTaskBlock->SetRoadNum(roadnum) ;
			}
		}
		
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	return true ;
}

bool CTaskManager::UpdateTaskBlockRoadNumNoTime(CTaskBlock *pTaskBlock)
{
	if ( pTaskBlock == NULL)
	{
		return false ;
	}
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	SetChoosingTask() ;

	CString sql = "" ;
	
	CString strtime = "" ;
	SYSTEMTIME oldtime = pTaskBlock->GetUpdateTime() ;
	strtime.Format("%d-%d-%d %d:%d:%d", oldtime.wYear,oldtime.wMonth,oldtime.wDay,oldtime.wHour,oldtime.wMinute,oldtime.wSecond) ;
	sql.Format("update tb_task_block set updatetime='%s',roadnum=%d where id=%I64d",strtime,pTaskBlock->GetRoadNum(),pTaskBlock->GetID()) ;
	int iaffect = 0;
	bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql,iaffect) ;
	return bupdate ;
}

bool CTaskManager::UpdateTaskBlockRoadNum(CTaskBlock *pTaskBlock)
{
	if ( pTaskBlock == NULL)
	{
		return false ;
	}
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	SetChoosingTask() ;

	CString sql = "" ;
	
	sql.Format("update tb_task_block set roadnum=%d where id=%I64d",pTaskBlock->GetRoadNum(),pTaskBlock->GetID()) ;
	int iaffect = 0 ;
	bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql, iaffect) ;
	return bupdate ;
}

void CTaskManager::SetChoosingTask()
{
	if ( CTaskManager::GetTaskManager()->GetSqlFlag() == POSTGRES_RUNNING)
	{
		CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	}
	else if ( CTaskManager::GetTaskManager()->GetSqlFlag() == MYSQL_RUNING)
	{
		CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_MYSQL);
	}
}

void CTaskManager::SetChoosingError()
{
	if ( GetSqlFlag() == POSTGRES_RUNNING)
	{
		CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_ERRORLOG_PGSQL);
	}
	else if ( GetSqlFlag() == MYSQL_RUNING)
	{
		CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_ERRORLOG_MYSQL);
	}
}

int CTaskManager::GetSqlFlag()
{
	return m_sqlFlag ;
}

void CTaskManager::SetSqlFlag( int flag )
{
	m_sqlFlag = flag ;
}

bool CTaskManager::LoadTaskDetailForNull( std::vector< __int64> &vtblockid, std::vector< int> &vtstatus )
{
	CString sql = "" ;
	if ( CTaskManager::GetTaskManager()->GetSqlFlag() == MYSQL_RUNING)
	{
		sql.Format("select tb_task_block.id from tb_task_block where tb_task_block.`status` not in (5,6,-1,-2) and tb_task_block.id not in (select tb_task_blockdetail.blockid from tb_task_blockdetail,tb_task_block where tb_task_block.`status` not in (5,6,-1,-2) and tb_task_blockdetail.blockid = tb_task_block.id group by tb_task_blockdetail.blockid)" ) ;
	}
	else if ( CTaskManager::GetTaskManager()->GetSqlFlag() == POSTGRES_RUNNING)
	{
		sql.Format("select tb_task_block.id from tb_task_block where tb_task_block.status not in (5,6,-1,-2) and tb_task_block.id not in (select tb_task_blockdetail.blockid from tb_task_blockdetail,tb_task_block where tb_task_block.status not in (5,6,-1,-2) and tb_task_blockdetail.blockid = tb_task_block.id group by tb_task_blockdetail.blockid)" ) ;
	}
	CTaskManager::GetTaskManager()->SetChoosingTask() ;
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB( DB_BLOCKTIME) ;
	

	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql( sql) ;
	if ( pRes == NULL)
	{
		return false ;
	}

	int rowcount = pRes->GetResRowCount() ;
	for ( int indexrow = 0; indexrow < rowcount; indexrow++)
	{
		vtblockid.push_back(pRes->GetResBigIntValue(indexrow, 0)) ;
		vtstatus.push_back(pRes->GetResIntValue( indexrow, 1)) ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	
	return true ;
}
void Split(CString strContent,char ch,std::vector<CString>& strResultArr) //不保留空字符串
{
	int npos;
	CString strResult;
	strResultArr.clear();
	
	npos=strContent.Find(ch);
	if (npos==-1)
	{
		strResultArr.push_back(strContent);
		return;
	}
	
	while (npos!=-1)
	{
		strResult=strContent.Left(npos);
		if(strResult!="")
			strResultArr.push_back(strResult);
		if(npos+1>strContent.GetLength()-1)
			break;
		strContent=strContent.Mid(npos+1);
		npos=strContent.Find(ch);
		if (npos==-1)
			strResultArr.push_back(strContent);
	}
}

bool CTaskManager::LoadTaskDetail(std::vector< __int64> &vtblockid,std::vector< int > &vtlayerid, std::vector< __int64 > &vtfeatureid, 
								  std::vector< int> &vtstatus, std::vector< _TSGEO::SGeoRect > &vtbound, std::vector< CString > &vtupdatetime,
								  std::vector<CString> &vtmanualcheck, std::vector<CString> &vtusername,
								  std::vector<int> &vtblockmanualroadnum, std::vector<CString> &vtblockusername, std::vector<__int64> &vtdetailid,
								  std::vector<int> &vtOwner,std::vector<CString> &vtblockOwner)
{
	_TSGEO::SGeoRect bound ;
	CString sql = "" ;
	//////////////////////////////////////////////////////////////////////////
	// modified at 20171201 
	sql.Format("select tb_task_blockdetail.blockid,tb_task_blockdetail.layerid,tb_task_blockdetail.featureid,\
				tb_task_block.status,st_astext(tb_task_block.envelope),tb_task_block.updatetime,\
				tb_task_blockdetail.manualcheck,tb_task_blockdetail.username,tb_task_block.manualroadnum,\
				tb_task_block.username,tb_task_blockdetail.id,tb_task_blockdetail.owner,tb_task_block.owner from tb_task_blockdetail,tb_task_block \
				where tb_task_block.status not in (5,6,-1,-2) and tb_task_block.id = tb_task_blockdetail.blockid" ) ;
	//////////////////////////////////////////////////////////////////////////
	CTaskManager::GetTaskManager()->SetChoosingTask() ;
	// CDB_Manager::GetDBManagerPtr()->ChooseDB( DB_BLOCKTIME) ;
	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql( sql) ;
	if ( pRes == NULL)
	{
		return false ;
	}
	
	int a = 0 ;
	int rowcount = pRes->GetResRowCount() ;
	for( int indexrow = 0; indexrow < rowcount; indexrow++)
	{
		a++ ;
		__int64 tempblockid = pRes->GetResBigIntValue( indexrow, 0);
		if ( tempblockid == 5874)
		{
			int a = 0 ;
		}
		vtblockid.push_back( pRes->GetResBigIntValue( indexrow, 0)) ;
		vtlayerid.push_back( pRes->GetResIntValue( indexrow, 1));
		vtfeatureid.push_back( pRes->GetResBigIntValue( indexrow, 2)) ;
		vtstatus.push_back(pRes->GetResIntValue( indexrow, 3)) ;
		vtupdatetime.push_back( pRes->GetResStringValue( indexrow, 5)) ;
		// 20180312
		vtmanualcheck.push_back(pRes->GetResStringValue(indexrow,6)) ;
		vtusername.push_back(pRes->GetResStringValue(indexrow,7)) ;
		vtblockmanualroadnum.push_back(pRes->GetResIntValue(indexrow,8)) ;
		vtblockusername.push_back(pRes->GetResStringValue( indexrow,9)) ;
		vtdetailid.push_back(pRes->GetResBigIntValue(indexrow,10)) ;
		vtOwner.push_back( pRes->GetResIntValue(indexrow,11)) ;
		vtblockOwner.push_back( pRes->GetResStringValue(indexrow,12)) ;
		// 20170904
		CString strbound = pRes->GetResStringValue( indexrow, 4);
		_TSGEO::SGeoRect blockbound ;
		//LINESTRING(122.208395 40.674103,122.209871 40.674113)
		int ipos = strbound.Find("(") ;
		if ( ipos != -1)
		{
			strbound = strbound.Mid( ipos+1) ;
			// 122.208395 40.674103,122.209871 40.674113)
			if ( strbound.Right(1) == ")")
			{
				strbound = strbound.Left(strbound.GetLength()-1) ;
				// 122.208395 40.674103,122.209871 40.674113
				vector< CString > vtTemp1 ;
				Split( strbound, ',', vtTemp1) ;
				if ( vtTemp1.size() == 2)
				{
					for ( int i = 0; i < vtTemp1.size(); i++)
					{
						CString strTemp = vtTemp1[i] ;
						vector< CString > vtTemp2 ;
						Split( strTemp, ' ', vtTemp2) ;
						if ( vtTemp2.size() == 2)
						{
							for ( int j = 0; j < vtTemp2.size(); j++)
							{
								CString strtemp2 = vtTemp2[j] ;
								if ( i == 0 && j == 0)
								{
									blockbound.x_min = atof(strtemp2) ;
								}
								else if ( i== 0 && j == 1)
								{
									blockbound.y_min = atof( strtemp2) ;
								}
								else if ( i == 1 && j == 0)
								{
									blockbound.x_max = atof( strtemp2) ;
								}
								else if ( i == 1 && j == 1)
								{
									blockbound.y_max = atof(strtemp2) ;
								}
							}
						}
					}
				}
				
			}
		}
		vtbound.push_back( blockbound) ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	return true ;
}