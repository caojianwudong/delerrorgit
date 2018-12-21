// CCreateTask.cpp: implementation of the CCreateTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vld.h"
#include "CreateTaskForChangedRoad.h"
#include "CCreateTask.h"

#include "CNaviMap.h"
#include "CLayer.h"
#include "CFeatureSet.h"
#include "CFeature.h"
#include "CRoadLayer.h"
#include "CJunctionLayer.h"
#include "CGeometry.h"

#include "CTask.h"
#include "CTaskManager.h"
#include "task_definition.h"
// #include "CTaskLinkPoi.h"
#include "CTaskChangeRoadTime.h"
#include "CTaskBlock.h"
#include "CTaskBlockDetail.h"
#include "CWriteLog.h"
#include "CDB_Manager.h"

#include <afxsock.h>
#include "winsock.h"
#include <math.h>

#include "vld.h"
#include "Db_Definition.h"

#include "CTransOwner.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int BLOCK_STATUS_UNKNOWN = -1;		// 未定义，这种情况下，不更新
const int BLOCK_STATUS_UNCHECK = 1 ;		// 待质检
const int BLOCK_STATUS_OK = 3 ;				// 质检成功
const int BLOCK_STATUS_ERR = 4 ;			// 质检失败
const int BLOCK_STATUS_PUBLISH = 5 ;		// 关闭-发布
const int BLOCK_STATUS_MERGE = 6 ;			// 关闭-合并
const int BLOCK_STATUS_MANUALERR = 7 ;		// 目视错误

const int LOAD_UNIT_COUNT = 10000 ;			// 一次加载数据过程的最大数

CCreateTask* CCreateTask::m_pstaticTaskPtr = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCreateTask::CCreateTask()
{
// 	m_sqlFlag = 1002 ;
// 	m_writelog = NULL ;
// 	m_pMap = CreateNaviMapObject() ;
// 
// 	m_pMap->SetCommitParams( SP_Toolkit ) ;
// 	m_pTransOwner = NULL ;
}

CCreateTask::~CCreateTask()
{
// 	if ( m_pMap != NULL )
// 	{
//  		m_pMap->Release() ;
// 		m_pMap = NULL ;
// 	}
}

CCreateTask* CCreateTask::GetCreateTaskPtr()
{
	if ( m_pstaticTaskPtr == NULL)
	{
		m_pstaticTaskPtr = new CCreateTask();
	}
	return m_pstaticTaskPtr;
}

void CCreateTask::Release()
{
	// 释放mysql数据库连接
	CTaskManager::GetTaskManager()->DestroyTaskManager() ;

	if( m_pstaticTaskPtr != NULL)
	{
		delete m_pstaticTaskPtr;
		m_pstaticTaskPtr = NULL;
	}
}
bool CCreateTask::ReadConfig()
{
	m_mulBatch_ErrorType.clear() ;
	char path[1024] ;
	::GetModuleFileName( NULL, path, 1024) ;
	CString strAppPath = path ;
	int ipos = strAppPath.ReverseFind('\\') ;
	if ( ipos != -1)
	{
		strAppPath = strAppPath.Left(ipos+1) ;
	}
	
	CString strConfigPath = strAppPath + "config\\errortype.ini" ;
	CStdioFile stfile ;
	
	if ( !stfile.Open(strConfigPath, CFile::modeReadWrite))
	{
		AfxMessageBox(strConfigPath + " 打开失败") ;
		return false;
	}
	
	CString strBatchID = "" ;
	CString strErrortype = "" ;
	CString msg ;
	int flag = -1 ;
	while ( stfile.GetPosition() != stfile.GetLength())
	{
		stfile.ReadString( msg) ;
		msg.TrimLeft() ;
		msg.TrimRight() ;
		if ( msg.GetLength() == 0 || msg.Left(2).CompareNoCase("//") == 0)
		{
			continue;
		}
		if ( msg.Find("batchid") != -1)
		{
			flag = 1 ;// 批次号 
			if (strBatchID != "" && m_mulBatch_ErrorType.find( strBatchID) == m_mulBatch_ErrorType.end())
			{
				m_mulBatch_ErrorType.insert(MUL_BATCH_ERRORTPE::value_type( strBatchID,"")) ;
			}
			continue;
		}
		else if ( msg.Find("errortype") != -1)
		{
			flag = 2 ;
			continue;
		}
		if ( flag == 1)
		{
			strBatchID = msg ;
		}
		else if ( flag == 2)
		{
			strErrortype = msg ;
			m_mulBatch_ErrorType.insert(MUL_BATCH_ERRORTPE::value_type( strBatchID, strErrortype)) ;
		}
	}
	if (strBatchID != "" && m_mulBatch_ErrorType.find( strBatchID) == m_mulBatch_ErrorType.end())
	{
		m_mulBatch_ErrorType.insert(MUL_BATCH_ERRORTPE::value_type( strBatchID,"")) ;
	}
	stfile.Close() ;
	return true ;
}
bool CCreateTask::CreateTaskForChangedRoad(CWriteLog *pWriteLog)
{
	m_writelog = pWriteLog ;

	if ( m_pTransOwner == NULL)
	{
		m_writelog->WriteLog("打开excel\n") ;

		m_pTransOwner = new CTransOwner() ;

		if ( !(m_pTransOwner->InitOwnerObject()))
		{

			m_writelog->WriteLog("建立数据库连接失败！\n") ;
			return false ;
		}

		m_writelog->WriteLog("关闭excel\n") ;

	}
	//////////////////////////////////////////////////////////////////////////
	// 读取存量block，并更新
	//ReadTableDetail() ;
	/////////
#ifdef _DEBUG
	m_writelog->WriteLog("创建NaviMap指针\n") ;
#endif

	if ( m_pMap == NULL )
	{
		m_writelog->WriteLog("创建NaviMap指针失败\n") ;
		return false ;
	}
	if ( !GetUID_UserName())
	{
		m_writelog->WriteLog("提取uid_username失败\n") ;
		return false ;
	}
	ReadConfig() ;
	CTaskManager::GetTaskManager()->SetSqlFlag( m_sqlFlag) ;

	WriteLogtoMysql() ;
	m_writelog->WriteLog("成功建立数据库连接\n") ;
	// 加载block数据进内存
	if ( !LoadBlockDetailStatus() )
	{
		// 加载数据出现失败，则放弃本次处理
		m_mapManualStatus.clear() ;
		m_mapState.clear() ;
		m_mapBound.clear() ;
		m_mulLayerDetails.clear() ;
		m_mulBlockDetails.clear() ;
		m_oldBlockStatus.clear() ;
		m_mapBlockStatus.clear() ;
		m_mapOldBlockBound.clear() ;
		m_mapBlockBound.clear() ;
		m_mapBlockUpdateTime.clear() ;
		m_mapManualCheck.clear() ;
		m_mapUserName.clear() ;
		m_mapOwner.clear() ;
		m_mapBlockManualRoadnum.clear() ;
		m_mapBlockUserName.clear() ;
		m_mapBlockOwner.clear() ;
		m_mapFeatureUserName.clear() ;
		m_mapFeatureOwner.clear() ;
		m_mapFeatureManualCheck.clear() ;
		m_mapLID_FID_DetailID.clear() ;
		m_mapUID_UserName.clear() ;

		m_writelog->WriteLog( "放弃本轮block状态更新操作\n" ) ;
		return false ; 
	}

	// 更新block状态
	/// modified at 2017/11/16
	//UpdateBlockStatus();
	UpdateBlockStatus_Version2() ;
	//更新blockdetail中为空的block状态
	LoadBlockForNull() ;
	
	// 更新校正道路条数和制作人
 	UpdateBlockDetail() ;
	// 将block的最新状态写入数据库中
	UpLoadBlockStatus_method2();

	m_writelog->WriteLog("完成一轮block状态更新\n") ;

	m_mapManualStatus.clear() ;
	m_mapState.clear() ;
	m_mapBound.clear() ;
	m_mulLayerDetails.clear() ;
	m_mulBlockDetails.clear() ;
	m_oldBlockStatus.clear() ;
	m_mapBlockStatus.clear() ;
	m_mapOldBlockBound.clear() ;
	m_mapBlockBound.clear() ;
	m_mapBlockUpdateTime.clear() ;
	m_mapManualCheck.clear() ;
	m_mapUserName.clear() ;
	m_mapOwner.clear() ;
	m_mapBlockManualRoadnum.clear() ;
	m_mapBlockUserName.clear() ;
	m_mapBlockOwner.clear() ;
	m_mapFeatureUserName.clear() ;
	m_mapFeatureOwner.clear() ;
	m_mapFeatureManualCheck.clear() ;
	m_mapLID_FID_DetailID.clear() ;
	m_mapUID_UserName.clear() ;


	//////////////////////////////////////////////////////////////////////////

	return true ;
}

// bool CCreateTask::UpdateBlockStatusNew( CTaskBlock *pTaskBlock )
// {
// 	// true为需要关闭，false不需要
// 	if ( pTaskBlock ==NULL)
// 	{
// 		return false ;
// 	}
// 	
// 	// 将该pTaskBlock关联的对象加载到内存中
// 	bool bupdate = CTaskManager::GetTaskManager()->LoadTaskBlockDetailsForBlock( pTaskBlock) ;
// 	if ( bupdate == false)
// 	{
// 		return false ;
// 	}
// 	
// 	
// 	int iroadsize = 0 ;
// 	int ijuncsize = 0 ;
// 	bool roadchange = false ; // 道路是否改变
// 	bool juncchange = false ; // 交叉点是否改变
// 	
// 	// 获取一个block关联道路图层所有的ID列表
// 	OID *pRoadID = pTaskBlock->GetFeatureIDs(1, iroadsize) ;
// 	// 根据道路ID列表加载道路
// 	bool broad = m_pRoadLayer->Load( pRoadID, iroadsize) ;
// 	
// 	
// 	int flag = 5 ;// 默认为待质检task.tb_task_block.status，状态（1：待质检，3：质检通过，4：质检失败；5：关闭，完成，6：关闭，合并）
// 	
// 	int check_err = -1 ; // -1为没有出现，1为出现
// 	int check_ok = -1 ;
// 	int check_uncheck = -1 ;
// 	int optype_published = -1 ; // -1表示全部为published，否则存在
// 	
// 	// 1、最高级是质检失败,有一个err就是失败
// 	// 2、其次是有一个nocheck,算待质检
// 	// 3、再次有一个noerr,算质检通过
// 	// 4、都是published且都是noerr，算完成、关闭
// 
// 	if ( broad)
// 	{
// 		// 如果加载成功，判断道路是否被修改，如果没有并且道路已经检查且没有错误，即所有道路可发布，关闭该block
// // 		roadchange = CheckIsHasChanged( pRoadID, iroadsize, m_pRoadLayer) ;
// 		for ( int i = 0; i < iroadsize; i++)
// 		{
// 			OID id = pRoadID[i] ;
// 			CFeature *pFeature = m_pRoadLayer->GetDataSourcePtr()->GetFeaturePtr(id) ;
// 			
// 			// 检查是否存在道路被修改，尚待添加一个edit状态
// 			if ( pFeature == NULL)
// 			{
// 				return false ;
// 			}
// 			OpType type = pFeature->GetOpType() ;
// 			CheckStatus status = pFeature->GetGeometryPtr()->GetAutoCheck() ;
// 			if ( status == IRCS_Error)
// 			{
// 				check_err = 1 ;
// 				break;
// 			}
// 			else if ( status == IRCS_NoErr)
// 			{
// 				check_ok = 1 ;
// 			}
// 			else if ( status == IRCS_NoCheck)
// 			{
// 				check_uncheck = 1 ;
// 			}
// 
// 			if ( type != IROT_Published)
// 			{
// 				optype_published = 1 ;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		return false ;
// 	}
// 	
// 	// 获取一个block关联交叉点图层所有的ID列表
// 	OID *pJuncID = pTaskBlock->GetFeatureIDs(24,ijuncsize) ;
// 	// 根据交叉点ID列表加载交叉点
// 	bool bjun = m_pJunctionLayer->Load( pJuncID, ijuncsize) ;
// 	if ( bjun)
// 	{
// // 		juncchange = CheckIsHasChanged( pJuncID, ijuncsize, m_pJunctionLayer) ;
// 		for ( int i = 0; i < ijuncsize; i++)
// 		{
// 			OID id = pJuncID[i] ;
// 			CFeature *pFeature = m_pJunctionLayer->GetDataSourcePtr()->GetFeaturePtr(id) ;
// 			
// 			// 检查是否存在道路被修改，尚待添加一个edit状态
// 			if ( pFeature == NULL)
// 			{
// 				return false ;
// 			}
// 			OpType type = pFeature->GetOpType() ;
// 			CheckStatus status = pFeature->GetGeometryPtr()->GetAutoCheck() ;
// 			if ( status == IRCS_Error)
// 			{
// 				check_err = 1 ;
// 				break;
// 			}
// 			else if ( status == IRCS_NoErr)
// 			{
// 				check_ok = 1 ;
// 			}
// 			else if ( status == IRCS_NoCheck)
// 			{
// 				check_uncheck = 1 ;
// 			}
// 
// 			if ( type != IROT_Published)
// 			{
// 				optype_published = 1 ;
// 			}
// 			
// 		}
// 	}
// 	else
// 	{
// 		return false ;
// 	}
// 	
// 	if ( check_err == 1)
// 	{
// 		flag = 4 ;  // 质检失败
// 	}
// 	else if ( check_uncheck == 1)
// 	{
// 		flag = 1 ; // 待质检
// 	}
// 	else if ( check_ok == 1)
// 	{
// 		if ( optype_published== -1)
// 		{
// 			flag = 5 ; // 完成、关闭
// 		}
// 		else
// 		{
// 			flag = 3; // 质检通过
// 		}
// 	}
// 	
// 
// 	pTaskBlock->SetStatus(flag) ;
// 	return true ;
// }

