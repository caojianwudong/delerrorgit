//## begin module%375BECF903A3.cp preserve=no
//	//////////////////////////////////////////////////////////////////////
//	//
//	//  ���ߣ�
//	//  �������ڣ�
//	//  ����޸����ڣ�
//	//
//	//////////////////////////////////////////////////////////////////////
//## end module%375BECF903A3.cp

//## Module: CRoadLayer%375BECF903A3; Package specification
//## Subsystem: GIAE Components%372FC3E50277

#ifndef CRoadLayer_h
#define CRoadLayer_h 1

//## begin module%375BECF903A3.includes preserve=yes
#include "commondef.h"	// Added by ClassView
#include "CLayer.h"	// Added by ClassView
//## end module%375BECF903A3.includes

// CRoadLayerInfo
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
class CMetaData ;
class CTimeLimitFieldsInfo ;
class CVehicleLimitFieldsInfo ;
class CTurnFieldsInfo ;
class CDirectionFieldsInfo ;
class CLaneFieldsInfo ;
class CJunctionReferenceFieldsInfo ;
class CGuideFieldsInfo ;
class CJunctionViewFieldsInfo ;
class CJunctionSAFacilityFieldsInfo ;
class CExitInfoFieldsInfo ;
class CFields;

class CJunctionVideoFieldsInfo;
class CJunctionVRViewFieldsInfo;
class CNewTurnFieldsInfo;
class CNewLaneFieldsInfo;
class CNewDirectionFieldsInfo;

//## end module%375BECF903A3.additionalDeclarations
//##ModelId=46B7B83603D8
typedef std::map<OID, CFields*>		CFieldsMap ;

//##ModelId=46B7B8370000
typedef std::vector<CFields*>		CFieldsList ;

//##ModelId=46B7B8370002
typedef CFieldsMap::iterator		CFieldsMapIterator ;

typedef std::map<OID,OID>			MAPNODESEQ;

typedef std::map<OID,MAPNODESEQ>	MAPWAYNODE;


//## Class: CRoadLayer%367FD86F00C8
//	CRoadLayer:����һ��ʸ��ͼ�㡣
//
//## Category: GIAE%367FD730015F
//## Subsystem: GIAE Components%372FC3E50277
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B8370177
class __declspec(dllexport) CRoadLayer: public CLayer //## Inherits: <unnamed>%37AA4F38006F
{
public:


	//##ModelId=46B7B8370186
	CTimeLimitFieldsInfo * GetTimeLimitFieldsInfoPtr (  );
	//##ModelId=46B7B83701A5
	CFields* CloneFieldsInTimeTable( int ObjectType, OID ObjectID, CFields *pSourceFields );
	CFields* CloneFieldsInTimeTable( OID RecordID, CFields *pSourceFields );
	//##ModelId=46B7B83701C5
	CFeatureSet* GetFieldListFromTimeLimitTable ( int ObjectType, OID ObjectID, const char* setname );
	//##ModelId=46B7B83701E4
	CFields* GetFieldFromTimeLimitTable ( OID ID );
	CFields* GetFieldFromTimeLimitTableByIndex(int index);
	//##ModelId=46B7B8370213
	bool RemoveFieldListFromTimeLimitTable ( int ObjectType, OID ObjectID );
	//##ModelId=46B7B8370232
	bool RemoveFieldFromTimeLimitTable( OID ID );
	//##ModelId=46B7B83A000F
	//OID  GetUniqueFieldIDinTimeLimitTable ( );
	int  GetFieldCountInTimeLimitTable();
	//##ModelId=46B7B839037A
	bool AddFieldToTimeLimitTable ( OID ID, CFields * pFields );
	
	
	//////////////////////////////////////////////////////////////////////////
	//##ModelId=46B7B8370251
	CVehicleLimitFieldsInfo * GetVehicleLimitFieldsInfoPtr (  );
	//##ModelId=46B7B8370271
	CFields* CloneFieldsInVehicleTable( int ObjectType, OID ObjectID, CFields *pSourceFields );
	CFields* CloneFieldsInVehicleTable( OID RecordID, CFields *pSourceFields );
	//##ModelId=46B7B8370290
	CFeatureSet* GetFieldListFromVehicleLimitTable ( int ObjectType, OID ObjectID, const char* setname );
	//##ModelId=46B7B83702AF
	CFields * GetFieldFromVehicleLimitTable ( OID ID );
	CFields * GetFieldFromVehicleLimitTableByIndex(int index);
	//##ModelId=46B7B83702CE
	bool RemoveFieldListFromVehicleLimitTable ( int ObjectType, OID ObjectID );
	//##ModelId=46B7B83702EE
	bool RemoveFieldFromVehicleLimitTable( OID ID );
	//##ModelId=46B7B83A002E
	//OID  GetUniqueFieldIDinVehicleLimitTable ( );
	int  GetFieldCountInVehicleLimitTalbe();
	//##ModelId=46B7B83903B9
	bool AddFieldToVehicleLimitTable ( OID ID, CFields * pFields );
	
	
	//////////////////////////////////////////////////////////////////////////
	//##ModelId=46B7B837030D
	CTurnFieldsInfo * GetTurnFieldsInfoPtr(  );
	//##ModelId=46B7B837031C
	CFeatureSet* GetFieldListFromTurnTable( OID RoadID, OID JunctionID, const char* setname );
	//##ModelId=46B7B837031C
	CFeatureSet* GetFieldListFromTurnTableByInRoad( OID RoadID, OID JunctionID, const char* setname );
	//##ModelId=46B7B837033C
	CFeatureSet* GetFieldListFromTurnTable( OID JunctionID, const char* setname );
	//##ModelId=46B7B837034B
	CFields* GetFieldFromTurnTable( OID ID );
	CFields* GetFieldFromTurnTableByIndex(int index);
	//##ModelId=46B7B837036B
	CFields* CloneFieldsInTurnTable( OID JunctionID, OID StartRoadID, OID EndRoadID, CFields *pSourceFields );
	CFields* CloneFieldsInTurnTable( OID RecordID, CFields *pSourceFields );
	//##ModelId=46B7B837037A
	bool RemoveFieldListFromTurnTable ( OID RoadID );
	//##ModelId=46B7B8370399
	bool RemoveFieldListFromTurnTable ( OID RoadID, OID JunctionID );
	//##ModelId=46B7B83703A9
	bool RemoveFieldFromTurnTable( OID ID );
	//##ModelId=46B7B83703C8
	bool ModifyRoadIDInTurnTable ( OID RoadID, OID JunctionID, OID NewRoadID );
	bool ModifyJunctionIDFromTurnTable( OID new_id, OID old_id );
	//##ModelId=46B7B8380000
	//OID  GetUniqueFieldIDinTurnTable ( );
	int  GetFieldCountInTurnTable();
	//##ModelId=46B7B8390399
	bool AddFieldToTurnTable ( OID ID, CFields * pFields );


