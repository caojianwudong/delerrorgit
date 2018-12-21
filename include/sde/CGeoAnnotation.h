//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%40B009580157.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40B009580157.cm

//## begin module%40B009580157.cp preserve=no
//## end module%40B009580157.cp

//## Module: CGeoAnnotation%40B009580157; Pseudo Package specification

#ifndef CGeoAnnotation_h 
#define CGeoAnnotation_h 1

//## begin module%40B009580157.additionalIncludes preserve=no
//## end module%40B009580157.additionalIncludes

//## begin module%40B009580157.includes preserve=yes
//## end module%40B009580157.includes

#include "CGeometry.h"
#include "CGeopoints.h"
#include "commondef.h"	// Added by ClassView
//## begin module%40B009580157.additionalDeclarations preserve=yes
//## end module%40B009580157.additionalDeclarations
class CFeature ;
//## begin CGeoAnnotation%40B009580157.preface preserve=yes
//## end CGeoAnnotation%40B009580157.preface

//## Class: CGeoAnnotation%40B009580157
//## Category: CGeometry%407001E50071
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83F0261
class __declspec(dllexport) CGeoAnnotation : public CGeometry  //## Inherits: <unnamed>%40B0096C035B
{
  //## begin CGeoAnnotation%40B009580157.initialDeclarations preserve=yes
  //## end CGeoAnnotation%40B009580157.initialDeclarations

  public:
	//##ModelId=46B7B83F0263
	  int GetVisibleTypeLevel();
	//##ModelId=46B7B83F0264
	  void SetVisibleTypeLevel( int iVisibleTypeLevel );
	//##ModelId=46B7B83F0266
	  SGeoRect GetAnnoBound();
	//##ModelId=46B7B83F0267
	  const char * GetLineString1();
	//##ModelId=46B7B83F0271
	  const char * GetLineString2();
	//##ModelId=46B7B83F0272
	  const char * GetLineString3();
	//##ModelId=46B7B83F0273
	  const char * GetLineString4();
	//##ModelId=46B7B83F0274
	  bool SetLineString4( const char * name );
	//##ModelId=46B7B83F0276
	  bool SetLineString3( const char * name );
	//##ModelId=46B7B83F0278
	  bool SetLineString2( const char * name );
	//##ModelId=46B7B83F0281
	  bool SetLineString1( const char * name );
	//##ModelId=46B7B83F0283
	  bool bISAnnoHor();
	//##ModelId=46B7B83F0284
	  void SetAnnoDirection( bool bIsHor );
	//##ModelId=46B7B83F0286
	  int GetLineCount();
	//##ModelId=46B7B83F0287
	  void SetLineCount( int count );
	//##ModelId=46B7B83F0290
	  void	SetOwnerLayerID ( LAYER layer_id ) ;
	//##ModelId=46B7B83F0292
	  LAYER	GetOwnerLayerID() ;
	//##ModelId=46B7B83F0293
	  void	SetVSLevel ( int level ) ;
	//##ModelId=46B7B83F0295
	  int	GetVSLevel ( ) ;
	//##ModelId=46B7B83F0296
	  void	SetOwnerFeatureID ( OID feature_id ) ;
	//##ModelId=46B7B83F0298
	  OID	GetOwnerFeatureID() ;

	//##ModelId=46B7B83F029F
	  void SetTruePoint( SGeoPoint point );
	//##ModelId=46B7B83F02A1
	  SGeoPoint GetTruePoint();
	//##ModelId=46B7B83F02A2
 	  void SetDisplayPoint( SGeoPoint point );
	//##ModelId=46B7B83F02A4
	  SGeoPoint GetDisplayPoint();
	//##ModelId=46B7B83F02A5
	  int	GetAnnotationCode( ) ;
	//##ModelId=46B7B83F02AF
	  void	SetAnnotationCode ( int code ) ;
	//##ModelId=46B7B83F02B1
	  double GetAnnotationSize() ;
	//##ModelId=46B7B83F02B2
	  void	SetAnnotationSize( double size ) ;
	//##ModelId=46B7B83F02B4
	  SGeoRect	GetAnnotationBound() ;
  	  	
    //## Constructors (generated)
	//##ModelId=46B7B83F02B5
      CGeoAnnotation(CFeature* 	m_pOwner);

    //## Destructor (generated)
	//##ModelId=46B7B83F02BF
      ~CGeoAnnotation();


    //## Other Operations (specified)
      //## Operation: GetGeoType%40B00958015D
	//##ModelId=46B7B83F02C0
      int GetGeoType ();


    // Additional Public Declarations
      //## begin CGeoAnnotation%40B009580157.public preserve=yes
      //## end CGeoAnnotation%40B009580157.public

  protected:
    // Additional Protected Declarations
      //## begin CGeoAnnotation%40B009580157.protected preserve=yes
      //## end CGeoAnnotation%40B009580157.protected

  private:
    // Additional Private Declarations
      //## begin CGeoAnnotation%40B009580157.private preserve=yes
      //## end CGeoAnnotation%40B009580157.private

  private: //## implementation
    // Data Members for Class Attributes
	//##ModelId=45502F80005B
      //## Attribute: pString%40B009580167
      //## begin CGeoAnnotation::pString%40B009580167.attr preserve=no  private: char* {U} 0
	//##ModelId=46B7B83F02C2
	SGeoPoint	m_TruePoint ;
	
	//##ModelId=46B7B83F02CF
	SGeoPoint	m_DisplayPoint ;
      //## end CGeoAnnotation::pString%40B009580167.attr

	//##ModelId=46B7B83F02D3
	  int		m_AnnotationCode;

	//##ModelId=46B7B83F02D4
	  double	m_AnnotationSize ;

	//##ModelId=46B7B83F02DF
	  SGeoRect	m_AnnotationRect ;

	//##ModelId=46B7B83F02E3
	  LAYER		m_OwnerLayerID ;
	//##ModelId=46B7B83F02EE
	  OID		m_OwnerFeatureID ;

	//##ModelId=46B7B83F02EF
	  int		m_VSLevel ;

	//##ModelId=46B7B83F02F0
	  int		m_LineCount ;
	//##ModelId=46B7B83F02F1
	  int		m_Direction ;
	 
	//##ModelId=46B7B83F02FD
	  char		m_strLine1[MAX_ANNOTATION_LEN] ;
	//##ModelId=46B7B83F02FE
	  char		m_strLine2[MAX_ANNOTATION_LEN] ;
	//##ModelId=46B7B83F02FF
	  char		m_strLine3[MAX_ANNOTATION_LEN] ;
	//##ModelId=46B7B83F030D
	  char		m_strLine4[MAX_ANNOTATION_LEN] ;

	//##ModelId=46B7B83F030E
	  int		m_iVisibleTypeLevel  ;
	  
};

//## begin CGeoAnnotation%40B009580157.postscript preserve=yes
//## end CGeoAnnotation%40B009580157.postscript

// Class CGeoAnnotation 

//## begin module%40B009580157.epilog preserve=yes
//## end module%40B009580157.epilog


#endif
