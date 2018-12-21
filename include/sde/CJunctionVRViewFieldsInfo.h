//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CJunctionVRViewFieldsInfo%405A57A401BB; Pseudo Package specification

#ifndef CJunctionVRViewFieldsInfo_h
#define CJunctionVRViewFieldsInfo_h 1

//## begin module%405A57A401BB.additionalIncludes preserve=no
//## end module%405A57A401BB.additionalIncludes

//## begin module%405A57A401BB.includes preserve=yes
//## end module%405A57A401BB.includes

#include "CFieldsInfo.h"
//## begin module%405A57A401BB.additionalDeclarations preserve=yes
#include <string>
#include "commondef.h"	// Added by ClassView
#include "CFields.h"	// Added by ClassView

//## end module%405A57A401BB.additionalDeclarations


//## begin CJunctionVRViewFieldsInfo%405A57A401BB.preface preserve=yes
//## end CJunctionVRViewFieldsInfo%405A57A401BB.preface

//## Class: CJunctionVRViewFieldsInfo%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B836038B
class __declspec(dllexport) CJunctionVRViewFieldsInfo: public CFieldsInfo
{ 
  //## begin CJunctionVRViewFieldsInfo%405A57A401BB.initialDeclarations preserve=yes
  //## end CJunctionVRViewFieldsInfo%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7B836039A
	  bool CheckFieldsInfo();
	 
	//##ModelId=46B7B836039B
	  int GetCompoundJunctionIDIndex();
	  
	//##ModelId=46B7B836039C
	  int GetStartRoadIDIndex();
	  
	//##ModelId=46B7B836039D
	  int GetEndRoadIDIndex();
	 
	//##ModelId=46B7B836039C
	  int GetStartRoadMeshIDIndex();
	  
	//##ModelId=46B7B836039D
	  int GetEndRoadMeshIDIndex();
	 
	//##ModelId=46B7B836039E
	  int GetJunctionVRViewIDIndex();
    //## Constructors (generated)
	//##ModelId=46B7B836039F
      CJunctionVRViewFieldsInfo();

    //## Destructor (generated)
	//##ModelId=46B7B83603A0
      ~CJunctionVRViewFieldsInfo();

    // Additional Public Declarations
      //## begin CJunctionVRViewFieldsInfo%405A57A401BB.public preserve=yes
      //## end CJunctionVRViewFieldsInfo%405A57A401BB.public

  protected:
    // Additional Protected Declarations
      //## begin CJunctionVRViewFieldsInfo%405A57A401BB.protected preserve=yes
      //## end CJunctionVRViewFieldsInfo%405A57A401BB.protected

  private:


  private: //## implementation
    // Data Members for Class Attributes

	//##ModelId=46B7B83603A9
	  int		m_iTurnIDIndex ;

	//##ModelId=46B7B83603AA
	  int		m_iStartRoadIDIndex ;
	  int		m_iStartRoadMeshIDIndex ;

	//##ModelId=46B7B83603AB
	  int		m_iEndRoadIDIndex ;
	  int		m_iEndRoadMeshIDIndex ;

	//##ModelId=46B7B83603AC
	  int		m_iCompoundJuncIDIndex ;
      //## end CJunctionVRViewFieldsInfo::m_vectorField%405BD629003E.attr

    // Data Members for Associations

      //## Association: DataAccess::SDE::<unnamed>%405A5BBE014D
      //## Role: CJunctionVRViewFieldsInfo::<the_Field>%405A5BBE0338
      //## begin CJunctionVRViewFieldsInfo::<the_Field>%405A5BBE0338.role preserve=no  public: Field { -> UHgN}
      //## end CJunctionVRViewFieldsInfo::<the_Field>%405A5BBE0338.role

    // Additional Implementation Declarations
      //## begin CJunctionVRViewFieldsInfo%405A57A401BB.implementation preserve=yes
      //## end CJunctionVRViewFieldsInfo%405A57A401BB.implementation

};

//## begin CJunctionVRViewFieldsInfo%405A57A401BB.postscript preserve=yes
//## end CJunctionVRViewFieldsInfo%405A57A401BB.postscript

// Class CJunctionVRViewFieldsInfo 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog


#endif
