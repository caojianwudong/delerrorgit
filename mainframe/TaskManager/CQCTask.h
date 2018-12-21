// CQCTask.h: interface for the CQCTask class.
//	qctask ����itemset��block��Ϣ
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

	// �ο�������
	_TSGEO::SGeoRect GetBound() ;
	void SetBound(_TSGEO::SGeoRect bound) ;
	// ��òο�ͼ��ĸ���
	int GetReferLayerCount() ;
	// ��ȡ�ο�ͼ����
	const char* GetLayerNameByIndex(int iIndex) ;
	void SetLayerName(const char *szLayername) ;
	// ��òο�����
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