/*
void CCreateTask::ReadTableDetail()
{
	//////////////////////////////////////////////////////////////////////////
	m_writelog->WriteLog("加载数据库blockdetail信息\n") ;
	vector< OID > vtblockid ;
	vector< int > vtlayerid ;
	vector< OID > vtfeatureid ;
	vector< int > vtstatus ;
	bool bload = CTaskManager::GetTaskManager()->LoadTaskDetail(vtblockid, vtlayerid, vtfeatureid, vtstatus) ;
	if ( !bload)
	{
		return  ;
	}
	if ( vtfeatureid.size() == 0)
	{
		return ;
	}

	m_mapState.clear() ;
	m_mulLayerDetails.clear() ;
	m_mulBlockDetails.clear() ;
	m_oldBlockStatus.clear() ;
	for ( int i = 0; i < vtfeatureid.size(); i++)
	{
		OID blockid = vtblockid[i] ;
		int layerid = vtlayerid[i] ;
		OID featureid = vtfeatureid[i] ;
		int status = vtstatus[i] ;
		PAIR_INT_OID pairl_f ;
		pairl_f.first = layerid ;
		pairl_f.second = featureid ;

		m_oldBlockStatus.insert(MAP_OID_INT::value_type( blockid, status)) ;
		m_mulBlockDetails.insert( MUL_BLOCK_OID::value_type(blockid, pairl_f)) ;
		m_mulLayerDetails.insert( MUL_LAYER_OID::value_type(layerid, featureid)) ;
	}

	vtblockid.clear() ;
	vtfeatureid.clear() ;
	vtlayerid.clear() ;
	vtstatus.clear() ;

	m_writelog->WriteLog("创建NaviMap指针\n") ;
	m_pMap = CreateNaviMapObject() ;

	//////////////////////////////////////////////////////////////////////////
	m_writelog->WriteLog("根据featureid加载对象并提取对象状态\n") ;
	// 遍历所有对象的属性状态
	// 获取对象的状态：待质检，质检失败，质检成功，关闭-合并，关闭-发布
	// 将全部非关闭状态block内的要素的最新状态信息加载进内存
	MUL_LAYER_OID::iterator itlower ;
	MUL_LAYER_OID::iterator itupper ;
	for ( MUL_LAYER_OID::iterator itlayer = m_mulLayerDetails.begin(); itlayer != m_mulLayerDetails.end();)
	{
		int layerid = itlayer->first ;
		CString strLayerName = GetLayerNameByLayerID( layerid) ;
		int index = 0 ;
		itlower = m_mulLayerDetails.lower_bound( layerid) ;
		itupper = m_mulLayerDetails.upper_bound( layerid) ;

		int icount = m_mulLayerDetails.count(layerid) ;
		int currentindex = 0 ;
		OID *ptempFeatureID = new OID[LOAD_UNIT_COUNT] ;
		while ( itlower != itupper)
		{
			OID featureid = itlower->second ;

			currentindex++ ;
			if ( index < LOAD_UNIT_COUNT )
			{
				ptempFeatureID[index] = featureid ;		
				index++ ;
			}
			else	// index == LOAD_UNIT_COUNT
			{
				Load( layerid, ptempFeatureID, index ) ;
				index = 0 ;
			}
			itlower++ ;
			itlayer++ ; 
		}

		if ( ptempFeatureID != NULL && index >0 )
		{
			Load( layerid, ptempFeatureID, index ) ;
		}
		if ( ptempFeatureID != NULL )
		{
			delete []ptempFeatureID ;
 			ptempFeatureID = NULL ;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	m_writelog->WriteLog("获取block的最新状态\n") ;
	// 更新每个block的状态
	MAP_OID_INT mapBlockState ;
	MAP_OID_STATE::iterator itstate ;
	MUL_BLOCK_OID::iterator itblocklower ;
	MUL_BLOCK_OID::iterator itblockupper ;
	for ( MUL_BLOCK_OID::iterator itblock = m_mulBlockDetails.begin(); itblock != m_mulBlockDetails.end();)
	{
		OID blockid = itblock->first;
		itblocklower = m_mulBlockDetails.lower_bound(blockid) ;
		itblockupper = m_mulBlockDetails.upper_bound(blockid) ;
		int flag = 5 ;
		int check_err = -1 ; // -1为没有出现，1为出现
		int check_ok = -1 ;
		int check_uncheck = -1 ;
		int optype_published = -1 ; // -1表示全部为published，否则存在

		while ( itblocklower != itblockupper)
		{
			PAIR_INT_OID pairl_f = itblocklower->second ;
			itstate = m_mapState.find( pairl_f) ;
			if ( itstate != m_mapState.end())
			{
				int featureflag = itstate->second ;
				if ( featureflag == BLOCK_STATUS_ERR )
				{
					check_err = 1 ;
				}
				else if ( featureflag == BLOCK_STATUS_UNCHECK )
				{
					check_uncheck = 1 ;
				}
				else if ( featureflag == BLOCK_STATUS_OK )
				{
					check_ok = 1 ;
				}
				else if ( featureflag == BLOCK_STATUS_PUBLISH )
				{
					optype_published = 1 ;
				}
			}
			itblocklower++ ;
			itblock++ ;
		}
		if ( check_err == 1)
		{
			flag = BLOCK_STATUS_ERR ;  // 质检失败
		}
		else if ( check_uncheck == 1)
		{
			flag = BLOCK_STATUS_UNCHECK ; // 待质检
		}
		else if ( check_ok == 1)
		{
			if ( optype_published== -1)
			{
				flag = BLOCK_STATUS_PUBLISH ; // 完成、关闭
			}
			else
			{
				flag = BLOCK_STATUS_OK ; // 质检通过
			}
		}
		else
		{
// 			CString strmess ;
// 			strmess.Format("4 check_err:%d ,check_uncheck:%d ,check_ok:%d ",check_err,check_uncheck,check_ok) ;
// 			
// 			AfxMessageBox(strmess) ;
		}
		mapBlockState.insert(MAP_OID_INT::value_type(blockid,flag)) ; // 记录block状态
	}

	//////////////////////////////////////////////////////////////////////////
	m_writelog->WriteLog("将block状态上传至数据库\n") ;

	CString strfront = "update tb_task_block set status = CASE id " ;
	CString strmid = "" ;
	CString strend = " end where id in(" ;
 
	MAP_OID_INT::iterator itblockstate ;
	MAP_OID_INT::iterator itoldblockstate ;
	int index = 0 ;
	int max_row = 1000 ;
	for ( itblockstate = mapBlockState.begin(); itblockstate != mapBlockState.end(); itblockstate++)
	{
		OID blockid = itblockstate->first ;
		int newstatus = itblockstate->second ;
		//////////////////////////////////////////////////////////////////////////
		// 检验block状态是否发生变化，状态没有发生变化就不更新
		// 如果想做状态未变化就不更新，最好是block未发生变化+block状态也未变化才不更新
// 		itoldblockstate = m_oldBlockStatus.find( blockid ) ;
// 		if (itoldblockstate != m_oldBlockStatus.end() )
// 		{
// 			int oldstatus = itoldblockstate->second ;
// 			if ( newstatus == oldstatus)
// 			{
// 				continue;// 状态一样，跳过
// 			}
// 		}
		//////////////////////////////////////////////////////////////////////////

		CString sblockid ;
		CString status ;
		sblockid.Format("%I64d", blockid) ;
		status.Format("%d", newstatus) ;
		
		strmid += " when " + sblockid + " then " + status ;
		strend += sblockid + "," ;

		index++ ;
		if ( index % max_row == 0)
		{
			if ( strmid.Find("when") != -1)
			{
				strend = strend.Left(strend.GetLength()-1) ;
				strend += ")" ;
			}

			CString sql = strfront + strmid + strend ;
			CTaskManager::GetTaskManager()->ExcuteSql( sql) ;
			strmid = "" ;
			strend = " end where id in(" ;
		}
	}

	if ( strmid.Find("when") != -1)
	{
		strend = strend.Left(strend.GetLength()-1) ;
		strend += ")" ;
		CString sql = strfront + strmid + strend ;
		CTaskManager::GetTaskManager()->ExcuteSql( sql) ;
		strmid = "" ;
		strend = " end where id in(" ;
	}
	m_mapState.clear() ;
	m_mulLayerDetails.clear() ;
	m_mulBlockDetails.clear() ;
	m_oldBlockStatus.clear() ;

	if ( m_pMap != NULL)
	{
		m_pMap->Release() ;
		m_pMap = NULL ;
	}

}*/


CString CCreateTask::GetLayerNameByLayerID( int layerid )
{
	CString strLayerName = "" ;
	if ( layerid == 1)
	{
		strLayerName = "Road" ;
	}
	else if ( layerid ==2)
	{
		strLayerName = "POI" ;
	}
	else if ( layerid == 3)
	{
		strLayerName = "VS" ;
	}
	else if ( layerid == 4)
	{
		strLayerName = "Trafficcam" ;
	}
	else if ( layerid == 5)
	{
		strLayerName = "WarnInfo" ;
	}
	else if ( layerid == 6)
	{
		strLayerName = "SpeedLimit" ;
	}
	else if ( layerid == 7)
	{
		strLayerName = "Obj" ;
	}
	else if ( layerid == 8)
	{
		strLayerName = "Railway" ;
	}
	else if ( layerid == 9)
	{
		strLayerName = "Vegetation" ;
	}
	else if ( layerid == 10)
	{
		strLayerName = "Water" ;
	}
	else if ( layerid ==11 )
	{
		strLayerName = "Island" ;
	}
	else if ( layerid == 12)
	{
		strLayerName = "BuildingLine" ;
	}
	else if ( layerid == 13)
	{
		strLayerName = "BuildingArea" ;
	}
	else if ( layerid == 14)
	{
		strLayerName = "Building" ;
	}
	else if ( layerid == 15)
	{
		strLayerName = "Xian" ;
	}
	else if ( layerid ==16 )
	{
		strLayerName = "Diqu" ;
	}
	else if ( layerid == 17)
	{
		strLayerName = "Province" ;
	}
	else if ( layerid ==18 )
	{
		strLayerName = "Country" ;
	}
	else if ( layerid == 19)
	{
		strLayerName = "Mesh" ;
	}
	else if ( layerid == 20)
	{
		strLayerName = "ErrorInfo" ;
	}
	else if ( layerid == 21)
	{
		strLayerName = "Questioninfo" ;
	}
	else if ( layerid == 22)
	{
		strLayerName = "MarkInfo" ;
	}
	else if ( layerid == 23)
	{
		strLayerName = "TestInfo" ;
	}
	else if ( layerid == 24)
	{
		strLayerName = "Junction" ;
	}
	else if ( layerid == 25)
	{
		strLayerName = "Compound" ;
	}
	else if ( layerid ==26 )
	{
		strLayerName = "TimeLimit" ;
	}
	return strLayerName ;
}

int CCreateTask::GetFeatureStatus(CFeature *pFeature, int &manualstatus)
{
	manualstatus = -1 ;
	if ( pFeature == NULL )
		return BLOCK_STATUS_UNKNOWN ;

	int flag = -1 ;// 默认为待质检task.tb_task_block.status，状态（1：待质检，3：质检通过，4：质检失败；5：关闭，完成，6：关闭，合并）
	int check_err = -1 ;			// -1为没有出现，1为出现
	int check_ok = -1 ;
	int check_uncheck = -1 ;
	int optype_published = 1 ;		// 1表示为published，-1为非pulished
	OpType type = IROT_Submit ;		// junction图层没有optype字段，结合init状态的数据不会被识别进block中，因此这里初值给IROT_Submit

	//////////////////////////////////////////////////////////////////////////
	// 这里是将optype属性和autocheck属性合成为一个状态信息
	CheckStatus status = pFeature->GetGeometryPtr()->GetAutoCheck() ;
	CheckStatus manulsatus = pFeature->GetGeometryPtr()->GetManuCheck() ;
	if ( manulsatus == IRCS_Error)
	{
		manualstatus = BLOCK_STATUS_MANUALERR ;
	}
	// optype = init 未进行修改，该要素的autocheck状态无效
	// optype = init 状态的数据，不应该会进入block里，因此这里无需此判断
	//	if ( type == IROT_Init )
	//		return BLOCK_STATUS_UNKNOWN ;

	// 如果要素的confirm状态不是 ready_for_qc 则认为要素的autocheck状态无效
	// 如果要素的optype状态是published 则可以无视confirm的状态

	ELayerType layertype = pFeature->GetOwnerLayerPtr()->GetLayerType() ;

	if ( layertype == JUNCTION_LAYER ) // 交叉点需要单独处理
	{
		// auto为error，即为4
		// aoto为uncheck，即为1
		// aoto如果为ok，检查manual是否ok，是则为5，否则置为3
		
		if ( status == IRCS_Error)
		{
			flag = BLOCK_STATUS_ERR ;
		}
		else if ( status == IRCS_NoCheck)
		{
			flag = BLOCK_STATUS_UNCHECK ;
		}
		else if ( status == IRCS_NoErr )
		{
			//////////////////////////////////////////////////////////////////////////
			// modified at 2017/11/21 begin
// 			if ( manulsatus == IRCS_NoErr )
// 			{
// 				flag = BLOCK_STATUS_PUBLISH ;
// 			}
// 			else 
// 			{
// 				flag = BLOCK_STATUS_OK ;
// 			}
			// 由于发布的状态不由本工具负责更新
			flag = BLOCK_STATUS_OK ;
			// modified at 2017/11/21 end
		//////////////////////////////////////////////////////////////////////////
		}
		return flag ;
	}
	else if ( pFeature->GetOwnerLayerPtr()->GetLayerType() == ROAD_LAYER )
	{
		type = pFeature->GetOpType() ;
		Confirm confirm = pFeature->GetGeometryPtr()->GetConfirm() ;
		if ( confirm == IRCF_ConfirmOK && type == IROT_Submit )
			return BLOCK_STATUS_UNKNOWN ;
	}

	// 关于autocheck的状态
	if ( status == IRCS_Error )
	{
		check_err = 1 ;
	}
	else if ( status == IRCS_NoErr )
	{
		check_ok = 1 ;
	}
	else if ( status == IRCS_NoCheck )
	{
		check_uncheck = 1 ;
	}
	// 关于optype的状态
	if ( type != IROT_Published )
	{
		optype_published = -1 ;
	}
	// 汇总
	if ( check_err == 1) // 第一顺位
	{
		flag = BLOCK_STATUS_ERR ;  // 质检失败
	}
	else if ( check_uncheck == 1) // 第二顺位
	{
		flag = BLOCK_STATUS_UNCHECK ; // 待质检
	}
	else if ( check_ok == 1 )
	{
		//////////////////////////////////////////////////////////////////////////
		// modified at 2017/11/19 begin
// 		if ( optype_published == 1) // 第四顺位
// 		{
// 			flag = BLOCK_STATUS_PUBLISH ; // 完成、关闭
// 		}
// 		else // 第三顺位
// 		{
// 			flag = BLOCK_STATUS_OK ; // 质检通过
// 		}
		// 由于发布的状态不由本工具负责更新
		flag = BLOCK_STATUS_OK ;
		// modified at 2017/11/19 end
		//////////////////////////////////////////////////////////////////////////
	}
	else
	{
		// 为什么会走到这里的呢？
		m_writelog->WriteLog("为什么会到这里呢？");
	}

	return flag ;
}

