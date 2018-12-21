//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%4070027E0052.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4070027E0052.cm

//## begin module%4070027E0052.cp preserve=no
//## end module%4070027E0052.cp

//## Module: CGeoPolygon%4070027E0052; Pseudo Package specification

#ifndef CGeoPolygon_h
#define CGeoPolygon_h 1

//## begin module%4070027E0052.additionalIncludes preserve=no
//## end module%4070027E0052.additionalIncludes

//## begin module%4070027E0052.includes preserve=yes
//## end module%4070027E0052.includes

#include "CGeometry.h"
#include "CGeoPoints.h"
//## begin module%4070027E0052.additionalDeclarations preserve=yes
//## end module%4070027E0052.additionalDeclarations

class CFeature ;
//## begin CGeoPolygon%4070027E0052.preface preserve=yes
//## end CGeoPolygon%4070027E0052.preface

//## Class: CGeoPolygon%4070027E0052
//## Category: DataAccess::CGeoO%407001E50071
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83E030D
class __declspec(dllexport) CGeoPolygon : public CGeometry  //## Inherits: <unnamed>%40A1DABA0251
{
  //## begin CGeoPolygon%4070027E0052.initialDeclarations preserve=yes
  //## end CGeoPolygon%4070027E0052.initialDeclarations

  public:
	//##ModelId=46B7B83E031D
	  double GetArea();
    //## Constructors (generated)
	//##ModelId=46B7B83E032C
      CGeoPolygon(CFeature* 	m_pOwner);

    //## Destructor (generated)
	//##ModelId=46B7B83E032E
      ~CGeoPolygon();


    //## Other Operations (specified)
      //## Operation: GetGeoType%40A44FEE0148
	//##ModelId=46B7B83E033C
      int GetGeoType ();

      //## Operation: SetPointsCount%4085E53101F3
	//##ModelId=46B7B83E034B
      void SetPointCount (int nCount);

      //## Operation: GetPointsCount%4085E58A0137
	//##ModelId=46B7B83E034D
      int GetPointCount ();

      //## Operation: GetPoints%40794BBD00BB
	//##ModelId=46B7B83E035B
      CGeoPoints* GetPointsPtr ();

	//##ModelId=46B7B83E035C
	  void SetCentralPoint ( SGeoPoint point  ) ;
   // Additional Public Declarations
      //## begin CGeoPolygon%4070027E0052.public preserve=yes
	//##ModelId=46B7B83E036C
	  SGeoPoint GetCentralPoint( );
      //## end CGeoPolygon%4070027E0052.public

	//##ModelId=46B7B83E036D
	int	GetIslandCount ( ) ; 
	//##ModelId=46B7B83E036E
	OID	GetIslandID (  int index  ) ; 
	//##ModelId=46B7B83E037A
	void	SetIslandID (  int index , OID ID  ) ; 
	//##ModelId=46B7B83E037D
	void	SetIslandCount (  int count  ) ; 

	//##ModelId=46B7B83E037F
	int	GetArcCount ( ) ; 
	//##ModelId=46B7B83E038A
	void	SetArcID (  int index , OID arcID  ) ; 
	//##ModelId=46B7B83E038D
	void	SetArcCount (  int arcCount  ) ; 
	//##ModelId=46B7B83E038F
	OID	GetArcID (  int index  ) ; 
 
	//##ModelId=46B7B83E0399
	OID	GetOuterPolygonID() ;
	//##ModelId=46B7B83E039A
	void SetOuterPolygonID(OID id) ;

	//##ModelId=46B7B83E039C
	void	ArcToPoints ( ) ; 

  protected:
    // Additional Protected Declarations
      //## begin CGeoPolygon%4070027E0052.protected preserve=yes
      //## end CGeoPolygon%4070027E0052.protected

  private:
    // Additional Private Declarations
      //## begin CGeoPolygon%4070027E0052.private preserve=yes
      //## end CGeoPolygon%4070027E0052.private
	//##ModelId=46B7B83E039D
	void	FreeArcsMem () ; 

	//##ModelId=46B7B83E03A9
	void	FreeIslandsMem () ; 

	//##ModelId=46B7B83E03AA
	void	FreeMem () ; 

  private: //## implementation
    // Data Members for Class Attributes
	//##ModelId=45502F7F023F

      //## Attribute: arrayPoints%40794A69035B
      //## begin CGeoPolygon::arrayPoints%40794A69035B.attr preserve=no  private: CGeoPoints* {U} 
	//##ModelId=46B7B83E03AC
      CGeoPoints arrayPoint;
	//##ModelId=46B7B83E03BA
	  SGeoPoint  CentralPoint;
      //## end CGeoPolygon::arrayPoints%40794A69035B.attr

      //## Attribute: nPointsCount%4085E4EB003D
      //## begin CGeoPolygon::nPointsCount%4085E4EB003D.attr preserve=no  private: double {U} 0
	//##ModelId=46B7B83E03BE
	  double m_Area;
      //## end CGeoPolygon::nPointsCount%4085E4EB003D.attr

    // Data Members for Associations
	//##ModelId=46B7B83E03BF
	int 	m_ArcCount ;
	/** 组成面状目标的线状特征对象的个数。其值域为 1..MAX_ARCS_OF_POLYGON_OBJECT **/
 
	//##ModelId=46B7B83E03C8
	OID* 	m_pArcIDs ;
	/** 组成面状目标的线状特征对象的ID数组。其中，对于每个ID值：
1. 当ID值为正数时，则表示多边形边界的方向与弧段的方向相同；
2. 当ID值为负数时，则表示多边形边界的方向与弧段的方向相反； **/
 
	//##ModelId=46B7B83E03C9
	int 	m_IslandCount ;
	/** 该面状目标所包含的岛多边形特征对象的个数。其值域为：0 .. MAX_ISLANDS_OF_POLYGON_OBJECT **/
 
	//##ModelId=46B7B83E03CA
	OID* 	m_pIslandIDs ;
	/** 该面状目标所包含的岛多边形特征对象的ID数组。 **/
 
	//##ModelId=46B7B83E03D8
	OID		m_OuterPolygonID ;
	/**岛多边形的外围多边形的对象ID。**/

      //## Association: DataAccess::CGeoO::<unnamed>%40794C8401B5
      //## Role: CGeoPolygon::<the_CGeoPoints>%40794C8500BB
      //## begin CGeoPolygon::<the_CGeoPoints>%40794C8500BB.role preserve=no  public: CGeoPoints { -> UHgN}
      //## end CGeoPolygon::<the_CGeoPoints>%40794C8500BB.role

    // Additional Implementation Declarations
      //## begin CGeoPolygon%4070027E0052.implementation preserve=yes
      //## end CGeoPolygon%4070027E0052.implementation

};

//## begin CGeoPolygon%4070027E0052.postscript preserve=yes
//## end CGeoPolygon%4070027E0052.postscript

// Class CGeoPolygon 

//## begin module%4070027E0052.epilog preserve=yes
//## end module%4070027E0052.epilog


#endif
