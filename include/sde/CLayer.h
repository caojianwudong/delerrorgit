//## begin module%375BECF903A3.cp preserve=no
//	//////////////////////////////////////////////////////////////////////
//	//
//	//  作者：
//	//  创建日期：
//	//  最后修改日期：
//	//
//	//////////////////////////////////////////////////////////////////////
//## end module%375BECF903A3.cp

//## Module: CLayer%375BECF903A3; Package specification
//## Subsystem: GIAE Components%372FC3E50277

#ifndef CLayer_h
#define CLayer_h 1

//## begin module%375BECF903A3.includes preserve=yes
#include "commondef.h"	// Added by ClassView
//## end module%375BECF903A3.includes
#define		READ_MEMORY_SIZE  524288 

// CLayerInfo
// CFieldsInfo
// CFeatureSet
//#include "CFeatureSet.h"
//#include "..\\attribute\\CFieldsInfo.h"
//#include "CMetaData.h"
//## begin module%375BECF903A3.additionalDeclarations preserve=yes

class CNaviMap ;
class CFeatureSet ;
class CFeature ;
class CFieldsInfo ;
class CFields ;
class CMetaData ;

typedef std::map<std::string, CFeatureSet*>		CFeatureSetMap ;

typedef CFeatureSetMap::iterator	CFeatureSetMapIterator ;

typedef CFeatureSetMap::value_type	CFeatureSetMapValueType ;

//## end module%375BECF903A3.additionalDeclarations


//## Class: CLayer%367FD86F00C8
//	CLayer:代表一个矢量图层。
//
//	<<说明>>
//	该类表示隶属于某个工作区的一个矢量图层，其中包含该图层的描述信息、图层属性数据的字段结构信息、和该图层所包含的地理特征对象。同时提供访问这些数据的方法。
//	其中：
//	a. 通过GetOwnerWorkAreaPtr()获得该图层所属工作区对象的指针；
//	b. 图层描述信息存放在CLayerInfo类中，通过GetLayerInfoPtr()获取CLayerInfo类的指针；
//	c. 图层属性数据的字段结构信息存放在CFieldsInfo类中，通过GetFieldsInfoPtr()获取CFieldsInfo类的指针；
//	d. 图层建立与删除：使用CreateLayerInFile()在数据库中建立该图层对象，通过DeleteLayerInFile()在数据库中删除该图层对象；
//	e. 属性信息处理：使用LoadLayerInfo()从数据库中装载该图层的描述信息和属性数据的字段结构信息；如果对图层的部分描述信息进行了修改（图层名称不能修改），则使用UpdateLayerInfoToFile()将修改后的内容保存到数据库中；
//	f. 地理特征数据的装载：使用Open()打开图层,从数据库中装载特征对象；可以使用SetLoadFilter()设置装载条件，从而可以只装载部分数据；使用LoadFeaturesAppendant()从数据库中补充装载数据；
//	g. 地理特征对象的访问：当特征数据被装载到内存后，对每一个地理特征都在内存中生成相应的特征对象(Feature Object)，并通过CFeatureSet对象组织起来，从而可以根据需要使用不同的方法访问某一个特征对象。其中：通过GetAllFeaturesPtr()获取管理所有特征对象的特征对象集合的指针。通过它可以访问该图层所包含的所有特征对象；注意：特征对象集合中只存储指向实际特征对象的指针，提供对各类特征对象的便利的访问方式。而每个特征对象在内存中只存储一次，不会造成冗余。
//	h. 特征对象集合：对于各种查询分析结果的管理，使用NewFeatureSet()可以另外创建一个特征对象集合(CFeatureSet类型），用以保存各种查询和分析的结果。可以在各集合之间进行各种集合运算操作，从而可以实现各种嵌套和迭代的复杂的查询与分析。
//	   该对象集合被创建后，如果是临时使用的集合对象，则可以由创建它的对象进行管理和删除。但如果该集合在创建后需要进行统一的管理，以便于进行后继的操作（如显示、查询/分析结果的联合等），则可以将该对象加入到属于CLayer对象的CFeatureSets对象中，并通过该对象对所有被管理的特征对象集合进行访问。
//	i. 特征对象选择集：一个图层对象中还包含一个被称为“选择集”(Selection)的特征对象集合，其中维护所有被选中的特征对象。被选中的特征对象可以是用户通过交互操作直接选中，也可以是各种查询分析之后的结果。通过ReplaceSet()方法，可以将放在某个CFeatureSet对象中的查询分析结果拷贝到Selection对象中。在进行地图显示时，可以对Selection中的特征对象进行加亮显示；
//	j. 地理特征对象的编辑：通过NewFeature(),DeleteFeature(),UpdateFeature()来创建、删除和修改一个特征对象。对特征对象的编辑操作对上述各种特征对象集合立即可见，但为提高效率，不立即更新到数据库中。当完成一段编辑操作后，调用UpdateFeaturesToFile()方法将更新写入到数据库中；
//	k. 数据入库：在进行批量数据的入库时，为提高入库效率，调用BatchInsertToFile()方法进行批量数据入库。它将把该图层在内存中的所有特征对象的数据一次性插入到数据库中；
//	m. 使用ComputeBound()和ComputeFeatureCount()方法计算并更新图层边界和图层包含特征对象的数目。
//## Category: GIAE%367FD730015F
//## Subsystem: GIAE Components%372FC3E50277
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83B0157
class __declspec(dllexport) CLayer  //## Inherits: <unnamed>%37AA4F38006F
{
  public:
	  time_t GetModifiedTime();
	  bool ReadFile();
	  char * ForwordFilePtr( int length, bool is_string );
	  void BackupModifiedFeature( CFeature * pFeature );

