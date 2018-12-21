// TaskProject.h: interface for the CTaskProject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKPROJECT_H__A1757CA1_F5C3_4CDD_A345_155645A1C408__INCLUDED_)
#define AFX_TASKPROJECT_H__A1757CA1_F5C3_4CDD_A345_155645A1C408__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class _declspec(dllexport) CTaskProject  
{
public:
	CTaskProject();
	virtual ~CTaskProject();
	void SetId(__int64 id);
	__int64 GetId();
	int GetType();
	void SetType(int strType);
	int GetState();
	void SetState(int strState);
	int GetUid();
	void SetUid(int strUid);
	int GetDifficulty();
	void SetDifficulty(int strDifficulty);
	CString GetDescription();
	void SetDescription(CString strDescription);
	void SetPriority(int priority) ;
	int GetPriority() ;
	CString GetCity();
	void SetCity(CString strCity);
	CString GetProvince();
	void SetProvince(CString strProvince);
	CString GetName();
	void SetName(CString strName);
	void SetCreateTime( SYSTEMTIME systime) ;
	SYSTEMTIME GetCreateTime() ;


private:

	__int64 m_id;
	int m_type;//	��Ŀ���ͣ�1:��Ƶ�༭��2:ƽ�����Ա༭��3:λ�ñ༭	int
	int m_uid;//	��Ŀ�����Ա	int
	int m_pdifficulty;//	�Ѷ�ϵ��	int
	int m_priority;//	���ȼ���Ĭ����id����ͬ	int
	int m_state;	//״̬��0δ��ʼ    1�������ڽ���  2������ͣ;   3���������ѱ���������ɣ�������״̬4���������   5�ύ��ɣ��ɵ��������ϴ�ĸ�⣩	int
	int m_tasknum;//	������������	int
	__int64 m_systemid ; // ����ƽ̨ID bigint
	CString m_description;//	��Ŀ����	varchar
	SYSTEMTIME	m_createtime;//	����ʱ��	timestamp
	CString m_province;//	��Ŀ����ʡ��	varchar
	CString m_city;//	��Ŀ��������	varchar
	CString	m_name;//	��Ŀ��	varchar
	int	m_paccess;//	0�����У�1��˽��	int
	CString	m_checkprogress;//	У����ҵ�Ľ���	varchar
	int	m_checkstate;//	У��״̬��0δ��ʼ1��ʼ2��ͣ3����4���	int
	CString	m_modifyprogress;	//�޸Ľ���	varchar
	int	m_modifystate;//	�޸�״̬��0δ��ʼ��1��ʼ��2��ͣ��3������4���	int
	CString	m_confirmprogress;//	��֤������	varchar
	int	m_confirmstate;//	��֤���״̬��0δ��ʼ��1��ʼ��2��ͣ��3������4���	int
	CString	m_overprogress;//	������ɽ��ȣ���ɵ������ʾ���Ե���	varchar
	double	m_poitotckdisl;//	����POI��켣������ϵʱʹ�ã����POI���켣�Ĵ�ֱ����	double
	double	m_poitotckdisr;//	����POI��켣������ϵʱʹ�ã��Ҳ�POI���켣�Ĵ�ֱ����	double
	SYSTEMTIME m_creatime;

};

#endif // !defined(AFX_TASKPROJECT_H__A1757CA1_F5C3_4CDD_A345_155645A1C408__INCLUDED_)
