//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CDirectionFieldsInfo%405A57A401BB; Pseudo Package specification

#ifndef CDirectionFieldsInfo_h
#define CDirectionFieldsInfo_h 1

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


//## begin CDirectionFieldsInfo%405A57A401BB.preface preserve=yes
//## end CDirectionFieldsInfo%405A57A401BB.preface

//## Class: CDirectionFieldsInfo%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B8400271
class __declspec(dllexport) CDirectionFieldsInfo: public CAttachFieldsInfo
{ 
  //## begin CDirectionFieldsInfo%405A57A401BB.initialDeclarations preserve=yes
  //## end CDirectionFieldsInfo%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7B8400273
	  virtual bool CheckFieldsInfo();
	 
	//##ModelId=46B7B8400280
	  int GetCompoundJunctionIDIndex();
	  virtual int GetAttachFeatureIDIndex();
	  virtual int GetAttachFeatureMeshIDIndex();
	
	//##ModelId=46B7B8400281
	  int GetJunctionIDIndex();
	  
	//##ModelId=46B7B8400282
	  int GetStartRoadIDIndex();

	//##ModelId=46B7B8400283
	  int GetDirectionIDIndex();
	  virtual int GetIDIndex();
	  
	//##ModelId=46B7B8400284
	  int GetEndRoadID1Index();
	//##ModelId=46B7B8400285
	  int GetEndRoadID2Index();
	//##ModelId=46B7B8400286
	  int GetEndRoadID3Index();
	//##ModelId=46B7B8400287
	  int GetEndRoadID4Index();
	//##ModelId=46B7B8400290
	  int GetEndRoadID5Index();
	//##ModelId=46B7B8400291
	  int GetEndRoadID6Index();
	//##ModelId=46B7B8400292
	  int GetEndRoadID7Index();
	//##ModelId=46B7B8400293
	  int GetEndRoadID8Index();
	  
    //## Constructors (generated)
	//##ModelId=46B7B8400294
      CDirectionFieldsInfo();

    //## Destructor (generated)
	//##ModelId=46B7B8400295
      ~CDirectionFieldsInfo();

    // Additional Public Declarations
      //## begin CDirectionFieldsInfo%405A57A401BB.public preserve=yes
      //## end CDirectionFieldsInfo%405A57A401BB.public

  protected:
    // Additional Protected Declarations
      //## begin CDirectionFieldsInfo%405A57A401BB.protected preserve=yes
      //## end CDirectionFieldsInfo%405A57A401BB.protected

  private: //## implementation
    // Data Members for Class Attributes

	  int		m_iStartRoadIDIndex ;
	//##ModelId=46B7B84002A2
	  int		m_iEndRoadID1Index ;
	//##ModelId=46B7B84002AF
	  int		m_iEndRoadID2Index ;
	//##ModelId=46B7B84002B0
	  int		m_iEndRoadID3Index ;
	//##ModelId=46B7B84002B1
	  int		m_iEndRoadID4Index ;
	//##ModelId=46B7B84002B2
	  int		m_iEndRoadID5Index ;
	//##ModelId=46B7B84002BF
	  int		m_iEndRoadID6Index ;
	//##ModelId=46B7B84002C0
	  int		m_iEndRoadID7Index ;
	//##ModelId=46B7B84002C1
	  int		m_iEndRoadID8Index ;
     //## end CDirectionFieldsInfo::m_vectorField%405BD629003E.attr

    // Data Members for Associations
};

//## begin CDirectionFieldsInfo%405A57A401BB.postscript preserve=yes
//## end CDirectionFieldsInfo%405A57A401BB.postscript

// Class CDirectionFieldsInfo 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog


#endif
