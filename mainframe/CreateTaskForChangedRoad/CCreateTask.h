// CCreateTask.h: interface for the CCreateTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCREATETASK_H__23C1A812_A612_4655_9EE7_F3122AE97190__INCLUDED_)
#define AFX_CCREATETASK_H__23C1A812_A612_4655_9EE7_F3122AE97190__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "commondef.h"
#include "task_definition.h"

#include "CWriteLog.h"
#include <vector>
#include <map>
using namespace std ;

class CNaviMap ;
class CLayer ;
class CFeature ;
class CRoadLayer ;
class CJunctionLayer ;

class CTask ;
class CWriteLog ;
// class CTaskLinkPoi ;
class CTaskChangeRoadTime ;
class CFeature ;
class CTaskBlock ;

typedef multimap< int, OID > MUL_INT_OID ;

typedef pair< int, OID > PAIR_INT_OID ;
typedef map< PAIR_INT_OID, int > MAP_OID_STATE ;
typedef multimap< int, OID > MAP_OID_CONFIRM ;
typedef multimap< OID, PAIR_INT_OID > MUL_BLOCK_OID ;
typedef multimap< int, OID > MUL_LAYER_OID ;
typedef map< OID, int > MAP_OID_INT ;
typedef map< OID, SGeoRect > MAP_BlOCK_BOUND ;
typedef map< PAIR_INT_OID, SGeoRect > MAP_OID_BOUND ;
typedef map< OID, CString > MAP_OID_CSTRING ;
typedef map< PAIR_INT_OID, CString > MAP_LID_FID_CSTRING ;
typedef map< PAIR_INT_OID, OID > MAP_LID_FID_BID ;

typedef multimap<CString, CString> MUL_BATCH_ERRORTPE ;

typedef 
struct STRUCT_DB
{
	CString					host ;						// ip
	CString					username ;					// �û���
	CString					password ;					// ����
	CString					dbname ;						// ���ݿ�����
	CString					port ;						// �˿ں�
	CString					linkip ;					// host_port_db
	STRUCT_DB()
	{
		host = username = password = dbname = port = "" ;
	}
};


class CTransOwner ;
class CCreateTask  
{
protected:
	CCreateTask();

public:
	virtual ~CCreateTask();
	
	bool					CreateTaskForChangedRoad(CWriteLog *pWriteLog) ;

	static CCreateTask*		GetCreateTaskPtr();
	static void				Release();

	void DeleteError() ;

private:

	// ����block״̬
//	bool					UpdateBlockStatusNew(CTaskBlock *pTaskBlock) ;

	/// ���ȴ������block
	// ����δ�رյĴ���block
//	bool					ReadTableBlock() ;

// 	void					ReadTableDetail() ;
	// ȡ��Feature��״̬��Ϣ
	int						GetFeatureStatus(CFeature *pFeature, int &manualstatus);
	// get bound by feature
	SGeoRect				GetFeatureBound( CFeature *pFeature) ;
	CString					GetFeatureManualCheck( CFeature *pFeature) ;
	std::string				GetFeatureUserName( CFeature *pFeature) ;
	int						GetFeatureOwner(CFeature *pFeature) ;


	// ��λ�ڸ���ͼ���ڵ�Ҫ�ص�״̬��Ŀ�Ӽ��״̬/�߼����״̬/bound�����ؽ��ڴ�
	bool					Load(int layerid, OID *ptempFeatureID, int feature_count);
	// �����ݿ��м��طǹر�״̬block�ڵ�Ҫ���Լ�Ҫ��״̬��Ϣ���ڴ�
	bool					LoadBlockDetailStatus();

	// ����block��feature������״̬������block��status��Ϣ
//	void					UpdateBlockStatus();
	void					UpdateBlockStatus_Version2();

	// 
	int						GetBlockStatus(bool is_err, bool is_ok, bool is_uncheck, bool is_publish);
	// 
	void					UpLoadBlockStatus();
	void					UpLoadBlockStatus_method2() ;

	CString					GetLayerNameByLayerID(int layerid) ;

	void					BacktoWorker(OID blockid);
	void					WriteLogtoMysql() ;

	// 2017--7-11
	// ���طǡ��ر�/������״̬����blockdetailΪ�յ�block���ڴ�
	bool					LoadBlockForNull() ;
	CString					GetBoundByRect(SGeoRect bound) ;

	int						CompareTwoBound(SGeoRect bound1, SGeoRect bound2, SGeoRect &mergeBound) ;

	// 20170927 ����layerid-featureid�������ݣ�ˢconfirm״̬
	bool					UpdateConfirm() ;
	bool					ReadConfig() ;

	_TSGEO::SGeoRect		TransTSGeoRect(SGeoRect rect) ;
	SGeoRect				TransGeoRect(_TSGEO::SGeoRect rect) ;

	// 20180312 
	bool					GetUID_UserName() ;

	// ����У������������Ϣ
	void					UpdateBlockDetail() ;

	void					DeleteShapeFromBlock() ;


private:
	CString					m_strAppPath ;					// exe����·��
	CWriteLog*				m_writelog ;					// ��־ָ��

	CRoadLayer*				m_pRoadLayer ;
	CJunctionLayer*			m_pJunctionLayer ;
	CNaviMap*				m_pMap; 

	MAP_OID_STATE			m_mapManualStatus ;
	MAP_OID_STATE			m_mapState ;					// �洢ָ��Ҫ�أ�layerid+featureid����״̬
	MUL_BLOCK_OID			m_mulBlockDetails ;				// �洢����block��������Ϣ��block�ڰ�����ЩҪ�أ�
	MUL_LAYER_OID			m_mulLayerDetails ;				// �洢
	MAP_OID_INT				m_oldBlockStatus ;
	MAP_OID_BOUND			m_mapBound ;
	
	

	
	MAP_OID_INT				m_mapBlockStatus ;
	MAP_BlOCK_BOUND			m_mapBlockBound ;
	MAP_BlOCK_BOUND			m_mapOldBlockBound ;
	MAP_OID_CSTRING			m_mapBlockUpdateTime ;


	static CCreateTask*		m_pstaticTaskPtr;

	// 20170927
	MAP_OID_CONFIRM			m_mapConfirm ;

	int						m_sqlFlag ;

	// 20180312
	MAP_LID_FID_CSTRING			m_mapManualCheck ;
	MAP_LID_FID_CSTRING			m_mapUserName ;


	MAP_OID_INT					m_mapBlockManualRoadnum ;
	MAP_OID_CSTRING				m_mapBlockUserName ;
	MAP_OID_CSTRING				m_mapBlockOwner ;


	MAP_LID_FID_BID				m_mapOwner ;

	MAP_LID_FID_BID				m_mapLID_FID_DetailID ;

	MAP_LID_FID_CSTRING			m_mapFeatureManualCheck ;
	MAP_LID_FID_CSTRING			m_mapFeatureUserName ;
	MAP_LID_FID_BID				m_mapFeatureOwner ;

	MAP_OID_CSTRING				m_mapUID_UserName ;

	CTransOwner *			m_pTransOwner ;


	MUL_BATCH_ERRORTPE			m_mulBatch_ErrorType ;
};

#endif // !defined(AFX_CCREATETASK_H__23C1A812_A612_4655_9EE7_F3122AE97190__INCLUDED_)