	/////////////////////////////////////////////////
	//##ModelId=46B7B838000F
	CDirectionFieldsInfo * GetDirectionFieldsInfoPtr (  );
	//##ModelId=46B7B838001F
	CFeatureSet* GetFieldListFromDirectionTable ( OID RoadID, OID JunctionID, const char* setname );
	//##ModelId=46B7B838002E
	CFeatureSet* GetFieldListFromDirectionTable ( OID JunctionID, const char* setname );
	//##ModelId=46B7B838003E
	CFields * GetFieldFromDirectionTable ( OID ID );
	CFields * GetFieldFromDirectionTableByIndex(int index);
	//##ModelId=46B7B838004E
	CFields * CloneFieldsInDirectionTable ( OID JunctionID, OID StartRoadID, CFields *pSourceFields );
	CFields * CloneFieldsInDirectionTable ( OID RecordID, CFields *pSourceFields );
	//##ModelId=46B7B838005E
	bool RemoveFieldListFromDirectionTable ( OID RoadID );
	//##ModelId=46B7B838007D
	bool RemoveFieldListFromDirectionTable ( OID RoadID, OID JunctionID );
	//##ModelId=46B7B838008C
	bool RemoveFieldFromDirectionTable( OID ID );
	//##ModelId=46B7B838009C
	bool RemoveEndRoadIDFromDirectionTable( OID RoadID );
	//##ModelId=46B7B83800AB
	bool ModifyRoadIDInDirectionTable ( OID RoadID, OID JunctionID, OID NewRoadID );
	//##ModelId=46B7B83800BB
	bool ModifyEndRoadIDFromDirectionTable( OID RoadID, OID JunctionID, OID EndRoadID ) ;
	bool ModifyJunctionIDFromDirectionTable( OID new_id, OID old_id );
	bool IsEndRoadIDInDirectionTable( OID RoadID, OID JunctionID ) ;
	//##ModelId=46B7B8390215
	//OID  GetUniqueFieldIDinDirectionTable ( );
	int  GetFieldCountInDirectionTalbe();
	//##ModelId=46B7B839034D
	bool AddFieldToDirectionTable ( OID ID, CFields * pFields );


