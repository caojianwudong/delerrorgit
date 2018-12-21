// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CNAVIMAP_454573A302CE_INCLUDED
#define _INC_CNAVIMAP_454573A302CE_INCLUDED

#include "Commondef.h"

class CLayer ;
class CRoadLayer ;
class CPOILayer ;
class CVSLayer ;

//##ModelId=46B7D170032C
struct ConnInfo
{
	long iDataSourceID;
	long iReferSourceID;
	long iIDSourceID;
};
typedef std::vector<CLayer *>	VECTOR_LayerList ;
typedef std::map<long, IUnknown *> MAP_ConnList;
typedef MAP_ConnList::value_type MAP_ConnListValueType;
typedef MAP_ConnList::iterator MAP_ConnListIt;
typedef std::map<_bstr_t, ConnInfo> MAP_LayerConnInfoList;
typedef MAP_LayerConnInfoList::value_type MAP_LayerConnInfoListValyeType;
typedef MAP_LayerConnInfoList::iterator MAP_LayerConnInfoListIt;
//##ModelId=455025270357
//ͼ����
//�������ӵ�ͼ���վ���ͼ������ÿ����ͼ����̶������򣬳�����
//��Ĳ��ֽ����ü�����
//##ModelId=46B7B83A0251
class __declspec(dllexport) CNaviMap 
{
public:
	//int LoadLayerByTemplate( const char * template_name, const char * map_name, const char * layer_name, const char * szFullPath );
	//��ȡͼ����Χ
	//##ModelId=46B7B83A02FD
	SGeoRect GetBound(  );

	void ResetUndoFeature();
	void ClearUndoFeatureSet();
	bool bISSaveUndoInfo();
	void SetSaveUndoInfo( bool bISSaveStatus );
	//##ModelId=46B7B83A0252
	CLayer * ResetLayer( );
	//##ModelId=46B7B83A0253
	void CloneLayer ( LAYER LayerID );
	//##ModelId=46B7B83A0262
	void Release();
	//##ModelId=46B7B83A0263
	int GetMapLayerIndexByLayerID( LAYER ID );
	//##ModelId=46B7B83A0265
	CPOILayer * GetPOILayerPtr();
	//##ModelId=46B7B83A0266
	CVSLayer * GetVSLayerPtr();
	//##ModelId=46B7B83A0267
	CRoadLayer * GetRoadLayerPtr();
	//##ModelId=46B7B83A0268
	//bool InitAllLayerFromTemplate ( const char * TemplateFile );
	//##ModelId=46B7B83A0272
	CNaviMap() ;
	
	//##ModelId=46B7B83A0280
	~CNaviMap() ;

	//����ͼ�����
	//##ModelId=46B7B83A0290
	MESH GetID();

	//����ͼ�����
	//##ModelId=46B7B83A029F
	bool SetID(MESH MapID);

	//����ͼ������
	//##ModelId=46B7B83A02AF
	const char * GetName();

	//����ͼ������
	//##ModelId=46B7B83A02BF
	bool SetName(const char * szName);

	//����ͼ��˵��
	//##ModelId=46B7B83A02DE
	const char * GetDesc();

	//����ͼ��˵��
	//##ModelId=46B7B83A02EE
	bool SetDesc(const char * szDesc);

	//��ȡͼ����Χ
	//##ModelId=46B7B83A02FD
	SGeoRect GetBound( bool	bIs25 );

	//����ͼ����Χ
	//##ModelId=46B7B83A030D
	bool SetBound(SGeoRect sBound);

	//��ȡ������󱣴��ʱ��
	//##ModelId=46B7B83A031C
	time_t GetLastModifiedTime();

	//��ȡʸ����ı����߷�ĸ
	//##ModelId=46B7B83A032C
	UINT GetScale();

	//����ͼ�������߷�ĸ
	//##ModelId=46B7B83A033C
	bool SetScale(UINT sScale);

	//��ȡ���ݰ汾��
	//##ModelId=46B7B83A034B
	const char * GetDataVersion();

	//��
	//##ModelId=46B7B83A035B
	bool Open( const char * szFullPath );

	//����
	//##ModelId=46B7B83A036B
	bool Save( const char * szFullPath );

	//�ر�
	//##ModelId=46B7B83A036D
	bool Close();

	//���ص�ͼͼ������
	//##ModelId=46B7B83A037A
	int	GetMapLayerCount();

	//�������ƻ�ȡ��ͼͼ��ָ�롣
	//##ModelId=46B7B83A037B
	CLayer * GetMapLayerByName( const char * szName ) ;

	//�������ƻ�ȡ��ͼͼ������ֵ
	//##ModelId=46B7B83A038B
	CLayer * GetMapLayerByIndex( int LayerIndex ) ;

	//ͨ������ֵ��ȡָ����ͼͼ��
	//##ModelId=46B7B83A038D
	int GetMapLayerIndexByName( const char * szName ) ;

	//���ݵ�ͼͼ������ֵ��ȡ��ͼͼ������
	//##ModelId=46B7B83A039A
	const char * GetMapLayerNameByIndex( int LayerIndex ) ;

	//���õ�ǰͼ�㡣
	//##ModelId=46B7B83A039C
	bool SetCurrentMapLayer( int LayerIndex ) ;

	//��ȡ��ǰͼ�㡣
	//##ModelId=46B7B83A03AA
	CLayer * GetCurrentMapLayer() ;

