//## begin module%375BECF903A3.cp preserve=no
//	//////////////////////////////////////////////////////////////////////
//	//
//	//  ���ߣ�
//	//  �������ڣ�
//	//  ����޸����ڣ�
//	//
//	//////////////////////////////////////////////////////////////////////
//## end module%375BECF903A3.cp

//## Module: CBackgroundLayer%375BECF903A3; Package specification
//## Subsystem: GIAE Components%372FC3E50277

#ifndef CBackgroundLayer_h
#define CBackgroundLayer_h 1

//## begin module%375BECF903A3.includes preserve=yes
#include <map>
#include "commondef.h"	// Added by ClassView
#include "CLayer.h"
//## end module%375BECF903A3.includes

// CBackgroundLayerInfo
// CFieldsInfo
// CFeatureSet
//#include "CFeatureSet.h"
//#include "..\\attribute\\CFieldsInfo.h"
//#include "CMetaData.h"
//## begin module%375BECF903A3.additionalDeclarations preserve=yes

class CNaviMap ;

//## end module%375BECF903A3.additionalDeclarations


//## Class: CBackgroundLayer%367FD86F00C8
//	CBackgroundLayer:����һ��ʸ��ͼ�㡣
//
//	<<˵��>>
//	�����ʾ������ĳ����������һ��ʸ��ͼ�㣬���а�����ͼ���������Ϣ��ͼ���������ݵ��ֶνṹ��Ϣ���͸�ͼ���������ĵ�����������ͬʱ�ṩ������Щ���ݵķ�����
//	���У�
//	a. ͨ��GetOwnerWorkAreaPtr()��ø�ͼ�����������������ָ�룻
//	b. ͼ��������Ϣ�����CBackgroundLayerInfo���У�ͨ��GetPOILayerInfoPtr()��ȡCBackgroundLayerInfo���ָ�룻
//	c. ͼ���������ݵ��ֶνṹ��Ϣ�����CFieldsInfo���У�ͨ��GetFieldsInfoPtr()��ȡCFieldsInfo���ָ�룻
//	d. ͼ�㽨����ɾ����ʹ��CreatePOILayerInFile()�����ݿ��н�����ͼ�����ͨ��DeletePOILayerInFile()�����ݿ���ɾ����ͼ�����
//	e. ������Ϣ����ʹ��LoadPOILayerInfo()�����ݿ���װ�ظ�ͼ���������Ϣ���������ݵ��ֶνṹ��Ϣ�������ͼ��Ĳ���������Ϣ�������޸ģ�ͼ�����Ʋ����޸ģ�����ʹ��UpdatePOILayerInfoToFile()���޸ĺ�����ݱ��浽���ݿ��У�
//	f. �����������ݵ�װ�أ�ʹ��Open()��ͼ��,�����ݿ���װ���������󣻿���ʹ��SetLoadFilter()����װ���������Ӷ�����ֻװ�ز������ݣ�ʹ��LoadFeaturesAppendant()�����ݿ��в���װ�����ݣ�
//	g. ������������ķ��ʣ����������ݱ�װ�ص��ڴ�󣬶�ÿһ���������������ڴ���������Ӧ����������(Feature Object)����ͨ��CFeatureSet������֯�������Ӷ����Ը�����Ҫʹ�ò�ͬ�ķ�������ĳһ�������������У�ͨ��GetAllFeaturesPtr()��ȡ������������������������󼯺ϵ�ָ�롣ͨ�������Է��ʸ�ͼ����������������������ע�⣺�������󼯺���ֻ�洢ָ��ʵ�����������ָ�룬�ṩ�Ը�����������ı����ķ��ʷ�ʽ����ÿ�������������ڴ���ֻ�洢һ�Σ�����������ࡣ
//	h. �������󼯺ϣ����ڸ��ֲ�ѯ��������Ĺ���ʹ��NewFeatureSet()�������ⴴ��һ���������󼯺�(CFeatureSet���ͣ������Ա�����ֲ�ѯ�ͷ����Ľ���������ڸ�����֮����и��ּ�������������Ӷ�����ʵ�ָ���Ƕ�׺͵����ĸ��ӵĲ�ѯ�������
//	   �ö��󼯺ϱ��������������ʱʹ�õļ��϶���������ɴ������Ķ�����й����ɾ����������ü����ڴ�������Ҫ����ͳһ�Ĺ����Ա��ڽ��к�̵Ĳ���������ʾ����ѯ/������������ϵȣ�������Խ��ö�����뵽����CBackgroundLayer�����CFeatureSets�����У���ͨ���ö�������б�������������󼯺Ͻ��з��ʡ�
//	i. ��������ѡ�񼯣�һ��ͼ������л�����һ������Ϊ��ѡ�񼯡�(Selection)���������󼯺ϣ�����ά�����б�ѡ�е��������󡣱�ѡ�е���������������û�ͨ����������ֱ��ѡ�У�Ҳ�����Ǹ��ֲ�ѯ����֮��Ľ����ͨ��ReplaceSet()���������Խ�����ĳ��CFeatureSet�����еĲ�ѯ�������������Selection�����С��ڽ��е�ͼ��ʾʱ�����Զ�Selection�е�����������м�����ʾ��
//	j. ������������ı༭��ͨ��NewFeature(),DeleteFeature(),UpdateFeature()��������ɾ�����޸�һ���������󡣶���������ı༭���������������������󼯺������ɼ�����Ϊ���Ч�ʣ����������µ����ݿ��С������һ�α༭�����󣬵���UpdateFeaturesToFile()����������д�뵽���ݿ��У�
//	k. ������⣺�ڽ����������ݵ����ʱ��Ϊ������Ч�ʣ�����BatchInsertToFile()������������������⡣�����Ѹ�ͼ�����ڴ��е������������������һ���Բ��뵽���ݿ��У�
//	m. ʹ��ComputeBound()��ComputeFeatureCount()�������㲢����ͼ��߽��ͼ����������������Ŀ��
//## Category: GIAE%367FD730015F
//## Subsystem: GIAE Components%372FC3E50277
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B84002CE
class  __declspec(dllexport) CBackgroundLayer: public CLayer  //## Inherits: <unnamed>%37AA4F38006F
{
  public:
    //## Constructors (specified)
      //## Operation: CBackgroundLayer%925876938
	//##ModelId=46B7B84002D0
      CBackgroundLayer (CNaviMap* ownerNaviMap, LAYER layerID, jmeta * pFieldsInfo);

    //## Destructor (specified)
      //## Operation: ~CBackgroundLayer%928790182
	//##ModelId=46B7B84002DE
      ~CBackgroundLayer ();


 
    //## Other Operations (specified)
      //## Operation: SetPOILayerType%933908409
	//##ModelId=455025290098
      //void SetPOILayerType (EPOILayerType POILayerType);

      //## Operation: GetPOILayerType%933908408
	//##ModelId=46B7B84002DF
      virtual ELayerType GetLayerType () ;

      //## Operation: NewFeature%925876952
	//##ModelId=46B7B84002E1
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

	  // �����ύ
	  virtual bool Commit(CommitParams params);
	  
	  // ������¼�ύ
	  virtual bool CommitFeature(OID oid);

	  unsigned CommitByEditor(ISQLConnector * pConn, CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);
	  
	  unsigned CommitByVerifier(ISQLConnector * pConn, CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);
	  
      unsigned CommitByToolkit(ISQLConnector * pConn, CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);

  protected:

	  bool CreateDataView(ISQLConnector * pConn);

	  virtual CFeature * CatchFromReferSource(OID oid);

};

// Class CBackgroundLayer 

//## begin module%375BECF903A3.epilog preserve=yes
//## end module%375BECF903A3.epilog


#endif