	/////////////////////////////////////////////////
	//##ModelId=46B7B83800CB
	CLaneFieldsInfo * GetLaneFieldsInfoPtr (  );
	//##ModelId=46B7B83800DA
	CFeatureSet* GetFieldListFromLaneTable ( OID RoadID, OID JunctionID, const char* setname );
	//##ModelId=46B7B83800EA
	CFeatureSet* GetFieldListFromLaneTable ( OID JunctionID, const char* setname );
	//##ModelId=46B7B83800ED
	CFields * GetFieldFromLaneTable ( OID ID );
	CFields * GetFieldFromLaneTableByIndex(int index);
	//##ModelId=46B7B83800FA
	CFields * CloneFieldsInLaneTable ( OID JunctionID, OID StartRoadID, CFields *pSourceFields );
	CFields * CloneFieldsInLaneTable ( OID RecordID, CFields *pSourceFields ) ;
	//##ModelId=46B7B8380109
	bool RemoveFieldListFromLaneTable ( OID RoadID );
	//##ModelId=46B7B838010B
	bool RemoveFieldListFromLaneTable ( OID RoadID, OID JunctionID );
	//##ModelId=46B7B838011B
	bool RemoveFieldFromLaneTable( OID ID );
	//##ModelId=46B7B8380128
	bool RemoveEndRoadIDFromLaneTable( OID RoadID );
	//##ModelId=46B7B8380138
	bool ModifyRoadIDInLaneTable ( OID RoadID, OID JunctionID, OID NewRoadID );
	//##ModelId=46B7B838013C
	bool ModifyEndRoadIDInLaneTable( OID JunctionID, OID EndRoadID, OID NewEndRoadID ) ;
	bool IsEndRoadIDInLaneTable( OID JunctionID, OID EndRoadID ) ;
	bool ModifyJunctionIDFromLaneTable( OID new_id, OID old_id );
	//##ModelId=46B7B8390222
	//OID  GetUniqueFieldIDinLaneTable ( );
	int  GetFieldCountInLaneTable();
	//##ModelId=46B7B839036B
	bool AddFieldToLaneTable ( OID ID, CFields * pFields );


	////////////////////////////////////////
	//##ModelId=46B7B8380148
	CJunctionReferenceFieldsInfo * GetJunctionReferenceFieldsInfoPtr (  );
	//##ModelId=46B7B8380149
	CFields * CloneFieldsInJunctionReferenceTable ( OID JunctionID, OID POIID, CFields *pSourceFields );
	CFields * CloneFieldsInJunctionReferenceTable ( OID RecordID, CFields *pSourceFields );
	CFields * CloneFieldsInJunctionReferenceTable ( OID JunctionID, SGlobeFeatureID POIID, CFields *pSourceFields) ;
	//##ModelId=46B7B8380157
	CFeatureSet* GetFieldListFromJunctionReferenceTable ( OID JunctionID, const char* setname );
	//##ModelId=46B7B838015A
	CFeatureSet* GetFieldListFromJunctionReferenceTableByPOI ( OID JunctionID, OID POIID, int MeshID, const char* setname );
	//##ModelId=46B7B8380167
	CFields * GetFieldFromJunctionReferenceTable ( OID ID );
	CFields * GetFieldFromJunctionReferenceTableByIndex(int index);
	//##ModelId=46B7B8380169
	bool RemoveFieldListFromJunctionReferenceTableByJunction ( OID JunctionID );
	//##ModelId=46B7B838016B
	bool RemoveFieldListFromJunctionReferenceTableByPOI ( OID POIID, int MeshID );
	//##ModelId=46B7B8380177
	bool RemoveFieldFromJunctionReferenceTable( OID ID );
	bool ModifyJunctionIDFromJunctionReferenceTable( OID new_id, OID old_id );
	//##ModelId=46B7B8390223
	//OID  GetUniqueFieldIDinJunctionReferenceTable ( );
	int  GetFieldCountInJunctionReferencetable();
	//##ModelId=46B7B839035B
	bool AddFieldToJunctionReferenceTable ( OID ID, CFields * pFields );


	//## Operation: AddColumn%928878564
	//##ModelId=46B7B83802FD
	bool AddColumnToRoadAttr (char* name, char* caption, FIELDTYPE type, int length = 0);
	//##ModelId=46B7B83803B9
	bool AddColumnToJunctionAttr (char* name, char* caption, FIELDTYPE type, int length = 0);
	//##ModelId=46B7B839002E
	bool AddColumnToCompoundJunctionAttr (char* name, char* caption, FIELDTYPE type, int length = 0);
	//##ModelId=46B7B839007D
	bool AddColumnToTimeLimitTable (char* name, char* caption, FIELDTYPE type, int length = 0);
	//##ModelId=46B7B83900CB
	bool AddColumnToVehicleLimitTable (char* name, char* caption, FIELDTYPE type, int length = 0);
	//##ModelId=46B7B8390119
	bool AddColumnToTurnTable (char* name, char* caption, FIELDTYPE type, int length = 0);
	//##ModelId=46B7B8390167
	bool AddColumnToDirectionTable (char* name, char* caption, FIELDTYPE type, int length = 0);
	//##ModelId=46B7B83901B5
	bool AddColumnToLaneTable (char* name, char* caption, FIELDTYPE type, int length = 0);
	//##ModelId=46B7B8390203
	bool AddColumnToJunctionReferenceLimitTable (char* name, char* caption, FIELDTYPE type, int length = 0);


