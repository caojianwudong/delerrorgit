//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%407002740042.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%407002740042.cm

//## begin module%407002740042.cp preserve=no
//## end module%407002740042.cp

//## Module: CGeoPolyline%407002740042; Pseudo Package specification

#ifndef CGeoPolyline_h
#define CGeoPolyline_h 1

//## begin module%407002740042.additionalIncludes preserve=no
//## end module%407002740042.additionalIncludes

//## begin module%407002740042.includes preserve=yes
//## end module%407002740042.includes

#include "CGeometry.h"
#include "CGeoPoints.h"
//## begin module%407002740042.additionalDeclarations preserve=yes
//## end module%407002740042.additionalDeclarations

class CFeature ;
//## begin CGeoPolyline%407002740042.preface preserve=yes
//## end CGeoPolyline%407002740042.preface

//## Class: CGeoPolyline%407002740042
//## Category: DataAccess::CGeoO%407001E50071
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83E02AF
class __declspec(dllexport) CGeoPolyline : public CGeometry  //## Inherits: <unnamed>%40A1DAB2006D
{
  //## begin CGeoPolyline%407002740042.initialDeclarations preserve=yes
  //## end CGeoPolyline%407002740042.initialDeclarations

  public:
    //## Constructors (generated)
	//##ModelId=46B7B83E02B1
      CGeoPolyline(CFeature* 	m_pOwner);

    //## Destructor (generated)
	//##ModelId=46B7B83E02BF
      ~CGeoPolyline();


    //## Other Operations (specified)
      //## Operation: GetGeoType%40A44FE502CE
	//##ModelId=46B7B83E02C0
      int GetGeoType ();

      //## Operation: SetPointsCount%409F7F39008C
	//##ModelId=46B7B83E02C1
      void SetPointCount (int nCount);

      //## Operation: GetPointsCount%409F7F540232
	//##ModelId=46B7B83E02C3
      int GetPointCount ();

      //## Operation: GetPoints%409F7F65032C
	//##ModelId=46B7B83E02CE
      CGeoPoints* GetPointsPtr ();

	//##ModelId=46B7B83E02CF
	void	SetLeftPolygonID (  OID polygonID  ) ; 
 
	//##ModelId=46B7B83E02D1
	void	SetRightPolygonID (  OID polygonID  ) ; 
 
	//##ModelId=46B7B83E02D3
	OID	GetRightPolygonID ( ) ; 
 
	//##ModelId=46B7B83E02D4
	OID	GetEndNodeID ( ) ; 
 
	//##ModelId=46B7B83E02D5
	OID	GetStartNodeID ( ) ; 
 
	//##ModelId=46B7B83E02DE
	void	SetEndNodeID (  OID nodeID  ) ; 
 
	//##ModelId=46B7B83E02E0
	void	SetStartNodeID (  OID nodeID  ) ; 
 
	//##ModelId=46B7B83E02E2
	OID	GetLeftPolygonID ( ) ; 
    // Additional Public Declarations
      //## begin CGeoPolyline%407002740042.public preserve=yes
      //## end CGeoPolyline%407002740042.public

  protected:
    // Additional Protected Declarations
      //## begin CGeoPolyline%407002740042.protected preserve=yes
      //## end CGeoPolyline%407002740042.protected

  private:
    // Additional Private Declarations
      //## begin CGeoPolyline%407002740042.private preserve=yes
      //## end CGeoPolyline%407002740042.private

  private: //## implementation
    // Data Members for Class Attributes
	//##ModelId=45502F7F0116

      //## Attribute: arrayPoints%407005C100CF
      //## begin CGeoPolyline::arrayPoints%407005C100CF.attr preserve=no  private: CGeoPoints* {U} 
	//##ModelId=46B7B83E02E4
      CGeoPoints arrayPoint;
      //## end CGeoPolyline::arrayPoints%407005C100CF.attr

    // Data Members for Associations

      //## Association: DataAccess::CGeoO::<unnamed>%4079454E005D
      //## Role: CGeoPolyline::<the_CGeoPoints>%4079454E03B9
      //## begin CGeoPolyline::<the_CGeoPoints>%4079454E03B9.role preserve=no  public: CGeoPoints { -> UHgN}
      //## end CGeoPolyline::<the_CGeoPoints>%4079454E03B9.role
	//##ModelId=46B7B83E02EE
	OID 	m_StartNodeID ;
	/** 作为线状目标首节点的点状特征对象的ID值。 **/
 
	//##ModelId=46B7B83E02EF
	OID 	m_EndNodeID ;
	/** 作为线状目标末节点的点状特征对象的ID值。 **/
 
	//##ModelId=46B7B83E02F0
	OID 	m_LeftPolygonID ;
	/** 线状目标左侧多边形特征对象的ID值。 **/
 
	//##ModelId=46B7B83E02F1
	OID 	m_RightPolygonID ;
	/** 线状目标右侧多边形特征对象的ID值。 **/

    // Additional Implementation Declarations
      //## begin CGeoPolyline%407002740042.implementation preserve=yes
      //## end CGeoPolyline%407002740042.implementation

};

//## begin CGeoPolyline%407002740042.postscript preserve=yes
//## end CGeoPolyline%407002740042.postscript

// Class CGeoPolyline 

//## begin module%407002740042.epilog preserve=yes
//## end module%407002740042.epilog


#endif
