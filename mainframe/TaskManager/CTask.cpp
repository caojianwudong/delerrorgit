// CTask.cpp: implementation of the CTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskManager.h"
#include "CTask.h"
#include "CTaskManager.h"

#include "CConvertTool.h"
#include <algorithm>

#include "CTaskLinkAttach.h"
#include "CTaskLinkFieldData.h"
#include "CTaskBlock.h"
#include "CTaskBlockDetail.h"
#include "task_definition.h"

#include "CTaskBlock.h"

#include "CDBFields.h"


#include "CDB_Manager.h"
#include "DB_ResultSet.h"
#include "Db_Definition.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTask::CTask()
{
	m_id = 0;
	m_idCheckRoleUser = 0;
	m_idEditRoleUser = 0;
	m_idProject = 0;
	m_iRoleId = 0;
	m_iState = -1;
	m_iTaskType = -1;
	m_ShapeIndex = -1;
	m_sProName = "";
	m_dLastExit = 0;

	m_pBlock = NULL ;
	m_ShapeIndex = 0;
}

CTask::~CTask()
{
	ReleaseTask();
}

void CTask::Clear()
{

	vt_shape_id.clear();
	map_shapeid_poiid.clear();
	map_shapeid_poiid_poiid.clear();
	map_shapeid_picid.clear();
	map_shapeid_picid.clear();
	map_picid_poiid.clear();
	map_poiid_picid.clear();
	map_pic_path.clear();
}

__int64 CTask::GetID()
{
	int index = GetIndex("id");
	if( index != -1)
		return m_id = GetInt64ByIndex(index);
	return -1;
}

void CTask::SetID(__int64 id)
{
	int index = GetIndex("id");
	if( index != -1)
		SetInt64ByIndex(index,id);
	m_id = id;
}

void CTask::SetProjectName(CString sProjectName)
{
	m_sProName = sProjectName;
}

CString CTask::GetProjectName()
{
	return m_sProName;
}

void CTask::SetRoleId(int roleid)
{
	m_iRoleId = roleid;
}

int CTask::GetRoleId()
{
	return m_iRoleId;
}

__int64 CTask::GetBatchId()
{
	int index = GetIndex("batchid");
	if( index == -1)
		return -1;
	m_batchid = GetInt64ByIndex(index);
	return m_batchid;
}

void CTask::SetBatchId(__int64 batchid )
{
	int index = GetIndex("batchid");
	if( index == -1)
		return ;
	SetInt64ByIndex(index , batchid);
	m_batchid = batchid;
}

void CTask::SetLastExit(double lastexit)
{
	m_dLastExit = lastexit;
}

double CTask::GetLastExit()
{
	return m_dLastExit;
}

void CTask::SetEditRoleId(int iEditRoleId)
{
	int index = GetIndex("editid");
	if( index == -1)
		return ;
	SetIntByIndex(index, iEditRoleId);
	m_idEditRoleUser = iEditRoleId;
}

int CTask::GetEditRoleId()
{
	int index = GetIndex("editid");
	if( index == -1)
		return 0;
	m_idEditRoleUser = GetIntByIndex(index);
	return m_idEditRoleUser;
}

void CTask::SetCheckRoleId(int idCheckRole)
{
	m_idCheckRoleUser = idCheckRole;
}

int CTask::GetCheckRoleId()
{
	return m_idCheckRoleUser;
}

void CTask::SetTaskType(int tasktype)
{
	m_iTaskType = tasktype;
}

int CTask::GetTaskType()
{
	return m_iTaskType;
}

void CTask::SetState(int state)
{
	int index = GetIndex("state");
	if( index != -1)
		SetIntByIndex(index,state);
	m_iState = state;
}

int CTask::GetState()
{
	int index = GetIndex("state");
	if( index != -1)
		return m_iState = GetIntByIndex(index);
	return -1;
}

void CTask::SetProcess(int process )
{
	int index = GetIndex("process");
	if( index != -1)
		SetIntByIndex(index,process);
}

int CTask::GetProcess()
{
	int index = GetIndex("process");
	if( index != -1)
		return  GetIntByIndex(index);
	return -1;
}

void CTask::SetProjectId(__int64 id)
{
	int index = GetIndex("projectid");
	if( index != -1)
		SetInt64ByIndex(index,id);
	m_idProject = id;
}

__int64 CTask::GetProjectId()
{
	int index = GetIndex("projectid");
	if( index != -1)
		return  m_idProject = GetInt64ByIndex(index);
	return -1;
}

void CTask::SetReferData(CString strRefer)
{
	m_strRefer = strRefer;
}

CString CTask::GetReferData()
{
	return m_strRefer;
}

void CTask::ReleaseTask()
{
	MAP_SHAPEID_FIELDDATA::iterator iter;
	for ( iter = map_taskLinkFieldData.begin(); iter != map_taskLinkFieldData.end(); iter++ )
	{
		
		CTaskLinkFieldData* pFieldData = iter->second;
		if( pFieldData == NULL)
			continue;
		delete pFieldData;
		pFieldData = NULL;
		
	}
	map_taskLinkFieldData.clear();
	
	int iSizeAttach = vt_taskLinkAttach.size();
	for ( int j = 0 ; j < iSizeAttach;  j++)
	{
		CTaskLinkAttach* pAttach = vt_taskLinkAttach.at(j);
		if( pAttach == NULL)
			continue;
		delete pAttach;
		pAttach = NULL;
	}
	vt_taskLinkAttach.clear();

	if ( m_pBlock != NULL )
	{
		delete m_pBlock ;
		m_pBlock = NULL ;
	}
	Clear();
}

int  CTask::GetLinkDbFieldDataCount()
{
	return map_taskLinkFieldData.size();
}

