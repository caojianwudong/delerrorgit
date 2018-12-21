//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A578700DD.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A578700DD.cm

//## begin module%405A578700DD.cp preserve=no
//## end module%405A578700DD.cp

//## Module: Field%405A578700DD; Pseudo Package specification

#ifndef FieldInfo_h
#define FieldInfo_h 1

//## begin module%405A578700DD.additionalIncludes preserve=no
//## end module%405A578700DD.additionalIncludes

//## begin module%405A578700DD.includes preserve=yes
//## end module%405A578700DD.includes

#include "commondef.h"
//## begin module%405A578700DD.additionalDeclarations preserve=yes
//## end module%405A578700DD.additionalDeclarations


//## begin FieldInfo%405A578700DD.preface preserve=yes
//## end Field%405A578700DD.preface

//## Class: Field%405A578700DD
//	《说明》：单个字段的描述信息。
//	包括：字段的名称、字段的类型、字段的长度和字段的值
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83F03C9
class __declspec(dllexport) CFieldInfo 
{
  //## begin FieldInfo%405A578700DD.initialDeclarations preserve=yes
  //## end Field%405A578700DD.initialDeclarations

  public:
	//##ModelId=46B7B83F03D8
	  void SetFieldName(const char * name);
	//##ModelId=46B7B83F03DA
	  void SetFieldType(FIELDTYPE type);
    //## Constructors (specified)
      //## Operation: Field%405BD4B4038A
	//##ModelId=46B7B83F03DC
      CFieldInfo (const char* szName, const char* szCaption, int nFieldType, int nLength);

    //## Destructor (generated)
	//##ModelId=46B7B8400001
      ~CFieldInfo();


    //## Other Operations (specified)
      //## Operation: GetFieldName%405BD4E901A5
	//##ModelId=46B7B8400002
      const char* GetFieldName ();

      //## Operation: GetFieldCaption%405BD4F202CE
	//##ModelId=46B7B8400003
      const char* GetFieldCaption ();

      //## Operation: SetFieldCaption%405BD503037A
	//##ModelId=46B7B8400004
      void SetFieldCaption (const char* szCaption);

      //## Operation: GetFieldType%405BD50C029F
	//##ModelId=46B7B8400006
      FIELDTYPE GetFieldType ();

      //## Operation: GetFieldLength%405BD5190399
	//##ModelId=46B7B8400007
      int GetFieldMaxLength ();

    // Additional Public Declarations
      //## begin Field%405A578700DD.public preserve=yes
      //## end Field%405A578700DD.public

  protected:
    // Additional Protected Declarations
      //## begin Field%405A578700DD.protected preserve=yes
      //## end Field%405A578700DD.protected

  private:
    // Additional Private Declarations
      //## begin Field%405A578700DD.private preserve=yes
      //## end Field%405A578700DD.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: m_szFieldName%405BD4350177
      //## begin Field::m_szFieldName%405BD4350177.attr preserve=no  private: char[FIELDNAMELEN] {U} 
	//##ModelId=46B7B840000F
      char m_szFieldName[MAX_FIELD_NAME_LEN];
      //## end Field::m_szFieldName%405BD4350177.attr

      //## Attribute: m_szFieldCaption%405BD440033C
      //## begin Field::m_szFieldCaption%405BD440033C.attr preserve=no  private: char[FIELDCAPTIONLEN] {U} 
	//##ModelId=46B7B8400010
      char m_szFieldCaption[MAX_FIELD_NAME_LEN];
      //## end Field::m_szFieldCaption%405BD440033C.attr

      //## Attribute: m_nFieldType%405BD44D000F
      //## begin Field::m_nFieldType%405BD44D000F.attr preserve=no  private: FIELDTYPE {U} 
	//##ModelId=46B7D172010A
      FIELDTYPE m_nFieldType;
      //## end Field::m_nFieldType%405BD44D000F.attr

      //## Attribute: m_nFieldLength%405BD49C0109
      //## begin Field::m_nFieldLength%405BD49C0109.attr preserve=no  private: int {U} 
	//##ModelId=46B7B840001F
      int m_nFieldMaxLength;
      //## end Field::m_nFieldLength%405BD49C0109.attr

};

//## begin Field%405A578700DD.postscript preserve=yes
//## end Field%405A578700DD.postscript

// Class Field 

//## begin module%405A578700DD.epilog preserve=yes
//## end module%405A578700DD.epilog


#endif
