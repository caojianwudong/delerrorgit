//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CTimeLimitFieldsInfo%405A57A401BB; Pseudo Package specification

#ifndef CTimeLimitFieldsInfo_h
#define CTimeLimitFieldsInfo_h 1

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


//## begin CTimeLimitFieldsInfo%405A57A401BB.preface preserve=yes
//## end CTimeLimitFieldsInfo%405A57A401BB.preface

//## Class: CTimeLimitFieldsInfo%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83603B9
class __declspec(dllexport) CTimeLimitFieldsInfo: public CAttachFieldsInfo
{
  //## begin CTimeLimitFieldsInfo%405A57A401BB.initialDeclarations preserve=yes
  //## end CTimeLimitFieldsInfo%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7B83603BB
	  bool CheckFieldsInfo();
	//##ModelId=46B7B83603BC
	  int GetObjectTypeIndex();
	//##ModelId=46B7B83603C8
	  int GetObjectIDIndex();
	  virtual int GetAttachFeatureIDIndex();
	  virtual int GetAttachFeatureMeshIDIndex();
	//##ModelId=46B7B83603C9
	  int GetTimeIDIndex();
	  virtual int GetIDIndex();
    //## Constructors (generated)
	//##ModelId=46B7B83603CA
      CTimeLimitFieldsInfo();

    //## Destructor (generated)
	//##ModelId=46B7B83603CB
      ~CTimeLimitFieldsInfo();

  private: //## implementation
    // Data Members for Class Attributes

	//##ModelId=46B7B83603CD
	  int		m_iObjectTypeIndex ;

      //## end CTimeLimitFieldsInfo::m_vectorField%405BD629003E.attr

    // Data Members for Associations

      //## Association: DataAccess::SDE::<unnamed>%405A5BBE014D
      //## Role: CTimeLimitFieldsInfo::<the_Field>%405A5BBE0338
      //## begin CTimeLimitFieldsInfo::<the_Field>%405A5BBE0338.role preserve=no  public: Field { -> UHgN}
      //## end CTimeLimitFieldsInfo::<the_Field>%405A5BBE0338.role

    // Additional Implementation Declarations
      //## begin CTimeLimitFieldsInfo%405A57A401BB.implementation preserve=yes
      //## end CTimeLimitFieldsInfo%405A57A401BB.implementation

};

//## begin CTimeLimitFieldsInfo%405A57A401BB.postscript preserve=yes
//## end CTimeLimitFieldsInfo%405A57A401BB.postscript

// Class CTimeLimitFieldsInfo 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog


#endif