CTaskLinkFieldData* CTask::GetLinkFieldDataByIndex(int index)
{
	int inx = 0;
	CTaskLinkFieldData* pFieldData = NULL;
	MAP_SHAPEID_FIELDDATA::iterator iter;
	for ( iter = map_taskLinkFieldData.begin(); iter != map_taskLinkFieldData.end() ;iter++ )
	{
		pFieldData = iter->second;
		if( inx == index)
		{
			break;
		}
		pFieldData = NULL;
		inx++;
	}
	return pFieldData;
}

bool CTask::GetPoiIdByShapeid(__int64 shapeid ,vtDef* pvtDef)
{
	MAP_SHAPEID_FIELDDATA::iterator iterlow = map_taskLinkFieldData.lower_bound(shapeid);
	MAP_SHAPEID_FIELDDATA::iterator iterup  = map_taskLinkFieldData.upper_bound(shapeid);
	MAP_SHAPEID_FIELDDATA::iterator iter    ;
	for (  iter = iterlow; iter != iterup ; iter++ )
	{
		CTaskLinkFieldData* pFieldData = iter->second;
		if( pFieldData == NULL)
			continue;
		pvtDef->vt.push_back(pFieldData->GetFeatureId());
	}
	return true;
}

bool CTask::GetPicIdByShapeid(__int64 shapeid ,vtDef* pvtdef)
{
	if( pvtdef == NULL)
		return false;
	std::vector<CTaskLinkAttach* >::iterator iter ;
	for (  iter = vt_taskLinkAttach.begin(); iter != vt_taskLinkAttach.end() ; iter++ )
	{
		CTaskLinkAttach* pAttach = *iter;
		if( pAttach == NULL)
			continue;
		if( pAttach->GetShapeId() == shapeid)
			pvtdef->vt.push_back( pAttach->GetAttachId());
	}
	return true;
}

bool CTask::GetPicIdByPoiid(__int64 poiid, vtDef* pvtdef)
{
	if( pvtdef == NULL)
		return false;
	std::vector<CTaskLinkAttach* >::iterator iter ;
	for (  iter = vt_taskLinkAttach.begin(); iter != vt_taskLinkAttach.end() ; iter++ )
	{
		CTaskLinkAttach* pAttach = *iter;
		if( pAttach == NULL)
			continue;
		if( pAttach->GetFeatureid() == poiid)
			pvtdef->vt.push_back( pAttach->GetAttachId());
	}
	return true;
}

int CTask::GetLinkAttachCount()
{
	int iSize = vt_taskLinkAttach.size();
	return iSize;
}

CTaskLinkAttach* CTask::GetLinkAttachByIndex(int index)
{
	int iSize = vt_taskLinkAttach.size();
	if( index < 0 || index >= iSize)
		return NULL;
	return vt_taskLinkAttach.at(index);
}

bool CTask::GetPoiIdByPicid(__int64 picid, vtDef* pvtdef)
{
	if( pvtdef == NULL)
		return false;
	std::vector<CTaskLinkAttach* >::iterator iter ;
	for (  iter = vt_taskLinkAttach.begin(); iter != vt_taskLinkAttach.end() ; iter++ )
	{
		CTaskLinkAttach* pAttach = *iter;
		if( pAttach == NULL)
			continue;
		if( pAttach->GetAttachId() == picid)
			pvtdef->vt.push_back( pAttach->GetFeatureid());
	}
	return true;
}

void CTask::SetCurrentShapeIndex(int index)
{
	m_ShapeIndex = index;
}

int CTask::GetCurrentShapeIndex()
{
	return m_ShapeIndex;
}

CTaskLinkFieldData* CTask::GetCurrentFieldData()
{
	int index = 0;
	CTaskLinkFieldData* pLinkFieldData = NULL;
	int iSize = vt_shape_id.size();
	if( m_ShapeIndex < 0 || m_ShapeIndex >= iSize)
		return NULL;
	__int64 shapeid = vt_shape_id.at( m_ShapeIndex );
	
	return  pLinkFieldData;
}

__int64 CTask::GetCurrentShapeId()
{
	int iSize = vt_shape_id.size();
	if( m_ShapeIndex < 0 || m_ShapeIndex >= iSize)
		return 0;
	__int64 shapeid = vt_shape_id.at( m_ShapeIndex );
	return  shapeid;
}