	  virtual void ClearUndoFeatureSet();

	  virtual void ResetUndoFeatureSet() ;

	  //##ModelId=46B7B83B0158
	  bool CloneFields( CFields *source, CFields *taget );
	//##ModelId=46B7B83B0167
	  void CloneFeature( CFeature * pFeature, CFeature * pNewFeature );
	//##ModelId=46B7B83B016A
	  bool DeleteFeatures( CFeatureSet * p_featureset );
	//##ModelId=46B7B83B016C
	  void SetLayerBound( SGeoRect bound );
	//##ModelId=46B7B83B0178
	  SGeoRect GetLayerBound();
    //## Constructors (specified)
      //## Operation: CLayer%925876938
	//##ModelId=46B7B83B0179
      CLayer (CNaviMap* ownerNaviMap, LAYER layerID, jmeta * pFieldsInfo);

    //## Destructor (specified)
      //## Operation: ~CLayer%928790182
	//##ModelId=46B7B83B01F4
      ~CLayer ();


 
    //## Other Operations (specified)
      //## Operation: SetLayerType%933908409
	//##ModelId=455025290098
      //void SetLayerType (ELayerType layerType);

      //## Operation: GetLayerType%933908408
	//##ModelId=46B7B83B0271
      virtual ELayerType GetLayerType ()=0 ;

   //## Other Operations (specified)
      //## Operation: GetLayerID%936208090
	//##ModelId=46B7B83B0273
      LAYER GetLayerID ();

      //## Operation: GetLayerName%928790183
	//##ModelId=46B7B83B02EE
      const char* GetLayerName ();

      //## Operation: SetLayerName%936208091
	//##ModelId=46B7B83B035B
      bool SetLayerName (const char* name);

     //## Operation: GetOwnerWorkAreaPtr%921180755
	//##ModelId=46B7B83B03D8
      CNaviMap* GetOwnerNaviMapPtr ();

      //## Operation: GetFieldsInfoPtr%921180768
	//##ModelId=46B7B83C005D
      CFieldsInfo* GetFieldsInfoPtr ();

      //## Operation: GetLayerInfoPtr%925876939
	//##ModelId=46B7B83C00CB
      CMetaData* GetLayerInfoPtr ();

      //## Operation: GetStatus%925876940
	//##ModelId=46B7B83C0148
      ELayerStatusType GetStatus ();

      //## Operation: IsDataLoaded%933695661
	//##ModelId=46B7B83C01B5
      bool IsDataLoaded ();

      //## Operation: IsModified%939396473
	//##ModelId=46B7B83C0222
      bool IsModified ();

