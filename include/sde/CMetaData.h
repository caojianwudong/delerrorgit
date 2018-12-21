//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CMetaData%405A57A401BB; Pseudo Package specification

#ifndef CMetaData_h
#define CMetaData_h 1

//## begin module%405A57A401BB.additionalIncludes preserve=no
//## end module%405A57A401BB.additionalIncludes

//## begin module%405A57A401BB.includes preserve=yes
//## end module%405A57A401BB.includes

#include "CFieldInfo.h"
#include "CFieldValue.h"
//## begin module%405A57A401BB.additionalDeclarations preserve=yes
#include <map>
#include <vector>
#include <string>

//##ModelId=46B7B83B005D
typedef std::vector< CFieldValue * >			VECTOR_FieldValue;
//##ModelId=46B7B83B005F
typedef std::vector< CFieldInfo * >			VECTOR_FieldInfo;
//## end module%405A57A401BB.additionalDeclarations


//## begin CMetaData%405A57A401BB.preface preserve=yes
//## end CMetaData%405A57A401BB.preface

//## Class: CMetaData%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83B007D
class __declspec(dllexport) CMetaData 
{
  //## begin CMetaData%405A57A401BB.initialDeclarations preserve=yes
  //## end CMetaData%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7B83B007E
 	  FIELDTYPE GetFieldTypeByIndex( int index );
   //## Constructors (generated)
	//##ModelId=46B7B83B0080
      CMetaData();

    //## Destructor (generated)
	//##ModelId=46B7B83B0081
      ~CMetaData();

      //## Operation: Size%405BDAF40271
	//##ModelId=46B7B83B008C
      int Size ();

	//##ModelId=46B7B83B008D
      int GetIntByIndex (int index );
	
	//##ModelId=46B7B83B008F
	  double  GetDoubleByIndex (int index ) ;

	//##ModelId=46B7B83B0091
	  const char *  GetStringByIndex (int index ) ;

      //##ModelId=46B7B83B008F
      __int64  GetBigintByIndex (int index ) ;

	//##ModelId=46B7B83B0093
      bool SetIntByIndex (int index, int iVal );
	
	//##ModelId=46B7B83B009D
	  bool SetDoubleByIndex (int index, double dVal ) ;

      //##ModelId=46B7B83B008F
      bool SetBigintByIndex (int index, __int64 dVal ) ;

	//##ModelId=46B7B83B00A0
	  bool SetStringByIndex (int index, const char * strVal ) ;
      //## Operation: GetField%405BD72A02EE
	//##ModelId=46B7B83B00A3
      CFieldInfo* GetFieldInfoPtr (int index);
      //## Operation: GetIndex%405BE4FE0138
	//##ModelId=46B7B83B00A5
      int GetIndex (const char* szFieldName);

	//##ModelId=46B7B83B00AC
	  bool	AddField ( CFieldInfo* pInfo, CFieldValue * pValue ) ;
		
	//##ModelId=46B7B83B00AF
      bool	RemoveFieldByIndex (int index );

	//##ModelId=46B7B83B00B1
      bool	RemoveFieldByName (const char* szFieldName );

	//##ModelId=46B7B83B00BB
      const char* GetFieldNameByIndex (int index );
    // Additional Public Declarations
      //## begin CMetaData%405A57A401BB.public preserve=yes
      //## end CMetaData%405A57A401BB.public

  protected:
    // Additional Protected Declarations
      //## begin CMetaData%405A57A401BB.protected preserve=yes
      //## end CMetaData%405A57A401BB.protected

  private:

    //## Other Operations (specified)
      //## Operation: ClearMember%405BD784030D
	//##ModelId=46B7B83B00BD
      void ClearMember ();

    // Additional Private Declarations
      //## begin CMetaData%405A57A401BB.private preserve=yes
      //## end CMetaData%405A57A401BB.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: m_vectorField%405BD629003E
      //## begin CMetaData::m_vectorField%405BD629003E.attr preserve=no  private: VECTOR_Field {U} 
	//##ModelId=46B7B83B00BF
      VECTOR_FieldValue		m_vectorFieldValue;
      //## end CMetaData::m_vectorField%405BD629003E.attr
	//##ModelId=46B7B83B00CC
      VECTOR_FieldInfo		m_vectorFieldInfo;

    // Data Members for Associations

      //## Association: DataAccess::SDE::<unnamed>%405A5BBE014D
      //## Role: CMetaData::<the_Field>%405A5BBE0338
      //## begin CMetaData::<the_Field>%405A5BBE0338.role preserve=no  public: Field { -> UHgN}
      //## end CMetaData::<the_Field>%405A5BBE0338.role

    // Additional Implementation Declarations
      //## begin CMetaData%405A57A401BB.implementation preserve=yes
      //## end CMetaData%405A57A401BB.implementation

};

//## begin CMetaData%405A57A401BB.postscript preserve=yes
//## end CMetaData%405A57A401BB.postscript

// Class CMetaData 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog


#endif
