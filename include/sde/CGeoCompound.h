//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%407002620042.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%407002620042.cm

//## begin module%407002620042.cp preserve=no
//## end module%407002620042.cp

//## Module: CGeoCompound%407002620042; Pseudo Package specification

#ifndef CGeoCompound_h
#define CGeoCompound_h 1

//## begin module%407002620042.additionalIncludes preserve=no
//## end module%407002620042.additionalIncludes

//## begin module%407002620042.includes preserve=yes
//## end module%407002620042.includes

#include "commondef.h"	// Added by ClassView
#include "CGeometry.h"
//## begin module%407002620042.additionalDeclarations preserve=yes
//## end module%407002620042.additionalDeclarations

class CFeature ;
//## begin CGeoCompound%407002620042.preface preserve=yes
//## end CGeoCompound%407002620042.preface

//## Class: CGeoCompound%407002620042
//## Category: DataAccess::CGeoO%407001E50071
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83F0128
class __declspec(dllexport) CGeoCompound : public CGeometry  //## Inherits: <unnamed>%40A1DD0B031C
{
  //## begin CGeoCompound%407002620042.initialDeclarations preserve=yes
  //## end CGeoCompound%407002620042.initialDeclarations

  public:
	  void AddArcID( OID arc_id );
	  void ModifyJunctionIDInJunctionList( OID new_id, OID old_id );
	//##ModelId=46B7B83F012A
	  bool Uion( CGeoCompound * pCompound );
	//##ModelId=46B7B83F0139
	  bool ModifyRoadID( OID RoadID1, OID RoadID2, bool bIsAdd );
	//##ModelId=46B7B83F013D
	  bool	Init() ;
	//##ModelId=46B7B83F013E
	  bool AddLinkList( std::vector<OID> linkList );
	//##ModelId=46B7B83F0140
	  bool AddArcList( std::vector<OID> arcList );
	//##ModelId=46B7B83F0148
	  bool AddJunctionList( std::vector<OID> junctionList );
	//##ModelId=46B7B83F014A
	  bool AddLink( OID linkID );
	//##ModelId=46B7B83F014C
	  bool RemoveLink( OID linkID );
	//##ModelId=46B7B83F014E
	  bool RemoveArc( OID arcID );
	//##ModelId=46B7B83F0157
	  bool RemoveJunction( OID junctionID );
	//##ModelId=46B7B83F0159
	  bool ReplaceArc( OID arcID, OID NewArcID );
	//##ModelId=46B7B83F015C
	  bool IsLinkInCompoundJunction( OID LinkID );
	//##ModelId=46B7B83F0167
	  bool IsJunctionInCompoundJunction( OID junctionID );
	//##ModelId=46B7B83F0169
	  int	FindArcInArcList ( OID arcID );
	//##ModelId=46B7B83F016B
	  int	FindLinkInLinkList ( OID linkID );
	//##ModelId=46B7B83F016D
	  int	FindJunctionInJunctionList ( OID junctionID );
	//##ModelId=46B7B83F0178
	  void SetPoint( SGeoPoint point );
	//##ModelId=46B7B83F017A
	  SGeoPoint GetPoint();
    //## Constructors (generated)
	//##ModelId=46B7B83F017B
      CGeoCompound(CFeature* 	m_pOwner);

    //## Constructors (specified)
      //## Operation: CGeoCompound%407955DB0128
	//##ModelId=46B7B83F0186
      CGeoCompound (CFeature* 	m_pOwner,double X, double Y);
    //## Destructor (generated)
	//##ModelId=46B7B83F0196
      ~CGeoCompound();


    //## Other Operations (specified)
      //## Operation: GetGeoType%40A44FD8002E
	//##ModelId=46B7B83F01A5
      int GetGeoType ();

      //## Operation: GetX%407002AC00DF
	//##ModelId=46B7B83F01A6
      double GetX ();

      //## Operation: GetY%407002EF0217
	//##ModelId=46B7B83F01B5
      double GetY ();

      //## Operation: SetX%407002F4036F
	//##ModelId=46B7B83F01B6
      void SetX (double X);

      //## Operation: SetY%40700328014C
	//##ModelId=46B7B83F01C6
      void SetY (double Y);


	//##ModelId=46B7B83F01D4
	void	SetArcID (  int index , OID arcID  ) ; 
	//##ModelId=46B7B83F01E4
	void	SetLinkID (  int index , OID linkID  ) ; 
	//##ModelId=46B7B83F01E7
	void	SetJunctionID (  int index , OID junctionID  ) ; 
 
	//##ModelId=46B7B83F01EA
	int	GetArcCount ( ) ; 
	//##ModelId=46B7B83F01F4
	int	GetLinkCount ( ) ; 
	//##ModelId=46B7B83F01F5
	int	GetJunctionCount ( ) ; 
 
	//##ModelId=46B7B83F01F6
	OID	GetArcID (  int index  ) ; 
	//##ModelId=46B7B83F0203
	OID	GetLinkID (  int index  ) ; 
	//##ModelId=46B7B83F0205
	OID	GetJunctionID (  int index  ) ; 

private:

	//##ModelId=46B7B83F0207
	void	FreeMem () ; 
    // Additional Public Declarations
      //## begin CGeoCompound%407002620042.public preserve=yes
      //## end CGeoCompound%407002620042.public

  protected:
    // Additional Protected Declarations
      //## begin CGeoCompound%407002620042.protected preserve=yes
      //## end CGeoCompound%407002620042.protected


  private: //## implementation
    // Data Members for Class Attributes

	//##ModelId=46B7B83F0214
	SGeoPoint	m_Point ;
	//##ModelId=4550252C029C
 
	//##ModelId=46B7B83F0225
	std::vector<OID> 	m_ArcIDs ;
		/** 关联弧段的ID数组。 **/

	//##ModelId=46B7B83F0233
	std::vector<OID> 	m_LinkIDs ;
		/** 关联弧段的ID数组。 **/

	//##ModelId=46B7B83F0238
	std::vector<OID> 	m_JunctionIDs ;
		/** 关联弧段的ID数组。 **/

	//##ModelId=45502F7F0378
   // Additional Implementation Declarations
      //## begin CGeoCompound%407002620042.implementation preserve=yes
      //## end CGeoCompound%407002620042.implementation

};

//## begin CGeoCompound%407002620042.postscript preserve=yes
//## end CGeoCompound%407002620042.postscript

// Class CGeoCompound 

//## begin module%407002620042.epilog preserve=yes
//## end module%407002620042.epilog


#endif