      //## Operation: SetModified%939915314
	//##ModelId=46B7B83C0280
      void SetModified (bool modified);

      //## Operation: GetInsertFeatureSetPtr%939396474
	//##ModelId=46B7B83C02EE
      CFeatureSet* GetInsertFeatureSetPtr ();

      //## Operation: UpdateLayerInfoToFile%925876942
	//##ModelId=46B7B83C02FD
      bool UpdateLayerInfoToFile ();

      //## Operation: ComputeBound%921180763
	//##ModelId=46B7B83C035B
      void ComputeBound ();

      //## Operation: AddColumn%928878564
	//##ModelId=46B7B83C03B9
      virtual bool AddColumn (char* name, char* caption, FIELDTYPE type, int length = 0);

      //## Operation: LoadDataFromFile%925876947
	//##ModelId=46B7B83D002E
      virtual bool LoadDataFromFile (const char * szFullPath);

      //## Operation: SaveDataToFile%925876955
	//##ModelId=46B7B83D006D
      virtual bool SaveDataToFile (const char * szFullPath);

      //## Operation: Clear%928790184
	//##ModelId=46B7B83D009C
      virtual void Clear ();

      //## Operation: NewFeature%925876952
	//##ModelId=46B7B83D00FA
      virtual CFeature* NewFeature (GEOTYPE type, OID featureID = -1);

      //## Operation: UpdateFeature%925876954
	//##ModelId=46B7B83D0148
      bool UpdateFeature (OID featureID	// 要修改对象的FID。
      );

      //## Operation: DeleteFeature%925876953
	//##ModelId=46B7B83D0196
      virtual bool DeleteFeature (OID featureID	// 要删除对象的FID。
      );

	  virtual bool ResumeFeature (OID featureID // 要恢复对象的FID。
	  );

      //## Operation: GetAllFeaturesPtr%925876949
	//##ModelId=46B7B83D0222
      CFeatureSet* GetAllFeaturesPtr ();

      //## Operation: GetSelectionPtr%925876950
	//##ModelId=46B7B83D0271
      CFeatureSet* GetSelectionPtr ();

      //## Operation: IsCacheFileSynchronizWithFile%955402614
	//##ModelId=46B7B83D02BF
      bool IsCacheFileSynchronizWithFile ();

      //## Operation: LockTable%962899124
	//##ModelId=46B7B83D030D
      bool LockTable (const char* tableName);

      //## Operation: IsTableLocked%962899125
	//##ModelId=46B7B83D030F
      bool IsTableLocked (const char* tableName);

      //## Operation: UnLockTables%962899128
	//##ModelId=46B7B83D031C
      bool UnLockTables ();

      //## Operation: LockLayerForUpdate%962899126
	//##ModelId=46B7B83D031D
      bool LockLayerForUpdate ();

      //## Operation: IsLayerLockedByOthers%962899127
	//##ModelId=46B7B83D034B
      bool IsLayerLockedByOthers ();

      //## Operation: IsLayerLockedByMe%962899132
	//##ModelId=46B7B83D036B
      bool IsLayerLockedByMe ();

      //## Operation: ReportLockWarningMsg%962899133
	//##ModelId=46B7B83D0399
      bool ReportLockWarningMsg ();
 
	//##ModelId=46B7B83D03B9
	  virtual bool LoadLayerInfoFromFile ( char *&p_buffer, char *file_buffer, int file_length );

	//##ModelId=46B7B83D03CA
	  virtual bool SaveLayerInfoToFile ( FILE *fp );

	//##ModelId=46B7B83E000F
	  virtual bool CloneLayer ( CLayer *pLayer );

	//##ModelId=46B7B83E0012
	  virtual void Release();

	  CFeatureSet* CreateQuerySet(const char* setname);

	  bool DeleteFeatureInQuerySet(CFeature *pFeature);
  protected:

      //## Operation: LoadFieldCaption%936982462
	//##ModelId=46B7B83E0020
      bool LoadFieldsInfoFormFile ( CFieldsInfo *pInfo, char *&p_buffer, char *file_buffer, int file_length );
  
      //## Operation: LoadFieldCaption%936982462
	//##ModelId=46B7B83E002E
      bool SaveFieldsInfoToFile ( CFieldsInfo *pInfo, FILE *fp );

private:


