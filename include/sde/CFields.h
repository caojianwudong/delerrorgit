//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A57A401BB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A57A401BB.cm

//## begin module%405A57A401BB.cp preserve=no
//## end module%405A57A401BB.cp

//## Module: CFields%405A57A401BB; Pseudo Package specification

#ifndef CFields_h
#define CFields_h 1

//## begin module%405A57A401BB.additionalIncludes preserve=no
//## end module%405A57A401BB.additionalIncludes

//## begin module%405A57A401BB.includes preserve=yes
//## end module%405A57A401BB.includes

#include "CFieldsInfo.h"
#include "CFieldValue.h"
//## begin module%405A57A401BB.additionalDeclarations preserve=yes
#include <string>
#include "commondef.h"	// Added by ClassView

typedef std::vector< CFieldValue * >			VECTOR_FieldValue;
//## end module%405A57A401BB.additionalDeclarations


//## begin CFields%405A57A401BB.preface preserve=yes
//## end CFields%405A57A401BB.preface

//## Class: CFields%405A57A401BB
//## Category: DataAccess%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7D172007D
class __declspec(dllexport) CFields 
{
  //## begin CFields%405A57A401BB.initialDeclarations preserve=yes
  //## end CFields%405A57A401BB.initialDeclarations

  public:
	//##ModelId=46B7D172007E
	  void SetFieldsInfoPtr1( CFieldsInfo * pFieldsInfo );
	//##ModelId=46B7D1720080
	  FIELDTYPE GetFieldTypeByIndex( int index );
    //## Constructors (generated)
	//##ModelId=46B7D172008C
      CFields( CFieldsInfo* pFieldsInfo );

    //## Destructor (generated)
	//##ModelId=46B7D172008E
      ~CFields();

      //## Operation: Size%405BDAF40271
	//##ModelId=46B7D172008F
      int Size ();

      //## Operation: GetField%405BD72A02EE
	//##ModelId=46B7D172009C
      int GetIntByIndex (int index );
	
	//##ModelId=46B7D172009E
	  double  GetDoubleByIndex (int index ) ;

      __int64 GetBigintByIndex(int index);

      VARIANT GetVariantByIndex(int index);

	//##ModelId=46B7D17200A0
	  const char *  GetStringByIndex (int index ) ;

	//##ModelId=46B7D17200AB
      bool SetIntByIndex (int index, int iVal );
	
	//##ModelId=46B7D17200AE
	  bool SetDoubleByIndex (int index, double dVal ) ;

	//##ModelId=46B7D17200B1
	  bool SetStringByIndex (int index, const char * strVal ) ;

      bool SetBigintByIndex(int index, __int64 llVal);

      bool SetVariantByIndex(int index, const VARIANT & var);

      //## Operation: GetIndex%405BE4FE0138
	//##ModelId=46B7D17200BC
      int GetIndex (const char* szFieldName);

	//##ModelId=46B7D17200BE
	  bool	SetFieldsInfoPtr( CFieldsInfo	*pFieldsInfo ) ;

	//##ModelId=46B7D17200C0
	  CFieldsInfo	* GetFieldsInfoPtr ( ) ;

	//##ModelId=46B7D17200C1
	 void	Release() ;	
    // Additional Public Declarations
      //## begin CFields%405A57A401BB.public preserve=yes
      //## end CFields%405A57A401BB.public

     // 获取编辑状态
     ModifyStatus QueryModifyStatus(int index);

     bool QueryVerifyStatus(int index);

	 bool QueryNotNullValue(int index);

	 void SetNotNullValue(int index);
     
     // 清除编辑状态(加载数据/同步数据之后使用)
     void         ClearStatusFlags();
     
     CheckStatus  GetAutoCheck(int index);
     
     void         SetAutoCheck(int index, CheckStatus status);
     
     CheckStatus  GetManuCheck(int index);
     
     void         SetManuCheck(int index, CheckStatus status);
     
     OpType       GetOpType(int index);
     
     void         SetOpType(int index, OpType type);

	 Confirm	  GetConfirm(int index);

	 void		  SetConfirm(int index, Confirm confirm);

  protected:
    // Additional Protected Declarations
      //## begin CFields%405A57A401BB.protected preserve=yes
      //## end CFields%405A57A401BB.protected

  private:

    //## Other Operations (specified)
      //## Operation: ClearMember%405BD784030D
	//##ModelId=46B7D17200C2
      void ClearMember ();

    // Additional Private Declarations
      //## begin CFields%405A57A401BB.private preserve=yes
      //## end CFields%405A57A401BB.private

    // Data Members for Class Attributes
  protected:
	//##ModelId=46B7D17200CC
	  CFieldsInfo	* m_pFieldsInfo ;

  private: //## implementation
      //## Attribute: m_vectorField%405BD629003E
      //## begin CFields::m_vectorField%405BD629003E.attr preserve=no  private: VECTOR_Field {U} 
	//##ModelId=4550252D0201
      //VECTOR_FieldValue		m_vectorFieldValue;
	//##ModelId=46B7D17200DB
	  CFieldValue	 *			m_vectorFieldValue ;
	//##ModelId=46B7D17200DF
	  int						m_iFieldCount ;
      //## end CFields::m_vectorField%405BD629003E.attr

    // Data Members for Associations

      //## Association: DataAccess::SDE::<unnamed>%405A5BBE014D
      //## Role: CFields::<the_Field>%405A5BBE0338
      //## begin CFields::<the_Field>%405A5BBE0338.role preserve=no  public: Field { -> UHgN}
      //## end CFields::<the_Field>%405A5BBE0338.role

    // Additional Implementation Declarations
      //## begin CFields%405A57A401BB.implementation preserve=yes
      //## end CFields%405A57A401BB.implementation

};

//## begin CFields%405A57A401BB.postscript preserve=yes
//## end CFields%405A57A401BB.postscript
extern "C"
{
	 __declspec(dllexport) CFields* CreateFieldsObject( CFieldsInfo * pInfo ) ;
}


// Class CFields 

//## begin module%405A57A401BB.epilog preserve=yes
//## end module%405A57A401BB.epilog


#endif
