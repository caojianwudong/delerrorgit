//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CJunctionReferenceFieldsInfo%405A57A401BB; Pseudo Package specification

#ifndef CJunctionReferenceFieldsInfo_h
#define CJunctionReferenceFieldsInfo_h 1

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


//## begin CJunctionReferenceFieldsInfo%405A57A401BB.preface preserve=yes
//## end CJunctionReferenceFieldsInfo%405A57A401BB.preface

//## Class: CJunctionReferenceFieldsInfo%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83E0213
class __declspec(dllexport) CJunctionReferenceFieldsInfo: public CAttachFieldsInfo
{
  //## begin CJunctionReferenceFieldsInfo%405A57A401BB.initialDeclarations preserve=yes
  //## end CJunctionReferenceFieldsInfo%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7B83E0215
	  bool CheckFieldsInfo();
	//##ModelId=46B7B83E0216
	  int GetPOIIndex();
	//##ModelId=46B7B83E0217
	  int	GetMeshIDIndex() ;
	//##ModelId=46B7B83E0222
	  int GetJunctionIndex();
	  virtual int GetAttachFeatureIDIndex();
	  virtual int GetAttachFeatureMeshIDIndex();
	//##ModelId=46B7B83E0223
	  int GetJunctionReferenceIDIndex();
	  virtual int GetIDIndex();
    //## Constructors (generated)
	//##ModelId=46B7B83E0224
      CJunctionReferenceFieldsInfo();

    //## Destructor (generated)
	//##ModelId=46B7B83E0225
      ~CJunctionReferenceFieldsInfo();

    // Additional Public Declarations
      //## begin CJunctionReferenceFieldsInfo%405A57A401BB.public preserve=yes
      //## end CJunctionReferenceFieldsInfo%405A57A401BB.public

  protected:
    // Additional Protected Declarations
      //## begin CJunctionReferenceFieldsInfo%405A57A401BB.protected preserve=yes
      //## end CJunctionReferenceFieldsInfo%405A57A401BB.protected


  private: //## implementation
    // Data Members for Class Attributes

	//##ModelId=46B7B83E0227
	  int		m_iPOIIndex ;

	//##ModelId=46B7B83E0233
	  int		m_iMeshIDIndex ;
      //## end CJunctionReferenceFieldsInfo::m_vectorField%405BD629003E.attr

    // Data Members for Associations

      //## Association: DataAccess::SDE::<unnamed>%405A5BBE014D
      //## Role: CJunctionReferenceFieldsInfo::<the_Field>%405A5BBE0338
      //## begin CJunctionReferenceFieldsInfo::<the_Field>%405A5BBE0338.role preserve=no  public: Field { -> UHgN}
      //## end CJunctionReferenceFieldsInfo::<the_Field>%405A5BBE0338.role

    // Additional Implementation Declarations
      //## begin CJunctionReferenceFieldsInfo%405A57A401BB.implementation preserve=yes
      //## end CJunctionReferenceFieldsInfo%405A57A401BB.implementation

};

//## begin CJunctionReferenceFieldsInfo%405A57A401BB.postscript preserve=yes
//## end CJunctionReferenceFieldsInfo%405A57A401BB.postscript

// Class CJunctionReferenceFieldsInfo 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog


#endif