    //## Other Operations (specified)
      //## Operation: Open%925876941
	//##ModelId=46B7B83E0031
	bool LoadStringFromFile1(char *taget);
	bool LoadStringFromFile11(char *&p_buffer, char *file_buffer, int file_length, char *taget);

	//##ModelId=46B7B83E004E
 	  void WriteStringToFile1( const char * str , FILE *fp);

	  //## Other Operations (specified)
      //## Operation: Open%925876941
	//##ModelId=46B7B83E0031
	bool LoadStringFromFile( char *taget);
	bool LoadStringFromFile10(char *&p_buffer, char *file_buffer, int file_length, char *taget);

      //## Operation: LoadMetaDataFromFile%939396472
	//##ModelId=46B7B83E0042
      bool LoadMetaDataFromFile (char *&p_buffer, char *file_buffer, int file_length );

	//##ModelId=46B7B83E004E
 	  void WriteStringToFile( const char * str , FILE *fp);
     //## Operation: LoadMetaDataFromFile%939396472
	//##ModelId=46B7B83E0051
      bool SaveMetaDataToFile ( FILE *fp );

	//##ModelId=46B7B83E005E
	  bool HasCacheFile () ;

      //## Operation: GetUniqueFID%928790186
	//##ModelId=46B7B83E009C
      OID GetUniqueFID ();

	  void LoadAttachLayer(CLayer *pLayer, bool isRefer);

	  SGeoRect LoadAttachLayer(SGeoRect rect, bool isRefer);

protected:

	  bool IsFeatureModified(CFeature *pFeature);

// 集合及ID分配
public:
    
    // 处理ID分配  
    OID GetMaxFeatureID ();
    
    // 获取编辑库的数据集合
    CFeatureSet* GetDataSourcePtr();
    
    // 获取成果库的数据集合
    CFeatureSet* GetReferSourcePtr();
    
    // 获取删除集的数据集合(删除的Feature可能为编辑库的一部分)
    CFeatureSet* GetObsoletedPtr();

// 标准ID查询
public:
    // 根据OID获取EMPID
    bool GetEMPIDByOID(OID * pOIDS, unsigned nOIDS, int * empid, int * meshid);
    
    // 根据EMPID获取OID
    bool GetOIDByEMPID(int * empid, int * meshid, unsigned nOIDS, OID * pOIDS);

	// 同步EMPID和OID
	bool SyncEMPIDAndOID(int * empid, int * meshid, unsigned nOIDS, OID * pOIDS);

    // 判定ID在成果库中是否存在
    bool QueryOIDFromReferSource(OID * pOIDs, bool * pExists, unsigned nOIDS);

// 游标支持
public:    

    // 打开编辑库游标(项目编号)
    virtual ISQLTransact * OpenCursorForDataSource(unsigned projID);
    
    // 打开编辑库游标(JSON参数)
    virtual ISQLTransact * OpenCursorForDataSource(LPCSTR cjson);

    // 打开编辑库游标(区域参数)
    virtual ISQLTransact * OpenCursorForDataSource(SGeoRect * pRects, unsigned nRects);

	// 打开编辑库游标(时间段)
	virtual ISQLTransact * OpenCursorForDataSource(time_t tBegin, time_t tEnd);

    // 打开成果库游标(JSON参数)
    virtual ISQLTransact * OpenCursorForReferSource(LPCSTR cjson);

    // 打开成果库游标(区域参数)
    virtual ISQLTransact * OpenCursorForReferSource(SGeoRect * pRects, unsigned nRects);

	// 打开成果库游标(其它图层)
	virtual ISQLTransact * OpenCursorForReferSource(CLayer * pOtherLayer, bool isrefer);

	// 打开成果库游标(时间段)
	virtual ISQLTransact * OpenCursorForReferSource(time_t tBegin, time_t tEnd);

    // 载入游标数据(成果库/编辑库均使用该函数载入数据), 返回下一游标位置
    ISQLTransact * LoadFromCursor(unsigned nRecord, ISQLTransact * pCursor, bool isrefer);