bool CTask::InitData()
{
	/* 资料关联模式一
	    根据外业资料id,求取外业资料id和poiid的关联关系，外业资料id和照片id的关联关系
		求取外业资料关联的poi，这些poiid与照片id的关联关系
		求取照片与poiid的关联关系
	*/
// 	if (	m_iTaskType  ==  TASKTYPE_FOOT_PRORERTY //2000,//平板步调属性任务shape
// 		|| 	m_iTaskType  ==  TASKTYPE_FOOT_PRORERTYERROR //2001,//平板属性改错任务shape
// 		||  m_iTaskType  ==  TASKTYPE_FOOT_PRORERTYNEWADD //2002,//平板属性新增任务
// 		||  m_iTaskType  ==  TASKTYPE_FOOT_PRORERTYNEWADDDOOR //= 2003,//平板属性新增门址任务
// 		||  m_iTaskType  ==  TASKTYPE_FOOT_PRORERTYMODIFY //2004,//平板属性修改任务
// 		||  m_iTaskType  ==  TASKTYPE_FOOT_PRORERTYMODIFYDOOR //= 2005,//平板属性修改门址任务
// 		||  m_iTaskType  ==  TASKTYPE_FOOT_GEOMETRY //2100,//平板步调几何任务
// 		||  m_iTaskType  ==  TASKTYPE_FOOT_GEOMETRYERROR //2101,//车调几何改错任务
// 		||  m_iTaskType  ==  TASKTYPE_CAR_PRORERTY  // 3000,//车调属性任务shape
// 		||	m_iTaskType  ==  TASKTYPE_CAR_PRORERTYERROR   //3001,//车调属性改错任务
// 		||	m_iTaskType  ==  TASKTYPE_CAR_GEOMETRY //3100,//车调几何任务(增加轨迹绘制)
// 		||	m_iTaskType  ==  TASKTYPE_CAR_GEOMETRYERROR //3101,//车调几何改错任务
// 		||	m_iTaskType  ==  TASKTYPE_NET_PRORERTY //4000,//非实测属性任务shape
// 		||  m_iTaskType  ==  TASKTYPE_NET_PRORERTYERROR //4001,//非实测属性改错任务shape
// 		||	m_iTaskType  ==  TASKTYPE_NET_GEOMETRY //4100,//非实测几何任务
// 		||  m_iTaskType  ==  TASKTYPE_NET_GEOMETRYERROR //4101,//非实测几何改错任务
// 		||  m_iTaskType  ==  TASKTYPE_COMPLANIT_PRORERTY //5000,//客投属性任务
// 		||  m_iTaskType  ==  TASKTYPE_COMPLANIT_PRORERTYERROR //5001,//客投属性改错任务
// 		||  m_iTaskType  ==  TASKTYPE_COMPLANIT_GEOMETRY  //5100,//客投几何任务 目前只有这个任务有shape
// 		||  m_iTaskType  ==  TASKTYPE_COMPLANIT_GEOMETRYERROR //5101,//客投几何改错任务 shape
// 		||  m_iTaskType  ==  TASKTYPE_CROW_PRORERTYERROR // 8001,//众包属性改错任务
// 		||  m_iTaskType  ==  TASKTYPE_CROW_GEOMETRY //8100,//众包几何任务
// 		||  m_iTaskType  ==  TASKTYPE_ROADCHANGE_GEOMETRY // 9100,//临时定义道路变化
// 		)
	{
		std::vector<__int64> vt_poiidtmp;//关联外业资料的POI
		std::vector<__int64> vt_picidtmp;
		int iFieldDataCount = GetLinkDbFieldDataCount();
		for ( int i = 0 ;  i < iFieldDataCount ; i++ )
		{
			CTaskLinkFieldData* pFieldData = GetLinkFieldDataByIndex(i);
			if( pFieldData == NULL)
				continue;
			std::vector<__int64>::iterator iter = std::find(vt_shape_id.begin(),vt_shape_id.end(),pFieldData->GetShapeId());
			if( iter == vt_shape_id.end())
				vt_shape_id.push_back( pFieldData->GetShapeId() );
			std::vector<__int64>::iterator iter2 = std::find(vt_poiidtmp.begin(),vt_poiidtmp.end() ,pFieldData->GetFeatureId());
			if ( iter2 == vt_poiidtmp.end())
			{
				vt_poiidtmp.push_back(pFieldData->GetFeatureId());
			}
		}
		
		
		int iShapeCount = vt_shape_id.size();
		for ( int j = 0 ; j< iShapeCount ; j++ )
		{
			std::vector<__int64> vt_picid;
			vtDef vtdef_poiid;
			vtDef vtdef_picid;
			__int64 shapeid = vt_shape_id.at(j);
			GetPoiIdByShapeid(shapeid,&vtdef_poiid);
			map_shapeid_poiid.insert(std::make_pair(shapeid,vtdef_poiid.vt));
			
			GetPicIdByShapeid(shapeid,&vtdef_picid);
			map_shapeid_picid.insert(std::make_pair(shapeid , vtdef_picid.vt));
			
		}
		
		int iPoiCount = vt_poiidtmp.size();
		for ( int k = 0 ; k < iPoiCount ; k++ )
		{
			vtDef vtdef;
			__int64 poiid = vt_poiidtmp.at(k);
			GetPicIdByPoiid(poiid,&vtdef);
			map_poiid_picid.insert( std::make_pair( poiid,vtdef.vt));
		}
		
		int iAttachCount = GetLinkAttachCount();
		for ( int m = 0 ; m < iAttachCount ; m++)
		{
			CTaskLinkAttach* pAttach = GetLinkAttachByIndex( m );
			if( pAttach == NULL)
				continue;
			std::vector<__int64>::iterator iter = std::find(vt_picidtmp.begin(),vt_picidtmp.end() , pAttach->GetAttachId() );
			if( iter == vt_picidtmp.end())
				vt_picidtmp.push_back( pAttach->GetAttachId());
		}
		int iPicCount = vt_picidtmp.size();
		for ( int n = 0 ; n < iPicCount ; n++ )
		{
			vtDef vtdef_poiid;
			__int64 picid = vt_picidtmp.at(n);
			bool bGet = GetPoiIdByPicid(picid,&vtdef_poiid);
			if( bGet )
				map_picid_poiid.insert( std::make_pair( picid,vtdef_poiid.vt));
		}

		/////////////////////////////////////////////////////////////////////////
	}//if ( m_iTaskType  ==  TASKTYPE_FOOT_PRORERTY   )
	
	return true;
}

bool CTask::GetPicByShapeId(__int64 shapeid,vtDef* pvtDef)
{
	if( pvtDef == NULL)
		return false;
	std::map<__int64,std::vector<__int64> >::iterator iter;
	iter = map_shapeid_picid.find(shapeid);
	if( iter == map_shapeid_picid.end())
		return false;
	pvtDef->vt = iter->second;
	return true;
}

bool CTask::GetPoiByPicId(__int64 picid,std::vector<__int64> &vt)
{
	std::map<__int64,std::vector<__int64> >::iterator iter;
	iter = map_picid_poiid.find(picid);
	if( iter == map_picid_poiid.end())
		return false;
	vt= iter->second;
	return true;
}

int CTask::GetFieldDataCount()
{
	int iCount = vt_shape_id.size();
	return iCount;
}

__int64 CTask::GetShapeIdByIndex(int index)
{
	int iCount = GetFieldDataCount();
	if( index < 0 || index >= iCount)
		return 0;
	return vt_shape_id.at(index);
}


CString CTask::GetPicPathByPicid(__int64 picid)
{
	std::map<__int64,CString >::iterator iter = map_pic_path.find(picid);
	if( iter == map_pic_path.end())
		return "";
	return iter->second;
}