	//���ݵ�ͼͼ������ɾ����ͼͼ�㡣
	//##ModelId=46B7B83A03AB
	bool DeleteMapLayerByName( const char * szName ) ;

	//��������ֵɾ����ͼͼ��
	//##ModelId=46B7B83A03B9
	bool DeleteMapLayerByIndex( int layer_index ) ;

	//�����ƶ�һ�㡣
	//##ModelId=46B7B83A03BB
	bool MoveNext( int iIndex );

	//�����ƶ�һ�㡣
	//##ModelId=46B7B83A03C8
	bool MovePrev( int iIndex );

	//�ƶ������㡣
	//##ModelId=46B7B83A03CA
	bool MoveTop( int iIndex );

	//�ƶ����ײ㡣
	//##ModelId=46B7B83A03CC
	bool MoveBottom( int iIndex );

	//�ƶ���ָ����λ�á�
	//##ModelId=46B7B83A03D9
	bool MoveTo( int iIndex, int iPos );

	//��ȡ��ͼ�Ƿ��޸Ĺ���
	//##ModelId=46B7B83A03DC
	bool IsModified();

	//����ͼ����޸ı�ǡ�
	//##ModelId=46B7B83B0000
	void SetModified( bool bModified=true );

// lishman@20170315 �������Խӿ�
public:

    // ��ȡ�û�ID
    unsigned GetUserID();

    // �����û�ID
    void SetUserID(unsigned uID);
    
    // ��ȡ��ĿID
    unsigned GetProject();

    // ������ĿID(0:��ʾ�ύ����ʱ��������project�ֶ�)
    void SetProject(unsigned projID);

    // ��ȡ�ύ����
	CommitParams GetCommitParams();

    // �����ύ����
    void SetCommitParams(CommitParams mode);

    IUIDManger *  GetUIDFactory();
 
    IEMPLayer   *   GetEMPLayer(LPCSTR sdelayer, LPCSTR pdblayer);

    ISQLConnector * GetDataSource(LPCSTR strlayer);

	bool IsLoadRefer();

	bool IsLoadAttach(const char * strAttachLayerName);

	const char * GetConfig(const char * strKey);

public:

    // ����ͼ�����ƻ�ȡ��Դ�������
    unsigned QueryLayerResource(const char * layerName);

    // ��ȡ���½���׼ͼ��
    CLayer * GetOrMakeLayer(const char * layerName);

    // ��׼���ظ���(NOTIMPL)
    bool Open(MESH * mapID, unsigned nMap, unsigned uScale);

    // ��׼��������(NOTIMPL)
    bool Open(SGeoRect * pRects, unsigned nRects);

    // �������
    bool Save();

	void QueryMapBound();

	void ReleaseMemory();

private:

	bool LoadConnConfig();

private:
	SGeoRect Get25000Bound( SGeoRect bound );

	bool m_bISSaveStatus;

	//�½�һ����ͼͼ��
	//##ModelId=46B7B83B0003
	bool AddMapLayer(CLayer * pMapLayer);

	//ȷ��ͼ�������ͼ���������Ƿ��ͻ
	//##ModelId=46B7B83B000F
	bool Verify ( MESH	MapID, UINT	Scale );

	//ͼ�����
	//##ModelId=46B7B83B0012
	UINT		m_iMapIndex ;

	//ͼ��������
	//##ModelId=46B7B83B001F
	UINT		m_iMapScale ;

	//��ͼ����
	//##ModelId=46B7B83B0020
	char		m_strMapName[MAP_NAME_MAX_LENGTH] ;

	//��ͼ����
	//##ModelId=46B7B83B0021
	char		m_strMapDesc[MAP_DESC_MAX_LENGTH] ;

	//��ͼ����
	//##ModelId=46B7B83B0023
	SGeoRect		m_MapBound ;

	//�����޸�ʱ��
	//##ModelId=46B7B83B002E
	time_t		m_LastModifiedTime ;

	//�ļ��汾
	//##ModelId=46B7B83B002F
	char		ver[16] ;

	//�Ƿ��޸�
	//##ModelId=46B7B83B003E
	bool		m_bIsModified ;
	
	//ͼ���б�
	//##ModelId=46B7D17003C9
	VECTOR_LayerList  m_MapLayerList ;

	//��ǰͼ��
	//##ModelId=46B7B83B0044
	int								m_CurrentMapLayerIndex ;

	//��ǰ��ʾ����
	//##ModelId=46B7B83B004F
	SGeoRect					    m_CurrentMapPos ;

    // �û����
	unsigned   m_userID;

    // ��Ŀ���
    unsigned   m_projID;
	
    // �ύ����
	CommitParams m_paramCommit;

    // ID��ͼ�����ӿ�
    IUIDManger  * m_pUIDManager;
    
    // �ɹ���ͼ�����ӿ�
    IEMPManager * m_pEmpManager;

    jmeta         m_jConfig;

    std::vector< std::pair<std::string, ISQLConnector *> > m_dbConns; 

	bool m_bLoadRefer;

	std::map<std::string, bool> m_attach;

	std::map<std::string, std::string> m_mapConfig;

//	MAP_ConnList m_mapConnList;

//	MAP_LayerConnInfoList m_mapLayerConnInfoList;

//	ConnInfo m_sDefaultConnInfo;

};

extern "C"
{
	 __declspec(dllexport) CNaviMap* CreateNaviMapObject() ;
}


#endif /* _INC_CNAVIMAP_454573A302CE_INCLUDED */