    // 从游标中加载OID数据
    unsigned QueryOIDFromCursor(OID * pOIDs, unsigned maxsize, ISQLTransact * pCursor);

    // 关闭游标数据(成果库/编辑库均使用该函数关闭游标)
    void       DestoryCursor(ISQLTransact * & pCursor);

    // 从编辑库加载数据, 返回加载状态
    virtual unsigned LoadFromDataSource(OID * pOIDs, unsigned nOIDS, bool isrefer);

    // 从成果库加载数据，返回加载状态 
    virtual unsigned LoadFromReferSource(OID * pOIDs, unsigned nOIDS, bool isrefer);

public:

    // 加载格网(NOTIMPL)
    bool Load(MESH * mapID, unsigned nMap, unsigned nScale);
    
    // 加载区域(NOTIMPL)
    bool Load(SGeoRect * pRects, unsigned nRects);
    
    // 加载OID列表(NOTIMPL)
    bool Load(OID * pOIDs, unsigned nOID);
    
    // 区
    bool Load(LPCSTR cjson);

    // 
    bool Load(unsigned projID);

	//根据起始和终止时间加载时间段内已提交的数据
	bool Load(time_t tBegin, time_t tEnd);

	//根据其它图层加载数据
	bool Load(CLayer * pOtherLayer);

    // 
    /*bool Location(SGeoRect & rect);*/

	bool LocationData(SGeoRect * pRects, unsigned nRects);

	bool LocationRefer(SGeoRect * pRects, unsigned nRects);

	bool LocationData(SGeoRect & rect);
	
	bool LocationRefer(SGeoRect & rect);

    // 
    /*bool Location(OID * pOIDs, unsigned nOID);*/

	bool LocationData(OID * pOIDs, unsigned nOID);

	bool LocationRefer(OID *pOIDs, unsigned nOID);

	//根据其它图层加载数据
	bool LocationRefer(CLayer * pOtherLayer);
    
    // 数据提交
    virtual bool Commit(CommitParams params);

	// 单条记录提交
	virtual bool CommitFeature(OID oid);

	// 附属表修改提交
	virtual unsigned CommitAttach(CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);

	//加载关联图层数据
	bool LoadByLinkField(LPCSTR desLyname, LPCSTR linkFieldName);

	//删除区域外的数据(区域边界上的不删除)
	bool DropOutOfRegion(SGeoRect *rect);

	// 获取编辑库连接式(ISQLConnector)
//	IUnknown * GetDataSource();

	// 设置编辑库连接参数
//	bool SetDataSource(IUnknown *pConn);
	
    // 获取成果库连接式(ISQLConnector)
   // IUnknown * GetReferSource();

	// 设置成果库连接参数
//	bool SetReferSource(IUnknown *pConn);
	
    // 获取ID关系连接式(ISQLConnector)
  //  IUnknown * GetIDSource();

	// 设置ID关系数据库连接参数
//	bool SetIDSource(IUnknown *pConn);
    
protected:
    
    // 创建Feature实例
    CFeature * CreateFeature(OID fid, GEOTYPE gType);
    
	virtual CFeature * CatchFromReferSource(OID oid);

	void ReOpenConn();
protected:

    // Data Members for Class Attributes

      //## Attribute: m_LayerID%37CD96DF030F
      //	图层的标识码。改成员变量由构造函数传入。
      //## begin CLayer::m_LayerID%37CD96DF030F.attr preserve=no  private: int {UA} 
	//##ModelId=46B7B83E00DA
      LAYER m_LayerID;
      //## end CLayer::m_LayerID%37CD96DF030F.attr


      //## Attribute: m_pFieldsInfo%36E816D601B4
      //	指向包含该图层属性字段结构信息的CFieldsInfo对象的指针。
      //	该指针由GetFieldsInfoPtr()获取；
      //	该指针指向的CFieldsInfo对象在CLayer的构造函数中创建，在析构函数中删除。
      //## begin CLayer::m_pFieldsInfo%36E816D601B4.attr preserve=no  private: CFieldsInfo* {UA} 
	//##ModelId=46B7B83E00EB
      CFieldsInfo* m_pFieldsInfo;
      //## end CLayer::m_pFieldsInfo%36E816D601B4.attr
protected:
      //## Attribute: m_pLayerInfo%36E86B0A0337
      //	指向包含该图层描述信息的CLayerInfo对象的指针。
      //	该指针由GetLayerInfoPtr()获取；
      //	该指针指向的CLayerInfo对象在CLayer的构造函数中创建，在析构函数中删除。
      //## begin CLayer::m_pLayerInfo%36E86B0A0337.attr preserve=no  private: CLayerInfo* {UA} 
	//##ModelId=46B7B83E00F0
      CMetaData* m_pLayerInfo;
      //## end CLayer::m_pLayerInfo%36E86B0A0337.attr