__int64 CTask::GetPicIdByPath(CString strPicName)
{
	std::map<__int64,CString >::iterator iter = map_pic_path.begin();
	for ( ; iter != map_pic_path.end() ; iter++ )
	{
		__int64 picid = iter->first;
		CString spath = iter->second;
		if( spath.Find( strPicName) != -1)
			return picid;
	}
	return -1;
}

void CTask::AddPicPath(__int64 picid,CString strPath)
{
	if( strPath.IsEmpty())
		return ;
	std::map<__int64,CString >::iterator iter = map_pic_path.find(picid);
	if( iter != map_pic_path.end())
		return ;
	map_pic_path.insert(std::make_pair(picid,strPath));
}


__int64 CTask::GetShapeIdByFeatureId(int poiid)
{
	std::map<__int64 , std::vector<__int64> >::iterator iter;
	for ( iter = map_shapeid_poiid.begin() ; iter != map_shapeid_poiid.end() ; iter++ )
	{
		__int64 shapeid = iter->first;
		std::vector<__int64> vt_poi = iter->second;
		std::vector<__int64>::iterator  iterpoi = std::find(vt_poi.begin(),vt_poi.end(),poiid);
		if( iterpoi != vt_poi.end())
			return shapeid;
	}
	return 0;
}

int CTask::GetShapeIndexByShapeid(__int64 shapeid)
{
	int isize = vt_shape_id.size();
	for ( int i = 0 ; i < isize ; i++ )
	{
		__int64 id = vt_shape_id.at( i );
		if( id == shapeid)
			return i;
	}
	return -1;
}

__int64 CTask::GetNextShapeIndex()
{
	m_ShapeIndex++;
	return m_ShapeIndex;
}

__int64 CTask::GetPreShapeIndex()
{
	m_ShapeIndex--;
	return m_ShapeIndex;
}

void CTask::AddTaskLinkFieldData(__int64 shapeid,CTaskLinkFieldData* pFieldData)
{
	map_taskLinkFieldData.insert( std::make_pair(shapeid,pFieldData));
}

void CTask::AddTaskLinkItemset(__int64 itemsetid)
{
	m_vtTaskLinkItemset.push_back(itemsetid);
}

int CTask::GetTaskLinkItemsetCount()
{
	return m_vtTaskLinkItemset.size();
}

__int64 CTask::GetTaskLinkItemsetByIndex(int index)
{
	if(index >= 0 && index < m_vtTaskLinkItemset.size())
	{
		return m_vtTaskLinkItemset[index];
	}
	else
	{
		return -1;
	}
}

void CTask::AddTaskLinkAttach(CTaskLinkAttach* pAttach)
{
	vt_taskLinkAttach.push_back( pAttach );
}

/*
创建任务的时候，会把从属关系的POI都拿过来，所以这里不需要在通过feature查找了
*/
void CTask::GetPoiLinkPoi()
{
	std::vector<__int64> vtpoi;
	int iShapecount = vt_shape_id.size();
	for ( int i = 0 ; i < iShapecount ; i++ )
	{
		__int64 shapeid = vt_shape_id.at(i);
		vtDef vddef;
		GetPoiIdByShapeid(shapeid,&vddef);
		vtpoi = vddef.vt;

		map_shapeid_poiid_poiid.insert(std::make_pair(shapeid,vtpoi ));
	}
}

bool CTask::GetPoiLinkPoiByShapeId(__int64 shapeid,vtDef* pvtDef)
{
	if( pvtDef == NULL)
		return false;
	std::map<__int64,std::vector<__int64> >::iterator iter = map_shapeid_poiid_poiid.find(shapeid);
	if( iter == map_shapeid_poiid_poiid.end())
		return false;
	pvtDef->vt = iter->second;
	return true;
}

void CTask::AddNewTaskLinkFieldData(__int64 shapeid,CTaskLinkFieldData* pFieldData)
{
	if( pFieldData == NULL)
		return ;
	//内存保存
	map_taskLinkFieldData.insert( std::make_pair(shapeid,pFieldData));
	//整理shapeid - poiid 关系
	int poiid = pFieldData->GetFeatureId();
	std::map<__int64 ,std::vector<__int64> >::iterator iter = map_shapeid_poiid.find(shapeid);
	if( iter != map_shapeid_poiid.end())
	{
		std::vector<__int64>::iterator iterpoi = std::find( iter->second.begin(),iter->second.end(),poiid);
		if( iterpoi == iter->second.end())
			iter->second.push_back(poiid);
	}
    //整理shapeid -poi poi-poi关系
	iter = map_shapeid_poiid_poiid.find(shapeid);
	if ( iter != map_shapeid_poiid_poiid.end())
	{
		std::vector<__int64 >::iterator iterpoi = std::find(iter->second.begin(),iter->second.end(),poiid);
		if( iterpoi == iter->second.end())
			iter->second.push_back(poiid);
	}
}

void CTask::AddNewTaskLinkAttach(CTaskLinkAttach* pAttach)
{
	if( pAttach == NULL)
		return ;
	//整理pic - poi关系
	int picid = pAttach->GetAttachId();
	int poiid = pAttach->GetFeatureid();
	std::map<__int64,std::vector<__int64 > >::iterator iter = map_picid_poiid.find(picid);
	if( iter != map_picid_poiid.end() )
	{
		std::vector<__int64 >::iterator iterpoi  = std::find(iter->second.begin(),iter->second.end(),poiid );
		if ( iterpoi == iter->second.end() )
		{
			iter->second.push_back( poiid);
		}

	}

	//整理poi- pic关系
	iter = map_poiid_picid.find(poiid);
	if ( iter != map_poiid_picid.end() )
	{
		std::vector<__int64 >::iterator iterpic = std::find( iter->second.begin(),iter->second.end(),picid);
		if( iterpic == iter->second.end())
		{
			iter->second.push_back( picid);
		}
	}
	//保存到内存
	vt_taskLinkAttach.push_back(pAttach);

}

