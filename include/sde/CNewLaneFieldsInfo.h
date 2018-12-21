//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CNewLaneFieldsInfo%405A57A401BB; Pseudo Package specification

#ifndef CNewLaneFieldsInfo_h
#define CNewLaneFieldsInfo_h 1

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


//## begin CNewLaneFieldsInfo%405A57A401BB.preface preserve=yes
//## end CNewLaneFieldsInfo%405A57A401BB.preface

//## Class: CNewLaneFieldsInfo%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83E01B5
class __declspec(dllexport) CNewLaneFieldsInfo: public CFieldsInfo
{ 
  //## begin CNewLaneFieldsInfo%405A57A401BB.initialDeclarations preserve=yes
  //## end CNewLaneFieldsInfo%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7B83E01C6
	  bool CheckFieldsInfo();
	 
	//##ModelId=46B7B83E01C7
	  int GetJunctionIDIndex();
	  
	//##ModelId=46B7B83E01C8
	  int GetStartRoadIDIndex();
	  int GetStartRoadMeshIDIndex();
	 
	//##ModelId=46B7B83E01C9
	  int GetLaneIDIndex();
	  
	//##ModelId=46B7B83E01CA
	  int GetEndRoadID1Index();
	  int GetEndRoadID2Index();
	  int GetEndRoadID3Index();
	  int GetEndRoadID4Index();
	  int GetEndRoadID5Index();
	  int GetEndRoadID6Index();
	  int GetEndRoadID7Index();
	  int GetEndRoadID8Index();
	  int GetEndRoadID9Index();
	  int GetEndRoadID10Index();
	  int GetEndRoadID11Index();
	  int GetEndRoadID12Index();
	  int GetEndRoadID13Index();
	  int GetEndRoadID14Index();
	  int GetEndRoadID15Index();
	  int GetEndRoadID16Index();

	  MESH GetEndRoadMeshID1Index();
	  MESH GetEndRoadMeshID2Index();
	  MESH GetEndRoadMeshID3Index();
	  MESH GetEndRoadMeshID4Index();
	  MESH GetEndRoadMeshID5Index();
	  MESH GetEndRoadMeshID6Index();
	  MESH GetEndRoadMeshID7Index();
	  MESH GetEndRoadMeshID8Index();
	  MESH GetEndRoadMeshID9Index();
	  MESH GetEndRoadMeshID10Index();
	  MESH GetEndRoadMeshID11Index();
	  MESH GetEndRoadMeshID12Index();
	  MESH GetEndRoadMeshID13Index();
	  MESH GetEndRoadMeshID14Index();
	  MESH GetEndRoadMeshID15Index();
	  MESH GetEndRoadMeshID16Index();
	  
    //## Constructors (generated)
	//##ModelId=46B7B83E01DA
      CNewLaneFieldsInfo();

    //## Destructor (generated)
	//##ModelId=46B7B83E01DB
      ~CNewLaneFieldsInfo();

    // Additional Public Declarations
      //## begin CNewLaneFieldsInfo%405A57A401BB.public preserve=yes
      //## end CNewLaneFieldsInfo%405A57A401BB.public

  protected:
    // Additional Protected Declarations
      //## begin CNewLaneFieldsInfo%405A57A401BB.protected preserve=yes
      //## end CNewLaneFieldsInfo%405A57A401BB.protected

  private:


  private: //## implementation
    // Data Members for Class Attributes

	//##ModelId=46B7B83E01E4
	  int		m_iLaneIDIndex ;

	//##ModelId=46B7B83E01E5
	  int		m_iStartRoadIDIndex ;
	  int		m_iStartRoadMeshIDIndex ;

	//##ModelId=46B7B83E01E6
	  int		m_iJunctionIDIndex ;

	  int		m_iEndRoadID1Index ;
	  int		m_iEndRoadID2Index ;
	  int		m_iEndRoadID3Index ;
	  int		m_iEndRoadID4Index ;
	  int		m_iEndRoadID5Index ;
	  int		m_iEndRoadID6Index ;
	  int		m_iEndRoadID7Index ;
	  int		m_iEndRoadID8Index ;
	  int		m_iEndRoadID9Index ;
	  int		m_iEndRoadID10Index ;
	  int		m_iEndRoadID11Index ;
	  int		m_iEndRoadID12Index ;
	  int		m_iEndRoadID13Index ;
	  int		m_iEndRoadID14Index ;
	  int		m_iEndRoadID15Index ;
	  int		m_iEndRoadID16Index ;

	  MESH		m_iEndRoadMeshID1Index ;
	  MESH		m_iEndRoadMeshID2Index ;
	  MESH		m_iEndRoadMeshID3Index ;
	  MESH		m_iEndRoadMeshID4Index ;
	  MESH		m_iEndRoadMeshID5Index ;
	  MESH		m_iEndRoadMeshID6Index ;
	  MESH		m_iEndRoadMeshID7Index ;
	  MESH		m_iEndRoadMeshID8Index ;
	  MESH		m_iEndRoadMeshID9Index ;
	  MESH		m_iEndRoadMeshID10Index ;
	  MESH		m_iEndRoadMeshID11Index ;
	  MESH		m_iEndRoadMeshID12Index ;
	  MESH		m_iEndRoadMeshID13Index ;
	  MESH		m_iEndRoadMeshID14Index ;
	  MESH		m_iEndRoadMeshID15Index ;
	  MESH		m_iEndRoadMeshID16Index ;

     //## end CNewLaneFieldsInfo::m_vectorField%405BD629003E.attr

    // Data Members for Associations

      //## Association: DataAccess::SDE::<unnamed>%405A5BBE014D
      //## Role: CNewLaneFieldsInfo::<the_Field>%405A5BBE0338
      //## begin CNewLaneFieldsInfo::<the_Field>%405A5BBE0338.role preserve=no  public: Field { -> UHgN}
      //## end CNewLaneFieldsInfo::<the_Field>%405A5BBE0338.role

    // Additional Implementation Declarations
      //## begin CNewLaneFieldsInfo%405A57A401BB.implementation preserve=yes
      //## end CNewLaneFieldsInfo%405A57A401BB.implementation

};

//## begin CNewLaneFieldsInfo%405A57A401BB.postscript preserve=yes
//## end CNewLaneFieldsInfo%405A57A401BB.postscript

// Class CNewLaneFieldsInfo 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog


#endif
