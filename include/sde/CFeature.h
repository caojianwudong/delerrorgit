//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A575E01E3.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A575E01E3.cm

//## begin module%405A575E01E3.cp preserve=no
//## end module%405A575E01E3.cp

//## Module: CFeature%405A575E01E3; Pseudo Package specification

#ifndef CFeature_h
#define CFeature_h 1

//## begin module%405A575E01E3.additionalIncludes preserve=no
//## end module%405A575E01E3.additionalIncludes

//## begin module%405A575E01E3.includes preserve=yes
//## end module%405A575E01E3.includes

//## begin module%405A575E01E3.additionalDeclarations preserve=yes
//## end module%405A575E01E3.additionalDeclarations


//## begin CFeature%405A575E01E3.preface preserve=yes
#include "Commondef.h"
#include "cfields.h"

class CLayer ;
class CGeometry ;
//## end CFeature%405A575E01E3.preface
//## Class: CFeature%405A575E01E3
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B84001B5
class __declspec(dllexport) CFeature   //## Inherits: <unnamed>%405A5C070166
{
  //## begin CFeature%405A575E01E3.initialDeclarations preserve=yes
  //## end CFeature%405A575E01E3.initialDeclarations

  public:
	  SGlobeFeatureID GetGlobeFeatureID();
	  void SetOwnerFeatureID( OID feature_id );
	  OID GetOwnerFeatureID();
	//##ModelId=46B7B84001B6
	  void SetOwnerNaviMapID2(NAVIMAP id);
	//##ModelId=46B7B84001B8
	  void SetOwnerNaviMapID1(NAVIMAP id );
	//##ModelId=46B7B84001BA
	  void SetOwnerFeatureID2(OID id);
	//##ModelId=46B7B84001C5
	  void SetOwnerFeatureID1( OID id );
	//##ModelId=46B7B84001C7
	  NAVIMAP GetOwnerNaviMapID2();
	//##ModelId=46B7B84001C8
	  NAVIMAP GetOwnerNaviMapID1();
	//##ModelId=46B7B84001C9
	  OID GetOwnerFeatureID2();
	//##ModelId=46B7B84001CA
	  OID GetOwnerFeatureID1();
	//##ModelId=46B7B84001CB
	  int	IsHasInfomation();
	//##ModelId=46B7B84001CC
	  bool	IsInCompondFeature( ) ;
	//##ModelId=46B7B84001D4
	  int GetVisibleTypeLevel();
	//##ModelId=46B7B84001D5
	  void SetVisibleTypeLevel( int iVisibleTypeLevel );
	//##ModelId=46B7B84001D7
	  CFeature * GetOwnerFeaturePtr(  );
	//##ModelId=46B7B84001D8
	  void SetOwnerFeaturePtr( CFeature * pFeature );
	//##ModelId=46B7B84001DA
	  void ResetBound();
	//##ModelId=46B7B84001DB
	  CLayer * GetOwnerLayerPtr();
	//##ModelId=46B7B84001E4
      CFeature( CLayer* pOwnerLayer, CFeature * pParent, OID fid, int subType ) ;

    //## Destructor (generated)
	//##ModelId=46B7B84001E9
      ~CFeature();

    //## Other Operations (specified)
      //## Operation: GetFID%405BE00E033C
	//##ModelId=46B7B84001EA
      OID GetFID ();

      //## Operation: GetBound%405D80D70261
	//##ModelId=46B7B84001F4
      void GetBound (double& min_x, double& min_y, double& max_x, double& max_y);
     
	//##ModelId=46B7B84001F9
	  SGeoRect GetBound ();

      //## Operation: SetBound%405D81010167
	//##ModelId=46B7B8400203
      void SetBound (double min_x, double min_y, double max_x, double max_y);

      //## Operation: GetGeometry%405BE01A029F
	//##ModelId=46B7B8400208
      CGeometry * GetGeometryPtr ();

      //## Operation: GetAttrPos%40A21326004E
	//##ModelId=46B7B8400209
      CFields*  GetAttrPtr ();

	//##ModelId=46B7B8400213
	  int GetSubCode () ;

	//##ModelId=46B7B8400214
	  void SetSubCode( int subcode ) ;
	  // Additional Public Declarations
      //## begin CFeature%405A575E01E3.public preserve=yes
      //## end CFeature%405A575E01E3.public