      //## Attribute: m_pAllFeatures%36EE9E8902EA
      //	该指针指向AllFeatures特征对象集合。该集合中包含有该图层在内存中的所有特征对象的指针。
      //	该指针由GetAllFeaturesPtr()获取；
      //	AllFeatures特征对象集合在CLayer的构造函数中创建，在析构函数中删除；
      //## begin CLayer::m_pAllFeatures%36EE9E8902EA.attr preserve=no  private: CFeatureSet* {UA} 
	//##ModelId=46B7B83E00FB
      CFeatureSet* m_pAllFeatures;
      //## end CLayer::m_pAllFeatures%36EE9E8902EA.attr

      //## Attribute: m_pSelection%36EEA75F00F8
      //	该指针指向“选择集”（Selection)特征对象集合。该集合中包含有该图层中当前被选中的所有特征对象的指针。
      //	该指针由GetSelectionPtr()获取；
      //	Selection特征对象集合在CLayer的构造函数中创建，在析构函数中删除；
      //## begin CLayer::m_pSelection%36EEA75F00F8.attr preserve=no  private: CFeatureSet* {UA} 
	//##ModelId=46B7B83E0100
      CFeatureSet* m_pSelection;

	  CFeatureSet* m_pDeletedFeatureSet ;
	  CFeatureSet* m_pAddedFeatureSet ;
	  CFeatureSet* m_pModifiedFeatureSet ;
      CFeatureSet* m_pDataSourceFeatureSet; // 编辑库数据源
      CFeatureSet* m_pReferSourceFeatureSet;// 成果库数据源
      CFeatureSet* m_pObsoleteFeatureSet;   // 删除的数据源(删除的不会在所有数据源中)
	  CFeatureSet* m_pTemporaryFeatureSet; // 临时数据集

	  // ISQLConnector * : 编辑库连接式
	  ISQLConnector * m_pDataSource;

      IEMPLayer * m_pEmpLayer;

      IUIDLayer * m_pUIDLayer;
	  
	  // ISQLConnector * : 成果库连接式
	  //IUnknown * m_pReferSource;
	  
	  // ISQLConnector * : ID关系库连接式	
	  //IUnknown * m_pIDSource;

	  CFeatureSetMap m_AllFeatureSets;

      //## end CLayer::m_pSelection%36EEA75F00F8.attr
  protected:
	//##ModelId=46B7B83E0109

	  time_t	m_iModifiedTime ;

	  OID			m_iMaxID ;
      //## Attribute: m_status%3713DE6C03A1
      //	标识图层的当前状态。该成员变量的类型为LayerStatusType。
      //	其工作状态有：
      //
      //	1. LAYER_INIT               —— 图层对象刚刚建立，还未组织好属性信息；
      //	2. LAYER_OPENED_WITHOUT_DATA—— 图层的属性信息已组织完毕，且内存中与数据库中的数据相同，但图层中的地理数据还未被调入内存；
      //	2. LAYER_LOADED_AND_SAVED   —— 图层已被打开，且内存中含有图层的特征数据,并且这些数据已被保存到数据库中；
      //	3. LAYER_LOADED_AND_EDITING —— 图层已被打开，且内存中含有图层的特征数据,这些数据已被编辑过,但编辑后的数据还未被保存到数据库中；
      //
      //	关于CLayer对象中状态转移的详细说明，参见CLayer的状态图。
      //## begin CLayer::m_status%3713DE6C03A1.attr preserve=no  private: ELayerStatusType {UA} 
	//##ModelId=46B7B83E010B
      ELayerStatusType m_status;
      //## end CLayer::m_status%3713DE6C03A1.attr
  private:
      //## Attribute: m_IsLayerLockedByMe%3964F47B01A5
      //## begin CLayer::m_IsLayerLockedByMe%3964F47B01A5.attr preserve=no  private: bool {UA} 
	//##ModelId=46B7B83E0119
      bool m_IsLayerLockedByMe;
      //## end CLayer::m_IsLayerLockedByMe%3964F47B01A5.attr

