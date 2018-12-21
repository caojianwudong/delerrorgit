//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CVehicleLimitFieldsInfo%405A57A401BB; Pseudo Package specification

#ifndef CVehicleLimitFieldsInfo_h
#define CVehicleLimitFieldsInfo_h 1

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


//## begin CVehicleLimitFieldsInfo%405A57A401BB.preface preserve=yes
//## end CVehicleLimitFieldsInfo%405A57A401BB.preface

//## Class: CVehicleLimitFieldsInfo%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B836033D
class __declspec(dllexport) CVehicleLimitFieldsInfo: public CAttachFieldsInfo
{
  //## begin CVehicleLimitFieldsInfo%405A57A401BB.initialDeclarations preserve=yes
  //## end CVehicleLimitFieldsInfo%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7B836033F
	  bool CheckFieldsInfo();
	//##ModelId=46B7B836034B
	  int GetObjectTypeIndex();
	//##ModelId=46B7B836034C
	  int GetObjectIDIndex();
	  virtual int GetAttachFeatureIDIndex();
	  virtual int GetAttachFeatureMeshIDIndex();
	//##ModelId=46B7B836034D
	  int GetVehicleIDIndex();
	  virtual GetIDIndex();
    //## Constructors (generated)
	//##ModelId=46B7B836034E
      CVehicleLimitFieldsInfo();

    //## Destructor (generated)
	//##ModelId=46B7B836034F
      ~CVehicleLimitFieldsInfo();

  private: //## implementation
    // Data Members for Class Attributes

	//##ModelId=46B7B836037A
	  int		m_iObjectTypeIndex ;

      //## end CVehicleLimitFieldsInfo::m_vectorField%405BD629003E.attr

    // Data Members for Associations

      //## Association: DataAccess::SDE::<unnamed>%405A5BBE014D
      //## Role: CVehicleLimitFieldsInfo::<the_Field>%405A5BBE0338
      //## begin CVehicleLimitFieldsInfo::<the_Field>%405A5BBE0338.role preserve=no  public: Field { -> UHgN}
      //## end CVehicleLimitFieldsInfo::<the_Field>%405A5BBE0338.role

    // Additional Implementation Declarations
      //## begin CVehicleLimitFieldsInfo%405A57A401BB.implementation preserve=yes
      //## end CVehicleLimitFieldsInfo%405A57A401BB.implementation

};

//## begin CVehicleLimitFieldsInfo%405A57A401BB.postscript preserve=yes
//## end CVehicleLimitFieldsInfo%405A57A401BB.postscript

// Class CVehicleLimitFieldsInfo 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog


#endif
