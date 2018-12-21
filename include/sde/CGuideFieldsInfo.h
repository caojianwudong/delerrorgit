//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CGuideFieldsInfo%405A57A401BB; Pseudo Package specification

#ifndef CGuideFieldsInfo_h
#define CGuideFieldsInfo_h 1

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


//## begin CGuideFieldsInfo%405A57A401BB.preface preserve=yes
//## end CGuideFieldsInfo%405A57A401BB.preface

//## Class: CGuideFieldsInfo%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B836038B
class __declspec(dllexport) CGuideFieldsInfo: public CAttachRoadFieldsInfo
{ 
  //## begin CGuideFieldsInfo%405A57A401BB.initialDeclarations preserve=yes
  //## end CGuideFieldsInfo%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7B836039A
	  virtual bool CheckFieldsInfo();
	 
	//##ModelId=46B7B836039B
	  int GetCompoundJunctionIDIndex();
	  virtual int GetAttachFeatureIDIndex();
	  virtual int GetAttachFeatureMeshIDIndex();

	  virtual int GetStartRoadIDIndex();
	  virtual int GetEndRoadIDIndex();
	  virtual int GetStartRoadMeshIDIndex();
	  virtual int GetEndRoadMeshIDIndex();

	//##ModelId=46B7B836039E
	  int GetGuideIDIndex();
	  virtual int GetIDIndex();
    //## Constructors (generated)
	//##ModelId=46B7B836039F
      CGuideFieldsInfo();

    //## Destructor (generated)
	//##ModelId=46B7B83603A0
      ~CGuideFieldsInfo();

    // Additional Public Declarations
      //## begin CGuideFieldsInfo%405A57A401BB.public preserve=yes
      //## end CGuideFieldsInfo%405A57A401BB.public

  private: //## implementation
    // Data Members for Class Attributes
    // Data Members for Associations

      //## Association: DataAccess::SDE::<unnamed>%405A5BBE014D
      //## Role: CGuideFieldsInfo::<the_Field>%405A5BBE0338
      //## begin CGuideFieldsInfo::<the_Field>%405A5BBE0338.role preserve=no  public: Field { -> UHgN}
      //## end CGuideFieldsInfo::<the_Field>%405A5BBE0338.role

    // Additional Implementation Declarations
      //## begin CGuideFieldsInfo%405A57A401BB.implementation preserve=yes
      //## end CGuideFieldsInfo%405A57A401BB.implementation

};

//## begin CGuideFieldsInfo%405A57A401BB.postscript preserve=yes
//## end CGuideFieldsInfo%405A57A401BB.postscript

// Class CGuideFieldsInfo 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog


#endif