      //## Attribute: m_IsLayerLockedByOthers%3965F88F0194
      //## begin CLayer::m_IsLayerLockedByOthers%3965F88F0194.attr preserve=no  private: bool {UA} 
	//##ModelId=46B7B83E011A
      bool m_IsLayerLockedByOthers;
      //## end CLayer::m_IsLayerLockedByOthers%3965F88F0194.attr

	//##ModelId=46B7B83E011C
	  ELayerType m_LayerType;

	//##ModelId=46B7B83E0129
	  CNaviMap	* m_pOwnerMap ;

	//##ModelId=46B7B83E012D
	  char		m_strLayerName[MAX_FEATURESET_NAME_LEN] ;

	//##ModelId=46B7B83E0139
	  SGeoRect	m_Bound ;

	  bool m_bIsLoadCompound;

  protected:
	//##ModelId=46B7B83E013D
	  void CloneFiledsInfo( CFieldsInfo * taget, CFieldsInfo * source );
	//##ModelId=46B7B83E0149
	  bool LoadFeatureFieldsFromFile(CFields *p_feature_fields , CFieldsInfo *pInfo );
	
	  bool LoadFeatureFieldsFromFile1(CFields *p_feature_fields , CFieldsInfo *pInfo );
	//##ModelId=46B7B83E0167
	  bool LoadFeatureGeometryFromFile(CFeature *p_feature );

	//##ModelId=46B7B83E0186
	  bool SaveFeatureFieldsToFile(CFields *p_feature_fields , CFieldsInfo *pInfo, FILE * fp );

	  bool SaveFeatureFieldsToFile1(CFields *p_feature_fields , CFieldsInfo *pInfo, FILE * fp );
	
	//##ModelId=46B7B83E0197
	  bool SaveFeatureGeometryToFile(CFeature *p_feature, FILE * fp );
    // Data Members for Associations

   private: //## implementation
     //## Association: GIAE::<unnamed>%36E71ACE027D
      //## Role: CLayer::<the_CFieldsInfo>%36E71ACF01FC
      //## begin CLayer::<the_CFieldsInfo>%36E71ACF01FC.role preserve=no  public: CFieldsInfo {1 -> 1UHN}
      //## end CLayer::<the_CFieldsInfo>%36E71ACF01FC.role

      //## Association: GIAE::<unnamed>%36F95B800135
      //## Role: CLayer::<the_CFeatureSet>%36F95B80021B
      //## begin CLayer::<the_CFeatureSet>%36F95B80021B.role preserve=no  public: CFeatureSet {1 -> nUHN}
      //## end CLayer::<the_CFeatureSet>%36F95B80021B.role

      //## Association: GIAE::<unnamed>%375DB1BC008D
      //## Role: CLayer::<the_CLayerInfo>%375DB1BC023C
      //## begin CLayer::<the_CLayerInfo>%375DB1BC023C.role preserve=no  public: CLayerInfo {1 -> 1UHN}
      //## end CLayer::<the_CLayerInfo>%375DB1BC023C.role


      //## Association: GIAE::<unnamed>%384846AA012E
      //## Role: CLayer::<the_CEditProcessor>%384846AA0130
      //## begin CLayer::<the_CEditProcessor>%384846AA0130.role preserve=no  public: CEditProcessor {1 -> 1UHN}
      //## end CLayer::<the_CEditProcessor>%384846AA0130.role     

   protected:
		FILE	* m_fp ;
		int		m_file_length  ;
		char*	m_file_buffer ;
		int		m_read_size ;
		int		m_memory_cursor ;
		char*	m_p_buffer ;

};

// Class CLayer 

//## begin module%375BECF903A3.epilog preserve=yes
//## end module%375BECF903A3.epilog


#endif
