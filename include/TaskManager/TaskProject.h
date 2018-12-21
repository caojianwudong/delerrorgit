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
	int m_type;//	项目类型，1:视频编辑，2:平板属性编辑，3:位置编辑	int
	int m_uid;//	项目添加人员	int
	int m_pdifficulty;//	难度系数	int
	int m_priority;//	优先级，默认与id号相同	int
	int m_state;	//状态：0未开始    1任务正在进行  2任务暂停;   3所有任务已被锁定或完成，待解锁状态4、任务完成   5提交完成（可导出，可上传母库）	int
	int m_tasknum;//	下属任务数量	int
	__int64 m_systemid ; // 所属平台ID bigint
	CString m_description;//	项目描述	varchar
	SYSTEMTIME	m_createtime;//	创建时间	timestamp
	CString m_province;//	项目所属省份	varchar
	CString m_city;//	项目所属城市	varchar
	CString	m_name;//	项目名	varchar
	int	m_paccess;//	0：公有，1：私有	int
	CString	m_checkprogress;//	校验作业的进度	varchar
	int	m_checkstate;//	校验状态：0未开始1开始2暂停3锁定4完成	int
	CString	m_modifyprogress;	//修改进度	varchar
	int	m_modifystate;//	修改状态：0未开始，1开始，2暂停，3锁定，4完成	int
	CString	m_confirmprogress;//	验证检查进度	varchar
	int	m_confirmstate;//	验证检查状态：0未开始，1开始，2暂停，3锁定，4完成	int
	CString	m_overprogress;//	任务完成进度，完成的任务表示可以导出	varchar
	double	m_poitotckdisl;//	计算POI与轨迹关联关系时使用：左侧POI到轨迹的垂直距离	double
	double	m_poitotckdisr;//	计算POI与轨迹关联关系时使用：右侧POI到轨迹的垂直距离	double
	SYSTEMTIME m_creatime;

};

#endif // !defined(AFX_TASKPROJECT_H__A1757CA1_F5C3_4CDD_A345_155645A1C408__INCLUDED_)
