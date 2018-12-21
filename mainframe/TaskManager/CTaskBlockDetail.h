// CTaskBlockDetail.h: interface for the CTaskBlockDetail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTASKBLOCKDETAIL_H__EBB8A445_DBBE_4CA3_B383_CBA634DADEFD__INCLUDED_)
#define AFX_CTASKBLOCKDETAIL_H__EBB8A445_DBBE_4CA3_B383_CBA634DADEFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CTaskCommon.h"

class __declspec(dllexport) CTaskBlockDetail  : public CTaskCommon
{
public:
	CTaskBlockDetail();
	CTaskBlockDetail(int idbtype,const char *sztablename);
	virtual ~CTaskBlockDetail();

	void				SetID(__int64 id) ;
	__int64				GetID() ;

	void				SetBlockID(__int64 blockid) ;
	__int64				GetBlockID() ;

	void				SetLayerID(int layerid) ;
	int					GetLayerID() ;

	void				SetFeatureID(__int64 featureid) ;
	__int64				GetFeatureID() ;

	void				SetCreateTime(SYSTEMTIME time) ;
	SYSTEMTIME			GetCreateTime() ;

	void SetOperateType( int type );
	int GetOperateType();

	void SetDesc( CString strDesc );
	CString GetDesc();

	void SetIncrementtype( int incrementtype );
	int GetIncrementtype();

	void SetDirection( int direction );
	int GetDirection();

	bool   IsScanf();
	void   SetScanf(bool scanf);
private:
	__int64				m_id ;
	__int64				m_blockid ;
	int					m_layerid ;
	__int64				m_featureid;
	SYSTEMTIME			m_createtime ;
	int					m_operatetype;
	CString				m_desc;
	int					m_incrementtype;
	int					m_direction;
	//表示此POI是否被浏览过 (被点击,产生目视错误)制作过程中退出有进入的，会消除
	bool                m_bScanf;
};
// 
// extern "C"
// {
// 	__declspec(dllexport) CTaskBlockDetail *NewTaskBlockDetail() ;
// }


#endif // !defined(AFX_CTASKBLOCKDETAIL_H__EBB8A445_DBBE_4CA3_B383_CBA634DADEFD__INCLUDED_)