void CTask::AddDelDesc(CString skey,CString svalue,CString sdesc)
{
	VALUEPAIR vpair;
	vpair.first = svalue;
	vpair.second = sdesc;
	map_DBconfig.insert( std::make_pair(skey,vpair));
}

int CTask::GetDelDescCount()
{
	int iSize =	map_DBconfig.count("poideldesc");
	return iSize;
}

bool CTask::GetDelDescByIndex(int index,CString& ivalue ,CString& svalue)
{
	int inx = 0;
	MAP_STRINGPAIR::iterator iterup = map_DBconfig.upper_bound("poideldesc");
	MAP_STRINGPAIR::iterator iterlow = map_DBconfig.lower_bound("poideldesc");
	MAP_STRINGPAIR::iterator iter ;
	for ( iter = iterlow; iter != iterup ; iter++ )
	{
		if( inx == index)
		{
			VALUEPAIR vpair = iter->second;
			ivalue = vpair.first;
			svalue = vpair.second;
			return true;
		}
		inx++;
	}
  return false;
}

int CTask::GetInfoType(__int64 poiid)
{
	return 1;
}

bool CTask::bScan(__int64 poiid)
{
	CTaskBlockDetail* pDetail = GetTaskBlock()->GetTaskBlockDetailForFeatureIDPtr(poiid);
	if( pDetail == NULL)
		return false;
	return pDetail->IsScanf();
}

CString CTask::GetErrorTypeName(CString sErrtype)
{
	int inx = 0;
	MAP_STRINGPAIR::iterator iterup = map_DBconfig.upper_bound("errortype");
	MAP_STRINGPAIR::iterator iterlow = map_DBconfig.lower_bound("errortype");
	MAP_STRINGPAIR::iterator iter ;
	for ( iter = iterlow; iter != iterup ; iter++ )
	{
		VALUEPAIR vpair = iter->second;
		if( vpair.first == sErrtype)
			return vpair.second;
	
	}
	return "";
}

CString CTask::GetErrorTypeByName(CString stypeanme)
{
	int inx = 0;
	MAP_STRINGPAIR::iterator iterup = map_DBconfig.upper_bound("errortype");
	MAP_STRINGPAIR::iterator iterlow = map_DBconfig.lower_bound("errortype");
	MAP_STRINGPAIR::iterator iter ;
	for ( iter = iterlow; iter != iterup ; iter++ )
	{
		VALUEPAIR vpair = iter->second;
		if( vpair.second == stypeanme)
			return vpair.first;
	}
	return "";
}

CString CTask::GetErrorTypeNameByIndex(int index)
{
	int inx = 0;
	MAP_STRINGPAIR::iterator iterup = map_DBconfig.upper_bound("errortype");
	MAP_STRINGPAIR::iterator iterlow = map_DBconfig.lower_bound("errortype");
	MAP_STRINGPAIR::iterator iter ;
	for ( iter = iterlow; iter != iterup ; iter++ )
	{
		if( index == inx)
		{
			VALUEPAIR vpair = iter->second;
			return vpair.second;
		}
		inx++;
		
	}
	return "";
}

int  CTask::GetErrorCount()
{
	int inx = 0;
	MAP_STRINGPAIR::iterator iterup = map_DBconfig.upper_bound("errortype");
	MAP_STRINGPAIR::iterator iterlow = map_DBconfig.lower_bound("errortype");
	MAP_STRINGPAIR::iterator iter ;
	for ( iter = iterlow; iter != iterup ; iter++ )
	{
		CString s1 = iter->first;
		VALUEPAIR vp = iter->second;
		CString s2 = vp.first;
		CString s3 = vp.second;
		inx++;
	}
	return inx;
}

int  CTask::GetQuestionDescCount()
{
	int inx = 0;
	MAP_STRINGPAIR::iterator iterup = map_DBconfig.upper_bound("questiontype");
	MAP_STRINGPAIR::iterator iterlow = map_DBconfig.lower_bound("questiontype");
	MAP_STRINGPAIR::iterator iter ;
	for ( iter = iterlow; iter != iterup ; iter++ )
	{
		CString s1 = iter->first;
		VALUEPAIR vp = iter->second;
		CString s2 = vp.first;
		CString s3 = vp.second;
		inx++;
	}
	return inx;
}

void CTask::GetQuestionDescByIndex(int index,CString &sKey,CString& sValue)
{
	int inx = 0;
	MAP_STRINGPAIR::iterator iterup = map_DBconfig.upper_bound("questiontype");
	MAP_STRINGPAIR::iterator iterlow = map_DBconfig.lower_bound("questiontype");
	MAP_STRINGPAIR::iterator iter ;
	for ( iter = iterlow; iter != iterup ; iter++ )
	{
		if( inx == index)
		{
			CString s1 = iter->first;
			VALUEPAIR vp = iter->second;
			sKey = vp.first;
			sValue = vp.second;
		}
		inx++;
	}
}

void CTask::SetTaskBlock(CTaskBlock *pTaskBlock)
{
	m_pBlock = pTaskBlock ;
}

CTaskBlock *CTask::GetTaskBlock()
{
	return m_pBlock ;
}


bool CTask::LoadLinkInfo()
{
	ReleaseTask() ;
	Clear() ;

	if ( !LoadLinkAttach())
	{
//		return false ;
	}
	if ( !LoadLinkFielddata())
	{
//		return false ;
	}
	int index = GetIndex("blockid");
	if( index != -1)
	{
		__int64 blockid = GetInt64ByIndex(index);
		CString sMess;
		sMess.Format(" where id = %I64d", blockid );
		//加载关联的POI
		CTaskManager::GetTaskManager()->LoadTaskBlock( sMess );
	}
	return true;
}