SGeoRect CCreateTask::GetFeatureBound( CFeature *pFeature )
{
	SGeoRect rect ;
	if ( pFeature != NULL)
	{
		rect = pFeature->GetBound() ;
	}
	return rect ;
}

bool CCreateTask::Load(int layerid, OID *ptempFeatureID, int feature_count)
{
	CString strLayerName = GetLayerNameByLayerID( layerid) ;
	CLayer *pLayer = m_pMap->GetOrMakeLayer(strLayerName) ;
	if ( pLayer == NULL)
		return false ;

	bool bload = pLayer->Load( ptempFeatureID, feature_count) ;
	if ( !bload )
	{
		CString strMsg ;
		strMsg.Format( "加载LayerId: %d, %d 条要素失败\n", layerid, feature_count ) ;
		m_writelog->WriteLog( strMsg ) ;
		return false ;
	}

	int index_junctype = -1 ;
	int manualstatus = -1 ;
	int index_owner = -1 ;
	//////////////////////////////////////////////////////////////////////////
	// 获取block中对象的逻辑检查状态，目视检查状态，bound信息
	CFeatureSet *pFeatureSet = pLayer->GetDataSourcePtr()/*GetAllFeaturesPtr()*/ ;
	if ( pFeatureSet != NULL)
	{
		CFeature *pFeature = pFeatureSet->GetFirstFeaturePtr() ;
		while ( pFeature)
		{
#if _DEBUG
			if ( pFeature->GetFID() == 20000003064076)
			{
				int a = 0 ;
			}
#endif
			if ( layerid == 24 )
			{
				if ( index_junctype == -1)
				{
					index_junctype = pFeature->GetAttrPtr()->GetIndex("JunctionType") ;
					if ( index_junctype == -1)
					{
						return false ;
					}
				}
				if ( index_junctype != -1)
				{
					int junctype = pFeature->GetAttrPtr()->GetIntByIndex( index_junctype) ;
					if ( junctype == 0)
					{
						// 形状点
						pFeature = pFeatureSet->GetNextFeaturePtr() ;
						continue;
					}
				}
			}
			

// 			CString strMsg;
// 			strMsg.Format( "图层ID：%d，对象ID：%I64d加载成功\n", layerid,pFeature->GetFID());
// 			m_writelog->WriteLog( strMsg ) ;
			int flag = GetFeatureStatus( pFeature, manualstatus) ;
			SGeoRect bound = GetFeatureBound( pFeature) ;
			PAIR_INT_OID pairl_f ;
			pairl_f.first = layerid ;
			pairl_f.second = pFeature->GetFID() ;
			if ( m_mapManualStatus.find(pairl_f) == m_mapManualStatus.end())
			{
				m_mapManualStatus.insert(MAP_OID_STATE::value_type( pairl_f, manualstatus)) ;
			}
			if ( m_mapState.find(pairl_f) == m_mapState.end() )
			{
				m_mapState.insert(MAP_OID_STATE::value_type( pairl_f, flag)) ;
			}
			if ( m_mapBound.find( pairl_f) == m_mapBound.end())
			{
				m_mapBound.insert(MAP_OID_BOUND::value_type( pairl_f, bound)) ;
			}

			if ( index_owner == -1)
			{
				index_owner = pFeature->GetAttrPtr()->GetIndex("Owner") ;
				if ( index_owner == -1)
				{
					return false ;
				}
			}
			int owner = pFeature->GetAttrPtr()->GetIntByIndex(index_owner) ;
			m_mapFeatureOwner.insert(MAP_LID_FID_BID::value_type( pairl_f,owner)) ;


			// 20180312
			CString manualcheck = GetFeatureManualCheck( pFeature) ;
			CString username = GetFeatureUserName(pFeature).c_str() ;
			m_mapFeatureUserName.insert(MAP_LID_FID_CSTRING::value_type( pairl_f, username)) ;
			m_mapFeatureManualCheck.insert(MAP_LID_FID_CSTRING::value_type( pairl_f, manualcheck)) ;
			pFeature = pFeatureSet->GetNextFeaturePtr() ;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// 获取block中被删除对象的bound信息
	CFeatureSet *pObsoluteFeatureSet = pLayer->GetObsoletedPtr()/*GetAllFeaturesPtr()*/ ;
	if ( pObsoluteFeatureSet != NULL)
	{
		CFeature *pFeature = pObsoluteFeatureSet->GetFirstFeaturePtr() ;
		while ( pFeature)
		{
// 			CString strMsg;
// 			strMsg.Format( "删除对象 图层ID：%d，对象ID：%I64d加载成功\n", layerid,pFeature->GetFID());
// 			m_writelog->WriteLog( strMsg );

			SGeoRect bound = GetFeatureBound( pFeature) ;
			PAIR_INT_OID pairl_f ;
			pairl_f.first = layerid ;
			pairl_f.second = pFeature->GetFID() ;
			if ( m_mapBound.find( pairl_f) == m_mapBound.end())
			{
				m_mapBound.insert(MAP_OID_BOUND::value_type( pairl_f, bound)) ;
			}

			// 20180326
			if ( index_owner == -1)
			{
				index_owner = pFeature->GetAttrPtr()->GetIndex("Owner") ;
				if ( index_owner == -1)
				{
					return false ;
				}
			}
			int owner = pFeature->GetAttrPtr()->GetIntByIndex(index_owner) ;
			m_mapFeatureOwner.insert(MAP_LID_FID_BID::value_type( pairl_f,owner)) ;

			// 20180312
			CString manualcheck = GetFeatureManualCheck( pFeature) ;
			CString username = GetFeatureUserName(pFeature).c_str() ;
			m_mapFeatureUserName.insert(MAP_LID_FID_CSTRING::value_type( pairl_f, username)) ;
			m_mapFeatureManualCheck.insert(MAP_LID_FID_CSTRING::value_type( pairl_f, manualcheck)) ;
			pFeature = pObsoluteFeatureSet->GetNextFeaturePtr() ;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// 2017-11-30 begin
	// 简化日志的内容，日志文件涨的太快
	CString strMsg ;
	strMsg.Format( "本次需从LayerId: %d 中加载, %d 条要素\n", layerid, feature_count ) ;
	m_writelog->WriteLog( strMsg ) ;
	strMsg.Format( "本次共从LayerId: %d 中加载, %d 条存在要素\n", layerid, pFeatureSet->GetFeatureCount() ) ;
	m_writelog->WriteLog( strMsg ) ;
	strMsg.Format( "本次共从LayerId: %d 中加载, %d 条删除要素\n", layerid, pObsoluteFeatureSet->GetFeatureCount() ) ;
	m_writelog->WriteLog( strMsg ) ;
	// 2017-11-30 end
	//////////////////////////////////////////////////////////////////////////

	m_pMap->ReleaseMemory() ;

	return true ;
}

bool CCreateTask::LoadBlockDetailStatus()
{
	//////////////////////////////////////////////////////////////////////////
	m_writelog->WriteLog("开始加载数据库blockdetail信息\n") ;
	vector< __int64 > vtblockid ;
	vector< int > vtlayerid ;
	vector< __int64 > vtfeatureid ;
	vector< int > vtstatus ;
	vector< _TSGEO::SGeoRect > vtbound ;
	vector< CString > vtUpdateTime ;
	vector< CString> vtmanualcheck ;
	vector< CString> vtusername ;
	vector< int > vtblockmanualroadnum ;
	vector< CString > vtblockusername ;
	vector< __int64> vtdetailID ;
	vector< int > vtowner ;
	vector< CString> vtblockowner ;
	// 20180312
	bool bload = CTaskManager::GetTaskManager()->LoadTaskDetail(vtblockid, vtlayerid, vtfeatureid, vtstatus, vtbound, vtUpdateTime,vtmanualcheck,
		vtusername,vtblockmanualroadnum, vtblockusername,vtdetailID,vtowner,vtblockowner) ;
	if ( !bload )
	{
		return false ;
	}
	//////////////////////////////////////////////////////////////////////////
	// modified at 20171201 begin
	// 发现没有满足要求的数据，并不能代表加载失败
// 	if ( vtfeatureid.size() == 0 )
// 	{
// 		return false ;
// 	}
	// modified at 20171201 end
	//////////////////////////////////////////////////////////////////////////

	m_mapManualStatus.clear() ;
	m_mapState.clear() ;
	m_mapBound.clear() ;
	m_mulLayerDetails.clear() ;
	m_mulBlockDetails.clear() ;
	m_oldBlockStatus.clear() ;
	m_mapBlockStatus.clear() ;
	m_mapBlockUpdateTime.clear() ;
	m_mapOldBlockBound.clear() ;
	m_mapBlockBound.clear() ;
	m_mapManualCheck.clear() ;
	m_mapUserName.clear() ;
	m_mapOwner.clear() ;
	m_mapBlockManualRoadnum.clear() ;
	m_mapBlockUserName.clear() ;
	m_mapBlockOwner.clear() ;
	m_mapFeatureUserName.clear() ;
	m_mapFeatureOwner.clear() ;
	m_mapFeatureManualCheck.clear() ;
	m_mapLID_FID_DetailID.clear() ;
	for ( int i = 0; i < vtfeatureid.size(); i++)
	{
		OID blockid = vtblockid[i] ;
		int layerid = vtlayerid[i] ;
		OID featureid = vtfeatureid[i] ;
		int status = vtstatus[i] ;
		CString updatetime = vtUpdateTime[i] ;
		_TSGEO::SGeoRect bound = vtbound[i] ;
		SGeoRect transbound = TransGeoRect( bound) ;
		PAIR_INT_OID pairl_f ;
		pairl_f.first = layerid ;
		pairl_f.second = featureid ;
		
		m_oldBlockStatus.insert(MAP_OID_INT::value_type(blockid, status)) ;
		m_mulBlockDetails.insert( MUL_BLOCK_OID::value_type(blockid, pairl_f)) ;
		m_mulLayerDetails.insert( MUL_LAYER_OID::value_type(layerid, featureid)) ;
		m_mapOldBlockBound.insert(MAP_BlOCK_BOUND::value_type( blockid, transbound)) ;
		m_mapBlockUpdateTime.insert(MAP_OID_CSTRING::value_type( blockid, updatetime)) ;

#if _DEBUG
		if ( featureid == 20000003064076)
		{
			int a = 0 ;
		}
#endif
		//20180312
		CString manualcheck=vtmanualcheck[i] ;
		CString username = vtusername[i] ;
		int blockmanualroadnum = vtblockmanualroadnum[i] ;
		CString blockusername = vtblockusername[i] ;
		OID detailid = vtdetailID[i] ;
		int owner = vtowner[i] ;
		CString strowner = vtblockowner[i] ;

		m_mapManualCheck.insert(MAP_LID_FID_CSTRING::value_type(pairl_f, manualcheck)) ;
		m_mapUserName.insert(MAP_LID_FID_CSTRING::value_type(pairl_f,username)) ;
		m_mapBlockManualRoadnum.insert(MAP_OID_INT::value_type(blockid, blockmanualroadnum)) ;
		m_mapBlockUserName.insert(MAP_OID_CSTRING::value_type(blockid,blockusername)) ;
		m_mapLID_FID_DetailID.insert(MAP_LID_FID_BID::value_type(pairl_f,detailid)) ;
		m_mapOwner.insert(MAP_LID_FID_BID::value_type( pairl_f, owner)) ;
		m_mapBlockOwner.insert(MAP_OID_CSTRING::value_type(blockid, strowner)) ;
	}

	vtblockid.clear() ;
	vtfeatureid.clear() ;
	vtlayerid.clear() ;
	vtstatus.clear() ;
	vtbound.clear() ;
	vtUpdateTime.clear() ;
	vtowner.clear() ;
	vtdetailID.clear() ;
	vtblockmanualroadnum.clear() ;
	vtblockusername.clear() ;
	vtusername.clear() ;
	vtmanualcheck.clear() ;
	vtblockowner.clear() ;
	m_writelog->WriteLog("完成加载数据库blockdetail信息\n") ;
	//////////////////////////////////////////////////////////////////////////
	m_writelog->WriteLog("开始根据featureid加载对象并提取对象状态\n") ;
	// 遍历所有对象的属性状态
	// 获取对象的状态：待质检，质检失败，质检成功，关闭-合并，关闭-发布
	// 将全部非关闭状态block内的要素的最新状态信息加载进内存
	int total_feature_count = 0 ;
	MUL_LAYER_OID::iterator itlower ;
	MUL_LAYER_OID::iterator itupper ;
	bool load_data_status = false ;
	for ( MUL_LAYER_OID::iterator itlayer = m_mulLayerDetails.begin(); itlayer != m_mulLayerDetails.end();)
	{
		int layerid = itlayer->first ;
		CString strLayerName = GetLayerNameByLayerID(layerid) ;
		int index = 0 ;
		itlower = m_mulLayerDetails.lower_bound( layerid) ;
		itupper = m_mulLayerDetails.upper_bound( layerid) ;

		int icount = m_mulLayerDetails.count(layerid) ;
		OID *ptempFeatureID = new OID[LOAD_UNIT_COUNT] ;
		while ( itlower != itupper)
		{
			OID featureid = itlower->second ;

			total_feature_count ++ ;
			ptempFeatureID[index] = featureid ;		
			index++ ;

			// 个数到达LOAD_UNIT_COUNT时，就加载
			if ( index == LOAD_UNIT_COUNT )
			{
				load_data_status = Load( layerid, ptempFeatureID, index ) ;
				index = 0 ;
				if ( !load_data_status )
				{
					delete []ptempFeatureID ;
					return false ;
				}
			}
			itlower++ ;
			itlayer++ ; 
		}

		if ( index > 0 )
		{
			load_data_status = Load( layerid, ptempFeatureID, index ) ;
			if ( !load_data_status )
			{
				delete []ptempFeatureID ;
				return false ;
			}
		}

		if ( ptempFeatureID != NULL )
		{
			delete []ptempFeatureID ;
 			ptempFeatureID = NULL ;
		}
	}

	CString strMsg;
	strMsg.Format( "本次共计加载了 %d 个要素\n", total_feature_count );
	m_writelog->WriteLog( strMsg );
	m_writelog->WriteLog("完成根据featureid加载对象并提取对象状态\n");
	//////////////////////////////////////////////////////////////////////////

	return true ;
}

// void CCreateTask::UpdateBlockStatus()
// {
// 	//////////////////////////////////////////////////////////////////////////
// 	m_writelog->WriteLog("开始获取block的最新状态\n") ;
// 	// 更新每个block的状态
// 	MAP_OID_STATE::iterator itstate ;
// 	MUL_BLOCK_OID::iterator itblocklower ;
// 	MUL_BLOCK_OID::iterator itblockupper ;
// 	MAP_OID_BOUND::iterator itbound ;
// 	bool	have_backto_worker_block = false ;
// 
// 	MAP_OID_INT::iterator itoldstate ;
// 	
// // 	m_mapConfirm.clear() ;
// 
// 	for ( MUL_BLOCK_OID::iterator itblock = m_mulBlockDetails.begin(); itblock != m_mulBlockDetails.end();)
// 	{
// 		OID blockid = itblock->first;
// 		int oldstate = -1 ;  
// 		itoldstate = m_oldBlockStatus.find( blockid) ;
// 		if ( itoldstate != m_oldBlockStatus.end())
// 		{
// 			oldstate = itoldstate->second ;
// 		}
// 
// 		itblocklower = m_mulBlockDetails.lower_bound(blockid) ;
// 		itblockupper = m_mulBlockDetails.upper_bound(blockid) ;
// 		int flag = 5 ;
// 		bool check_err = false ;		// false为没有出现，1为出现
// 		bool check_ok = false ;
// 		bool check_uncheck = false ;
// 		bool optype_published = false ;
// 		bool confirm_no_readyforqc = false ; 
// 
// 		bool bhasFeature = false ;
// 
// 		SGeoRect rectblock ;
// 
// 		int nofeature = 0 ;
// 		CString strtest = "" ;
// 		int manualstatus = -1 ;
// 		//////////////////////////////////////////////////////////////////////////
// 		// 依次取得该block内所有要素的状态信息
// 
// 		CString strMsg ;
// 		strMsg.Format( "blockid: %I64d 开始运行\n", blockid );
// 				m_writelog->WriteLog( strMsg ) ;
// 
// 		while ( itblocklower != itblockupper)
// 		{
// 			PAIR_INT_OID pairl_f = itblocklower->second ;
// 			itstate = m_mapState.find( pairl_f) ;
// 
// 			itbound = m_mapBound.find( pairl_f) ;
// 			if ( itbound != m_mapBound.end())
// 			{
// 				if ( rectblock.x_max == -1 && itbound->second.x_max != -1)
// 				{
// 					rectblock = itbound->second ;
// 				}
// 				else
// 				{
// 					if (rectblock.x_max != -1 && itbound->second.x_max != -1)
// 					{
// 						rectblock.Union(itbound->second) ;
// 					}
// 				}
// 			}
// 
// 			if ( itstate != m_mapState.end())
// 			{
// 				bhasFeature = true ;
// 				int featureflag = itstate->second ;
// 				if ( featureflag == BLOCK_STATUS_ERR )
// 				{
// 					CString strMsg ;
// 					strMsg.Format( "blockid: %I64d 存在逻辑错误%d,%I64d\n", blockid,pairl_f.first, pairl_f.second );
// 					m_writelog->WriteLog( strMsg ) ;
// 					check_err = true ;
// 				}
// 				else if ( featureflag == BLOCK_STATUS_UNCHECK )
// 				{
// 					check_uncheck = true ;
// 				}
// 				else if ( featureflag == BLOCK_STATUS_OK )
// 				{
// 					check_ok = true ;
// 				}
// 				else if ( featureflag == BLOCK_STATUS_PUBLISH )
// 				{
// 					optype_published = true ;
// 				}
// 				else if ( featureflag == BLOCK_STATUS_UNKNOWN )
// 				{
// 					confirm_no_readyforqc = true ;
// 				}
// 			}
// 			else
// 			{
// 				nofeature++ ;
// 				CString msg = "" ;
// 				msg.Format("%I64d", pairl_f.second) ;
// 				strtest += msg + "," ;
// 			}
// 
// 
// 			MAP_OID_STATE::iterator itmanual = m_mapManualStatus.find( pairl_f) ;
// 			if ( itmanual != m_mapManualStatus.end())
// 			{
// 				int tempstatus = itmanual->second ;
// 				if ( tempstatus == BLOCK_STATUS_MANUALERR)
// 				{
// 					manualstatus = BLOCK_STATUS_MANUALERR ;
// 					CString strMsg ;
// 					strMsg.Format( "blockid: %I64d 存在目视错误%d,%I64d\n", blockid,pairl_f.first, pairl_f.second );
// 					m_writelog->WriteLog( strMsg ) ;
// 				}
// 			}
// 
// 			itblocklower++ ;
// 			itblock++ ;
// 		}
// 		
// 		m_mapBlockBound.insert(MAP_BlOCK_BOUND::value_type(blockid,rectblock)) ;
// 
// 		if ( !bhasFeature && oldstate != 3 && oldstate != 1)
// 		{
// 			// 如果该block对应的对象（道路和交叉点）都被删除了，那么将该block关闭
// 			m_mapBlockStatus.insert(MAP_OID_INT::value_type(blockid,1 )) ; // 记录block状态
// 			continue;
// 		}
// 
// 		//////////////////////////////////////////////////////////////////////////
// 		// 如果某个block中既存在 ready_for_qc+err 和 ready_for_qc+uncheck状态的数据
// 		// 则回退该block里状态为ready_for_qc+uncheck 的道路给作业员
// /*
// 		if ( (check_err || manualstatus == BLOCK_STATUS_MANUALERR)&& check_uncheck )
// 		{
// 			CString strMsg ;
// 			strMsg.Format( "blockid: %d 回退，status: %d\n", blockid, flag );
// 				m_writelog->WriteLog( strMsg ) ;
// 			BacktoWorker( blockid ) ;
// 			have_backto_worker_block = true ;
// 			confirm_no_readyforqc = true ;
// 		}
// */
// 
// 		// 如果用户均提交质检
// 		if ( !confirm_no_readyforqc )
// 		{
// 			flag = GetBlockStatus( check_err, check_ok, check_uncheck, optype_published );
// 			if ( flag == BLOCK_STATUS_UNKNOWN )// 不应该存在这种情况
// 			{
// 				CString strMsg ;
// 				strMsg.Format( "blockid: %d 状态错误，status: %d\n", blockid, flag );
// 				m_writelog->WriteLog( strMsg ) ;
// 			}
// 			//////////////////////////////////////////////////////////////////////////
// 			// modified at 2017-11-16 begin
// // 			else if ( flag == BLOCK_STATUS_ERR && manualstatus != BLOCK_STATUS_MANUALERR)// 理论上来说，状态为3的道路不会存在逻辑错误，此处为避免出现极端情况
// // 			{
// // 				if ( oldstate == 3)
// // 				{
// // 					// 如果原先是status为3，现在有err，改为1
// // 					m_mapBlockStatus.insert(MAP_OID_INT::value_type(blockid,1)) ;
// // 				}
// // 			}
// 			else if (flag == BLOCK_STATUS_ERR && check_uncheck ) // block的数据状态仅为 err+uncheck[+ok]状态时，需将block的状态变更为 待质检
// 			{
// 				m_mapBlockStatus.insert( MAP_OID_INT::value_type(blockid,1) );
// 			}
// 			//////////////////////////////////////////////////////////////////////////
// 			else if ( flag == BLOCK_STATUS_OK )// 理论上来说，状态为4的道路不会存在目视错误，此处为避免出现极端情况
// 			{
// 				if ( oldstate == 4)
// 				{
// 					// 如果原先status4,现在都是Ok，改为1
// 					m_mapBlockStatus.insert(MAP_OID_INT::value_type(blockid,1)) ;
// 				}
// 			}
// 			else
// 			{
// 				if ( oldstate == 3 && manualstatus == BLOCK_STATUS_MANUALERR) // 如果校正中的block，存在目视错误，则不予更新；否则会导致校正任务失效
// 				{
// 					CString strMsg ;
// 					strMsg.Format( "block: %d 校正中的block存在目视错误，不予更新状态\n", blockid );
// 					m_writelog->WriteLog( strMsg ) ;
// 				}
// 				else if ( flag != 3 && flag !=4 && flag != 5) // 如果某个block状态中不存在confirm_ok的状态，并且存在ready_for_qc+uncheck的状态，则置为1
// 				{
// 					// 如果一个block的状态更新为3、4时，该工具不再设为3、4，由质检去生成这两个状态
// 					m_mapBlockStatus.insert(MAP_OID_INT::value_type(blockid,flag)) ; // 记录block状态
// 				}
// 			}
// 		}
// 		//////////////////////////////////////////////////////////////////////////
// 		// added ad 2017-6-15 begin
// 		// block 中发现未提交质检与质检失败（confirm_ok+uncheck和ready_for_qc+err）并存时需要能够将block的状态修改为 质检失败
// 		// 因为有可能block原本的状态是质检成功，此时需要变更为质检失败
// 		else if ( confirm_no_readyforqc && check_err )
// 		{
// 			MAP_OID_INT::iterator it = m_oldBlockStatus.find(blockid) ;
// 			if (it != m_oldBlockStatus.end())
// 			{
// 				int oldstatus = it->second ;
// 				if (BLOCK_STATUS_ERR != oldstatus)
// 				{
// 					if ( BLOCK_STATUS_ERR != 3 && BLOCK_STATUS_ERR !=4 && BLOCK_STATUS_ERR !=5)
// 					{
// 						// 如果一个block的状态更新为3、4时，该工具不再设为3、4，由质检去生成这两个状态
// 						m_mapBlockStatus.insert(MAP_OID_INT::value_type(blockid,BLOCK_STATUS_ERR)) ; // 记录block状态
// 					}
// 				}
// 	 		}
// 		}
// 		// added at 2017-6-15 end
// 		//////////////////////////////////////////////////////////////////////////
// 		else
// 		{
// 			CString strMsg ;
// 			strMsg.Format( "block: %d 尚未重新提交质检，不予更新状态\n", blockid );
// 			m_writelog->WriteLog( strMsg ) ;
// 		}
// 	}
// 	m_writelog->WriteLog("完成获取block的最新状态\n") ;
// 	//////////////////////////////////////////////////////////////////////////
// 
// 	// 存在被退回的block，需要修改block的状态
// 	// 20171026 屏蔽被退回的逻辑
// /*
// 	UpdateConfirm() ;
// 	
// 	m_mapConfirm.clear() ;
// 
// 
// 	if ( have_backto_worker_block )
// 		m_pMap->Save() ;
// 
// 	m_pMap->ReleaseMemory() ;
// */
// 
// }

void CCreateTask::UpdateBlockStatus_Version2()
{
	//////////////////////////////////////////////////////////////////////////
	// 2017-11-16 
	// Version 1
	// 只要block中不存在confirm_ok+submit状态的数据，且有用户提交了质检，就可以将block的状态由(3/4)改为1
	//////////////////////////////////////////////////////////////////////////
	m_writelog->WriteLog("开始获取block的最新状态\n") ;
	// 更新每个block的状态
	MAP_OID_STATE::iterator itstate ;
	MUL_BLOCK_OID::iterator itblocklower ;
	MUL_BLOCK_OID::iterator itblockupper ;
	MAP_OID_BOUND::iterator itbound ;
	bool	have_backto_worker_block = false ;

	MAP_OID_INT::iterator itoldstate ;
	for ( MUL_BLOCK_OID::iterator itblock = m_mulBlockDetails.begin(); itblock != m_mulBlockDetails.end();)
	{
		OID blockid = itblock->first;
		int oldstate = -1 ;  
		itoldstate = m_oldBlockStatus.find( blockid) ;
		if ( itoldstate != m_oldBlockStatus.end())
		{
			oldstate = itoldstate->second ;
		}

		itblocklower = m_mulBlockDetails.lower_bound(blockid) ;
		itblockupper = m_mulBlockDetails.upper_bound(blockid) ;
		int flag = 5 ;
		bool check_err = false ;		// false为没有出现，1为出现
		bool check_ok = false ;
		bool check_uncheck = false ;
		bool optype_published = false ;
		bool confirm_no_readyforqc = false ; 
		bool bhasFeature = false ;

		SGeoRect rectblock ;

		int nofeature = 0 ;
		CString strtest = "" ;
		int manualstatus = -1 ;
#ifdef _DEBUG 
	blockid = blockid;
#endif
		//////////////////////////////////////////////////////////////////////////
		// 依次取得该block内所有要素的状态信息 begin

		CString strMsg ;
		strMsg.Format( "blockid: %I64d 开始运行\n", blockid );
				m_writelog->WriteLog( strMsg ) ;

		while ( itblocklower != itblockupper)
		{
			PAIR_INT_OID pairl_f = itblocklower->second ;
			itstate = m_mapState.find( pairl_f) ;

			itbound = m_mapBound.find( pairl_f) ;
			if ( itbound != m_mapBound.end())
			{
				if ( rectblock.x_max == -1 && itbound->second.x_max != -1)
				{
					rectblock = itbound->second ;
				}
				else
				{
					if (rectblock.x_max != -1 && itbound->second.x_max != -1)
					{
						rectblock.Union(itbound->second) ;
					}
				}
			}

			if ( itstate != m_mapState.end())
			{
				bhasFeature = true ;
				int featureflag = itstate->second ;
				if ( featureflag == BLOCK_STATUS_ERR )
				{
					CString strMsg ;
					strMsg.Format( "blockid: %I64d 存在逻辑错误%d,%I64d\n", blockid,pairl_f.first, pairl_f.second );
					m_writelog->WriteLog( strMsg ) ;
					check_err = true ;
				}
				else if ( featureflag == BLOCK_STATUS_UNCHECK )
				{
					if ( pairl_f.first == 24 )
					{
					}
					else
					{
						check_uncheck = true ;
					}
				}
				else if ( featureflag == BLOCK_STATUS_OK )
				{
					check_ok = true ;
				}
				else if ( featureflag == BLOCK_STATUS_PUBLISH )
				{
					optype_published = true ;
				}
				else if ( featureflag == BLOCK_STATUS_UNKNOWN )
				{
					confirm_no_readyforqc = true ;
				}
				
			}
			else
			{
				nofeature++ ;
				CString msg = "" ;
				msg.Format("%I64d", pairl_f.second) ;
				strtest += msg + "," ;
			}



			MAP_OID_STATE::iterator itmanual = m_mapManualStatus.find( pairl_f) ;
			if ( itmanual != m_mapManualStatus.end())
			{
				int tempstatus = itmanual->second ;
				if ( tempstatus == BLOCK_STATUS_MANUALERR)
				{
					manualstatus = BLOCK_STATUS_MANUALERR ;
					CString strMsg ;
					strMsg.Format( "blockid: %I64d 存在目视错误%d,%I64d\n", blockid,pairl_f.first, pairl_f.second );
					m_writelog->WriteLog( strMsg ) ;
				}
			}

			itblocklower++ ;
			itblock++ ;
		}

		m_writelog->WriteLog( strtest ) ;
		m_mapBlockBound.insert(MAP_BlOCK_BOUND::value_type(blockid,rectblock)) ;
		// 依次取得该block内所有要素的状态信息 end
		//////////////////////////////////////////////////////////////////////////


		// 如果该block中的对象（道路和交叉点）均被删除，那么将该block修改为BLOCK_STATUS_UNCHECK
		// 由质检程序修改为BLOCK_STATUS_OK，避免由本程序修改为BLOCK_STATUS_OK
		if ( !bhasFeature && oldstate != BLOCK_STATUS_OK && oldstate != BLOCK_STATUS_UNCHECK )
		{
			m_mapBlockStatus.insert( MAP_OID_INT::value_type(blockid,BLOCK_STATUS_UNCHECK )) ;
			continue ;
		}

		//////////////////////////////////////////////////////////////////////////
		// 如果用户均提交质检
		if ( !confirm_no_readyforqc )
		{
			flag = GetBlockStatus( check_err, check_ok, check_uncheck, optype_published );
			if ( flag == BLOCK_STATUS_UNKNOWN )// 不应该存在这种情况
			{
				CString strMsg ;
				strMsg.Format( "blockid: %d 状态错误，status: %d\n", blockid, flag );
				m_writelog->WriteLog( strMsg ) ;
			}
			// block内数据状态仅为 err+uncheck状态时，需将block的状态变更为待质检
			else if (flag == BLOCK_STATUS_ERR && check_uncheck ) 
			{
				m_mapBlockStatus.insert( MAP_OID_INT::value_type(blockid, BLOCK_STATUS_UNCHECK) );
			}
			// 会在后面比较状态是否一致，不在这里进行比较
			else if ( flag == BLOCK_STATUS_UNCHECK /*&& oldstate != BLOCK_STATUS_UNCHECK*/ ) 
			{
				m_mapBlockStatus.insert( MAP_OID_INT::value_type(blockid, BLOCK_STATUS_UNCHECK) );
			}
			//////////////////////////////////////////////////////////////////////////
			// 2017-11-21 added begin
			// 增加异常状态的处理：block识别时如果block的发生了修改，会先将block的状态修改为BLOCK_STATUS_ERR
			// 因此这里需要判断 如果block之前的状态是BLOCK_STATUS_ERR，且block内要素的状态又没有错，需要将block状态修改为BLOCK_STATUS_UNCHECK
			else if ( flag == BLOCK_STATUS_OK && oldstate == BLOCK_STATUS_ERR )
			{
				m_mapBlockStatus.insert( MAP_OID_INT::value_type(blockid, BLOCK_STATUS_UNCHECK) );
			}
			// 2017-11-21 added end
			//////////////////////////////////////////////////////////////////////////
		}
		//////////////////////////////////////////////////////////////////////////
		// added ad 2017-6-15 begin
		// block 中发现未提交质检与质检失败（confirm_ok+uncheck和ready_for_qc+err）并存时需要能够将block的状态修改为 质检失败
		// 因为有可能block原本的状态是质检成功，合并导致变更为质检失败
		else if ( confirm_no_readyforqc && check_err )
		{
			MAP_OID_INT::iterator it = m_oldBlockStatus.find(blockid) ;
			if (it != m_oldBlockStatus.end())
			{
				int oldstatus = it->second ;
				if ( BLOCK_STATUS_ERR != oldstatus  )
				{
					// 如果一个block的状态更新为3、4时，该工具不再设为3、4，由质检去生成这两个状态
// 					m_mapBlockStatus.insert(MAP_OID_INT::value_type(blockid,BLOCK_STATUS_ERR)) ; // 记录block状态
				}
	 		}
		}
		// added at 2017-6-15 end
		//////////////////////////////////////////////////////////////////////////
		else
		{
			CString strMsg ;
			strMsg.Format( "block: %d 尚未重新提交质检，不予更新状态\n", blockid );
			m_writelog->WriteLog( strMsg ) ;
		}
	}
	m_writelog->WriteLog("完成获取block的最新状态\n") ;
	//////////////////////////////////////////////////////////////////////////
}

 // 作废
// void CCreateTask::UpdateBlockStatustest()
// {
// 	//////////////////////////////////////////////////////////////////////////
// 	m_writelog->WriteLog("开始获取block的最新状态\n") ;
// 
// 	m_mapConfirm.clear() ;
// 	// 更新每个block的状态
// 	MAP_OID_STATE::iterator itstate ;
// 	MUL_BLOCK_OID::iterator itblocklower ;
// 	MUL_BLOCK_OID::iterator itblockupper ;
// 	MAP_OID_BOUND::iterator itbound ;
// 	bool	have_backto_worker_block = false ;
// 
// 	MAP_OID_INT::iterator itoldstate ;
// 
// 	for ( MUL_BLOCK_OID::iterator itblock = m_mulBlockDetails.begin(); itblock != m_mulBlockDetails.end();)
// 	{
// 		OID blockid = itblock->first;
// 		if ( blockid == 8752)
// 		{
// 			int a = 0 ;
// 		}
// 
// 
// 		int oldstate = -1 ;  
// 		itoldstate = m_oldBlockStatus.find( blockid) ;
// 		if ( itoldstate != m_oldBlockStatus.end())
// 		{
// 			oldstate = itoldstate->second ;
// 		}
// 
// 		itblocklower = m_mulBlockDetails.lower_bound(blockid) ;
// 		itblockupper = m_mulBlockDetails.upper_bound(blockid) ;
// 		int flag = 5 ;
// 		bool check_err = false ;		// false为没有出现，1为出现
// 		bool check_ok = false ;
// 		bool check_uncheck = false ;
// 		bool optype_published = false ;
// 		bool confirm_no_readyforqc = false ; 
// 
// 		bool bhasFeature = false ;
// 
// 		SGeoRect rectblock ;
// 
// 		int nofeature = 0 ;
// 		CString strtest = "" ;
// 		//////////////////////////////////////////////////////////////////////////
// 		// 依次取得该block内所有要素的状态信息
// 		int index = 0 ;
// 		while ( itblocklower != itblockupper)
// 		{
// 			index++ ;
// 			PAIR_INT_OID pairl_f = itblocklower->second ;
// 			itstate = m_mapState.find( pairl_f) ;
// 
// 			CString msg ;
// 			CString errorlog = "" ;
// 			msg.Format("lid:%d fid:%I64d", pairl_f.first, pairl_f.second) ;
// 			errorlog += msg ;
// 
// 			itbound = m_mapBound.find( pairl_f) ;
// 			if ( itbound != m_mapBound.end())
// 			{
// 				msg = GetBoundByRect(itbound->second) ;
// 				errorlog += " bound:"+msg ;
// 				if ( index == 1)
// 				{
// 					rectblock = itbound->second ;
// 					msg= GetBoundByRect( rectblock) ;
// 					errorlog += msg ;
// 				}
// 				else
// 				{
// 					if ( rectblock.x_max != -1)
// 					{
// 						rectblock.Union(itbound->second) ;
// 						msg= GetBoundByRect( rectblock) ;
// 						errorlog += msg ;
// 					}
// 					else
// 					{
// 						rectblock = itbound->second ;
// 						msg= GetBoundByRect( rectblock) ;
// 						errorlog += msg ;
// 					}
// 				}
// 			}
// 
// 			if ( itstate != m_mapState.end())
// 			{
// 				bhasFeature = true ;
// 				int featureflag = itstate->second ;
// 				if ( featureflag == BLOCK_STATUS_ERR )
// 				{
// 					check_err = true ;
// 				}
// 				else if ( featureflag == BLOCK_STATUS_UNCHECK )
// 				{
// 					check_uncheck = true ;
// 				}
// 				else if ( featureflag == BLOCK_STATUS_OK )
// 				{
// 					check_ok = true ;
// 				}
// 				else if ( featureflag == BLOCK_STATUS_PUBLISH )
// 				{
// 					optype_published = true ;
// 				}
// 				else if ( featureflag == BLOCK_STATUS_UNKNOWN )
// 				{
// 					confirm_no_readyforqc = true ;
// 				}
// 			}
// 			else
// 			{
// 				nofeature++ ;
// 				CString msg = "" ;
// 				msg.Format("%I64d", pairl_f.second) ;
// 				strtest += msg + "," ;
// 			}
// 			errorlog += "\n" ;
// 			m_writelog->WriteLog( errorlog) ;
// 			itblocklower++ ;
// 			itblock++ ;
// 		}
// 		
// 		CString msg= GetBoundByRect( rectblock) ;
// 		msg += "\n" ;
// 		m_writelog->WriteLog( msg) ;
// 		m_mapBlockBound.insert(MAP_BlOCK_BOUND::value_type(blockid,rectblock)) ;
// 
// 		if ( !bhasFeature)
// 		{
// 			// 如果该block对应的对象（道路和交叉点）都被删除了，那么将该block关闭
// 			m_mapBlockStatus.insert(MAP_OID_INT::value_type(blockid,BLOCK_STATUS_OK)) ; // 记录block状态
// 			continue;
// 		}
// 
// 		//////////////////////////////////////////////////////////////////////////
// 		// 如果某个block中既存在 ready_for_qc+err 和 ready_for_qc+uncheck状态的数据
// 		// 则回退该block里状态为ready_for_qc+uncheck 的道路给作业员
// 		if ( check_err && check_uncheck )
// 		{
// 			BacktoWorker( blockid ) ;
// 			have_backto_worker_block = true ;
// 		}
// 
// 		
// 
// 		// 如果用户尚未提交质检，则不予更新block的状态
// 		if ( !confirm_no_readyforqc )
// 		{
// 			flag = GetBlockStatus( check_err, check_ok, check_uncheck, optype_published );
// 			if ( flag == BLOCK_STATUS_UNKNOWN )
// 			{
// 				CString strMsg ;
// 				strMsg.Format( "blockid: %d 状态错误，status: %d\n", blockid, flag );
// 				m_writelog->WriteLog( strMsg ) ;
// 			}
// 			else if ( flag == BLOCK_STATUS_ERR)
// 			{
// 				if ( oldstate == 3)
// 				{
// 					// 如果原先是status为3，现在有err，改为1
// 					m_mapBlockStatus.insert(MAP_OID_INT::value_type(blockid,1)) ;
// 				}
// 			}
// 			else if ( flag == BLOCK_STATUS_OK)
// 			{
// 				if ( oldstate == 4)
// 				{
// 					// 如果原先status4,现在都是Ok，改为1
// 					m_mapBlockStatus.insert(MAP_OID_INT::value_type(blockid,1)) ;
// 				}
// 			}
// 			else
// 			{
// 				if ( flag != 3 && flag !=4 && flag != 5)
// 				{
// 					// 如果一个block的状态更新为3、4时，该工具不再设为3、4，由质检去生成这两个状态
// 					m_mapBlockStatus.insert(MAP_OID_INT::value_type(blockid,flag)) ; // 记录block状态
// 				}
// 			}
// 		}
// 		//////////////////////////////////////////////////////////////////////////
// 		// added ad 2017-6-15 begin
// 		// block 中发现未提交质检与质检失败（confirm_ok+uncheck和ready_for_qc+err）并存时需要能够将block的状态修改为 质检失败
// 		// 因为有可能block原本的状态是质检成功，此时需要变更为质检失败
// 		else if ( confirm_no_readyforqc && check_err )
// 		{
// 			MAP_OID_INT::iterator it = m_oldBlockStatus.find(blockid) ;
// 			if (it != m_oldBlockStatus.end())
// 			{
// 				int oldstatus = it->second ;
// 				if (BLOCK_STATUS_ERR != oldstatus)
// 				{
// 					if ( BLOCK_STATUS_ERR != 3 && BLOCK_STATUS_ERR !=4 && BLOCK_STATUS_ERR !=5)
// 					{
// 						// 如果一个block的状态更新为3、4时，该工具不再设为3、4，由质检去生成这两个状态
// 						m_mapBlockStatus.insert(MAP_OID_INT::value_type(blockid,BLOCK_STATUS_ERR)) ; // 记录block状态
// 					}
// 				}
// 	 		}
// 		}
// 		// added at 2017-6-15 end
// 		//////////////////////////////////////////////////////////////////////////
// 		else
// 		{
// 			CString strMsg ;
// 			strMsg.Format( "block: %d 尚未重新提交质检，不予更新状态\n", blockid );
// 			m_writelog->WriteLog( strMsg ) ;
// 		}
// 	}
// 	m_writelog->WriteLog("完成获取block的最新状态\n") ;
// 	//////////////////////////////////////////////////////////////////////////
// 
// 	// 存在被退回的block，需要修改block的状态
// 	if ( have_backto_worker_block )
// 		m_pMap->Save() ;
// 
// 	m_pMap->ReleaseMemory() ;
// 
// 	m_mapConfirm.clear() ;
// 
// }
int CCreateTask::GetBlockStatus(bool is_err, bool is_ok, bool is_uncheck, bool is_publish)
{
	//////////////////////////////////////////////////////////////////////////
	// 质检失败		的优先级最高，只要有错误，就是错误状态
	// 待质检		的优先级次之，uncheck+ok+publish 都是uncheck
	// 质检成功		的优先级再次，ok+publish是ok
	// 已发布		的优先级最低，全部都是publish时，才是已发布	
	if ( is_err )
		return BLOCK_STATUS_ERR ;			// 质检失败；

	if ( is_uncheck )
		return BLOCK_STATUS_UNCHECK ;		// 待质检；

	if ( is_ok )
		return BLOCK_STATUS_OK ;			// 质检成功；

	if ( is_publish )
		return BLOCK_STATUS_PUBLISH ;		// 已发布；

	return -1 ;
}

void CCreateTask::UpLoadBlockStatus()
{
	//////////////////////////////////////////////////////////////////////////
	m_writelog->WriteLog("开始将block状态上传至数据库\n") ;
	CTaskManager::GetTaskManager()->SetChoosingTask() ;

	CString strfront = "update tb_task_block set status = CASE id " ;
	CString strmid = "" ;
	CString strrects = "" ;
	CString strupdatetime = "" ;
	CString strend = " end where id in(" ;
 
	MAP_OID_INT::iterator itblockstate ;
	MAP_OID_INT::iterator itoldblockstate ;

	MAP_BlOCK_BOUND::iterator itoldbound ;
	MAP_BlOCK_BOUND::iterator itnewbound ;

	MAP_OID_CSTRING::iterator itupdatetime ;

	int index = 0 ;
	int max_row = 500 ;
	for ( itblockstate = m_mapBlockStatus.begin(); itblockstate != m_mapBlockStatus.end(); itblockstate++)
	{
		OID blockid = itblockstate->first ;
		int newstatus = itblockstate->second ;

		//////////////////////////////////////////////////////////////////////////
		// 检验block状态是否发生变化，状态没有发生变化就不更新
		// 如果想做状态未变化就不更新，最好是block未发生变化+block状态也未变化才不更新

		// 20170904
		itoldbound = m_mapOldBlockBound.find( blockid) ;
		itnewbound = m_mapBlockBound.find( blockid) ;
		SGeoRect newbound ;
		SGeoRect oldbound ;
		CString stroldbound ;
		CString strnewbound ;

		if ( itoldbound != m_mapOldBlockBound.end())
		{
			oldbound = itoldbound->second ;
		}
		if ( itnewbound != m_mapBlockBound.end())
		{
			newbound = itnewbound->second ;
		}

		CString strtempNewBound = GetBoundByRect( newbound) ;

		stroldbound = GetBoundByRect(oldbound) ;

		int megerflag = CompareTwoBound( oldbound, newbound, newbound) ;
		strnewbound = GetBoundByRect(newbound) ;

		// 2017-6-289
		itoldblockstate = m_oldBlockStatus.find( blockid ) ;
		int oldstatus = -1 ;
		if (itoldblockstate != m_oldBlockStatus.end() )
		{
			oldstatus = itoldblockstate->second ;
			if ( newstatus == oldstatus && (( fabs(oldbound.x_min - newbound.x_min) < 1e-6 &&fabs(oldbound.x_max - newbound.x_max) < 1e-6 &&
				fabs(oldbound.y_min - newbound.y_min) < 1e-6 && fabs(oldbound.y_max - newbound.y_max) < 1e-6 )))
			{
				continue;// 状态一样，跳过
			}
		}
		//////////////////////////////////////////////////////////////////////////

		///////////////////////////////日志测试
		CString tempmsg ;
		tempmsg.Format("%I64d",blockid) ;
		CString errorlog = "blockid:" ;
		errorlog += tempmsg ;
		errorlog += "		" ;
		tempmsg.Format("%d",oldstatus) ;
		errorlog += "oldstatus:" + tempmsg + "		" ;
		errorlog += "oldbound:" + stroldbound + "	" ;
		tempmsg.Format("%d", newstatus) ;
		errorlog += "newstatus:" + tempmsg +"	" ;
		errorlog += "newbound:" + strnewbound + "	";

		errorlog += "databound:" + strtempNewBound + "	" ;
		

		////////////////////////////////

		CString sblockid ;
		CString status ;
		CString scurtime = "" ;
		sblockid.Format("%I64d", blockid) ;
		status.Format("%d", newstatus) ;

		if ( newstatus != oldstatus)
		{
			CTime curtime = CTime::GetCurrentTime();
			scurtime = curtime.Format("%Y-%m-%d %H:%M:%S") ;
			strupdatetime += " when " + sblockid + " then '" + scurtime + "'::TIMESTAMP " ;
		}
		else
		{
			itupdatetime = m_mapBlockUpdateTime.find( blockid) ;
			scurtime = itupdatetime->second ;
			strupdatetime += " when " + sblockid + " then '" + scurtime + "'::TIMESTAMP " ;
		}
		errorlog += "updatetime:" + scurtime + "\n" ;

		m_writelog->WriteLog(errorlog) ;

		strmid += " when " + sblockid + " then " + status ;
		strend += sblockid + "," ;

		CString sbound ;
		sbound.Format(" st_geomfromtext('LINESTRING(%f %f,%f %f)') ", newbound.x_min, newbound.y_min, newbound.x_max, newbound.y_max) ;
		strrects += " when " + sblockid + " then " + sbound ;
#ifdef _DEBUG
		if ( blockid== 7850 )
		{
			CString s = newstatus==4 ? "状态上传：status=4" : "状态上传：status !=4" ;
			newstatus = newstatus;
			TRACE( strmid );
			AfxMessageBox( s ) ;
		}
#endif

		index++ ;
		if ( index % max_row == 0)
		{
			if ( strmid.Find("when") != -1)
			{
				strend = strend.Left(strend.GetLength()-1) ;
				strend += ")" ;
			}

			CString sql = strfront + strmid +" end, envelope = CASE id " + strrects + " end, updatetime = CASE id " + strupdatetime + strend ;
			if ( CTaskManager::GetTaskManager()->GetSqlFlag() == 1001)
			{
				sql += " and `status`  not in (5,6)" ;
			}
			else if ( CTaskManager::GetTaskManager()->GetSqlFlag() == 1002)
			{
				sql += " and \"status\"  not in (5,6)" ;
			}
			int iaffect = 0 ;
			CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql, iaffect) ;
			strmid = "" ;
			strend = " end where id in(" ;
		}
	}

	if ( strmid.Find("when") != -1)
	{
		strend = strend.Left(strend.GetLength()-1) ;
		strend += ")" ;
		CString sql = strfront + strmid +" end, envelope = CASE id " + strrects + " end, updatetime = CASE id " + strupdatetime  + strend ;
		if ( CTaskManager::GetTaskManager()->GetSqlFlag() == 1001)
		{
			sql += " and `status`  not in (5,6)" ;
		}
		else if ( CTaskManager::GetTaskManager()->GetSqlFlag() == 1002)
		{
			sql += " and \"status\"  not in (5,6)" ;
		}
		int iaffect = 0 ;
		CDB_Manager::GetDBManagerPtr()->ExcuteSql( sql, iaffect) ;
		strmid = "" ;
		strend = " end where id in(" ;
	}
	m_writelog->WriteLog("完成将block状态上传至数据库\n") ;
	//////////////////////////////////////////////////////////////////////////

}
void CCreateTask::UpLoadBlockStatus_method2()
{
	//////////////////////////////////////////////////////////////////////////
	m_writelog->WriteLog("开始将block状态上传至数据库\n") ;
	CTaskManager::GetTaskManager()->SetChoosingTask() ;

	CString strfront = "update tb_task_block set status = CASE id " ;
	CString strmid = "" ;
	CString strrects = "" ;
	CString strupdatetime = "" ;
	CString strend = " end where id in(" ;
 
	MAP_OID_INT::iterator itblockstate ;
	MAP_OID_INT::iterator itoldblockstate ;

	MAP_BlOCK_BOUND::iterator itoldbound ;
	MAP_BlOCK_BOUND::iterator itnewbound ;

	MAP_OID_CSTRING::iterator itupdatetime ;

	int index = 0 ;
	int max_row = 500 ;
	for ( itblockstate = m_mapBlockStatus.begin(); itblockstate != m_mapBlockStatus.end(); itblockstate++)
	{
		OID blockid = itblockstate->first ;
		int newstatus = itblockstate->second ;

		//////////////////////////////////////////////////////////////////////////
		// 检验block状态是否发生变化，状态没有发生变化就不更新
		// 如果想做状态未变化就不更新，最好是block未发生变化+block状态也未变化才不更新


		// 2017-6-289
		itoldblockstate = m_oldBlockStatus.find( blockid ) ;
		int oldstatus = -1 ;
		if (itoldblockstate != m_oldBlockStatus.end() )
		{
			oldstatus = itoldblockstate->second ;
			if ( newstatus == oldstatus)
			{
				continue;// 状态一样，跳过
			}
		}
		//////////////////////////////////////////////////////////////////////////

		///////////////////////////////日志测试
		CString tempmsg ;
		tempmsg.Format("%I64d",blockid) ;
		CString errorlog = "blockid:" ;
		errorlog += tempmsg ;
		errorlog += "		" ;
		tempmsg.Format("%d",oldstatus) ;
		errorlog += "oldstatus:" + tempmsg + "		" ;
		tempmsg.Format("%d", newstatus) ;
		errorlog += "newstatus:" + tempmsg +"	" ;
		

		////////////////////////////////

		CString sblockid ;
		CString status ;
		CString scurtime = "" ;
		sblockid.Format("%I64d", blockid) ;
		status.Format("%d", newstatus) ;

		if ( newstatus != oldstatus)
		{
			CTime curtime = CTime::GetCurrentTime();
			scurtime = curtime.Format("%Y-%m-%d %H:%M:%S") ;
			strupdatetime += " when " + sblockid + " then '" + scurtime + "'::TIMESTAMP " ;
		}
		else
		{
			itupdatetime = m_mapBlockUpdateTime.find( blockid) ;
			scurtime = itupdatetime->second ;
			strupdatetime += " when " + sblockid + " then '" + scurtime + "'::TIMESTAMP " ;
		}
		errorlog += "updatetime:" + scurtime + "\n" ;

		m_writelog->WriteLog(errorlog) ;

		strmid += " when " + sblockid + " then " + status ;
		strend += sblockid + "," ;

#ifdef _DEBUG
		if ( blockid== 7850 )
		{
			CString s = newstatus==4 ? "状态上传：status=4" : "状态上传：status !=4" ;
			newstatus = newstatus;
			TRACE( strmid );
			AfxMessageBox( s ) ;
		}
#endif

		index++ ;
		if ( index % max_row == 0)
		{
			if ( strmid.Find("when") != -1)
			{
				strend = strend.Left(strend.GetLength()-1) ;
				strend += ")" ;
			}

			CString sql = strfront + strmid +" end, updatetime = CASE id " + strupdatetime + strend ;
			if ( CTaskManager::GetTaskManager()->GetSqlFlag() == 1001)
			{
				sql += " and `status`  not in (5,6)" ;
			}
			else if ( CTaskManager::GetTaskManager()->GetSqlFlag() == 1002)
			{
				sql += " and \"status\"  not in (5,6)" ;
			}
			int iaffect = 0 ;
			CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql, iaffect) ;
			strmid = "" ;
			strend = " end where id in(" ;
		}
	}

	if ( strmid.Find("when") != -1)
	{
		strend = strend.Left(strend.GetLength()-1) ;
		strend += ")" ;
		CString sql = strfront + strmid +" end, updatetime = CASE id " + strupdatetime  + strend ;
		if ( CTaskManager::GetTaskManager()->GetSqlFlag() == 1001)
		{
			sql += " and `status`  not in (5,6)" ;
		}
		else if ( CTaskManager::GetTaskManager()->GetSqlFlag() == 1002)
		{
			sql += " and \"status\"  not in (5,6)" ;
		}
		int iaffect = 0 ;
		CDB_Manager::GetDBManagerPtr()->ExcuteSql( sql, iaffect) ;
		strmid = "" ;
		strend = " end where id in(" ;
	}
	m_writelog->WriteLog("完成将block状态上传至数据库\n") ;
	//////////////////////////////////////////////////////////////////////////

}
void CCreateTask::BacktoWorker(OID blockid)
{
	MAP_OID_STATE::iterator itstate ;
	MUL_BLOCK_OID::iterator itblocklower ;
	MUL_BLOCK_OID::iterator itblockupper ;
	CFeature *pFeature = NULL ;
	CString strLayerName ;
	int layerid ;
	OID featureid;

	//////////////////////////////////////////////////////////////////////////
	MUL_BLOCK_OID::iterator itblock = m_mulBlockDetails.find( blockid ) ;
	itblocklower = m_mulBlockDetails.lower_bound(blockid) ;
	itblockupper = m_mulBlockDetails.upper_bound(blockid) ;
	while ( itblocklower != itblockupper)
	{
		PAIR_INT_OID pairl_f = itblocklower->second ;
		itstate = m_mapState.find( pairl_f) ;
		if ( itstate != m_mapState.end())
		{
			int featureflag = itstate->second ;
			if ( featureflag == BLOCK_STATUS_UNCHECK )
			{
				layerid = pairl_f.first;
				featureid = pairl_f.second;

				// 20170927 为减小内存，重新加载数据进行刷值

				CString strMsg ;
				strMsg.Format( "blockid: %I64d 被回退对象%d,%I64d\n", blockid,pairl_f.first, pairl_f.second );
					m_writelog->WriteLog( strMsg ) ;
				m_mapConfirm.insert(MAP_OID_CONFIRM::value_type( layerid, featureid)) ;
/*
				strLayerName = GetLayerNameByLayerID( layerid ) ;
				pFeature = m_pMap->GetMapLayerByName( strLayerName)->GetDataSourcePtr()->GetFeaturePtr( featureid);
				if ( pFeature != NULL )
				{
					pFeature->GetGeometryPtr()->SetConfirm(IRCF_ConfirmOK);
				}
*/
			}
		}
		itblocklower++ ;
	}
}

void CCreateTask::WriteLogtoMysql()
{
	CString strIPAddr = "" ;
	CString strName = "" ;
/*
	char    HostName[100];
	gethostname(HostName, sizeof(HostName));// 获得本机主机名.
	
	hostent* hn;
	hn = gethostbyname(HostName);//根据本机主机名得到本机ip
	
	strIPAddr=inet_ntoa(*(struct in_addr *)hn->h_addr_list[0]);//把ip换成字符串形式*/
	WSADATA wsaData;  
    char name[155];      //定义用于存放获得主机名的变量  
//     char *ip;            //定义IP地址变量  
    PHOSTENT hostinfo;   
	
    //调用MAKEWORD()获得Winsocl版本的正确值，用于下面的加载Winscok库  
    if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )   
    {   //加载Winsock库，如果WSAStartup()函数返回值为0，说明加载成功，程序可以继续往下执行  
        if( gethostname ( name, sizeof(name)) == 0)   
        { //如果成功，将本地主机名存放入由name参数指定的缓冲区中  
            if((hostinfo = gethostbyname(name)) != NULL)   
            { //这是获取主机，如果获得主机名成功的话，将返回一个指针，指向hostinfo,hostinfo为PHOSTENT型的变量。  
                strIPAddr = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);   
                //inet_addr()函数把地址串转换为IP地址  
                //调用inet_ntoa()函数,将hostinfo结构变量中的h_addr_list转化为标准的IP地址(如202.197.11.12.)  
//                 printf(" IP地址: %s/n",ip);        //输出IP地址  
            }   
        }   
        WSACleanup( );         //卸载Winsock库，并释放所有资源  
    }   
	
	strName = name ;

	CString sql ;
	sql.Format("insert into tb_tool_log(ip,name,appname) values('%s','%s','%s')",strIPAddr, strName,"UpdateBlockState.exe") ;
#ifdef _DEBUG
	sql.Format("insert into tb_tool_log(ip,name,appname) values('%s','%s','%s')",strIPAddr, strName,"UpdateBlockState_Debug.exe") ;
#endif
	
// 	CTaskManager::GetTaskManager() ;
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_BLOCKTIME) ;
	CTaskManager::GetTaskManager()->SetChoosingTask() ;
	int iaffect = 0 ;
	CDB_Manager::GetDBManagerPtr()->ExcuteSql(sql, iaffect) ;
}

