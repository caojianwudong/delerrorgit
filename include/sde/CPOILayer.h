//## begin module%375BECF903A3.cp preserve=no
//	//////////////////////////////////////////////////////////////////////
//	//
//	//  作者：
//	//  创建日期：
//	//  最后修改日期：
//	//
//	//////////////////////////////////////////////////////////////////////
//## end module%375BECF903A3.cp

//## Module: CPOILayer%375BECF903A3; Package specification
//## Subsystem: GIAE Components%372FC3E50277

#ifndef CPOILayer_h
#define CPOILayer_h 1

//## begin module%375BECF903A3.includes preserve=yes
#include "commondef.h"	// Added by ClassView
#include "CLayer.h"
//## end module%375BECF903A3.includes

// CPOILayerInfo
// CFieldsInfo
// CFeatureSet
//#include "CFeatureSet.h"
//#include "..\\attribute\\CFieldsInfo.h"
//#include "CMetaData.h"
//## begin module%375BECF903A3.additionalDeclarations preserve=yes

class CNaviMap ;

//## end module%375BECF903A3.additionalDeclarations


//## Class: CPOILayer%367FD86F00C8
//	CPOILayer:代表一个矢量图层。
//
//	<<说明>>
//	该类表示隶属于某个工作区的一个矢量图层，其中包含该图层的描述信息、图层属性数据的字段结构信息、和该图层所包含的地理特征对象。同时提供访问这些数据的方法。
//	其中：
//	a. 通过GetOwnerWorkAreaPtr()获得该图层所属工作区对象的指针；
//	b. 图层描述信息存放在CPOILayerInfo类中，通过GetPOILayerInfoPtr()获取CPOILayerInfo类的指针；
//	c. 图层属性数据的字段结构信息存放在CFieldsInfo类中，通过GetFieldsInfoPtr()获取CFieldsInfo类的指针；
//	d. 图层建立与删除：使用CreatePOILayerInFile()在数据库中建立该图层对象，通过DeletePOILayerInFile()在数据库中删除该图层对象；
//	e. 属性信息处理：使用LoadPOILayerInfo()从数据库中装载该图层的描述信息和属性数据的字段结构信息；如果对图层的部分描述信息进行了修改（图层名称不能修改），则使用UpdatePOILayerInfoToFile()将修改后的内容保存到数据库中；
//	f. 地理特征数据的装载：使用Open()打开图层,从数据库中装载特征对象；可以使用SetLoadFilter()设置装载条件，从而可以只装载部分数据；使用LoadFeaturesAppendant()从数据库中补充装载数据；
//	g. 地理特征对象的访问：当特征数据被装载到内存后，对每一个地理特征都在内存中生成相应的特征对象(Feature Object)，并通过CFeatureSet对象组织起来，从而可以根据需要使用不同的方法访问某一个特征对象。其中：通过GetAllFeaturesPtr()获取管理所有特征对象的特征对象集合的指针。通过它可以访问该图层所包含的所有特征对象；注意：特征对象集合中只存储指向实际特征对象的指针，提供对各类特征对象的便利的访问方式。而每个特征对象在内存中只存储一次，不会造成冗余。
//	h. 特征对象集合：对于各种查询分析结果的管理，使用NewFeatureSet()可以另外创建一个特征对象集合(CFeatureSet类型），用以保存各种查询和分析的结果。可以在各集合之间进行各种集合运算操作，从而可以实现各种嵌套和迭代的复杂的查询与分析。
//	   该对象集合被创建后，如果是临时使用的集合对象，则可以由创建它的对象进行管理和删除。但如果该集合在创建后需要进行统一的管理，以便于进行后继的操作（如显示、查询/分析结果的联合等），则可以将该对象加入到属于CPOILayer对象的CFeatureSets对象中，并通过该对象对所有被管理的特征对象集合进行访问。
//	i. 特征对象选择集：一个图层对象中还包含一个被称为“选择集”(Selection)的特征对象集合，其中维护所有被选中的特征对象。被选中的特征对象可以是用户通过交互操作直接选中，也可以是各种查询分析之后的结果。通过ReplaceSet()方法，可以将放在某个CFeatureSet对象中的查询分析结果拷贝到Selection对象中。在进行地图显示时，可以对Selection中的特征对象进行加亮显示；
//	j. 地理特征对象的编辑：通过NewFeature(),DeleteFeature(),UpdateFeature()来创建、删除和修改一个特征对象。对特征对象的编辑操作对上述各种特征对象集合立即可见，但为提高效率，不立即更新到数据库中。当完成一段编辑操作后，调用UpdateFeaturesToFile()方法将更新写入到数据库中；
//	k. 数据入库：在进行批量数据的入库时，为提高入库效率，调用BatchInsertToFile()方法进行批量数据入库。它将把该图层在内存中的所有特征对象的数据一次性插入到数据库中；
//	m. 使用ComputeBound()和ComputeFeatureCount()方法计算并更新图层边界和图层包含特征对象的数目。
//## Category: GIAE%367FD730015F
//## Subsystem: GIAE Components%372FC3E50277
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83A00DA
class __declspec(dllexport) CPOILayer: public CLayer  //## Inherits: <unnamed>%37AA4F38006F
{
  public:
    //## Constructors (specified)
      //## Operation: CPOILayer%925876938
	//##ModelId=46B7B83A00DC
      CPOILayer (CNaviMap* ownerNaviMap, LAYER LayerID, jmeta * pFieldsInfo);

