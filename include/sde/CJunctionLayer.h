// CJunctionLayer.h: interface for the CJunctionLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CJUNCTIONLAYER_H__8B5627DD_32C8_4466_AD12_172A2A89A70B__INCLUDED_)
#define AFX_CJUNCTIONLAYER_H__8B5627DD_32C8_4466_AD12_172A2A89A70B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CLayer.h"

class __declspec(dllexport) CJunctionLayer : public CLayer 
{
public:
	CJunctionLayer(CNaviMap* ownerNaviMap, LAYER LayerID, jmeta * pFieldsInfo);
	~CJunctionLayer();

	virtual ELayerType GetLayerType () ;

	virtual CFeature* NewFeature (GEOTYPE type, OID featureID = -1);

	virtual void ClearUndoFeatureSet();
	
	virtual void ResetUndoFeatureSet() ;
	
	virtual bool DeleteFeature (OID featureID);
	
	virtual bool ResumeFeature (OID featureID);
	
	virtual void Clear ();
	
	virtual bool CloneLayer ( CLayer *pLayer );
	
	virtual void Release();

public:

	// 打开编辑库游标(项目编号)
    virtual ISQLTransact * OpenCursorForDataSource(unsigned projID);
    
    // 打开编辑库游标(JSON参数)
    virtual ISQLTransact * OpenCursorForDataSource(LPCSTR cjson);
	
    // 打开编辑库游标(区域参数)
    virtual ISQLTransact * OpenCursorForDataSource(SGeoRect * pRects, unsigned nRects);

	// 打开编辑库游标(时间段)
	virtual ISQLTransact * OpenCursorForDataSource(time_t tBegin, time_t tEnd);

	// 从编辑库加载数据, 返回加载状态
    virtual unsigned LoadFromDataSource(OID * pOIDs, unsigned nOIDS, bool isrefer);

	// 打开成果库游标(JSON参数)
    virtual ISQLTransact * OpenCursorForReferSource(LPCSTR cjson);
	
    // 打开成果库游标(区域参数)
    virtual ISQLTransact * OpenCursorForReferSource(SGeoRect * pRects, unsigned nRects);
	
	// 打开成果库游标(其它图层)
	virtual ISQLTransact * OpenCursorForReferSource(CLayer * pOtherLayer, bool isrefer);
	
	// 打开成果库游标(时间段)
	virtual ISQLTransact * OpenCursorForReferSource(time_t tBegin, time_t tEnd);
	
    virtual unsigned LoadFromReferSource(OID * pOIDs, unsigned nOIDS, bool isrefer);

	// 获取交叉点关联的道路
	virtual unsigned GetLinkRoadsByJunction(OID oid, OID * pOIDs, unsigned maxsize);

	//获取交叉点关联的道路（包括删除的道路）
	virtual unsigned GetLinkRoadsByJunctionWithDel(OID oid, OID * pOIDs, unsigned maxsize);

	virtual bool Commit(CommitParams params);
	
	virtual bool CommitFeature(OID oid);
	
	virtual unsigned CommitAttach(CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);

	unsigned CommitByEditor(ISQLConnector * pConn, CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);
	
	unsigned CommitByVerifier(ISQLConnector * pConn, CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);
	
    unsigned CommitByToolkit(ISQLConnector * pConn, CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);

	void DeleteFeatureByReload(OID nodeId);

	CFeature* CreateNewNode();

protected:
	
	bool CreateDataView(ISQLConnector * pConn);

	virtual CFeature * CatchFromReferSource(OID oid);

};

#endif // !defined(AFX_CJUNCTIONLAYER_H__8B5627DD_32C8_4466_AD12_172A2A89A70B__INCLUDED_)
