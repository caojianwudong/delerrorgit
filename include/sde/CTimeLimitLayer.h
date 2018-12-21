// CTimeLimitLayer.h: interface for the CTimeLimitLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTIMELIMITLAYER_H__DDCC400A_9AE4_4DA9_BB3D_4AF6076159F0__INCLUDED_)
#define AFX_CTIMELIMITLAYER_H__DDCC400A_9AE4_4DA9_BB3D_4AF6076159F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "commondef.h"	// Added by ClassView
#include "CLayer.h"	// Added by ClassView
class CNaviMap ;
class CFeatureSet ;
class CFeature ;
class CFieldsInfo ;
class CMetaData ;
class CFields;

class __declspec(dllexport) CTimeLimitLayer  : public CLayer
{
public:
	CTimeLimitLayer(CNaviMap* ownerNaviMap, LAYER layerID, jmeta * pFieldsInfo);
	~CTimeLimitLayer();

	virtual ELayerType GetLayerType () ;

	virtual CFeature* NewFeature (GEOTYPE type, OID featureID = -1);

	// �򿪳ɹ����α�(JSON����)
	virtual ISQLTransact * OpenCursorForReferSource(LPCSTR cjson);
	
	// �򿪳ɹ����α�(�������)
	virtual ISQLTransact * OpenCursorForReferSource(SGeoRect * pRects, unsigned nRects);
	
	// �򿪳ɹ����α�(����ͼ��)
	virtual ISQLTransact * OpenCursorForReferSource(CLayer * pOtherLayer, bool isrefer);
	
	// �򿪳ɹ����α�(ʱ���)
	virtual ISQLTransact * OpenCursorForReferSource(time_t tBegin, time_t tEnd);

	virtual unsigned LoadFromReferSource(OID * pOID, unsigned nOID, bool isrefer);

	virtual bool Commit(CommitParams params);
	
	virtual bool CommitFeature(OID oid);
	
	virtual unsigned CommitAttach(CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);

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

	virtual void ClearUndoFeatureSet();
	
	virtual void ResetUndoFeatureSet() ;
	
	virtual bool DeleteFeature (OID featureID);
	
	virtual bool ResumeFeature (OID featureID);
	
	virtual void Clear ();
	
	virtual bool CloneLayer ( CLayer *pLayer );
	
	virtual void Release();
	
protected:
	
	bool CreateDataView(ISQLConnector * pConn);
	
	virtual CFeature * CatchFromReferSource(OID oid);

};

#endif // !defined(AFX_CTIMELIMITLAYER_H__DDCC400A_9AE4_4DA9_BB3D_4AF6076159F0__INCLUDED_)
