// CTask.h: interface for the CTask class.
/*
	1.0 ��ҵ���ϼ�¼��ָfielddata���¼
	2.0 ��ҵ������ָfielddata���¼��shapeid��Ӧ����ҵ��
	3.0 ��ҵ���������ǰ�������õ���ҵ����id����˳������
	4.0 �������fielddata��attach��block��Ϣ������block����֮ǰ��linkpoi��Ϣ��
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTASK_H__FA1FB987_3AB8_4335_9B06_58D076878A37__INCLUDED_)
#define AFX_CTASK_H__FA1FB987_3AB8_4335_9B06_58D076878A37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "video_definition.h"

#include <vector>
#include <map>

#include "task_definition.h"

struct vtDef
{
	std::vector<__int64> vt;
};

enum RECORDTYPE
{
	RECORDTYPE_PHOTO = 1,//��Ƭ
	RECORDTYPE_SOUND = 2//����
};

class CTaskLinkAttach;
class CTaskLinkFieldData;
class CTaskBlock ;

typedef   std::pair<CString,CString>  VALUEPAIR;  
typedef std::multimap<CString, VALUEPAIR> MAP_STRINGPAIR;

// shapeid -- fielddata
typedef    std::multimap<__int64 ,CTaskLinkFieldData* >  MAP_SHAPEID_FIELDDATA;

#include "CTaskCommon.h"

struct FieldRefer 
{
	string strname ;
	__int64 batchid ;
	_TSGEO::SGeoRect bound ;
};

struct EditRefer 
{
	string strname ;
	_TSGEO::SGeoRect bound ;
};

typedef std::vector<FieldRefer>			VT_FieldRefer ;
typedef std::vector<EditRefer>			VT_EditRefer ;

class _declspec(dllexport) CTask  :public CTaskCommon
{
public:
	CTask();
	virtual ~CTask();

	__int64  GetID();
	void     SetID(__int64 id);
	int      GetTaskType();
	void     SetTaskType(int tasktype);
	int      GetState();
	void     SetState(int state);
	void     SetProcess(int process );
	int		 GetProcess();
	int      GetRoleId();
	void     SetRoleId(int roleid);
	void     SetEditRoleId(int iEditRoleId);
	int      GetEditRoleId();
	void     SetCheckRoleId(int idCheckRole);
	int      GetCheckRoleId();
	__int64       GetProjectId();
	void     SetProjectId(__int64);
	double   GetLastExit();
	void     SetLastExit(double lastexit);
	void     SetPriority(int priority);
	void     SetProjectName(CString sProjectName);
	CString  GetProjectName();

	__int64  GetBatchId();
	void     SetBatchId(__int64 batchid );

	CString  GetTaskName();

	void SetTaskBlock(CTaskBlock *pTaskBlock) ;
	CTaskBlock *GetTaskBlock() ;

	bool LoadLinkInfo()  ;


	//�ͷ������ڴ�
	void	ReleaseTask();
	//���������Ϣ
	void Clear();

	// �ο�������
	_TSGEO::SGeoRect GetQCBound() ;
	void SetQCBound(_TSGEO::SGeoRect bound) ;
	_TSGEO::SGeoRect GetToolBound() ;
	void SetToolBound(_TSGEO::SGeoRect bound) ;
	// qc�������ͼ��
	const char *GetQCLayerNameByIndex(int index) ;
	const char *GetToolLayerNameByIndex(int index) ;
	void SetQCReferLayerName(const char* szLayername) ;
	void SetToolReferLayerName(const char *szLayername) ;
	// ��òο�ͼ��ĸ���
	int GetQCReferLayerCount() ;
	int GetToolReferLayerCount() ;
	int GetEditReferLayerCount() ;
	int GetFieldReferLayerCount() ;
	// ��ȡ�ο�ͼ����Ϣ
	FieldRefer GetFieldReferIndex(int iIndex) ;
	void SetFieldRefer(FieldRefer fieldrefer) ;

	EditRefer GetEditReferIndex(int iIndex) ;
	void SetEditRefer(EditRefer editrefer) ;

	// ���ݹؼ��ֻ��referdata��jsonb,�˷��������Ѿ����ع�task����Ժ�LoadLinkInfo��
	void GetReferdataByKey(const char *szkey) ;
private:
	bool LoadLinkAttach() ;
	bool LoadLinkFielddata() ;

	//====================��ҵ����DB======================================//
public:
	//
	void  AddTaskLinkFieldData(__int64 shapeid,CTaskLinkFieldData* pFieldData);

	void  AddTaskLinkAttach(CTaskLinkAttach* pAttach);
	
	//��ȡ���ݱ�����ҵ���ϼ�¼��
	int GetLinkDbFieldDataCount();

	//����������ȡ���ݱ�����ҵ����
	CTaskLinkFieldData*  GetLinkFieldDataByIndex(int index);

	//������ҵ����id��ȡ��Ӧ��poiid
	bool  GetPoiIdByShapeid(__int64 shapeid,vtDef* pvtDef);

	//������ҵ����id��ȡ��Ӧ��piciid
	bool  GetPicIdByShapeid(__int64 shapeid ,vtDef* pvtdef);

	//����poiid��ȡ��Ӧ��piciid
	bool  GetPicIdByPoiid(__int64 poiid, vtDef* pvtdef);

	//=====================��Ƭ/��Ƶ=====================================//
public:
	//��ȡ���ݱ�����Ƭ�ļ�¼��
	int  GetLinkAttachCount();
	//����������ȡ���ݱ����Ƭ����
	CTaskLinkAttach*  GetLinkAttachByIndex(int index);

	//����picid��ȡpoi����
	bool GetPoiIdByPicid(__int64 picid, vtDef* pvtdef);

	//=======================poi=====================================//
public:

	//��ȡ������Ϣ
	int GetInfoType(__int64 poiid);

	//��ȡ�����ʶ
	bool bScan(__int64 poiid);

protected:

	//�����������ҵ���ϣ���map�洢��shapeid��������Ϊ�˷������
	//< shapeid , fileddata* >
	MAP_SHAPEID_FIELDDATA  map_taskLinkFieldData;
	//�����������Ƭ
	std::vector<CTaskLinkAttach* > vt_taskLinkAttach;

	//��������Ĵ����߼�����
	std::vector<__int64> m_vtTaskLinkItemset;

private:
	//����id
	__int64 m_id;
	//�������ͣ�1:��Ƶ��20:������ͨ����21:������ҵ����POI����22��������ҵ������ַ������23��������ҵ�޸�POI����24��������ҵ�޸���ַ������)
	int m_iTaskType;
	//��������:1:�������̣�2:������̣�3:�ۺϼ������
	int m_iFlowType;
	//����״̬��0δռ�ã�Ĭ�ϣ���1ռ�ã�2�ύ��3�������
	int m_iState;
	//��ɫ����
	int m_iRoleId;
	//�༭��Ա���һ�β�����Ƶʱ�Ľ�ɫ�û�id�������޸�Ϊͬһ��
	int m_idEditRoleUser;
	//У����Ա���һ�β�����Ƶʱ�Ľ�ɫ����id��У����֤Ϊͬһ��
	int m_idCheckRoleUser;
	//������������Ŀid
	__int64 m_idProject;
	// ������� ��Ƭ:POI���� ��Ƶ:
	double m_dLastExit;
	//���ȼ� ���Ȱ�������С������
	int  m_iPriority;
	//�ο�ͼ������
	char* m_szReferData;
	//��Ŀ����
	CString m_sProName;
	//����POI ���� 0: ��ʼֵ 1 :��ͨPOI 2:vip poi(У��ɸѡ��ʱ��Ż��޸����ֵ)
	int m_taskpoitype;
	//�ο�����
	CString m_strRefer;
	__int64 m_batchid;

	

public:
	//��ʼ����������
	bool  InitData();
  
	//�Ƿ������ύ����
	bool  bAlloCommitTask();


	//====================��ҵ����================================
public:
	
	//���õ�ǰ��������ҵ����
	void SetCurrentShapeIndex(int index);
	
    //��ȡ��ǰ��ҵ���ϵ�����
	int  GetCurrentShapeIndex();
	//��ȡ��ҵ���ϼ�¼����
	int  GetShapeIndexByShapeid(__int64 shapeid);
	
	//��ȡ��ǰ��������ҵ����
	CTaskLinkFieldData* GetCurrentFieldData();
	
	//��ȡ��ǰ��ҵ���ϵ�id
	__int64  GetCurrentShapeId();
	
	//��ȡ��ҵ���ϸ���
	int   GetFieldDataCount();
	//��ȡ��ҵ����id
	__int64  GetShapeIdByIndex(int index);
	
	//����poiid��ȡ��ҵ����id
	__int64  GetShapeIdByFeatureId(int poiid);

	//��ȡ��һ����ҵ��������
	__int64  GetNextShapeIndex();

	//��ȡ��һ����ҵ��������
	__int64  GetPreShapeIndex();

	//����������ҵ��¼��ϵ
	void  AddNewTaskLinkFieldData(__int64 shapeid,CTaskLinkFieldData* pFieldData);

	//����������Ƭ��¼��ϵ
	void  AddNewTaskLinkAttach(CTaskLinkAttach* pAttach);
	
	//======================��Ƭ/��Ƶ===========================
public:
	//������ҵ����id��ȡ��Ƭ����
	bool   GetPicByShapeId(__int64 shapeid,vtDef* pvtDef);
	
	
	bool   GetPoiByPicId(__int64 pic,std::vector<__int64> &vt);
	
	//������Ƭ������ȡ·��
	CString  GetPicPathByPicid(__int64 picid);

	//������Ƭ���ƻ�ȡpicid
	__int64 CTask::GetPicIdByPath(CString strPicName);
	
	void     AddPicPath(__int64 picid,CString strPath);
	
	
	//=======================poi===================================
public:

	//��ȡ����poi��(������sde����poi����ܵ���)
	void        GetPoiLinkPoi();

	bool        GetPoiLinkPoiByShapeId(__int64 shapeid,vtDef* pvtDef);

	//  
	void       AddDelDesc(CString ske,CString ikey,CString svalue);
	//��ȡ��һ��ɾ����������Ϣ
	int		   GetDelDescCount();

	bool       GetDelDescByIndex(int index,CString& ivalue ,CString& svalue);

	CString    GetErrorTypeName(CString sErrtype);

	CString    GetErrorTypeNameByIndex(int index);

	CString    GetErrorTypeByName(CString stypeanme);

	int		   GetErrorCount();

    int        GetQuestionDescCount();
	void       GetQuestionDescByIndex(int index,CString &sKey,CString& sValue);


	//by ycf 20170306 ��Ҫ�ṩһ�������ж���������е�POi����Щ�ֶ��б༭��Ȩ�ޣ���Щpoi���ƶ���Ȩ��
	bool         bAllow(){return true;}

	void SetReferData(CString strRefer);

	CString GetReferData();
	//������������Ĵ����߼�����
	void AddTaskLinkItemset(__int64 itemsetid);
	int GetTaskLinkItemsetCount();
	__int64 GetTaskLinkItemsetByIndex(int index);
private:
	

	//���õ�ǰ��������ҵ��������
	int     m_ShapeIndex ;
	
	//��ҵ����shapeid
	std::vector<__int64 > vt_shape_id;
	//shapeid,poiid
	std::map<__int64 ,std::vector<__int64> > map_shapeid_poiid;
	//shapeid,poi,poi ����ҵ���Ϲ�����Poi��poi������Poi ) ���ڹ���poi�б�
	std::map<__int64 ,std::vector<__int64> > map_shapeid_poiid_poiid;
	//shapeid,picid
	std::map<__int64 ,std::vector<__int64> > map_shapeid_picid;
	//pic,poiid
	std::map<__int64,std::vector<__int64> > map_picid_poiid;
	//poiid,picid
	std::map<__int64,std::vector<__int64> > map_poiid_picid;
	//pic ,path
	std::map<__int64,CString > map_pic_path;

	//���ݿ�������Ϣ
	MAP_STRINGPAIR    map_DBconfig;

	CTaskBlock *m_pBlock ;

	_TSGEO::SGeoRect m_sqcBound ;
	VT_CHAR m_vtqcLayerName ;
	_TSGEO::SGeoRect m_stoolBound ;
	VT_CHAR m_vttoolLayerName ;
	
	VT_EditRefer m_vtEditRefer ;
	VT_FieldRefer m_vtFieldRefer ;
	
};

#endif // !defined(AFX_CTASK_H__FA1FB987_3AB8_4335_9B06_58D076878A37__INCLUDED_)