bool CTask::LoadLinkAttach()
{
	int iIndex = GetIndex("id") ;
	__int64 iid = GetID();// GetInt64ByIndex(iIndex) ;
	CString strSQL; 
	strSQL.Format("select * from tb_task_link_attach where taskid=%I64d", iid) ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
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
		return false ;
	}
	CTaskLinkAttach *pTaskAttach = NULL ;
	
	CDBFieldInfo *pFieldInfo = NULL ;
	CDBValue *pValue = NULL ;
	MAP_RES::iterator it ;
	
	for ( it=mapres.begin(); it!=mapres.end(); it++ )
	{
		pTaskAttach = new CTaskLinkAttach() ;
		VT_RES vtres = it->second ;
		for ( int i=0; i<num_fields; i++ )
		{
			int mysqltype = vtFields.at(i).type ;
			pFieldInfo = new CDBFieldInfo(vtFields[i].name,vtFields[i].table,mysqltype) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(mysqltype));//再单独设置一下
			pValue = new CDBValue ;
			pTaskAttach->AddField(pFieldInfo, pValue) ;
			CString strval = vtres.at(i).c_str() ;
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pTaskAttach->SetIntByIndex(i,atoi(strval) ) ;
				break;
			case DBFT_Bigint:
				pTaskAttach->SetInt64ByIndex(i,_atoi64(strval) ) ;
				break;
			case DBFT_Double:
				pTaskAttach->SetDoubleByIndex(i, atof(strval) ) ;
				break;
			case DBFT_String:
				pTaskAttach->SetStringByIndex(i,strval) ;
				break;
			}
		}
		iIndex = pTaskAttach->GetIndex("itemsetid") ;
		__int64 iSetID = pTaskAttach->GetInt64ByIndex(iIndex) ;
		AddNewTaskLinkAttach(pTaskAttach) ;
		
	}
	return true;
}

bool CTask::LoadLinkFielddata()
{
	int iIndex = -1;
	__int64 iid = GetID();
	CString strSQL; 
	strSQL.Format("select * from tb_task_link_fielddata where taskid=%I64d", iid) ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
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
		return false ;
	}
	CTaskLinkFieldData *pTaskFielddata = NULL ;
	
	CDBFieldInfo *pFieldInfo = NULL ;
	CDBValue *pValue = NULL ;
	MAP_RES::iterator it ;
	
	for ( it=mapres.begin(); it!=mapres.end(); it++ )
	{
		pTaskFielddata = new CTaskLinkFieldData() ;
		VT_RES vtres = it->second ;
		for ( int i=0; i<num_fields; i++ )
		{
			int mysqltype = vtFields.at(i).type ;
			pFieldInfo = new CDBFieldInfo(vtFields[i].name,vtFields[i].table,mysqltype) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(mysqltype));//再单独设置一下
			pValue = new CDBValue ;
			pTaskFielddata->AddField(pFieldInfo, pValue) ;
			CString strval = vtres.at(i).c_str() ;
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pTaskFielddata->SetIntByIndex(i,atoi(strval) ) ;
				break;
			case DBFT_Bigint:
				pTaskFielddata->SetInt64ByIndex(i,_atoi64(strval) ) ;
				break;
			case DBFT_Double:
				pTaskFielddata->SetDoubleByIndex(i, atof(strval) ) ;
				break;
			case DBFT_String:
				pTaskFielddata->SetStringByIndex(i,strval) ;
				break;
			}
		}
		iIndex = pTaskFielddata->GetIndex("shapeid") ;
		__int64 ishapeid = pTaskFielddata->GetInt64ByIndex(iIndex) ;
		AddNewTaskLinkFieldData(ishapeid,pTaskFielddata) ;
		
	}
	return true;
}

CString CTask::GetTaskName()
{
	CString strTaskName = "";
	switch ( m_iTaskType )
	{
	case TASKTYPE_VIDEO:
		strTaskName = "车调密集视频";
		break;
	case TASKTYPE_FOOT_PRORERTY:
		strTaskName = "平板步调属性任务";
		break;
	case  TASKTYPE_FOOT_PRORERTYERROR:
		strTaskName = "平板属性改错任务";
		break;
	case TASKTYPE_FOOT_PRORERTYNEWADD :
		strTaskName = "平板属性新增任务";
		break;
	case 	TASKTYPE_FOOT_PRORERTYNEWADDDOOR :
		strTaskName = "平板属性新增门址任务";
		break;
	case 	TASKTYPE_FOOT_PRORERTYMODIFY :
		strTaskName = "平板属性修改任务";
		break;
    case TASKTYPE_FOOT_PRORERTYMODIFYDOOR :
		strTaskName  = "平板属性修改门址任务";
			break;
	case  TASKTYPE_FOOT_GEOMETRY:
		strTaskName = "平板步调几何任务";
		break;
	case  TASKTYPE_FOOT_GEOMETRYERROR:
		strTaskName = "步调几何改错任务";
		break;
	case  TASKTYPE_CAR_PRORERTY:
		strTaskName = "车调属性任务";
		break;
	case  TASKTYPE_CAR_PRORERTYERROR:
		strTaskName = "车调属性改错任务";
		break;
	case  TASKTYPE_CAR_GEOMETRY:
		strTaskName = "车调几何任务";
		break;
	case  TASKTYPE_CAR_GEOMETRYERROR:
		strTaskName = "车调几何改错任务";
		break;
	case  TASKTYPE_NET_PRORERTY:
		strTaskName = "非实测属性任务";
		break;
	case  TASKTYPE_NET_PRORERTYERROR:
		strTaskName = "非实测属性改错任务";
		break;
	case  TASKTYPE_NET_GEOMETRY:
		strTaskName = "非实测几何任务";
		break;
	case  TASKTYPE_NET_GEOMETRYERROR:
		strTaskName = "非实测几何改错任务";
		break;
	case  TASKTYPE_COMPLANIT_PRORERTY:
		strTaskName = "客投属性任务";
		break;
	case  TASKTYPE_COMPLANIT_PRORERTYERROR:
		strTaskName = "客投属性改错任务";
		break;
	case  TASKTYPE_COMPLANIT_GEOMETRY:
		strTaskName = "客投几何任务";
		break;
	case  TASKTYPE_COMPLANIT_GEOMETRYERROR:
		strTaskName = "客投几何改错任务";
		break;
	case TASKTYPE_CROW_PRORERTYERROR :
		strTaskName = "众包属性改错任务";
		break;
	case 	TASKTYPE_CROW_GEOMETRY :
		strTaskName = "众包几何任务";
		break;
	case TASKTYPE_ROADCHANGE_GEOMETRY :
		strTaskName = "道路变化几何任务";
		break;
	}
	return strTaskName;
}