bool CCreateTask::LoadBlockForNull()
{
	m_writelog->WriteLog("开始加载数据库blockdetail中为空的block信息\n") ;
	vector< OID > vtblockid ;
	vector< int > vtstatus ;
	bool bload = CTaskManager::GetTaskManager()->LoadTaskDetailForNull(vtblockid, vtstatus) ;
	if (!bload)
	{
		return false;
	}
	//////////////////////////////////////////////////////////////////////////
	// modified at 20171201 begin
	// 发现没有满足要求的数据，并不能代表加载失败
// 	if (vtblockid.size() == 0)
// 	{
// 		return false;
// 	}
	//////////////////////////////////////////////////////////////////////////
	
	for ( int i = 0; i < vtblockid.size(); i++)
	{
		OID blockid = vtblockid[i] ;
		int status = vtstatus[i] ;
		// 这部分block需要被关闭
		m_mapBlockStatus.insert(MAP_OID_INT::value_type( blockid, BLOCK_STATUS_MERGE)) ;
	}
	vtblockid.clear() ;
	vtstatus.clear() ;
	m_writelog->WriteLog("完成加载数据库blockdetail中为空的block信息\n") ;
	return true ;
}

CString CCreateTask::GetBoundByRect( SGeoRect bound )
{
	CString msg ;
	CString strBound = "" ;
	msg.Format("%f", bound.x_min) ;
	strBound+= msg +"," ;
	msg.Format("%f", bound.y_min) ;
	strBound += msg +"," ;
	msg.Format("%f", bound.x_max) ;
	strBound += msg +"," ;
	msg.Format("%f", bound.y_max) ;
	strBound+= msg ;
	return strBound ;
}

