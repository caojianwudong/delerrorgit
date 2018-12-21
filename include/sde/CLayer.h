//## begin module%375BECF903A3.cp preserve=no
//	//////////////////////////////////////////////////////////////////////
//	//
//	//  ���ߣ�
//	//  �������ڣ�
//	//  ����޸����ڣ�
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
//	CLayer:����һ��ʸ��ͼ�㡣
//
//	<<˵��>>
//	�����ʾ������ĳ����������һ��ʸ��ͼ�㣬���а�����ͼ���������Ϣ��ͼ���������ݵ��ֶνṹ��Ϣ���͸�ͼ���������ĵ�����������ͬʱ�ṩ������Щ���ݵķ�����
//	���У�
//	a. ͨ��GetOwnerWorkAreaPtr()��ø�ͼ�����������������ָ�룻
//	b. ͼ��������Ϣ�����CLayerInfo���У�ͨ��GetLayerInfoPtr()��ȡCLayerInfo���ָ�룻
//	c. ͼ���������ݵ��ֶνṹ��Ϣ�����CFieldsInfo���У�ͨ��GetFieldsInfoPtr()��ȡCFieldsInfo���ָ�룻
//	d. ͼ�㽨����ɾ����ʹ��CreateLayerInFile()�����ݿ��н�����ͼ�����ͨ��DeleteLayerInFile()�����ݿ���ɾ����ͼ�����
//	e. ������Ϣ����ʹ��LoadLayerInfo()�����ݿ���װ�ظ�ͼ���������Ϣ���������ݵ��ֶνṹ��Ϣ�������ͼ��Ĳ���������Ϣ�������޸ģ�ͼ�����Ʋ����޸ģ�����ʹ��UpdateLayerInfoToFile()���޸ĺ�����ݱ��浽���ݿ��У�
//	f. �����������ݵ�װ�أ�ʹ��Open()��ͼ��,�����ݿ���װ���������󣻿���ʹ��SetLoadFilter()����װ���������Ӷ�����ֻװ�ز������ݣ�ʹ��LoadFeaturesAppendant()�����ݿ��в���װ�����ݣ�
//	g. ������������ķ��ʣ����������ݱ�װ�ص��ڴ�󣬶�ÿһ���������������ڴ���������Ӧ����������(Feature Object)����ͨ��CFeatureSet������֯�������Ӷ����Ը�����Ҫʹ�ò�ͬ�ķ�������ĳһ�������������У�ͨ��GetAllFeaturesPtr()��ȡ������������������������󼯺ϵ�ָ�롣ͨ�������Է��ʸ�ͼ����������������������ע�⣺�������󼯺���ֻ�洢ָ��ʵ�����������ָ�룬�ṩ�Ը�����������ı����ķ��ʷ�ʽ����ÿ�������������ڴ���ֻ�洢һ�Σ�����������ࡣ
//	h. �������󼯺ϣ����ڸ��ֲ�ѯ��������Ĺ���ʹ��NewFeatureSet()�������ⴴ��һ���������󼯺�(CFeatureSet���ͣ������Ա�����ֲ�ѯ�ͷ����Ľ���������ڸ�����֮����и��ּ�������������Ӷ�����ʵ�ָ���Ƕ�׺͵����ĸ��ӵĲ�ѯ�������
//	   �ö��󼯺ϱ��������������ʱʹ�õļ��϶���������ɴ������Ķ�����й����ɾ����������ü����ڴ�������Ҫ����ͳһ�Ĺ����Ա��ڽ��к�̵Ĳ���������ʾ����ѯ/������������ϵȣ�������Խ��ö�����뵽����CLayer�����CFeatureSets�����У���ͨ���ö�������б�������������󼯺Ͻ��з��ʡ�
//	i. ��������ѡ�񼯣�һ��ͼ������л�����һ������Ϊ��ѡ�񼯡�(Selection)���������󼯺ϣ�����ά�����б�ѡ�е��������󡣱�ѡ�е���������������û�ͨ����������ֱ��ѡ�У�Ҳ�����Ǹ��ֲ�ѯ����֮��Ľ����ͨ��ReplaceSet()���������Խ�����ĳ��CFeatureSet�����еĲ�ѯ�������������Selection�����С��ڽ��е�ͼ��ʾʱ�����Զ�Selection�е�����������м�����ʾ��
//	j. ������������ı༭��ͨ��NewFeature(),DeleteFeature(),UpdateFeature()��������ɾ�����޸�һ���������󡣶���������ı༭���������������������󼯺������ɼ�����Ϊ���Ч�ʣ����������µ����ݿ��С������һ�α༭�����󣬵���UpdateFeaturesToFile()����������д�뵽���ݿ��У�
//	k. ������⣺�ڽ����������ݵ����ʱ��Ϊ������Ч�ʣ�����BatchInsertToFile()������������������⡣�����Ѹ�ͼ�����ڴ��е������������������һ���Բ��뵽���ݿ��У�
//	m. ʹ��ComputeBound()��ComputeFeatureCount()�������㲢����ͼ��߽��ͼ����������������Ŀ��
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
      bool UpdateFeature (OID featureID	// Ҫ�޸Ķ����FID��
      );

      //## Operation: DeleteFeature%925876953
	//##ModelId=46B7B83D0196
      virtual bool DeleteFeature (OID featureID	// Ҫɾ�������FID��
      );

	  virtual bool ResumeFeature (OID featureID // Ҫ�ָ������FID��
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

// ���ϼ�ID����
public:
    
    // ����ID����  
    OID GetMaxFeatureID ();
    
    // ��ȡ�༭������ݼ���
    CFeatureSet* GetDataSourcePtr();
    
    // ��ȡ�ɹ�������ݼ���
    CFeatureSet* GetReferSourcePtr();
    
    // ��ȡɾ���������ݼ���(ɾ����Feature����Ϊ�༭���һ����)
    CFeatureSet* GetObsoletedPtr();

// ��׼ID��ѯ
public:
    // ����OID��ȡEMPID
    bool GetEMPIDByOID(OID * pOIDS, unsigned nOIDS, int * empid, int * meshid);
    
    // ����EMPID��ȡOID
    bool GetOIDByEMPID(int * empid, int * meshid, unsigned nOIDS, OID * pOIDS);

	// ͬ��EMPID��OID
	bool SyncEMPIDAndOID(int * empid, int * meshid, unsigned nOIDS, OID * pOIDS);

    // �ж�ID�ڳɹ������Ƿ����
    bool QueryOIDFromReferSource(OID * pOIDs, bool * pExists, unsigned nOIDS);

// �α�֧��
public:    

    // �򿪱༭���α�(��Ŀ���)
    virtual ISQLTransact * OpenCursorForDataSource(unsigned projID);
    
    // �򿪱༭���α�(JSON����)
    virtual ISQLTransact * OpenCursorForDataSource(LPCSTR cjson);

    // �򿪱༭���α�(�������)
    virtual ISQLTransact * OpenCursorForDataSource(SGeoRect * pRects, unsigned nRects);

	// �򿪱༭���α�(ʱ���)
	virtual ISQLTransact * OpenCursorForDataSource(time_t tBegin, time_t tEnd);

    // �򿪳ɹ����α�(JSON����)
    virtual ISQLTransact * OpenCursorForReferSource(LPCSTR cjson);

    // �򿪳ɹ����α�(�������)
    virtual ISQLTransact * OpenCursorForReferSource(SGeoRect * pRects, unsigned nRects);

	// �򿪳ɹ����α�(����ͼ��)
	virtual ISQLTransact * OpenCursorForReferSource(CLayer * pOtherLayer, bool isrefer);

	// �򿪳ɹ����α�(ʱ���)
	virtual ISQLTransact * OpenCursorForReferSource(time_t tBegin, time_t tEnd);

    // �����α�����(�ɹ���/�༭���ʹ�øú�����������), ������һ�α�λ��
    ISQLTransact * LoadFromCursor(unsigned nRecord, ISQLTransact * pCursor, bool isrefer);

    // ���α��м���OID����
    unsigned QueryOIDFromCursor(OID * pOIDs, unsigned maxsize, ISQLTransact * pCursor);

    // �ر��α�����(�ɹ���/�༭���ʹ�øú����ر��α�)
    void       DestoryCursor(ISQLTransact * & pCursor);

    // �ӱ༭���������, ���ؼ���״̬
    virtual unsigned LoadFromDataSource(OID * pOIDs, unsigned nOIDS, bool isrefer);

    // �ӳɹ���������ݣ����ؼ���״̬ 
    virtual unsigned LoadFromReferSource(OID * pOIDs, unsigned nOIDS, bool isrefer);

public:

    // ���ظ���(NOTIMPL)
    bool Load(MESH * mapID, unsigned nMap, unsigned nScale);
    
    // ��������(NOTIMPL)
    bool Load(SGeoRect * pRects, unsigned nRects);
    
    // ����OID�б�(NOTIMPL)
    bool Load(OID * pOIDs, unsigned nOID);
    
    // ��
    bool Load(LPCSTR cjson);

    // 
    bool Load(unsigned projID);

	//������ʼ����ֹʱ�����ʱ��������ύ������
	bool Load(time_t tBegin, time_t tEnd);

	//��������ͼ���������
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

	//��������ͼ���������
	bool LocationRefer(CLayer * pOtherLayer);
    
    // �����ύ
    virtual bool Commit(CommitParams params);

	// ������¼�ύ
	virtual bool CommitFeature(OID oid);

	// �������޸��ύ
	virtual unsigned CommitAttach(CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);

	//���ع���ͼ������
	bool LoadByLinkField(LPCSTR desLyname, LPCSTR linkFieldName);

	//ɾ�������������(����߽��ϵĲ�ɾ��)
	bool DropOutOfRegion(SGeoRect *rect);

	// ��ȡ�༭������ʽ(ISQLConnector)
//	IUnknown * GetDataSource();

	// ���ñ༭�����Ӳ���
//	bool SetDataSource(IUnknown *pConn);
	
    // ��ȡ�ɹ�������ʽ(ISQLConnector)
   // IUnknown * GetReferSource();

	// ���óɹ������Ӳ���
//	bool SetReferSource(IUnknown *pConn);
	
    // ��ȡID��ϵ����ʽ(ISQLConnector)
  //  IUnknown * GetIDSource();

	// ����ID��ϵ���ݿ����Ӳ���
//	bool SetIDSource(IUnknown *pConn);
    
protected:
    
    // ����Featureʵ��
    CFeature * CreateFeature(OID fid, GEOTYPE gType);
    
	virtual CFeature * CatchFromReferSource(OID oid);

	void ReOpenConn();
protected:

    // Data Members for Class Attributes

      //## Attribute: m_LayerID%37CD96DF030F
      //	ͼ��ı�ʶ�롣�ĳ�Ա�����ɹ��캯�����롣
      //## begin CLayer::m_LayerID%37CD96DF030F.attr preserve=no  private: int {UA} 
	//##ModelId=46B7B83E00DA
      LAYER m_LayerID;
      //## end CLayer::m_LayerID%37CD96DF030F.attr


      //## Attribute: m_pFieldsInfo%36E816D601B4
      //	ָ�������ͼ�������ֶνṹ��Ϣ��CFieldsInfo�����ָ�롣
      //	��ָ����GetFieldsInfoPtr()��ȡ��
      //	��ָ��ָ���CFieldsInfo������CLayer�Ĺ��캯���д�����������������ɾ����
      //## begin CLayer::m_pFieldsInfo%36E816D601B4.attr preserve=no  private: CFieldsInfo* {UA} 
	//##ModelId=46B7B83E00EB
      CFieldsInfo* m_pFieldsInfo;
      //## end CLayer::m_pFieldsInfo%36E816D601B4.attr
protected:
      //## Attribute: m_pLayerInfo%36E86B0A0337
      //	ָ�������ͼ��������Ϣ��CLayerInfo�����ָ�롣
      //	��ָ����GetLayerInfoPtr()��ȡ��
      //	��ָ��ָ���CLayerInfo������CLayer�Ĺ��캯���д�����������������ɾ����
      //## begin CLayer::m_pLayerInfo%36E86B0A0337.attr preserve=no  private: CLayerInfo* {UA} 
	//##ModelId=46B7B83E00F0
      CMetaData* m_pLayerInfo;
      //## end CLayer::m_pLayerInfo%36E86B0A0337.attr

      //## Attribute: m_pAllFeatures%36EE9E8902EA
      //	��ָ��ָ��AllFeatures�������󼯺ϡ��ü����а����и�ͼ�����ڴ��е��������������ָ�롣
      //	��ָ����GetAllFeaturesPtr()��ȡ��
      //	AllFeatures�������󼯺���CLayer�Ĺ��캯���д�����������������ɾ����
      //## begin CLayer::m_pAllFeatures%36EE9E8902EA.attr preserve=no  private: CFeatureSet* {UA} 
	//##ModelId=46B7B83E00FB
      CFeatureSet* m_pAllFeatures;
      //## end CLayer::m_pAllFeatures%36EE9E8902EA.attr

      //## Attribute: m_pSelection%36EEA75F00F8
      //	��ָ��ָ��ѡ�񼯡���Selection)�������󼯺ϡ��ü����а����и�ͼ���е�ǰ��ѡ�е��������������ָ�롣
      //	��ָ����GetSelectionPtr()��ȡ��
      //	Selection�������󼯺���CLayer�Ĺ��캯���д�����������������ɾ����
      //## begin CLayer::m_pSelection%36EEA75F00F8.attr preserve=no  private: CFeatureSet* {UA} 
	//##ModelId=46B7B83E0100
      CFeatureSet* m_pSelection;

	  CFeatureSet* m_pDeletedFeatureSet ;
	  CFeatureSet* m_pAddedFeatureSet ;
	  CFeatureSet* m_pModifiedFeatureSet ;
      CFeatureSet* m_pDataSourceFeatureSet; // �༭������Դ
      CFeatureSet* m_pReferSourceFeatureSet;// �ɹ�������Դ
      CFeatureSet* m_pObsoleteFeatureSet;   // ɾ��������Դ(ɾ���Ĳ�������������Դ��)
	  CFeatureSet* m_pTemporaryFeatureSet; // ��ʱ���ݼ�

	  // ISQLConnector * : �༭������ʽ
	  ISQLConnector * m_pDataSource;

      IEMPLayer * m_pEmpLayer;

      IUIDLayer * m_pUIDLayer;
	  
	  // ISQLConnector * : �ɹ�������ʽ
	  //IUnknown * m_pReferSource;
	  
	  // ISQLConnector * : ID��ϵ������ʽ	
	  //IUnknown * m_pIDSource;

	  CFeatureSetMap m_AllFeatureSets;

      //## end CLayer::m_pSelection%36EEA75F00F8.attr
  protected:
	//##ModelId=46B7B83E0109

	  time_t	m_iModifiedTime ;

	  OID			m_iMaxID ;
      //## Attribute: m_status%3713DE6C03A1
      //	��ʶͼ��ĵ�ǰ״̬���ó�Ա����������ΪLayerStatusType��
      //	�乤��״̬�У�
      //
      //	1. LAYER_INIT               ���� ͼ�����ոս�������δ��֯��������Ϣ��
      //	2. LAYER_OPENED_WITHOUT_DATA���� ͼ���������Ϣ����֯��ϣ����ڴ��������ݿ��е�������ͬ����ͼ���еĵ������ݻ�δ�������ڴ棻
      //	2. LAYER_LOADED_AND_SAVED   ���� ͼ���ѱ��򿪣����ڴ��к���ͼ�����������,������Щ�����ѱ����浽���ݿ��У�
      //	3. LAYER_LOADED_AND_EDITING ���� ͼ���ѱ��򿪣����ڴ��к���ͼ�����������,��Щ�����ѱ��༭��,���༭������ݻ�δ�����浽���ݿ��У�
      //
      //	����CLayer������״̬ת�Ƶ���ϸ˵�����μ�CLayer��״̬ͼ��
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