void CTask::SetEditRefer(EditRefer editrefer)
{
	m_vtEditRefer.push_back(editrefer) ;
}

void CTask::SetFieldRefer(FieldRefer fieldrefer)
{
	m_vtFieldRefer.push_back(fieldrefer) ;
}

int CTask::GetEditReferLayerCount()
{
	return m_vtEditRefer.size() ;
}

int CTask::GetFieldReferLayerCount()
{
	return m_vtFieldRefer.size() ;
}

int CTask::GetQCReferLayerCount()
{
	return m_vtqcLayerName.size() ;
}

int CTask::GetToolReferLayerCount()
{
	return m_vttoolLayerName.size() ;
}

void CTask::GetReferdataByKey(const char *szkey) 
{
	int iIndex = GetIndex("referdata");
	if ( iIndex == -1 )
	{
		return ;
	}
	CString strReferdata = GetStringByIndex(iIndex) ;
	CString strSQL ;
	if ( strcmp(szkey,"qc") == 0 ||
		strcmp(szkey,"tool") == 0 )
	{
		strSQL.Format("SELECT json_extract(t.qc,'$.layer') as 'qclayer',"
			"json_extract(t.qc,'$.bound[0]') as 'xmin',"
			"json_extract(t.qc,'$.bound[2]') as 'xmax',"
			"json_extract(t.qc,'$.bound[1]') as 'ymin',"
			"json_extract(t.qc,'$.bound[3]') as 'ymax',"
			"json_length(t.qc->'$.layer') as 'num'"
			"FROM (select json_extract('%s','$.%s') AS 'qc' ) as t ", strReferdata,szkey) ;
		
		
		CDB_ResultSet *pRes1 = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
		if ( pRes1 != NULL)
		{
			int num_rows1 = pRes1->GetResRowCount();
			int num_fields1 = pRes1->GetResFieldCount();
		
			int iNum = 0 ;
			CString strLayernames = "" ;
			for(int i = 0; i < num_rows1; i++)
			{
				strLayernames.Format("%s",pRes1->GetResStringValue(i,0));
				
				

				if ( strcmp(szkey,"qc") == 0 )
				{
					
					m_sqcBound.x_min = atof(pRes1->GetResStringValue(i,1)) ;
					m_sqcBound.x_max = atof(pRes1->GetResStringValue(i,2)) ;
					m_sqcBound.y_min = atof(pRes1->GetResStringValue(i,3)) ;
					m_sqcBound.y_max = atof(pRes1->GetResStringValue(i,4)) ;

				}
				if ( strcmp(szkey,"tool") == 0 )
				{
					m_stoolBound.x_min = atof(pRes1->GetResStringValue(i,1)) ;
					m_stoolBound.x_max = atof(pRes1->GetResStringValue(i,2)) ;
					m_stoolBound.y_min = atof(pRes1->GetResStringValue(i,3)) ;
					m_stoolBound.y_max = atof(pRes1->GetResStringValue(i,4)) ;

				}
				
				int type5 = pRes1->GetFieldType(5);
				if(type5 == DBFT_Int) iNum = pRes1->GetResIntValue(i,5);
				else 
					iNum = atoi(pRes1->GetResStringValue(i,5)) ;
			}
			CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes1) ;
			if ( iNum > 0 )
			{
				strSQL = "" ;
				CString strmid = "" ;
				while ( iNum >= 0)
				{
					iNum-- ;
					if ( iNum < 0)
					{
						break ;
					}
					CString strtem ;
					strtem.Format("json_extract('%s','$[%d]') as 'qclayer%d'",strLayernames,iNum,iNum) ;
					if (strmid != "" )
					{
						strmid += "," ;
					}
					strmid += strtem ;
				}
				strSQL.Format("SELECT %s ", strmid) ;
				pRes1 = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
				CString strname = "" ;
			
				num_rows1 = pRes1->GetResFieldCount();
				int rowcount = pRes1->GetResRowCount();
				for(int r = 0; r < rowcount; r++)
				{
					while ( num_rows1 > 0 )
					{
						num_rows1-- ;
						strname = pRes1->GetResStringValue(r,num_rows1) ;
						strname.Replace("\"","");
						if ( strcmp(szkey,"qc") == 0 )
						{
							m_vtqcLayerName.push_back(strname.GetBuffer(0)) ;
						}
						if ( strcmp( szkey,"tool") == 0)
						{
							m_vttoolLayerName.push_back(strname.GetBuffer(0)) ;
						}
					}
				}
				CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes1) ;
			}
		}
	}
	else
	{
		strSQL.Format("select t.%s,json_length(t.%s) "
			"from (select json_extract('%s','$.%s') AS '%s') as t ",
			szkey,szkey,strReferdata,szkey,szkey) ;
		
		CDB_ResultSet *pRes1 = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
		if ( pRes1 != NULL)
		{
			int num_rows1 = pRes1->GetResRowCount();
			int num_fields1 = pRes1->GetResFieldCount();
		
			int iNum = 0 ;
			CString strkeyvalue = "" ;
			for(int r = 0; r < num_rows1; r++)
			{
				strkeyvalue = pRes1->GetResStringValue(r,0) ;
				int type1 = pRes1->GetFieldType(1);
				if(type1 == DBFT_Int) iNum = pRes1->GetResIntValue(r,1);
				else 
					iNum = atoi(pRes1->GetResStringValue(r,1)) ;
				
			}
			CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes1) ;
			if ( iNum > 0 )
			{
				strSQL = "" ;
				CString strmid = "" ;
				while ( iNum > 0)
				{
					iNum-- ;
					CString strtem ;
					strtem.Format("json_extract('%s','$[%d]') as 'layer%d'",strkeyvalue,iNum,iNum) ;
					if (strmid != "" )
					{
						strmid += "," ;
					}
					strmid += strtem ;
				}
				strSQL.Format("SELECT %s ", strmid) ;
				pRes1 = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
				CString strname = "" ;
				std::vector<CString> vtString ;
			
				num_rows1 = pRes1->GetResFieldCount();
				int rowcount = pRes1->GetResRowCount();
				for(int r = 0; r < rowcount; r++)
				{
					while ( num_rows1 > 0 )
					{
						num_rows1-- ;
						strname = pRes1->GetResStringValue(r,num_rows1) ;
//						strname.Replace("\"","");
						vtString.push_back(strname) ;
					}
				}
				CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes1) ;
				for ( int i=0; i<vtString.size(); i++ )
				{
					if ( strcmp(szkey,"edit") == 0 )
					{
						CString strval = vtString.at(i) ;
						strSQL.Format("select json_extract('%s','$.bound[0]') as xmin,"
							"json_extract('%s','$.bound[2]') as xmax,"
							"json_extract('%s','$.bound[1]') as ymin,"
							"json_extract('%s','$.bound[3]') as ymax,"
							"json_extract('%s','$.layer') as layer ",
							strval,strval,strval,strval,strval) ;
						pRes1 = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
						num_rows1 = pRes1->GetResRowCount();
						for(int r = 0; r < num_rows1; r++)
						{
							EditRefer editrefer ;
							editrefer.bound.x_min = atof(pRes1->GetResStringValue(r,0)) ;
							editrefer.bound.x_max = atof(pRes1->GetResStringValue(r,1)) ;
							editrefer.bound.y_min = atof(pRes1->GetResStringValue(r,2)) ;
							editrefer.bound.y_max = atof(pRes1->GetResStringValue(r,3)) ;
							CString strLayerName = pRes1->GetResStringValue(r,4) ;
							strLayerName.Replace("\"","") ;
							editrefer.strname = strLayerName.GetBuffer(0) ;
							SetEditRefer(editrefer) ;
						}
						CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes1) ;
					}
					if ( strcmp( szkey,"field") == 0 )
					{
						CString strval = vtString.at(i) ;
						strSQL.Format("select json_extract('%s','$.bound[0]') as xmin,"
							"json_extract('%s','$.bound[2]') as xmax,"
							"json_extract('%s','$.bound[1]') as ymin,"
							"json_extract('%s','$.bound[3]') as ymax,"
							"json_extract('%s','$.layer') as layer, "
							"json_extract('%s','$.batchid') as batch",
							strval,strval,strval,strval,strval,strval) ;
						pRes1 = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
						num_rows1 = pRes1->GetResRowCount();
						for(int r = 0; r < num_rows1; r++)
						{
							FieldRefer fieldrefer ;
							fieldrefer.bound.x_min = atof(pRes1->GetResStringValue(r,0)) ;
							fieldrefer.bound.x_max = atof(pRes1->GetResStringValue(r,1)) ;
							fieldrefer.bound.y_min = atof(pRes1->GetResStringValue(r,2)) ;
							fieldrefer.bound.y_max = atof(pRes1->GetResStringValue(r,3)) ;
							CString strLayerName = pRes1->GetResStringValue(r,4) ;
							strLayerName.Replace("\"","") ;
							fieldrefer.strname = strLayerName.GetBuffer(0) ;
							fieldrefer.batchid = _atoi64(pRes1->GetResStringValue(r,5)) ;
							SetFieldRefer(fieldrefer) ;
						}
						CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes1) ;
					}
					
				}
				CDB_Manager::GetDBManagerPtr()->ReleaseAllRes() ;
			}
		}
	}
	

}


