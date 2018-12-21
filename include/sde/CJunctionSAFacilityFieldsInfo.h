//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CJunctionSAFacilityFieldsInfo%405A57A401BB; Pseudo Package specification

#ifndef CJunctionSAFacilityFieldsInfo_h
#define CJunctionSAFacilityFieldsInfo_h 1

//## begin module%405A57A401BB.additionalIncludes preserve=no
//## end module%405A57A401BB.additionalIncludes

//## begin module%405A57A401BB.includes preserve=yes
//## end module%405A57A401BB.includes

#include "CFieldsInfo.h"
#include "CAttachFieldsInfo.h"
//## begin module%405A57A401BB.additionalDeclarations preserve=yes
#include <string>
#include "commondef.h"	// Added by ClassView
#include "CFields.h"	// Added by ClassView
using namespace std;
//## end module%405A57A401BB.additionalDeclarations


//## begin CJunctionSAFacilityFieldsInfo%405A57A401BB.preface preserve=yes
//## end CJunctionSAFacilityFieldsInfo%405A57A401BB.preface

//## Class: CJunctionSAFacilityFieldsInfo%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83E0213
class __declspec(dllexport) CJunctionSAFacilityFieldsInfo: public CAttachFieldsInfo
{
  //## begin CJunctionSAFacilityFieldsInfo%405A57A401BB.initialDeclarations preserve=yes
  //## end CJunctionSAFacilityFieldsInfo%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7B83E0215
	  bool CheckFieldsInfo();

	  int GetJunctionIndex();
	  virtual int GetAttachFeatureIDIndex();
	  virtual int GetAttachFeatureMeshIDIndex();
	//##ModelId=46B7B83E0223
	  virtual int GetIDIndex();
    //## Constructors (generated)
	//##ModelId=46B7B83E0224
      CJunctionSAFacilityFieldsInfo();

    //## Destructor (generated)
	//##ModelId=46B7B83E0225
      ~CJunctionSAFacilityFieldsInfo();

    // Additional Public Declarations
      //## begin CJunctionSAFacilityFieldsInfo%405A57A401BB.public preserve=yes
      //## end CJunctionSAFacilityFieldsInfo%405A57A401BB.public

  protected:
    // Additional Protected Declarations
      //## begin CJunctionSAFacilityFieldsInfo%405A57A401BB.protected preserve=yes
      //## end CJunctionSAFacilityFieldsInfo%405A57A401BB.protected

};

//## begin CJunctionSAFacilityFieldsInfo%405A57A401BB.postscript preserve=yes
//## end CJunctionSAFacilityFieldsInfo%405A57A401BB.postscript

// Class CJunctionSAFacilityFieldsInfo 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog


#endif
