//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CFieldsInfo%405A57A401BB; Pseudo Package specification

#ifndef CFieldsInfo_h
#define CFieldsInfo_h 1

//## begin module%405A57A401BB.additionalIncludes preserve=no
//## end module%405A57A401BB.additionalIncludes

//## begin module%405A57A401BB.includes preserve=yes
//## end module%405A57A401BB.includes

#include "CFieldInfo.h"
//## begin module%405A57A401BB.additionalDeclarations preserve=yes
#include <map>
#include <vector>
#include <string>

typedef std::vector< CFieldInfo * >			VECTOR_FieldInfo;
//##ModelId=4550252D00A8
//typedef map< string, CFieldInfo * >			MAP_Field;
//## end module%405A57A401BB.additionalDeclarations


//## begin CFieldsInfo%405A57A401BB.preface preserve=yes
//## end CFieldsInfo%405A57A401BB.preface

//## Class: CFieldsInfo%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83F033C
class __declspec(dllexport) CFieldsInfo 
{
  //## begin CFieldsInfo%405A57A401BB.initialDeclarations preserve=yes
  //## end CFieldsInfo%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7B83F033D
	  void Release();
    //## Constructors (generated)
	//##ModelId=46B7B83F034B
      CFieldsInfo();

    //## Destructor (generated)
	//##ModelId=46B7B83F034C
      ~CFieldsInfo();


    //## Other Operations (specified)
      //## Operation: AddField%405BD6B6030D
	//##ModelId=46B7B83F034D
      void AddField (const char* szName, const char* szCaption, int nFieldType, int nLength = 0);

      //## Operation: Size%405BDAF40271
	//##ModelId=46B7B83F0352
      int Size ();

      //## Operation: GetField%405BD72A02EE
	//##ModelId=46B7B83F035B
      CFieldInfo* GetFieldInfoPtr (int index);

      //## Operation: GetField%405BD73B0177
	//##ModelId=46B7B83F035D
      CFieldInfo* GetFieldInfoPtr (const char* szFieldName);

      //## Operation: GetIndex%405BE4FE0138
	//##ModelId=46B7B83F035F
      int GetIndex (const char* szFieldName);

	//##ModelId=46B7B83F0361
	  virtual bool CheckFieldsInfo() ;
    // Additional Public Declarations
      //## begin CFieldsInfo%405A57A401BB.public preserve=yes
      //## end CFieldsInfo%405A57A401BB.public

  protected:
    // Additional Protected Declarations
      //## begin CFieldsInfo%405A57A401BB.protected preserve=yes
      //## end CFieldsInfo%405A57A401BB.protected

  private:


    // Additional Private Declarations
      //## begin CFieldsInfo%405A57A401BB.private preserve=yes
      //## end CFieldsInfo%405A57A401BB.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: m_mapField%405BD60C035B
      //## begin CFieldsInfo::m_mapField%405BD60C035B.attr preserve=no  private: MAP_Field {U} 
	//##ModelId=4550252D0135
      //MAP_Field m_mapField;
      //## end CFieldsInfo::m_mapField%405BD60C035B.attr

      //## Attribute: m_vectorField%405BD629003E
      //## begin CFieldsInfo::m_vectorField%405BD629003E.attr preserve=no  private: VECTOR_Field {U} 
	//##ModelId=46B7B83F0364
      VECTOR_FieldInfo m_vectorField;
      //## end CFieldsInfo::m_vectorField%405BD629003E.attr

    // Data Members for Associations

      //## Association: DataAccess::SDE::<unnamed>%405A5BBE014D
      //## Role: CFieldsInfo::<the_Field>%405A5BBE0338
      //## begin CFieldsInfo::<the_Field>%405A5BBE0338.role preserve=no  public: Field { -> UHgN}
      //## end CFieldsInfo::<the_Field>%405A5BBE0338.role

    // Additional Implementation Declarations
      //## begin CFieldsInfo%405A57A401BB.implementation preserve=yes
      //## end CFieldsInfo%405A57A401BB.implementation

};

//## begin CFieldsInfo%405A57A401BB.postscript preserve=yes
//## end CFieldsInfo%405A57A401BB.postscript

// Class CFieldsInfo 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog
extern "C"
{
	 __declspec(dllexport) CFieldsInfo* CreateFieldsInfoObject( CFieldsInfo * pInfo ) ;
}


#endif
