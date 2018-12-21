//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CJunctionViewFieldsInfo%405A57A401BB; Pseudo Package specification

#ifndef CJunctionViewFieldsInfo_h
#define CJunctionViewFieldsInfo_h 1

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

//## end module%405A57A401BB.additionalDeclarations


//## begin CJunctionViewFieldsInfo%405A57A401BB.preface preserve=yes
//## end CJunctionViewFieldsInfo%405A57A401BB.preface

//## Class: CJunctionViewFieldsInfo%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B836038B
class __declspec(dllexport) CJunctionViewFieldsInfo: public CAttachRoadFieldsInfo
{ 
  //## begin CJunctionViewFieldsInfo%405A57A401BB.initialDeclarations preserve=yes
  //## end CJunctionViewFieldsInfo%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7B836039A
	  virtual bool CheckFieldsInfo();
	 
	//##ModelId=46B7B836039B
	  int GetCompoundJunctionIDIndex();
	  virtual int GetAttachFeatureIDIndex();
	  virtual int GetAttachFeatureMeshIDIndex();
	  
	//##ModelId=46B7B836039C
	  virtual int GetStartRoadIDIndex();
	  virtual int GetEndRoadIDIndex();
	  virtual int GetStartRoadMeshIDIndex();
	  virtual int GetEndRoadMeshIDIndex();
	 
	//##ModelId=46B7B836039E
	  int GetJunctionViewIDIndex();
	  virtual int GetIDIndex();
    //## Constructors (generated)
	//##ModelId=46B7B836039F
      CJunctionViewFieldsInfo();

    //## Destructor (generated)
	//##ModelId=46B7B83603A0
      ~CJunctionViewFieldsInfo();

    // Additional Public Declarations
      //## begin CJunctionViewFieldsInfo%405A57A401BB.public preserve=yes
      //## end CJunctionViewFieldsInfo%405A57A401BB.public
};

//## begin CJunctionViewFieldsInfo%405A57A401BB.postscript preserve=yes
//## end CJunctionViewFieldsInfo%405A57A401BB.postscript

// Class CJunctionViewFieldsInfo 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog


#endif