int CCreateTask::CompareTwoBound( SGeoRect bound1, SGeoRect bound2, SGeoRect &mergeBound )
{
	if ( bound1.x_min == -1)
	{
		mergeBound = bound2 ;
		return 1 ;
	}
	if ( bound2.x_min == -1)
	{
		mergeBound = bound1 ;
		return 1 ;
	}
	mergeBound = bound1 ;
	mergeBound.Union( bound2) ;
	if ( mergeBound == bound1)
	{
		// 合并后的mergebound跟bound1一样
		return -1 ;
	}
	return 1 ;
}

bool CCreateTask::UpdateConfirm()
{
	int size = 0 ;
	for ( MAP_OID_CONFIRM::iterator it = m_mapConfirm.begin(); it != m_mapConfirm.end(); )
	{
		int layerid = it->first ;
		MAP_OID_CONFIRM::iterator itlower = m_mapConfirm.lower_bound(layerid) ;
		MAP_OID_CONFIRM::iterator itupper = m_mapConfirm.upper_bound(layerid) ;
		int countfeature = m_mapConfirm.count(layerid) ;
		OID *pOID = new OID[countfeature] ;
		int index = 0 ;
		while( itlower != itupper)
		{
			pOID[index] = itlower->second ;
			index++ ;
			itlower++ ;
			it++ ;
			size++ ;
		}

		CString strLayerName = GetLayerNameByLayerID( layerid) ;
		CLayer *pLayer = m_pMap->GetOrMakeLayer(strLayerName) ;
		if ( pLayer == NULL)
		{
			continue;
		}
		pLayer->Load( pOID, countfeature) ;

		if ( countfeature > 0)
		{
			delete []pOID ;
			pOID = NULL ;
		}

		CFeatureSet *pFeatureSet = pLayer->GetAllFeaturesPtr() ;
		if ( pFeatureSet == NULL)
		{
			continue;
		}

		CFeature *pFeature = pFeatureSet->GetFirstFeaturePtr() ;
		while( pFeature) 
		{

			CString strMsg ;
			strMsg.Format( "设为confirm_ok:%s,%I64d\n", strLayerName,pFeature->GetFID());
			m_writelog->WriteLog( strMsg ) ;
			pFeature->GetGeometryPtr()->SetConfirm( IRCF_ConfirmOK) ;
			pFeature = pFeatureSet->GetNextFeaturePtr() ;
		}
		
		if ( size > LOAD_UNIT_COUNT)
		{
			m_pMap->Save() ;
			m_pMap->ReleaseMemory() ;
			size = 0 ;
		}
	}
	if ( size > 0)
	{
		m_pMap->Save() ;
		m_pMap->ReleaseMemory() ;
		size = 0 ;
	}
	return true ;
}