	CFieldsInfo * GetCompoundJunctionFieldsInfoPtr();
	CFieldsInfo  * GetJunctionFieldsInfoPtr();


	//##ModelId=46B7B83903D8
	CFields * CloneFields( CFields *pFields, CFieldsInfo * pFieldsInfo ) ;
	//## Attribute: m_pFieldsInfo%36E816D601B4
	//	ָ�������ͼ�������ֶνṹ��Ϣ��CFieldsInfo�����ָ�롣
	//	��ָ����GetFieldsInfoPtr()��ȡ��
	//	��ָ��ָ���CFieldsInfo������CRoadLayer�Ĺ��캯���д�����������������ɾ����
    //## begin CRoadLayer::m_pFieldsInfo%36E816D601B4.attr preserve=no  private: CFieldsInfo* {UA} 

public:
		
	//////////////////////////////////////////////////////////////////////////
	//�ؼ��ֶ�����
	//��ȡָ����·������ģɣ��ֶ�����,֧�����и�����
	int GetUniqueIDIndexByTableType( ETableTypeAttachedByRoad table_type );
	//��ȡָ����·������Ľ�����ֶ�����,֧�ֳ�ʱ��ͳ�����������ĸ�����
	int GetJunctionIDIndexByTableType( ETableTypeAttachedByRoad table_type );
	//��ȡָ����·�������ʻ���·�ֶ�����,֧�ֳ�����ת�򡢷����³�������ת���·���·��ʵ��ͼ��·�ڷŴ�ͼ��·�ڣ�����Ƶ��·��ǿ���յ���������Ϣ��
	int GetStartRoadIDIndexByTableType( ETableTypeAttachedByRoad table_type );
	//��ȡָ����·�������ʻ����·�ֶ�����,֧��ת����ת��·��ʵ��ͼ��·�ڷŴ�ͼ��·�ڣ�����Ƶ��·��ǿ���յ���������Ϣ��
	int GetEndRoadIDIndexByTableType( ETableTypeAttachedByRoad table_type );
	//��ȡָ����·�������ʻ���·�����ֶ�����,֧���³�������ת���·���·��ʵ��ͼ��·�ڷŴ�ͼ��·�ڣ�����Ƶ��·��ǿ���յ���������Ϣ��
	int GetStartRoadMeshIDIndexByTableType( ETableTypeAttachedByRoad table_type );
	//��ȡָ����·�������ʻ����·�����ֶ�����,֧����ת��·��ʵ��ͼ��·�ڷŴ�ͼ��·�ڣ�����Ƶ��·��ǿ���յ���������Ϣ��
	int GetEndRoadMeshIDIndexByTableType( ETableTypeAttachedByRoad table_type );
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//ͳ�ƺ�����δ����
	void GetRoadStaticInfo( char * filename );
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//�༭���˺���
	//ִ�б༭����ǰ���ô˺����������һ���༭�����ı��ݽ��
	virtual void ClearUndoFeatureSet();
	
	//�ָ��ϴα༭����ǰ��״̬
	virtual void ResetUndoFeatureSet() ;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//��ȡ��·�������������ָ����Ϣ,֧�����и�����
	CFieldsInfo						* GetFieldsInfoPtrByTableType( ETableTypeAttachedByRoad table_type );
	CGuideFieldsInfo				* GetJunctionGuideFieldsInfoPtr( ) ;
	CJunctionViewFieldsInfo			* GetJunctionViewFieldsInfoPtr( ) ;
	CJunctionVideoFieldsInfo		* GetJunctionVideoFieldsInfoPtr( ) ;
	CJunctionVRViewFieldsInfo		* GetJunctionVRViewFieldsInfoPtr( ) ;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//��ָ����������ָ���Ľ�������޸�Ϊ�µĽ������,֧���н����ĸ�����
	bool ModifyJunctionIDFromTableByType ( ETableTypeAttachedByRoad table_type, SGlobeFeatureID new_id, SGlobeFeatureID old_id ) ;
	//����������ָ���Ľ�������޸�Ϊ�µĽ������,����������ת�򡢷����³�������ת���·��򡢽��������·��ʵ��ͼ��·�ڷŴ�ͼ��·�ڣ�����Ƶ��·��ǿ���յ�����������Ϣ��������Ϣ
	bool ModifyJunctionIDFromTable ( SGlobeFeatureID new_id, SGlobeFeatureID old_id )  ;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////


	//��ָ����·���������½�һ����¼,֧�ֳ�����ת�򡢷����³�������ת���·���·��ʵ��ͼ��·�ڷŴ�ͼ��·�ڣ�����Ƶ��·��ǿ���յ���������Ϣ
	CFields * CloneFieldsInTableByType ( ETableTypeAttachedByRoad table_type, OID JunctionID, SGlobeFeatureID RoadID, CFields *pSourceFields );
	
