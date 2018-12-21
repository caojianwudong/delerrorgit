//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%407002620042.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%407002620042.cm

//## begin module%407002620042.cp preserve=no
//## end module%407002620042.cp

//## Module: CGeoPoint%407002620042; Pseudo Package specification

#ifndef CGeoPoint_h
#define CGeoPoint_h 1

//## begin module%407002620042.additionalIncludes preserve=no
//## end module%407002620042.additionalIncludes

//## begin module%407002620042.includes preserve=yes
//## end module%407002620042.includes

#include "commondef.h"	// Added by ClassView
#include "CGeometry.h"
//## begin module%407002620042.additionalDeclarations preserve=yes
//## end module%407002620042.additionalDeclarations

class CFeature ;
//## begin CGeoPoint%407002620042.preface preserve=yes
//## end CGeoPoint%407002620042.preface

//## Class: CGeoPoint%407002620042
//## Category: DataAccess::CGeoO%407001E50071
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83F004E
class __declspec(dllexport) CGeoPoint : public CGeometry  //## Inherits: <unnamed>%40A1DD0B031C
{
  //## begin CGeoPoint%407002620042.initialDeclarations preserve=yes
  //## end CGeoPoint%407002620042.initialDeclarations

  public:
	//##ModelId=46B7B83F005E
	  MESH GetMeetJunctionMeshID ( );
	//##ModelId=46B7B83F005F
	  void SetMeetJunctionMeshID ( MESH iMeetJunctionMeshID );
	//##ModelId=46B7B83F0061
	  OID GetMeetJunctionID();
	//##ModelId=46B7B83F0062
	  void SetMeetJunctionID( OID iMeetJunctionID );
	//##ModelId=46B7B83F0064
	  bool IsMeetJunction( );
	//##ModelId=46B7B83F0065
	  void SetMeetJunction( bool bIsMeetJunction );
	//##ModelId=46B7B83F006E
	  void SetChar ( char cVal );
	//##ModelId=46B7B83F0070
	  char GetChar();
	//##ModelId=46B7B83F0071
	  void SetVsLevel1( bool vs );
	//##ModelId=46B7B83F0073
	  void SetVsLevel2( bool vs );
	//##ModelId=46B7B83F0075
	  void SetVsLevel3( bool vs );
	//##ModelId=46B7B83F007E
	  void SetVsLevel4( bool vs );
	//##ModelId=46B7B83F0080
	  void SetVsLevel5( bool vs );
	//##ModelId=46B7B83F0082
	  bool GetVsLevel1();
	//##ModelId=46B7B83F0083
	  bool GetVsLevel2();
	//##ModelId=46B7B83F0084
	  bool GetVsLevel3();
	//##ModelId=46B7B83F0085
	  bool GetVsLevel4();
	//##ModelId=46B7B83F008C
	  bool GetVsLevel5();
	//##ModelId=46B7B83F008D
	  bool GetHP();
	//##ModelId=46B7B83F008E
	  void SetHP( bool hp );
	//##ModelId=46B7B83F0090
	  bool IsFindArcInArcList ( OID arcID );
	//##ModelId=46B7B83F0092
	  void SetTruePoint( SGeoPoint point );
	//##ModelId=46B7B83F009C
	  SGeoPoint GetTruePoint();
	//##ModelId=46B7B83F009D
 	  void SetDisplayPoint( SGeoPoint point );
	//##ModelId=46B7B83F009F
	  SGeoPoint GetDisplayPoint();
   //## Constructors (generated)
	//##ModelId=46B7B83F00A0
      CGeoPoint(CFeature* 	m_pOwner);

    //## Constructors (specified)
      //## Operation: CGeoPoint%407955DB0128
	//##ModelId=46B7B83F00A2
      CGeoPoint (CFeature* 	m_pOwner,double X, double Y);
    //## Destructor (generated)
	//##ModelId=46B7B83F00AC
      ~CGeoPoint();


    //## Other Operations (specified)
      //## Operation: GetGeoType%40A44FD8002E
	//##ModelId=46B7B83F00AD
      int GetGeoType ();

	//##ModelId=46B7B83F00AE
	void	SetArcID (  int index , OID arcID  ) ; 
 
	//##ModelId=46B7B83F00BC
	int	GetArcCount ( ) ; 
 
	//##ModelId=46B7B83F00BD
	OID	GetArcID (  int index  ) ; 
 
	//##ModelId=46B7B83F00BF
	void	SetArcCount (  int arcCount  ) ; 

private:

	//##ModelId=46B7B83F00C1
	void	FreeMem () ; 
    // Additional Public Declarations
      //## begin CGeoPoint%407002620042.public preserve=yes
      //## end CGeoPoint%407002620042.public

  protected:
    // Additional Protected Declarations
      //## begin CGeoPoint%407002620042.protected preserve=yes
      //## end CGeoPoint%407002620042.protected


  private: //## implementation
    // Data Members for Class Attributes

	//##ModelId=46B7B83F00CC
	SGeoPoint	m_TruePoint ;
	
	//##ModelId=46B7B83F00D1
	SGeoPoint	m_DisplayPoint ;
	//##ModelId=46B7B83F00DA
	int 	m_ArcCount ;
	/** 关联弧段的个数。其值域为：0 -- 最大允许的关联弧段数 MAX_RELATED_ARCS_OF_POINTOBJECT。该常数在definition_giae.h中定义。 **/

	//##ModelId=46B7B83F00DB
	OID* 	m_pArcIDs ;
	/** 关联弧段的ID数组。 **/

	//##ModelId=46B7B83F00DC
	char	m_VSLevel ;

	//##ModelId=46B7B83F00EA
	BOOL bHP;						//TRUE-悬挂点，FALSE-非悬挂点

	//##ModelId=46B7B83F00EB
	OID		m_iMeetJunctionID ;
	//##ModelId=46B7B83F00EC
	MESH		m_iMeetJunctionMeshID ;

	//##ModelId=45502F7F0378
   // Additional Implementation Declarations
      //## begin CGeoPoint%407002620042.implementation preserve=yes
      //## end CGeoPoint%407002620042.implementation

};

//## begin CGeoPoint%407002620042.postscript preserve=yes
//## end CGeoPoint%407002620042.postscript

// Class CGeoPoint 

//## begin module%407002620042.epilog preserve=yes
//## end module%407002620042.epilog


#endif
