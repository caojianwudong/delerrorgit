// CQCTask.h: interface for the CQCTask class.
//	qctask 包含itemset、block信息
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CQCTASK_H__9F29ABA9_7F9F_47DD_A2CB_30F015CEE859__INCLUDED_)
#define AFX_CQCTASK_H__9F29ABA9_7F9F_47DD_A2CB_30F015CEE859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CTaskCommon.h"
#include "CTaskLinkItemSet.h"
#include "task_definition.h"

class CTaskLinkItemSet ;
class CTaskBlock ;
class _declspec(dllexport)CQCTask : public CTaskCommon  
{
public:
	CQCTask();
	virtual ~CQCTask();
	void SetLinkItemSet(CTaskLinkItemSet *pItemset) ;
	CTaskLinkItemSet *GetLinkItemSet() ;
	void SetTaskBlock(CTaskBlock *pTaskBlock) ;
	CTaskBlock *GetTaskBlock() ;
	bool LoadLinkInfo() ;

	// 参考的区域
	_TSGEO::SGeoRect GetBound() ;
	void SetBound(_TSGEO::SGeoRect bound) ;
	// 获得参考图层的个数
	int GetReferLayerCount() ;
	// 获取参考图层名
	const char* GetLayerNameByIndex(int iIndex) ;
	void SetLayerName(const char *szLayername) ;
	// 获得参考层数
	int GetReferLevel() ;
private:
	__int64 m_iTaskID ;
	CTaskLinkItemSet * m_pLinkItemSet ;
	CTaskBlock *m_pBlock ;
	_TSGEO::SGeoRect m_sBound ;
	VT_CHAR m_vtLayerName ;
	int m_ilevel ;
};

#endif // !defined(AFX_CQCTASK_H__9F29ABA9_7F9F_47DD_A2CB_30F015CEE859__INCLUDED_)