	//��ָ����·���������½�һ����¼,֧�����б�
	CFields * CloneFieldsInTableByType ( ETableTypeAttachedByRoad table_type, OID RecordID, CFields *pSourceFields );
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//��ȡָ���������е�ĳ����¼,֧�����и�����
	CFields * GetFieldFromTableByType ( ETableTypeAttachedByRoad table_type, OID ID ) ;
	CFields * GetFieldFromTableByTypeByIndex(ETableTypeAttachedByRoad table_type, int index);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//ɾ��ָ���������е�ĳ����¼,֧�����и�����
	bool RemoveFieldFromTableByType ( ETableTypeAttachedByRoad table_type, OID ID ) ;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//��ȡָ����·�ĵ�·�������¼����,֧��ת����ת�򡢳���ʻ�롢����ʻ�롢�³���ʻ�롢�·���ʻ�롢·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	CFeatureSet* GetFieldListFromTableByType ( ETableTypeAttachedByRoad table_type, SGlobeFeatureID RoadID, OID JunctionID, const char* setname );
	
	//��ȡָ��ʻ���·�ĵ�·�������¼����,֧��ת����ת�򡢳���ʻ�롢����ʻ�롢�³���ʻ�롢�·���ʻ�롢·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	CFeatureSet* GetFieldListFromTableByInRoadByType ( ETableTypeAttachedByRoad table_type, SGlobeFeatureID RoadID, OID JunctionID, const char* setname );
	
	//��ȡָ��ʻ����·�ĵ�·�������¼����,֧��ת����ת��·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	CFeatureSet* GetFieldListFromTableByOutRoadByType ( ETableTypeAttachedByRoad table_type, SGlobeFeatureID RoadID, OID JunctionID, const char* setname );
	
	//��ȡָ��POI�Ĳ������¼����
	CFeatureSet* GetFieldListFromJunctionReferenceTableByPOI ( OID JunctionID, SGlobeFeatureID POIID, const char* setname );
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//��ȡָ��������ĳ����·�������¼����,֧�ֳ�����ת�򡢷����³�������ת���·��򡢽��������·��ʵ��ͼ��·�ڷŴ�ͼ��·�ڣ�����Ƶ��·��ǿ���յ���������Ϣ��SA��Ϣ
	CFeatureSet* GetFieldListFromTableByType ( ETableTypeAttachedByRoad table_type, OID JunctionID, const char* setname );
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//ɾ������������õ�·�����ļ�¼������ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	bool RemoveRoadIDFromTable( SGlobeFeatureID RoadID );
	
	//��ָ����������ɾ��ָ����·�����ļ�¼��֧��ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	bool RemoveRoadIDFromTableByType( ETableTypeAttachedByRoad table_type, SGlobeFeatureID RoadID );
	
	//��ָ����������ɾ��ָ��ʻ���·�����ļ�¼��֧��ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	bool RemoveStartRoadIDFromTableByType( ETableTypeAttachedByRoad table_type, SGlobeFeatureID RoadID );
	
	//��ָ����������ɾ��ָ��ʻ����·�����ļ�¼��֧��ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	bool RemoveEndRoadIDFromTableByType( ETableTypeAttachedByRoad table_type, SGlobeFeatureID RoadID );
	
	//ɾ��ָ��POI�Ľ����������¼
	bool RemoveFieldListFromJunctionReferenceTableByPOI ( SGlobeFeatureID POIID );
	
	
	//ɾ��ָ��RoadID���·����¼
	bool RemoveEndRoadIDInDirectionTable( SGlobeFeatureID RoadID ) ;
	
	//ɾ��ָ��RoadID���³�����¼
	bool RemoveEndRoadIDInLaneTable ( SGlobeFeatureID RoadID );
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//��·������Ϣ�ж���������
	bool IsEndRoadIDInDirectionTable( SGlobeFeatureID RoadID, OID JunctionID ) ;
	bool IsEndRoadIDInLaneTable( SGlobeFeatureID EndRoadID, OID JunctionID ) ;
	
	//�жϽ�����Ƿ����������Ϣ,����ֵΪ������Ϣ�ı�Type���������а��������ɣĵı�
	ETableTypeAttachedByRoad IsJunctionIDInTableAttachedByRoad( OID JunctionID ) ;
	
	//�жϵ�·�Ƿ����������Ϣ,����ֵΪ������Ϣ�ı�Type������ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	ETableTypeAttachedByRoad IsRoadIDInTableAttachedByRoad( OID JunctionID, SGlobeFeatureID RoadID ) ;
	
	//�жϵ�·�Ƿ�����ڸ������ʻ���·,����ֵΪ������Ϣ�ı�Type������ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	ETableTypeAttachedByRoad IsStartRoadIDInTableAttachedByRoad( OID JunctionID, SGlobeFeatureID RoadID ) ;
	