_TSGEO::SGeoRect CCreateTask::TransTSGeoRect( SGeoRect rect )
{
	_TSGEO::SGeoRect temp( rect.x_min, rect.y_min, rect.x_max, rect.y_max) ;
	return temp ;
}

SGeoRect CCreateTask::TransGeoRect( _TSGEO::SGeoRect rect )
{
	SGeoRect temp( rect.x_min, rect.y_min, rect.x_max, rect.y_max) ;
	return temp ;
}

bool CCreateTask::GetUID_UserName()
{
	m_mapUID_UserName.clear() ;

	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_EXTEND1_PGSQL) ;
	CString sql = "select id,realname from \"public\".tb_employee" ;
	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql( sql) ;
	if ( pRes == NULL)
	{
		return false;
	}
	int row = pRes->GetResRowCount() ;
	int fieldcount = pRes->GetResFieldCount() ;
	for ( int index_row = 0; index_row < row; index_row++)
	{
		OID uid = -1 ;
		CString username = "" ;
		for ( int index_field = 0; index_field < fieldcount; index_field++)
		{
			CString strfieldname = pRes->GetFieldName( index_field) ;
			if ( strfieldname == "id")
			{
				uid = pRes->GetResBigIntValue(index_row, index_field) ;
			}
			else if ( strfieldname == "realname")
			{
				username = pRes->GetResStringValue(index_row, index_field) ;
			}
		}
		if ( uid == 0)
		{
			int a =0 ;
		}
		m_mapUID_UserName.insert(MAP_OID_CSTRING::value_type( uid, username)) ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	return true ;

}

