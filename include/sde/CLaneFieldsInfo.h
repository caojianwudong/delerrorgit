//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CLaneFieldsInfo%405A57A401BB; Pseudo Package specification

#ifndef CLaneFieldsInfo_h
#define CLaneFieldsInfo_h 1

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


//## begin CLaneFieldsInfo%405A57A401BB.preface preserve=yes
//## end CLaneFieldsInfo%405A57A401BB.preface

//## Class: CLaneFieldsInfo%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83E01B5
class __declspec(dllexport) CLaneFieldsInfo: public CAttachFieldsInfo
{ 
  //## begin CLaneFieldsInfo%405A57A401BB.initialDeclarations preserve=yes
  //## end CLaneFieldsInfo%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7B83E01C6
	  virtual bool CheckFieldsInfo();
	 
	//##ModelId=46B7B83E01C7
	  int GetJunctionIDIndex();
	  virtual int GetAttachFeatureIDIndex();
	  virtual int GetAttachFeatureMeshIDIndex();
	  
	  int GetStartRoadIDIndex();
	  //int GetStartRoadMeshIDIndex();

	//##ModelId=46B7B83E01C9
	  int GetLaneIDIndex();
	  virtual int GetIDIndex();
	  
	//##ModelId=46B7B83E01CA
	  int GetEndRoadID1Index();
	//##ModelId=46B7B83E01CB
	  int GetEndRoadID2Index();
	//##ModelId=46B7B83E01D4
	  int GetEndRoadID3Index();
	//##ModelId=46B7B83E01D5
	  int GetEndRoadID4Index();
	//##ModelId=46B7B83E01D6
	  int GetEndRoadID5Index();
	//##ModelId=46B7B83E01D7
	  int GetEndRoadID6Index();
	//##ModelId=46B7B83E01D8
	  int GetEndRoadID7Index();
	//##ModelId=46B7B83E01D9
	  int GetEndRoadID8Index();
	  int GetEndRoadID9Index();
	  int GetEndRoadID10Index();
	  int GetEndRoadID11Index();
	  int GetEndRoadID12Index();
	  int GetEndRoadID13Index();
	  int GetEndRoadID14Index();
	  int GetEndRoadID15Index();
	  int GetEndRoadID16Index();
	  
    //## Constructors (generated)
	//##ModelId=46B7B83E01DA
      CLaneFieldsInfo();

    //## Destructor (generated)
	//##ModelId=46B7B83E01DB
      ~CLaneFieldsInfo();

    // Additional Public Declarations
      //## begin CLaneFieldsInfo%405A57A401BB.public preserve=yes
      //## end CLaneFieldsInfo%405A57A401BB.public

  protected:
    // Additional Protected Declarations
      //## begin CLaneFieldsInfo%405A57A401BB.protected preserve=yes
      //## end CLaneFieldsInfo%405A57A401BB.protected

  private: //## implementation
    // Data Members for Class Attributes

	//##ModelId=46B7B83E01E5
	  int		m_iStartRoadIDIndex;
	  int		m_iStartRoadMeshIDIndex;

	//##ModelId=46B7B83E01E7
	  int		m_iEndRoadID1Index ;
	//##ModelId=46B7B83E01F4
	  int		m_iEndRoadID2Index ;
	//##ModelId=46B7B83E01F5
	  int		m_iEndRoadID3Index ;
	//##ModelId=46B7B83E01F6
	  int		m_iEndRoadID4Index ;
	//##ModelId=46B7B83E01F7
	  int		m_iEndRoadID5Index ;
	//##ModelId=46B7B83E0203
	  int		m_iEndRoadID6Index ;
	//##ModelId=46B7B83E0204
	  int		m_iEndRoadID7Index ;
	//##ModelId=46B7B83E0205
	  int		m_iEndRoadID8Index ;
	  int		m_iEndRoadID9Index ;
	  int		m_iEndRoadID10Index ;
	  int		m_iEndRoadID11Index ;
	  int		m_iEndRoadID12Index ;
	  int		m_iEndRoadID13Index ;
	  int		m_iEndRoadID14Index ;
	  int		m_iEndRoadID15Index ;
	  int		m_iEndRoadID16Index ;

     //## end CLaneFieldsInfo::m_vectorField%405BD629003E.attr

    // Data Members for Associations

      //## Association: DataAccess::SDE::<unnamed>%405A5BBE014D
      //## Role: CLaneFieldsInfo::<the_Field>%405A5BBE0338
      //## begin CLaneFieldsInfo::<the_Field>%405A5BBE0338.role preserve=no  public: Field { -> UHgN}
      //## end CLaneFieldsInfo::<the_Field>%405A5BBE0338.role

    // Additional Implementation Declarations
      //## begin CLaneFieldsInfo%405A57A401BB.implementation preserve=yes
      //## end CLaneFieldsInfo%405A57A401BB.implementation

};

//## begin CLaneFieldsInfo%405A57A401BB.postscript preserve=yes
//## end CLaneFieldsInfo%405A57A401BB.postscript

// Class CLaneFieldsInfo 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog


#endif
