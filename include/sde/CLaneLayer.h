// CLaneLayer.h: interface for the CLaneLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLANELAYER_H__208E252B_05F7_4B82_951C_DB8D9BC21B84__INCLUDED_)
#define AFX_CLANELAYER_H__208E252B_05F7_4B82_951C_DB8D9BC21B84__INCLUDED_

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

class __declspec(dllexport) CLaneLayer  : public CLayer
{
public:
	CLaneLayer(CNaviMap* ownerNaviMap, LAYER layerID, jmeta * pFieldsInfo);
	~CLaneLayer();

	virtual ELayerType GetLayerType () ;

	virtual CFeature* NewFeature (GEOTYPE type, OID featureID = -1);
	
	// 打开成果库游标(JSON参数)
	virtual ISQLTransact * OpenCursorForReferSource(LPCSTR cjson);
	
	// 打开成果库游标(区域参数)
	virtual ISQLTransact * OpenCursorForReferSource(SGeoRect * pRects, unsigned nRects);
	
	// 打开成果库游标(其它图层)
	virtual ISQLTransact * OpenCursorForReferSource(CLayer * pOtherLayer, bool isrefer);
	
	// 打开成果库游标(时间段)
	virtual ISQLTransact * OpenCursorForReferSource(time_t tBegin, time_t tEnd);
	
	virtual unsigned LoadFromReferSource(OID * pOID, unsigned nOID, bool isrefer);

	virtual bool Commit(CommitParams params);
	
	virtual bool CommitFeature(OID oid);
	
	virtual unsigned CommitAttach(CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);

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

#endif // !defined(AFX_CLANELAYER_H__208E252B_05F7_4B82_951C_DB8D9BC21B84__INCLUDED_)
