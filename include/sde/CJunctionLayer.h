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

	// �򿪱༭���α�(��Ŀ���)
    virtual ISQLTransact * OpenCursorForDataSource(unsigned projID);
    
    // �򿪱༭���α�(JSON����)
    virtual ISQLTransact * OpenCursorForDataSource(LPCSTR cjson);
	
    // �򿪱༭���α�(�������)
    virtual ISQLTransact * OpenCursorForDataSource(SGeoRect * pRects, unsigned nRects);

	// �򿪱༭���α�(ʱ���)
	virtual ISQLTransact * OpenCursorForDataSource(time_t tBegin, time_t tEnd);

	// �ӱ༭���������, ���ؼ���״̬
    virtual unsigned LoadFromDataSource(OID * pOIDs, unsigned nOIDS, bool isrefer);

	// �򿪳ɹ����α�(JSON����)
    virtual ISQLTransact * OpenCursorForReferSource(LPCSTR cjson);
	
    // �򿪳ɹ����α�(�������)
    virtual ISQLTransact * OpenCursorForReferSource(SGeoRect * pRects, unsigned nRects);
	
	// �򿪳ɹ����α�(����ͼ��)
	virtual ISQLTransact * OpenCursorForReferSource(CLayer * pOtherLayer, bool isrefer);
	
	// �򿪳ɹ����α�(ʱ���)
	virtual ISQLTransact * OpenCursorForReferSource(time_t tBegin, time_t tEnd);
	
    virtual unsigned LoadFromReferSource(OID * pOIDs, unsigned nOIDS, bool isrefer);

	// ��ȡ���������ĵ�·
	virtual unsigned GetLinkRoadsByJunction(OID oid, OID * pOIDs, unsigned maxsize);

	//��ȡ���������ĵ�·������ɾ���ĵ�·��
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