EditRefer CTask::GetEditReferIndex(int iIndex)
{
	EditRefer editRefer ;
	if (iIndex <0 || iIndex>m_vtEditRefer.size() )
	{
		return editRefer ;
	}
	return m_vtEditRefer.at(iIndex) ;
}

FieldRefer CTask::GetFieldReferIndex(int iIndex)
{
	FieldRefer fieldRefer ;
	if (iIndex <0 || iIndex>m_vtFieldRefer.size() )
	{
		return fieldRefer ;
	}
	return m_vtFieldRefer.at(iIndex) ;
}

_TSGEO::SGeoRect CTask::GetQCBound()
{
	return m_sqcBound ;
}

void CTask::SetQCBound(_TSGEO::SGeoRect bound)
{
	m_sqcBound = bound ;
}

_TSGEO::SGeoRect CTask::GetToolBound()
{
	return m_stoolBound ;
}

void CTask::SetToolBound(_TSGEO::SGeoRect bound)
{
	m_stoolBound = bound ;
}

const char *CTask::GetQCLayerNameByIndex(int index) 
{
	if ( index <0 || index>m_vtqcLayerName.size() )
	{
		return "" ;
	}
	return m_vtqcLayerName.at(index).c_str() ;
}
const char *CTask::GetToolLayerNameByIndex(int index) 
{
	if ( index <0 || index>m_vttoolLayerName.size() )
	{
		return "" ;
	}
	return m_vttoolLayerName.at(index).c_str() ;
}

void CTask::SetQCReferLayerName(const char* szLayername)
{
	if ( !m_vtqcLayerName.empty() )
	{
		if ( find(m_vtqcLayerName.begin(),m_vtqcLayerName.end(),szLayername) != m_vtqcLayerName.end() )
		{
			return ;
		}
	}
	m_vtqcLayerName.push_back(szLayername) ;
}
void CTask::SetToolReferLayerName(const char *szLayername)
{
	if ( !m_vttoolLayerName.empty() )
	{
		if ( find(m_vttoolLayerName.begin(),m_vttoolLayerName.end(),szLayername) != m_vttoolLayerName.end() )
		{
			return ;
		}
	}
	m_vttoolLayerName.push_back(szLayername) ;
}
