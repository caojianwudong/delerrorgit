//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CNewDirectionFieldsInfo%405A57A401BB; Pseudo Package specification

#ifndef CNewDirectionFieldsInfo_h
#define CNewDirectionFieldsInfo_h 1

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


//## begin CNewDirectionFieldsInfo%405A57A401BB.preface preserve=yes
//## end CNewDirectionFieldsInfo%405A57A401BB.preface

//## Class: CNewDirectionFieldsInfo%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B8400271
class __declspec(dllexport) CNewDirectionFieldsInfo: public CFieldsInfo
{ 
  //## begin CNewDirectionFieldsInfo%405A57A401BB.initialDeclarations preserve=yes
  //## end CNewDirectionFieldsInfo%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7B8400273
	  bool CheckFieldsInfo();
	 
	//##ModelId=46B7B8400280
	  int GetCompoundJunctionIDIndex();
	
	//##ModelId=46B7B8400281
	  int GetJunctionIDIndex();
	  
	//##ModelId=46B7B8400282
	  int GetStartRoadIDIndex();
	  int GetStartRoadMeshIDIndex();
	 
	//##ModelId=46B7B8400283
	  int GetDirectionIDIndex();
	  
	  int GetEndRoadID1Index();
	  int GetEndRoadID2Index();
	  int GetEndRoadID3Index();
	  int GetEndRoadID4Index();
	  int GetEndRoadID5Index();
	  int GetEndRoadID6Index();
	  int GetEndRoadID7Index();
	  int GetEndRoadID8Index();
	  MESH GetEndRoadMeshID1Index();
	  MESH GetEndRoadMeshID2Index();
	  MESH GetEndRoadMeshID3Index();
	  MESH GetEndRoadMeshID4Index();
	  MESH GetEndRoadMeshID5Index();
	  MESH GetEndRoadMeshID6Index();
	  MESH GetEndRoadMeshID7Index();
	  MESH GetEndRoadMeshID8Index();
	  
    //## Constructors (generated)
	//##ModelId=46B7B8400294
      CNewDirectionFieldsInfo();

    //## Destructor (generated)
	//##ModelId=46B7B8400295
      ~CNewDirectionFieldsInfo();

    // Additional Public Declarations
      //## begin CNewDirectionFieldsInfo%405A57A401BB.public preserve=yes
      //## end CNewDirectionFieldsInfo%405A57A401BB.public

  protected:
    // Additional Protected Declarations
      //## begin CNewDirectionFieldsInfo%405A57A401BB.protected preserve=yes
      //## end CNewDirectionFieldsInfo%405A57A401BB.protected

  private:


  private: //## implementation
    // Data Members for Class Attributes

	//##ModelId=46B7B8400296
	  int		m_iDirectionIDIndex ;

	//##ModelId=46B7B840029F
	  int		m_iStartRoadIDIndex ;
	  int		m_iStartRoadMeshIDIndex ;

	//##ModelId=46B7B84002A0
	  int		m_iJunctionIDIndex ;

	//##ModelId=46B7B84002A1
	  int		m_iCompoundJuncIDIndex ;

	//##ModelId=46B7B84002A2
	  int		m_iEndRoadID1Index ;
	  int		m_iEndRoadID2Index ;
	  int		m_iEndRoadID3Index ;
	  int		m_iEndRoadID4Index ;
	  int		m_iEndRoadID5Index ;
	  int		m_iEndRoadID6Index ;
	  int		m_iEndRoadID7Index ;
	  int		m_iEndRoadID8Index ;
	  MESH		m_iEndRoadMeshID1Index ;
	  MESH		m_iEndRoadMeshID2Index ;
	  MESH		m_iEndRoadMeshID3Index ;
	  MESH		m_iEndRoadMeshID4Index ;
	  MESH		m_iEndRoadMeshID5Index ;
	  MESH		m_iEndRoadMeshID6Index ;
	  MESH		m_iEndRoadMeshID7Index ;
	  MESH		m_iEndRoadMeshID8Index ;
     //## end CNewDirectionFieldsInfo::m_vectorField%405BD629003E.attr

    // Data Members for Associations

      //## Association: DataAccess::SDE::<unnamed>%405A5BBE014D
      //## Role: CNewDirectionFieldsInfo::<the_Field>%405A5BBE0338
      //## begin CNewDirectionFieldsInfo::<the_Field>%405A5BBE0338.role preserve=no  public: Field { -> UHgN}
      //## end CNewDirectionFieldsInfo::<the_Field>%405A5BBE0338.role

    // Additional Implementation Declarations
      //## begin CNewDirectionFieldsInfo%405A57A401BB.implementation preserve=yes
      //## end CNewDirectionFieldsInfo%405A57A401BB.implementation

};

//## begin CNewDirectionFieldsInfo%405A57A401BB.postscript preserve=yes
//## end CNewDirectionFieldsInfo%405A57A401BB.postscript

// Class CNewDirectionFieldsInfo 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog


#endif
