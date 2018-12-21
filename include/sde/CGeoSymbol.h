//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%40B009580157.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40B009580157.cm

//## begin module%40B009580157.cp preserve=no
//## end module%40B009580157.cp

//## Module: CGeoSymbol%40B009580157; Pseudo Package specification

#ifndef CGeoSymbol_h
#define CGeoSymbol_h 1

//## begin module%40B009580157.additionalIncludes preserve=no
//## end module%40B009580157.additionalIncludes

//## begin module%40B009580157.includes preserve=yes
//## end module%40B009580157.includes

#include "CGeometry.h"
#include "CGeopoints.h"
//## begin module%40B009580157.additionalDeclarations preserve=yes
//## end module%40B009580157.additionalDeclarations
class CFeature ;
//## begin CGeoSymbol%40B009580157.preface preserve=yes
//## end CGeoSymbol%40B009580157.preface

//## Class: CGeoSymbol%40B009580157
//## Category: CGeometry%407001E50071
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83E0242
class __declspec(dllexport) CGeoSymbol : public CGeometry  //## Inherits: <unnamed>%40B0096C035B
{
  //## begin CGeoSymbol%40B009580157.initialDeclarations preserve=yes
  //## end CGeoSymbol%40B009580157.initialDeclarations

  public:
	//##ModelId=46B7B83E0244
	  void	SetOwnerLayerID ( LAYER layer_id ) ;
	//##ModelId=46B7B83E0246
	  LAYER	GetOwnerLayerID() ;
	//##ModelId=46B7B83E0251
	  void	SetVSLevel ( int level ) ;
	//##ModelId=46B7B83E0253
	  int	GetVSLevel ( ) ;
	//##ModelId=46B7B83E0254
	  void	SetOwnerFeatureID ( OID feature_id ) ;
	//##ModelId=46B7B83E0256
	  OID	GetOwnerFeatureID() ;

	//##ModelId=46B7B83E0257
	  void SetTruePoint( SGeoPoint point );
	//##ModelId=46B7B83E0259
	  SGeoPoint GetTruePoint();
	//##ModelId=46B7B83E0261
 	  void SetDisplayPoint( SGeoPoint point );
	//##ModelId=46B7B83E0263
	  SGeoPoint GetDisplayPoint();
	//##ModelId=46B7B83E0264
	  int	GetSymbolCode( ) ;
	//##ModelId=46B7B83E0265
	  void	SetSymbolCode ( int code ) ;
	//##ModelId=46B7B83E0267
	  double GetSymbolSize() ;
	//##ModelId=46B7B83E0268
	  void	SetSymbolSize( double size ) ;
	//##ModelId=46B7B83E026A
	  SGeoRect	GetSymbolBound() ;
  	  	
    //## Constructors (generated)
	//##ModelId=46B7B83E0271
      CGeoSymbol(CFeature* 	m_pOwner);

    //## Destructor (generated)
	//##ModelId=46B7B83E0273
      ~CGeoSymbol();


    //## Other Operations (specified)
      //## Operation: GetGeoType%40B00958015D
	//##ModelId=46B7B83E0274
      int GetGeoType ();


    // Additional Public Declarations
      //## begin CGeoSymbol%40B009580157.public preserve=yes
      //## end CGeoSymbol%40B009580157.public

  protected:
    // Additional Protected Declarations
      //## begin CGeoSymbol%40B009580157.protected preserve=yes
      //## end CGeoSymbol%40B009580157.protected

  private:
    // Additional Private Declarations
      //## begin CGeoSymbol%40B009580157.private preserve=yes
      //## end CGeoSymbol%40B009580157.private

  private: //## implementation
    // Data Members for Class Attributes
	//##ModelId=45502F80005B
      //## Attribute: pString%40B009580167
      //## begin CGeoSymbol::pString%40B009580167.attr preserve=no  private: char* {U} 0
	//##ModelId=46B7B83E0276
	SGeoPoint	m_TruePoint ;
	
	//##ModelId=46B7B83E0281
	SGeoPoint	m_DisplayPoint ;
      //## end CGeoSymbol::pString%40B009580167.attr

	//##ModelId=46B7B83E0285
	  int		m_SymbolCode;

	//##ModelId=46B7B83E0286
	  double	m_SymbolSize ;

	//##ModelId=46B7B83E0291
	  SGeoRect	m_SymbolRect ;

	//##ModelId=46B7B83E0295
	  LAYER		m_OwnerLayerID ;
	//##ModelId=46B7B83E029F
	  OID		m_OwnerFeatureID ;

	//##ModelId=46B7B83E02A0
	  int		m_VSLevel ;

	  
};

//## begin CGeoSymbol%40B009580157.postscript preserve=yes
//## end CGeoSymbol%40B009580157.postscript

// Class CGeoSymbol 

//## begin module%40B009580157.epilog preserve=yes
//## end module%40B009580157.epilog


#endif
