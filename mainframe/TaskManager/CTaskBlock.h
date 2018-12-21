// CTaskBlock.h: interface for the CTaskBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTASKBLOCK_H__476CAE32_D5F0_4A73_922A_1A5E29680A2D__INCLUDED_)
#define AFX_CTASKBLOCK_H__476CAE32_D5F0_4A73_922A_1A5E29680A2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <map>
using namespace std ;

#include "task_definition.h"

// #include "commondef.h"
class CTaskBlockDetail ;
typedef map< __int64, CTaskBlockDetail* >			TASKBLOCKDETAIL_MAP ;
typedef TASKBLOCKDETAIL_MAP::iterator				TASKBLOCKDETAIL_MAP_ITERATOR ;

#include "CTaskCommon.h"
class __declspec(dllexport) CTaskBlock  :public CTaskCommon
{
public:
	CTaskBlock();
	virtual ~CTaskBlock();

	void				SetID(__int64 id) ;
	__int64				GetID() ;

	void				SetType(int itype) ;
	int					GetType() ;
	
	void				SetRoadNum(int roadnum) ;
	int					GetRoadNum() ;
	
	void				SetErrorCount(int errorcount) ;
	int					GetErrorCount() ;

	void				SetStatus(int istatus) ;
	int					GetStatus() ;

	void				SetBound(_TSGEO::SGeoRect rect) ;
	_TSGEO::SGeoRect			GetBound() ;

	void				SetUpdateTime(SYSTEMTIME time) ;
	SYSTEMTIME			GetUpdateTime() ;

	bool				LoadLinkInfo() ;
	int					GetReferLevel() ;
	void				SetReferLevel(int ilevel) ;
	const char *		GetName() ;
	void				SetName(const char *szName) ;
public:
	// 对TaskBlockDetail的调用
	// 将taskblockdetail指针添加到集合里面
	void				AddTaskBlockDetail( CTaskBlockDetail *pTaskBlockDetail) ;
	// 获取size
	int					GetTaskBlockDetailCount() ;
	// 遍历
	CTaskBlockDetail*	GetFirstTaskBlockDetailPtr() ;
	CTaskBlockDetail*	GetNextTaskBlockDetailPtr() ;
	CTaskBlockDetail*	GetNextTaskBlockDetailPtr(CTaskBlockDetail* pTaskBlockDetail) ;
	// 删除
	bool				DeleteTaskBlockDetail(__int64 detailID) ;
	// 根据FeatureID获取TaskBlockDetail
	CTaskBlockDetail*	GetTaskBlockDetailForFeatureIDPtr(__int64 featureID) ;
	// 根据detailID获取TaskBlockDetail
	CTaskBlockDetail*	GetTaskBlockDetailForDetailIDPtr(__int64 detailID) ;

	// 得到一个Block关联一个图层对象的所有featureid
	__int64*			GetFeatureIDs(int layerid, int &size) ;
	// 更新一个detail
	bool UpdateBlockDetail(CTaskBlockDetail *pTaskBlockDetail,const char *szFieldNames) ;

private:
	__int64				m_id ;
	int					m_type ;
	int					m_status ;
	_TSGEO::SGeoRect			m_bound ;
	SYSTEMTIME			m_updatetime ;
	__int64				m_maxid ;
	int					m_ireferlevel ;
	string				m_strname ;
	int					m_roadnum ;
	
	int					m_errorCount ;

private:
	TASKBLOCKDETAIL_MAP*				m_mapTaskBlockDetail ;
	TASKBLOCKDETAIL_MAP_ITERATOR		m_currentTaskBlockDetailPtr ;
};

extern "C"
{
	__declspec(dllexport) CTaskBlock *CreateTaskBlock(__int64 iID,int ilevel=-1) ;
};

#endif // !defined(AFX_CTASKBLOCK_H__476CAE32_D5F0_4A73_922A_1A5E29680A2D__INCLUDED_)