      void ClearStatusFlags();

	  void SetLastModifiedTime(time_t time);

	  time_t GetLastModifiedTime();

	  CheckStatus  GetAutoCheck();
	  
	  CheckStatus  GetManuCheck();
	  
	  OpType       GetOpType();

	  void	SetUserID(OID userID);

	  OID	GetUserID();

	  void  SetConfirmUID(OID userID);

	  OID   GetConfirmUID();

	  Confirm	   GetConfirm();

	  bool IsModified();

	  void SetEditver(OID editver);

	  OID GetEditver();

	  void SetVer(const char *ver);

	  char *GetVer();

	  void SetBaseAutoCheck(CheckStatus autocheck);

	  CheckStatus GetBaseAutoCheck();

	  void SetBaseManualCheck(CheckStatus manualcheck);

	  CheckStatus GetBaseManualCheck();

	  void SetBaseOpType(OpType optype);

	  OpType GetBaseOpType();

	  void	SetWorkerID(OID workerID);
	  
	  OID	GetWorkerID();
	  
	  void  SetCheckerID(OID checkerID);
	  
	  OID   GetCheckerID();

private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: m_nSubType%405BDFC001B5
      //## begin CFeature::m_nSubType%405BDFC001B5.attr preserve=no  private: int {U} 
	//##ModelId=46B7B8400216
      OID m_nID;
      //## end CFeature::m_nSubType%405BDFC001B5.attr


      //## Attribute: m_pGeometry%405BDFCB0157
      //## begin CFeature::m_pGeometry%405BDFCB0157.attr preserve=no  private: Geometry* {U} 0
	//##ModelId=46B7B8400218
      CGeometry* m_pGeometry;
      //## end CFeature::m_pGeometry%405BDFCB0157.attr

      //## Attribute: m_lGeoPos%40A20FB6035B
      //## begin CFeature::m_lGeoPos%40A20FB6035B.attr preserve=no  private: long {U} 0
	//##ModelId=46B7D17201D5
      CFields *	 m_pFields;
      //## end CFeature::m_lGeoPos%40A20FB6035B.attr

      //## Attribute: m_lAttrPos%40A20FC6030D
      //## begin CFeature::m_lAttrPos%40A20FC6030D.attr preserve=no  private: long {U} 0
	  
	//##ModelId=46B7B8400228
	  CLayer	* m_pOwnerLayer ;

	//##ModelId=46B7B8400232
	  int		m_SubCode ;

	//##ModelId=46B7B8400234
	  SGeoRect 	m_Bound ;
      //## end CFeature::m_lAttrPos%40A20FC6030D.attr

	//##ModelId=46B7B8400245
	  CFeature  * m_pOwnerFeature ;

	//##ModelId=46B7B8400247
	  int		m_iVisibleTypeLevel ;

	//##ModelId=46B7B8400251
	  OID		m_iOwnerFeatureID1 ;

	//##ModelId=46B7B8400252
	  NAVIMAP   m_iOwnerNaviMapID1 ;

	//##ModelId=46B7B8400253
	  OID		m_iOwnerFeatureID2 ;

	//##ModelId=46B7B8400261
	  NAVIMAP		m_iOwnerNaviMapID2 ;

	  OID		m_iOwnerFeatureID ;

	  time_t	m_LastModifiedTime ;

	  OID		m_iUserID;

	  OID       m_iConfirmUID;

	  OID		m_iEditver;

	  char		m_strVer[MAX_FEATURESET_NAME_LEN];

	  CheckStatus	m_CSAutoCheck;

	  CheckStatus	m_CSManualCheck;

	  OpType	m_OTOpType;

	  OID		m_iWorkerID;

	  OID		m_iCheckerID;

    // Additional Implementation Declarations
      //## begin CFeature%405A575E01E3.implementation preserve=yes
      //## end CFeature%405A575E01E3.implementation
    friend class CFields ;

};

//## begin CFeature%405A575E01E3.postscript preserve=yes
//## end CFeature%405A575E01E3.postscript

// Class CFeature 

//## begin module%405A575E01E3.epilog preserve=yes
//## end module%405A575E01E3.epilog


#endif
