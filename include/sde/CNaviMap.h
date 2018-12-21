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
//图幅类
//导航电子地图按照矩形图幅管理，每个地图有其固定的区域，超出区
//域的部分将被裁减掉。
//##ModelId=46B7B83A0251
class __declspec(dllexport) CNaviMap 
{
public:
	//int LoadLayerByTemplate( const char * template_name, const char * map_name, const char * layer_name, const char * szFullPath );
	//获取图幅范围
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

	//返回图幅编号
	//##ModelId=46B7B83A0290
	MESH GetID();

	//设置图幅编号
	//##ModelId=46B7B83A029F
	bool SetID(MESH MapID);

	//返回图幅名称
	//##ModelId=46B7B83A02AF
	const char * GetName();

	//设置图幅名称
	//##ModelId=46B7B83A02BF
	bool SetName(const char * szName);

	//返回图幅说明
	//##ModelId=46B7B83A02DE
	const char * GetDesc();

	//设置图幅说明
	//##ModelId=46B7B83A02EE
	bool SetDesc(const char * szDesc);

	//获取图幅范围
	//##ModelId=46B7B83A02FD
	SGeoRect GetBound( bool	bIs25 );

	//设置图幅范围
	//##ModelId=46B7B83A030D
	bool SetBound(SGeoRect sBound);

	//获取数据最后保存的时间
	//##ModelId=46B7B83A031C
	time_t GetLastModifiedTime();

	//获取矢量层的比例尺分母
	//##ModelId=46B7B83A032C
	UINT GetScale();

	//设置图幅比例尺分母
	//##ModelId=46B7B83A033C
	bool SetScale(UINT sScale);

	//获取数据版本号
	//##ModelId=46B7B83A034B
	const char * GetDataVersion();

	//打开
	//##ModelId=46B7B83A035B
	bool Open( const char * szFullPath );

	//保存
	//##ModelId=46B7B83A036B
	bool Save( const char * szFullPath );

	//关闭
	//##ModelId=46B7B83A036D
	bool Close();

	//返回地图图层数量
	//##ModelId=46B7B83A037A
	int	GetMapLayerCount();

	//根据名称获取地图图层指针。
	//##ModelId=46B7B83A037B
	CLayer * GetMapLayerByName( const char * szName ) ;

	//根据名称获取地图图层索引值
	//##ModelId=46B7B83A038B
	CLayer * GetMapLayerByIndex( int LayerIndex ) ;

	//通过索引值获取指定地图图层
	//##ModelId=46B7B83A038D
	int GetMapLayerIndexByName( const char * szName ) ;

	//根据地图图层索引值获取地图图层名称
	//##ModelId=46B7B83A039A
	const char * GetMapLayerNameByIndex( int LayerIndex ) ;

	//设置当前图层。
	//##ModelId=46B7B83A039C
	bool SetCurrentMapLayer( int LayerIndex ) ;

	//获取当前图层。
	//##ModelId=46B7B83A03AA
	CLayer * GetCurrentMapLayer() ;

	//根据地图图层名称删除地图图层。
	//##ModelId=46B7B83A03AB
	bool DeleteMapLayerByName( const char * szName ) ;

	//根据索引值删除地图图层
	//##ModelId=46B7B83A03B9
	bool DeleteMapLayerByIndex( int layer_index ) ;

	//向下移动一层。
	//##ModelId=46B7B83A03BB
	bool MoveNext( int iIndex );

	//向上移动一层。
	//##ModelId=46B7B83A03C8
	bool MovePrev( int iIndex );

	//移动到顶层。
	//##ModelId=46B7B83A03CA
	bool MoveTop( int iIndex );

	//移动到底层。
	//##ModelId=46B7B83A03CC
	bool MoveBottom( int iIndex );

	//移动到指定的位置。
	//##ModelId=46B7B83A03D9
	bool MoveTo( int iIndex, int iPos );

	//获取地图是否被修改过。
	//##ModelId=46B7B83A03DC
	bool IsModified();

	//设置图层的修改标记。
	//##ModelId=46B7B83B0000
	void SetModified( bool bModified=true );

// lishman@20170315 新增属性接口
public:

    // 获取用户ID
    unsigned GetUserID();

    // 设置用户ID
    void SetUserID(unsigned uID);
    
    // 区取项目ID
    unsigned GetProject();

    // 设置项目ID(0:表示提交数据时，不更新project字段)
    void SetProject(unsigned projID);

    // 获取提交参数
	CommitParams GetCommitParams();

    // 设置提交参数
    void SetCommitParams(CommitParams mode);

    IUIDManger *  GetUIDFactory();
 
    IEMPLayer   *   GetEMPLayer(LPCSTR sdelayer, LPCSTR pdblayer);

    ISQLConnector * GetDataSource(LPCSTR strlayer);

	bool IsLoadRefer();

	bool IsLoadAttach(const char * strAttachLayerName);

	const char * GetConfig(const char * strKey);

public:

    // 根据图层名称获取资源配置序号
    unsigned QueryLayerResource(const char * layerName);

    // 获取或新建标准图层
    CLayer * GetOrMakeLayer(const char * layerName);

    // 标准加载格网(NOTIMPL)
    bool Open(MESH * mapID, unsigned nMap, unsigned uScale);

    // 标准加载区域(NOTIMPL)
    bool Open(SGeoRect * pRects, unsigned nRects);

    // 保存参数
    bool Save();

	void QueryMapBound();

	void ReleaseMemory();

private:

	bool LoadConnConfig();

private:
	SGeoRect Get25000Bound( SGeoRect bound );

	bool m_bISSaveStatus;

	//新建一个地图图层
	//##ModelId=46B7B83B0003
	bool AddMapLayer(CLayer * pMapLayer);

	//确认图幅编号与图幅比例尺是否冲突
	//##ModelId=46B7B83B000F
	bool Verify ( MESH	MapID, UINT	Scale );

	//图幅编号
	//##ModelId=46B7B83B0012
	UINT		m_iMapIndex ;

	//图幅比例尺
	//##ModelId=46B7B83B001F
	UINT		m_iMapScale ;

	//地图名称
	//##ModelId=46B7B83B0020
	char		m_strMapName[MAP_NAME_MAX_LENGTH] ;

	//地图描述
	//##ModelId=46B7B83B0021
	char		m_strMapDesc[MAP_DESC_MAX_LENGTH] ;

	//地图区域
	//##ModelId=46B7B83B0023
	SGeoRect		m_MapBound ;

	//最后的修改时间
	//##ModelId=46B7B83B002E
	time_t		m_LastModifiedTime ;

	//文件版本
	//##ModelId=46B7B83B002F
	char		ver[16] ;

	//是否被修改
	//##ModelId=46B7B83B003E
	bool		m_bIsModified ;
	
	//图层列表
	//##ModelId=46B7D17003C9
	VECTOR_LayerList  m_MapLayerList ;

	//当前图层
	//##ModelId=46B7B83B0044
	int								m_CurrentMapLayerIndex ;

	//当前显示区域
	//##ModelId=46B7B83B004F
	SGeoRect					    m_CurrentMapPos ;

    // 用户编号
	unsigned   m_userID;

    // 项目编号
    unsigned   m_projID;
	
    // 提交参数
	CommitParams m_paramCommit;

    // ID库图层管理接口
    IUIDManger  * m_pUIDManager;
    
    // 成果库图层管理接口
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