	//�жϵ�·�Ƿ�����ڸ������ʻ����·,����ֵΪ������Ϣ�ı�Type������ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	ETableTypeAttachedByRoad IsEndRoadIDInTableAttachedByRoad( OID JunctionID, SGlobeFeatureID RoadID ) ;
	
	//�жϵ�·�Ƿ����������Ϣ��֧��ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	bool IsRoadIDInTableAttachedByRoadByType( ETableTypeAttachedByRoad table_type, OID JunctionID, SGlobeFeatureID RoadID ) ;
	
	//�жϵ�·�Ƿ�����ڸ������ʻ���·��֧��ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	bool IsStartRoadIDInTableAttachedByRoadByType( ETableTypeAttachedByRoad table_type, OID JunctionID, SGlobeFeatureID RoadID ) ;
	
	//�жϵ�·�Ƿ�����ڸ������ʻ����·��֧��ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	bool IsEndRoadIDInTableAttachedByRoadByType( ETableTypeAttachedByRoad table_type, OID JunctionID, SGlobeFeatureID RoadID ) ;
	
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//�༭��·�󣬸��µ�·�������еĹ�����Ϣ
	bool ModifyRoadIDInTurnTable ( SGlobeFeatureID RoadID, OID JunctionID, SGlobeFeatureID NewRoadID );
	
	bool ModifyRoadIDInDirectionTable ( SGlobeFeatureID RoadID, OID JunctionID, SGlobeFeatureID NewRoadID );
	
	bool ModifyEndRoadIDFromDirectionTable( SGlobeFeatureID RoadID, OID JunctionID, SGlobeFeatureID EndRoadID ) ;
	
	bool ModifyRoadIDInLaneTable ( SGlobeFeatureID RoadID, OID JunctionID, SGlobeFeatureID NewRoadID );
	
	bool ModifyEndRoadIDInLaneTable( OID JunctionID, SGlobeFeatureID EndRoadID, SGlobeFeatureID NewEndRoadID ) ;
	
	//������ĳ��·�ڵ�·���������и�������Ϣ������ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	bool ModifyRoadIDInTable ( SGlobeFeatureID RoadID, OID JunctionID, SGlobeFeatureID NewRoadID );
	
	//������ĳ��·�ڵ�·���������и�������Ϣ������ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	bool ModifyStartRoadIDInTable ( SGlobeFeatureID RoadID, OID JunctionID, SGlobeFeatureID NewRoadID );
	
	//������ĳ��·�ڵ�·������ָ����������Ϣ��֧��ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	bool ModifyRoadIDInTableByType ( ETableTypeAttachedByRoad table_type, SGlobeFeatureID RoadID, OID JunctionID, SGlobeFeatureID NewRoadID );
	
	//������ĳ��·�ڵ�·������ָ����������Ϣ��֧��ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	bool ModifyStartRoadIDInTableByType ( ETableTypeAttachedByRoad table_type, SGlobeFeatureID RoadID, OID JunctionID, SGlobeFeatureID NewRoadID );
	
	//������ĳ��·�ڵ�·������ָ����������Ϣ��֧��ת����ת�򡢳����������³������·���·�ڷŴ�ͼ��·��ʵ��ͼ��·��3d��Ƶ��·��ǿ���յ���������Ϣ
	bool ModifyEndRoadIDInTableByType ( ETableTypeAttachedByRoad table_type, SGlobeFeatureID RoadID, OID JunctionID, SGlobeFeatureID NewRoadID );
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//�����ֶ���ָ���ĵ�·������
	bool AddColumnToTableAttachedByRoad ( ETableTypeAttachedByRoad table_type, char* name, char* caption, FIELDTYPE type, int length = 0 );
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//���Ӽ�¼��ָ���ĵ�·������
	bool AddFieldsToTableByType ( ETableTypeAttachedByRoad table_type, OID id, CFields *pFields );
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//OID  GetUniqueFieldIDinTableByType( ETableTypeAttachedByRoad table_type );
	int  GetFieldCountInTableByType(ETableTypeAttachedByRoad table_type);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

public:

	//## Constructors (specified)
	//## Operation: CRoadLayer%925876938
	//##ModelId=46B7B8380179
	CRoadLayer (CNaviMap* ownerNaviMap, LAYER layerID, jmeta * pFieldsInfo);

	//## Destructor (specified)
	//## Operation: ~CRoadLayer%928790182
	//##ModelId=46B7B8380242
	~CRoadLayer ();

	virtual ELayerType GetLayerType () ;

	//##ModelId=46B7B8390232
	virtual bool DeleteFeature (OID featureID) ;

	//##ModelId=46B7B8390235
	virtual bool LoadDataFromFile (const char * szFullPath);
	
	//## Operation: SaveDataToFile%925876955
	//##ModelId=46B7B8390238
	virtual bool SaveDataToFile (const char * szFullPath);

	//## Operation: NewFeature%925876952
	//##ModelId=46B7B8390290
	virtual CFeature* NewFeature (GEOTYPE type, OID featureID = -1);