CString CCreateTask::GetFeatureManualCheck( CFeature *pFeature )
{
	if ( pFeature == NULL)
	{
		return "" ;
	}
	if ( pFeature->GetManuCheck() == IRCS_NoCheck)
	{
		return "uncheck" ;
	}
	else if ( pFeature->GetManuCheck() == IRCS_Error)
	{
		return "err" ;
	}
	else if ( pFeature->GetManuCheck() == IRCS_NoErr)
	{
		return "ok" ;
	}
	else
	{
		return "" ;
	}
}

std::string CCreateTask::GetFeatureUserName( CFeature *pFeature )
{
	std::string strtemp = "" ;
	if ( pFeature == NULL)
	{
		return strtemp ;
	}
	OID uid = pFeature->GetUserID() ;
	MAP_OID_CSTRING::iterator ituid = m_mapUID_UserName.find( uid) ;
	if ( ituid != m_mapUID_UserName.end())
	{
		return (ituid->second).GetBuffer(0) ;
	}
	else
	{
		return strtemp ;
	}
}

void CCreateTask::UpdateBlockDetail()
{
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	MAP_OID_STATE::iterator itstate ;
	MUL_BLOCK_OID::iterator itblocklower ;
	MUL_BLOCK_OID::iterator itblockupper ;
	MAP_OID_BOUND::iterator itbound ;

	
	MAP_LID_FID_CSTRING::iterator itmanualcheck ;
	MAP_LID_FID_CSTRING::iterator itusername ;
	MAP_LID_FID_CSTRING::iterator itfeaturemanualcheck ;
	MAP_LID_FID_CSTRING::iterator itfeatureusername ;
	MAP_LID_FID_BID::iterator itowner ;
	MAP_LID_FID_BID::iterator itfeatureowner ;
	MAP_OID_INT::iterator itblockmanualroadnum ;
	MAP_OID_CSTRING::iterator itblockusername ;
	MAP_OID_CSTRING::iterator itblockowner ;

	CString sqlfront = "update tb_task_blockdetail set " ;
	CString sqlmanualcheck= " manualcheck = CASE id " ;
	CString sqlusernameend = "username = CASE id " ;
	CString sqlowner = " owner = CASE id " ;
	CString sqlend = " where id in (" ;
	
	CString sqlblockfront = "update tb_task_block set " ;
	CString sqlblockmanual = " manualroadnum = CASE id " ;
	CString sqlblockusername = " username = CASE id " ;
	CString sqlblockowner = " owner = CASE id " ;
	CString sqlblockend = " where id in (" ;

	CString msg ;
	MAP_LID_FID_BID::iterator itdetail ;
	for ( MUL_BLOCK_OID::iterator itblock = m_mulBlockDetails.begin(); itblock != m_mulBlockDetails.end();)
	{
		OID blockid = itblock->first;
		int oldstate = -1 ;  

		itblocklower = m_mulBlockDetails.lower_bound(blockid) ;
		itblockupper = m_mulBlockDetails.upper_bound(blockid) ;


	
		int blockfrontmanualroadnum = 0 ;
		itblockmanualroadnum = m_mapBlockManualRoadnum.find( blockid) ;
		if ( itblockmanualroadnum != m_mapBlockManualRoadnum.end())
		{
			blockfrontmanualroadnum = itblockmanualroadnum->second ;
		}
		CString blockfrontusername = "" ;
		itblockusername = m_mapBlockUserName.find( blockid) ;
		if ( itblockusername != m_mapBlockUserName.end())
		{
			blockfrontusername = itblockusername->second ;
		}
		CString blockfrontowner = "" ;
		itblockowner = m_mapBlockOwner.find(blockid) ;
		if ( itblockowner != m_mapBlockOwner.end())
		{
			blockfrontowner = itblockowner->second ;
		}
		std::map<CString,int> mapblockUserName  ;
		std::map<int,int> mapOwner ;
		int blockmanualroadnum = 0 ;
		CString strblockusername = "" ;
		int index = 0 ;
		OID detailid = -1 ;
		int errorcount = 0 ;
		while ( itblocklower != itblockupper)
		{
			PAIR_INT_OID pair_l = itblocklower->second ;
			itmanualcheck = m_mapManualCheck.find(pair_l) ;
			itfeaturemanualcheck = m_mapFeatureManualCheck.find(pair_l) ;
			detailid = -1 ;
			if ( itmanualcheck != m_mapManualCheck.end() && itfeaturemanualcheck != m_mapFeatureManualCheck.end())
			{
				CString strmanualcheck = itmanualcheck->second ;
				CString strfeaturemanualcheck = itfeaturemanualcheck->second ;
				if ( strfeaturemanualcheck == "ok" && pair_l.first == 1)
				{
					blockmanualroadnum++ ;
				}
				if ( strmanualcheck != strfeaturemanualcheck)
				{
					if ( detailid == -1)
					{
						itdetail = m_mapLID_FID_DetailID.find( pair_l) ;
						if ( itdetail != m_mapLID_FID_DetailID.end())
						{
							detailid = itdetail->second ;
							msg.Format("%I64d,", detailid) ;
							sqlend += msg ;
						}
					}
					if ( detailid != -1)
					{
						msg.Format("%I64d", detailid) ;
						sqlmanualcheck += " when " ;
						sqlmanualcheck += msg ;
						sqlmanualcheck += " then '" ;
						sqlmanualcheck += strfeaturemanualcheck ;
						sqlmanualcheck += "' " ;
					}
					errorcount++ ;
				}
			}

			itowner = m_mapOwner.find( pair_l) ;
			itfeatureowner = m_mapFeatureOwner.find( pair_l) ;

			if ( itowner != m_mapOwner.end() && itfeatureowner != m_mapFeatureOwner.end())
			{
				int owner = itowner->second ;
				int featureowner = itfeatureowner->second ;
				if ( pair_l.first == 1)
				{
					mapOwner.insert(std::map<int,int>::value_type( featureowner,owner)) ;
				}
				if ( owner != featureowner)
				{
					if ( detailid == -1)
					{
						itdetail = m_mapLID_FID_DetailID.find( pair_l) ;
						if ( itdetail != m_mapLID_FID_DetailID.end())
						{
							detailid = itdetail->second ;
							msg.Format("%I64d,", detailid) ;
							sqlend += msg ;
						}
					}
					if ( detailid != -1)
					{
						msg.Format("%I64d", detailid) ;
						sqlowner += " when " ;
						sqlowner += msg ;
						sqlowner += " then " ;
						msg.Format("%d", featureowner) ;
						sqlowner += msg ;
						sqlowner += " " ;
					}
					errorcount++ ;
				}
			}

			itusername = m_mapUserName.find( pair_l) ;
			itfeatureusername = m_mapFeatureUserName.find( pair_l) ;
			
			if ( itusername != m_mapUserName.end() && itfeatureusername != m_mapFeatureUserName.end())
			{
				CString username = itusername->second ;
				CString strfeatureusername = itfeatureusername->second ;
				if ( pair_l.first == 1)
				{
					mapblockUserName.insert(std::map<CString,int>::value_type( strfeatureusername,0)) ;
				}
				if ( username != strfeatureusername)
				{
					if ( detailid == -1)
					{
						itdetail = m_mapLID_FID_DetailID.find( pair_l) ;
						if ( itdetail != m_mapLID_FID_DetailID.end())
						{
							detailid = itdetail->second ;
							msg.Format("%I64d,", detailid) ;
							sqlend += msg ;
						}
					}
					if ( detailid != -1)
					{
						msg.Format("%I64d", detailid) ;
						sqlusernameend += " when " ;
						sqlusernameend += msg ;
						sqlusernameend += " then '" ;
						sqlusernameend += strfeatureusername ;
						sqlusernameend += "' " ;
					}
					errorcount++ ;
				}
			}

			if ( errorcount == 5000)
			{
				if ( sqlend.Find(",") != -1)
				{
					sqlend = sqlend.Left(sqlend.GetLength()-1) ;
					sqlend += ")" ;

					CString sql = sqlfront ;
					if ( sqlmanualcheck.Find("when") != -1)
					{
						sqlmanualcheck += " else manualcheck end " ;
						sql += sqlmanualcheck ;
					}
					if ( sqlusernameend.Find("when") != -1)
					{
						sqlusernameend += " else username end " ;
						if ( sqlmanualcheck.Find("when") != -1)
						{
							sql += "," ;
							sql += sqlusernameend ;
						}
						else
						{
							sql += sqlusernameend ;
						}
					}
					sql += sqlend ;

					int affect = 0 ;
					bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql( sql, affect) ;
					if ( !bupdate || bupdate)
					{
						m_writelog->WriteLog( sql) ;
					}
					sqlfront = "update tb_task_blockdetail set " ;
					sqlmanualcheck= " manualcheck = CASE id " ;
					sqlusernameend = "username = CASE id " ;
					sqlowner = " owner = CASE id " ;
					sqlend = " where id in (" ;
					errorcount = 0 ;
				}
			}

			itblocklower++ ;
			itblock++ ;
		}

		if ( blockmanualroadnum != blockfrontmanualroadnum)
		{
			msg.Format("%I64d", blockid) ;

			sqlblockend += msg ;
			sqlblockend += "," ;


			sqlblockmanual += " when " ;
			sqlblockmanual += msg ;
			sqlblockmanual += " then " ;
			msg.Format("%d", blockmanualroadnum) ;
			sqlblockmanual += msg ;
			sqlblockmanual += " " ;

		}

		for ( std::map<CString,int>::iterator itfeatureusernametemp = mapblockUserName.begin(); itfeatureusernametemp != mapblockUserName.end(); itfeatureusernametemp++)
		{
			CString username = itfeatureusernametemp->first ;
			if ( username.GetLength() == 0)
			{
				continue;
			}
			strblockusername += username ;
			strblockusername += ";" ;
		}
		if ( strblockusername.Find(";") != -1)
		{
			strblockusername = strblockusername.Left(strblockusername.GetLength()-1) ;
		}
		if ( strblockusername != blockfrontusername)
		{
			msg.Format("%I64d", blockid) ;
			if ( blockmanualroadnum == blockfrontmanualroadnum)
			{
				sqlblockend += msg ;
				sqlblockend += "," ;
			}
			
			sqlblockusername += " when " ;
			sqlblockusername += msg ;
			sqlblockusername += " then '" ;
			sqlblockusername += strblockusername ;
			sqlblockusername += "' " ;
		}

		CString strblockowner = "" ;
		std::map<CString,int> mapblockownername ;
		for ( std::map<int,int>::iterator itfeatureownertemp = mapOwner.begin(); itfeatureownertemp!= mapOwner.end(); itfeatureownertemp++)
		{
			int owner = itfeatureownertemp->first ;
			CString strownername = m_pTransOwner->GetProCityNameByOnwer(owner) ;
			mapblockownername.insert(std::map<CString,int>::value_type(strownername,-1)) ;
		}
		for ( std::map<CString,int>::iterator itfeatureownernametemp = mapblockownername.begin(); itfeatureownernametemp != mapblockownername.end(); itfeatureownernametemp++)
		{
			CString temp = itfeatureownernametemp->first ;
			if ( temp.GetLength() == 0)
			{
				continue;
			}
			strblockowner += temp ;
			strblockowner += ";" ;
		}
		if ( strblockowner.Find(";") != -1)
		{
			strblockowner = strblockowner.Left(strblockowner.GetLength()-1) ;
		}
		if ( strblockowner != blockfrontowner)
		{
			msg.Format("%I64d", blockid) ;
			if ( blockmanualroadnum == blockfrontmanualroadnum && strblockusername == blockfrontusername )
			{
				sqlblockend += msg ;
				sqlblockend += "," ;
			}
			
			sqlblockowner += " when " ;
			sqlblockowner += msg ;
			sqlblockowner += " then '" ;
			sqlblockowner += strblockowner ;
			sqlblockowner += "' " ;
		}
	}

	if ( sqlend.Find(",") != -1)
				{
		sqlend = sqlend.Left(sqlend.GetLength()-1) ;
		sqlend += ")" ;
		
		CString sql = sqlfront ;
		if ( sqlmanualcheck.Find("when") != -1)
		{
			sqlmanualcheck += " else manualcheck end " ;
			sql += sqlmanualcheck ;
		}
		if ( sqlusernameend.Find("when") != -1)
		{
			sqlusernameend += " else username end " ;
			if ( sqlmanualcheck.Find("when") != -1)
			{
				sql += "," ;
				sql += sqlusernameend ;
			}
			else
			{
				sql += sqlusernameend ;
			}
		}
		sql += sqlend ;
		
		int affect = 0 ;
		bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql( sql, affect) ;
		if ( !bupdate || bupdate)
		{
			m_writelog->WriteLog( sql) ;
		}
		sqlfront = "update tb_task_blockdetail set " ;
		sqlmanualcheck= " manualcheck = CASE id " ;
		sqlusernameend = "username = CASE id " ;
		sqlend = " where id in (" ;
	}

	
	if ( sqlblockend.Find(",") != -1)
	{
		sqlblockend = sqlblockend.Left(sqlblockend.GetLength()-1) ;
		sqlblockend += ")" ;
		
		CString sql = sqlblockfront ;
		if ( sqlblockmanual.Find("when") != -1)
		{
			sqlblockmanual += " else manualroadnum end " ;
			sql += sqlblockmanual ;
		}
		if ( sqlblockusername.Find("when") != -1)
		{
			sqlblockusername += " else username end " ;
			if ( sqlblockmanual.Find("when") != -1)
			{
				sql += "," ;
				sql += sqlblockusername ;
			}
			else
			{
				sql += sqlblockusername ;
			}
		}
		if ( sqlblockowner.Find("when") != -1)
		{
			sqlblockowner += " else owner end " ;
			if ( sqlblockusername.Find("when") != -1 || sqlblockmanual.Find("when") != -1)
			{
				sql += "," ;
				sql += sqlblockowner ;
			}
			else
			{
				sql += sqlblockowner ;
			}
		}
		sql += sqlblockend ;
		
		int affect = 0 ;
		bool bupdate = CDB_Manager::GetDBManagerPtr()->ExcuteSql( sql, affect) ;
		if ( !bupdate || bupdate)
		{
			m_writelog->WriteLog( sql) ;
		}
	}
}

void CCreateTask::DeleteShapeFromBlock()
{
	
}

void CCreateTask::DeleteError()
{
// 	if(!ReadConfig())
// 	{
// 		return ;
// 	}

	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	CString sql = "" ;
	
	
	bool bDel = true ;


	bDel = true ;
	while ( bDel)
	{
		sql.Format("select *,now() as nowtime from public.tb_way_tags_history order by id desc limit 10") ;
		int affect = 0;
		CDB_ResultSet *result = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql( sql) ;
		if ( result == NULL)
		{
			continue;
		}

		int irowcount = result->GetResRowCount() ;
		for ( int index_row = 0; index_row < irowcount; index_row++)
		{
			
		}

		Sleep(10000) ;
	}
	
	

}
