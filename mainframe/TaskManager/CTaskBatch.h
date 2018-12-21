// TaskBatch.h: interface for the CTaskBatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKBATCH_H__673416E7_BFB6_4D1C_8A92_A5C1DEBF46EB__INCLUDED_)
#define AFX_TASKBATCH_H__673416E7_BFB6_4D1C_8A92_A5C1DEBF46EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CDBFields.h"
#include <string>
using namespace std;
class _declspec(dllexport)  CTaskBatch  :public CDBFields
{
public:
	CTaskBatch();
	virtual ~CTaskBatch();

	const char * GetRemark();
	void SetRemark(const char * str);
	int GetUID();
	void SetUID(int iUID);
	int GetDataSetType();
	void SetDataSetType(int iDataSetType);
	__int64 GetProjectId();
	void SetProjectId(__int64 iProjectId);
	__int64 GetDataSetId();
	void SetDataSetId(__int64 iDataSetId);
	__int64 GetBatchId();
	void SetBatchId(__int64 iBatchId);
	__int64 GetId();
	void SetId(__int64 id);
	void SetCreateTime(SYSTEMTIME tCreateTime);
	SYSTEMTIME GetCreateTime();
	void SetSystemid(int systemid) ;
	int GetSystemid() ;

protected:
	__int64 m_id;
	int m_datasettype;
	__int64 m_datasetid;
	__int64 m_projectid;
	int m_uid;
	__int64 m_batchid;
	SYSTEMTIME m_creatime;
	std::string m_remark;
	int m_systemid ;

};

#endif // !defined(AFX_TASKBATCH_H__673416E7_BFB6_4D1C_8A92_A5C1DEBF46EB__INCLUDED_)