	//##ModelId=46B7B839030D
	virtual bool LoadLayerInfoFromFile ( char *&p_buffer, char *file_buffer, int file_length );
	
	//##ModelId=46B7B839031D
	virtual bool SaveLayerInfoToFile ( FILE *fp );

	//##ModelId=46B7B839033C
	virtual bool CloneLayer( CLayer * pLayer ) ;

	//##ModelId=46B7B839034B
	virtual void Release();
	
	virtual bool ResumeFeature (OID featureID);
	
	virtual void Clear ();

	//////////////////////////////////////////////////////////////////////////
	//�༭���˺���
	void BackupModifiedFields( CFields * pFields );
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////


protected:
	//��ȡ����ʱ�ı���ʱID
	OID GetBackupFieldsID( CFields *pFields );

private:
	CFeatureSet * GetFieldsListPtrByTableType( ETableTypeAttachedByRoad table_type, int isourcetype );

public:

	virtual CFeature * GetStartJunctionFeature(OID roadID);

	virtual CFeature * GetEndJunctionFeature(OID roadID);

public:
	// �򿪱༭���α�
    virtual ISQLTransact * OpenCursorForDataSource(unsigned projID);

	virtual ISQLTransact * OpenCursorForDataSource(SGeoRect * pRects, unsigned nRects);

	virtual ISQLTransact * OpenCursorForDataSource(time_t tBegin, time_t tEnd);

	virtual ISQLTransact * OpenCursorForDataSource(LPCSTR cjson);

	virtual bool Commit(CommitParams params);
	
	virtual bool CommitFeature(OID oid);

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

	unsigned CommitByEditor(ISQLConnector * pConn, CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);
	
	unsigned CommitByVerifier(ISQLConnector * pConn, CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);
	
    unsigned CommitByToolkit(ISQLConnector * pConn, CFeature ** pFeatures, unsigned nFeatures, bool bDeleted);

	bool BreakRoadByBoundary(OID *pOIDs, unsigned nOIDs);
	
	CFeature* CreateNewWay();

protected:

	bool CreateDataView(ISQLConnector * pConn);

	virtual CFeature * CatchFromReferSource(OID oid);

private: //## implementation

	void CopyFields(CFields *pFieldsTo, CFields *pFieldsFrom, ETableTypeAttachedByRoad table_type, OID id);

	void ComputeJunctionLink();

	CJunctionSAFacilityFieldsInfo	* GetJunctionSAFacilityFieldsInfoPtr( ) ;
	
	CExitInfoFieldsInfo				* GetExitInfoFieldsInfoPtr( ) ;

	bool		AddFieldToJunctionViewTable( OID ID, CFields * pFields );

	bool		AddFieldToJunctionGuideTable( OID ID, CFields * pFields );

	bool		AddFieldToJunctionSAFacilityTable( OID ID, CFields * pFields );

	bool		AddFieldToExitInfoTable( OID ID, CFields * pFields );
	
	bool		UpdateArcJunctionIDField( ) ;

	bool BreakRoad(CFeature * pFeature, std::map<CFeature *, int> &featureList, CFeatureSet * pNewJunctions);
	
	bool BreakRoadByLayer(CFeature * pFeature, CLayer * pLayer, int iLevel, std::map<CFeature *, int> &featureList, CFeatureSet * pNewJunctions);
	
	bool MergeRoadsBrokenByEnclave(CFeature * pFeature, std::map<CFeature *, int> &featureList, CFeatureSet * pNewJunctions, std::vector<CFeature *> &pRoadList, std::vector<CFeature *> &pNodeList);
	
	CFeature * MergeRoads(std::vector<CFeature *> &roadList, CFeatureSet * pNewJunctions);
	
	unsigned CommitBrokenRoads(CFeature ** pFeatures, unsigned nFeatures);
	
	unsigned CommitBrokenNodes(CFeature ** pFeatures, unsigned nFeatures);
	
	bool ReloadRoads(CFeature ** pFeatures, unsigned nFeatures);

	bool RecalculateLength(CFeature * pFeature);

	bool LoadWayNode(OID oid);

	void SetWayNodeID(OID roadID, OID seqID, OID nodeID);
	
	OID GetWayNodeID(OID roadID, OID seqID);
	// Data Members for Associations

	//## Association: GIAE::<unnamed>%36E71ACE027D
	//## Role: CRoadLayer::<the_CFieldsInfo>%36E71ACF01FC
	//## begin CRoadLayer::<the_CFieldsInfo>%36E71ACF01FC.role preserve=no  public: CFieldsInfo {1 -> 1UHN}
	//## end CRoadLayer::<the_CFieldsInfo>%36E71ACF01FC.role

	//## Association: GIAE::<unnamed>%36F95B800135
	//## Role: CRoadLayer::<the_CFeatureSet>%36F95B80021B
	//## begin CRoadLayer::<the_CFeatureSet>%36F95B80021B.role preserve=no  public: CFeatureSet {1 -> nUHN}
	//## end CRoadLayer::<the_CFeatureSet>%36F95B80021B.role

