//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%4070026A0236.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4070026A0236.cm

//## begin module%4070026A0236.cp preserve=no
//## end module%4070026A0236.cp

//## Module: CGeoPoints%4070026A0236; Pseudo Package specification

#ifndef CGeoPoints_h
#define CGeoPoints_h 1

//## begin module%4070026A0236.additionalIncludes preserve=no
//## end module%4070026A0236.additionalIncludes

//## begin module%4070026A0236.includes preserve=yes
#include "CGeopoint.h"
#include "commondef.h"	// Added by ClassView
//## end module%4070026A0236.includes

//## begin module%4070026A0236.additionalDeclarations preserve=yes
//## end module%4070026A0236.additionalDeclarations


//## begin CGeoPoints%4070026A0236.preface preserve=yes
//## end CGeoPoints%4070026A0236.preface

//## Class: CGeoPoints%4070026A0236
//## Category: DataAccess::CGeoO%407001E50071
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83E03D9
class __declspec(dllexport) CGeoPoints 
{
  //## begin CGeoPoints%4070026A0236.initialDeclarations preserve=yes
  //## end CGeoPoints%4070026A0236.initialDeclarations

  public:
	//##ModelId=46B7B83F0000
	  SGeoRect GetBound();
	//##ModelId=46B7B83F0001
	  void RevesePoints();
    //## Constructors (generated)
	//##ModelId=46B7B83F0002
      CGeoPoints();

    //## Destructor (generated)
	//##ModelId=46B7B83F0003
      ~CGeoPoints();


    //## Other Operations (specified)
      //## Operation: GetPoint%4070038E0340
	//##ModelId=46B7B83F0004
      SGeoPoint GetPoint (int index);

      //## Operation: GetPoint%40794C22003E
	//##ModelId=46B7B83F000F
      void GetPoint (int index, double& x, double& y);

      //## Operation: GetPtCount%40700409035F
	//##ModelId=46B7B83F0013
      int GetPtCount ();

      //## Operation: SetPointCount%4070052D0014
	//##ModelId=46B7B83F0014
      void SetPointCount (int nPtCount);

      //## Operation: SetPoint%4079436D009C
	//##ModelId=46B7B83F0016
      void SetPoint (int index, double x, double y);

      //## Operation: SetPoint%4079439803C8
	//##ModelId=46B7B83F0022
      void SetPoint (int index, SGeoPoint point);

    // Additional Public Declarations
      //## begin CGeoPoints%4070026A0236.public preserve=yes
	//##ModelId=46B7B83F0025
	  bool ResetPoints(  VECTOR_PointArray point_array  );
      //## end CGeoPoints%4070026A0236.public
	//##ModelId=46B7B83F0027
	  void GetPointArray(  VECTOR_PointArray & point_array  );

  protected:
    // Additional Protected Declarations
      //## begin CGeoPoints%4070026A0236.protected preserve=yes
      //## end CGeoPoints%4070026A0236.protected

  private:
    // Additional Private Declarations
      //## begin CGeoPoints%4070026A0236.private preserve=yes
      //## end CGeoPoints%4070026A0236.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: pArrayX%4070035700DF
      //## begin CGeoPoints::pArrayX%4070035700DF.attr preserve=no  private: double* {U} 0
	//##ModelId=46B7B83F002F
      double* pArrayX;
      //## end CGeoPoints::pArrayX%4070035700DF.attr

      //## Attribute: pArrayY%4070037101E8
      //## begin CGeoPoints::pArrayY%4070037101E8.attr preserve=no  private: double* {U} 0
	//##ModelId=46B7B83F0030
      double* pArrayY;
      //## end CGeoPoints::pArrayY%4070037101E8.attr

      //## Attribute: nPtCount%4070037A0330
      //## begin CGeoPoints::nPtCount%4070037A0330.attr preserve=no  private: double {U} 0
	//##ModelId=46B7B83F0031
      int nPtCount;
      //## end CGeoPoints::nPtCount%4070037A0330.attr

    // Additional Implementation Declarations
      //## begin CGeoPoints%4070026A0236.implementation preserve=yes
      //## end CGeoPoints%4070026A0236.implementation

};

//## begin CGeoPoints%4070026A0236.postscript preserve=yes
//## end CGeoPoints%4070026A0236.postscript

// Class CGeoPoints 

//## begin module%4070026A0236.epilog preserve=yes
//## end module%4070026A0236.epilog


#endif