    //## Destructor (specified)
      //## Operation: ~CPOILayer%928790182
	//##ModelId=46B7B83A00E0
      ~CPOILayer ();


 
    //## Other Operations (specified)
      //## Operation: SetPOILayerType%933908409
	//##ModelId=455025290098
      //void SetPOILayerType (EPOILayerType POILayerType);

      //## Operation: GetPOILayerType%933908408
	//##ModelId=46B7B83A00EA
      virtual ELayerType GetLayerType () ;

      //## Operation: NewFeature%925876952
	//##ModelId=46B7B83A00EC
      virtual CFeature* NewFeature (GEOTYPE type, OID featureID = -1);

	  virtual void ClearUndoFeatureSet();
	  
	  virtual void ResetUndoFeatureSet() ;
	  
	  virtual bool DeleteFeature (OID featureID);
	  
	  virtual bool ResumeFeature (OID featureID);
	  
	  virtual void Clear ();
	  
	  virtual bool CloneLayer ( CLayer *pLayer );
	  
	  virtual void Release();


  public:
      // 打开编辑库游标
      virtual ISQLTransact * OpenCursorForDataSource(unsigned projID);
      
      virtual ISQLTransact * OpenCursorForDataSource(LPCSTR cjson);
      
      virtual ISQLTransact * OpenCursorForDataSource(SGeoRect * pRects, unsigned nRects);

	  virtual ISQLTransact * OpenCursorForDataSource(time_t tBegin, time_t tEnd);

      virtual bool Commit(CommitParams params);

	  virtual bool CommitFeature(OID oid);

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

	  //根据projectid,计算真位置包围盒
	  virtual bool QueryTruePtBoundary(unsigned projectid, SGeoRect *rect);

	  virtual bool DropPointInBoundary(SGeoRect *rect);

	  //查看区域范围内是否有projectid的数据
	  virtual bool IsExistsData(unsigned projectid, SGeoRect *rect);
	  
	  unsigned CommitByEditor(ISQLConnector * pConn, CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);

      unsigned CommitByVerifier(ISQLConnector * pConn, CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);

      unsigned CommitByToolkit(ISQLConnector * pConn, CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);

  protected:

      unsigned CommitAsInitialize(ISQLConnector * pConn, CFeature ** pFeatures, unsigned nFeatures, _variant_t & ver);

      virtual CFeature * CatchFromReferSource(OID oid);

  protected:
	  
	  bool CreateDataView(ISQLConnector * pConn);

};

// Class CPOILayer 

//## begin module%375BECF903A3.epilog preserve=yes
//## end module%375BECF903A3.epilog


#endif