	//## Association: GIAE::<unnamed>%375DB1BC008D
	//## Role: CRoadLayer::<the_CRoadLayerInfo>%375DB1BC023C
	//## begin CRoadLayer::<the_CRoadLayerInfo>%375DB1BC023C.role preserve=no  public: CRoadLayerInfo {1 -> 1UHN}
	//## end CRoadLayer::<the_CRoadLayerInfo>%375DB1BC023C.role


	//## Association: GIAE::<unnamed>%384846AA012E
	//## Role: CRoadLayer::<the_CEditProcessor>%384846AA0130
	//## begin CRoadLayer::<the_CEditProcessor>%384846AA0130.role preserve=no  public: CEditProcessor {1 -> 1UHN}
	//## end CRoadLayer::<the_CEditProcessor>%384846AA0130.role

private:
	
	MAPWAYNODE m_mapWayNode;

	//CFieldsInfo						* m_pRoadFieldsInfo;
	//##ModelId=46B7B83A0063
	CFieldsInfo						* m_pJunctionFieldsInfo;
	//##ModelId=46B7B83A0068
	CFieldsInfo						* m_pCompoundJunctionFieldsInfo;

	CTimeLimitFieldsInfo			* m_pTimeLimitFieldsInfo;
	CVehicleLimitFieldsInfo			* m_pVehicleLimitFieldsInfo ;
	CTurnFieldsInfo					* m_pTurnFieldsInfo ;
	CLaneFieldsInfo					* m_pLaneFieldsInfo ;
	CDirectionFieldsInfo			* m_pDirectionFieldsInfo ;
	CJunctionReferenceFieldsInfo	* m_pJunctionReferenceFieldsInfo ;
	CGuideFieldsInfo				* m_pJunctionGuideFieldsInfo ;
	CJunctionViewFieldsInfo			* m_pJunctionViewFieldsInfo ;
	CExitInfoFieldsInfo				* m_pExitInfoFieldsInfo ;
	CJunctionSAFacilityFieldsInfo	* m_pJunctionSAFacilityFieldsInfo ;

	CJunctionVideoFieldsInfo		* m_pJunctionVideoFieldsInfo ;
	CJunctionVRViewFieldsInfo		* m_pJunctionVRViewFieldsInfo ;
	//##ModelId=46B7B83A007E
	CNewTurnFieldsInfo				* m_pNewTurnFieldsInfo ;
	//##ModelId=46B7B83A0083
	CNewLaneFieldsInfo				* m_pNewLaneFieldsInfo ;
	//##ModelId=46B7B83A008D
	CNewDirectionFieldsInfo			* m_pNewDirectionFieldsInfo ;

	//##ModelId=46B7B83A009D
	CFieldsMap				m_TimeLimitFieldsMap ;
	//##ModelId=46B7B83A00A2
	CFieldsMap				m_VehicleLimitFieldsMap ;
	//##ModelId=46B7B83A00AC
	CFieldsMap				m_TurnFieldsMap ;
	//##ModelId=46B7B83A00BC
	CFieldsMap				m_DirectionFieldsMap ;
	//##ModelId=46B7B83A00C1
	CFieldsMap				m_LaneFieldsMap ;
	//##ModelId=46B7B83A00CC
	CFieldsMap				m_JunctionReferenceFieldsMap ;
	CFieldsMap				m_JunctionGuideFieldsMap ;
	CFieldsMap				m_JunctionViewFieldsMap ;
	CFieldsMap				m_ExitInfoFieldsMap ;
	CFieldsMap				m_JunctionSAFacilityFieldsMap ;

	CFieldsMap				m_JunctionVideoFieldsMap ;
	CFieldsMap				m_JunctionVRViewFieldsMap ;
	//##ModelId=46B7B83A00AC
	CFieldsMap				m_NewTurnFieldsMap ;
	//##ModelId=46B7B83A00BC
	CFieldsMap				m_NewDirectionFieldsMap ;
	//##ModelId=46B7B83A00C1
	CFieldsMap				m_NewLaneFieldsMap ;

	CFieldsMap	*			m_bDeletedFieldsMap ;
	CFieldsMap	*			m_bAddedFieldsMap ;
	CFieldsMap	*			m_bModifiedFieldsMap ;

private: //## implementation
	//////////////////////////////////////////////////////////////////////////
	//�༭���˺���
	void BackupDeletedFields( CFields *pFields );
	void BackupAddedFields( CFields * pFields );
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	void		AddFieldsToLayer( CFields * pFields );
	CFields *	GetFieldsFromLayer( OID id );
};

// Class CRoadLayer 

//## begin module%375BECF903A3.epilog preserve=yes
//## end module%375BECF903A3.epilog


#endif
