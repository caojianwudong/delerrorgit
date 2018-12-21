//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%405A532D009F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%405A532D009F.cm

//## begin module%405A532D009F.cp preserve=no
//## end module%405A532D009F.cp

//## Module: FieldValue%405A532D009F; Pseudo Package specification

#ifndef FieldValue_h
#define FieldValue_h 1

//## begin module%405A532D009F.additionalIncludes preserve=no
//## end module%405A532D009F.additionalIncludes

//## begin module%405A532D009F.includes preserve=yes
//## end module%405A532D009F.includes

//## begin module%405A532D009F.additionalDeclarations preserve=yes
//## end module%405A532D009F.additionalDeclarations


//## begin FieldValue%405A532D009F.preface preserve=yes
//## end FieldValue%405A532D009F.preface

//## Class: FieldValue%405A532D009F
//	《说明》：一个字段的值
//## Category: 数据访问模块%4056B67500D5
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83F031C
class __declspec(dllexport) CFieldValue 
{
  //## begin FieldValue%405A532D009F.initialDeclarations preserve=yes
  //## end FieldValue%405A532D009F.initialDeclarations

  public:
    //## Constructors (generated)
	//##ModelId=46B7B83F031D
      CFieldValue();

    //## Destructor (generated)
	//##ModelId=46B7B83F031E
      ~CFieldValue();


    //## Other Operations (specified)
      //## Operation: GetInt%405BD268007D
	//##ModelId=46B7B83F031F
      int GetInt ();

      //## Operation: SetInt%405BD2FD035B
	//##ModelId=46B7B83F0320
      void SetInt (int value);

      //## Operation: GetDouble%405BD2AF02BF
	//##ModelId=46B7B83F032D
      double GetDouble ();

      //## Operation: SetDouble%405BD2F1003E
	//##ModelId=46B7B83F032E
      void SetDouble (double value);

      //## Operation: GetString%405BD2B70196
	//##ModelId=46B7B83F0330
      const char* GetString ();

      //## Operation: SetString%405BD2DE01C5
	//##ModelId=46B7B83F0331
      void SetString (const char* value);

      __int64  GetBigint();

      void SetBigint(__int64 value);

      // 获取编辑状态
      bool         QueryVerifyStatus();

	  bool		   QueryNotNullValue();

	  void		   SetNotNullValue();
      
      ModifyStatus QueryModifyStatus();

      // 清除编辑状态(加载数据/同步数据之后使用)
      void         ClearStatusFlags();

      CheckStatus  GetAutoCheck();

      void         SetAutoCheck(CheckStatus status);

      CheckStatus  GetManuCheck();
      
      void         SetManuCheck(CheckStatus status);

      OpType       GetOpType();

      void         SetOpType(OpType type);

	  Confirm	   GetConfirm();

	  void		   SetConfirm(Confirm confirm);

    // Additional Public Declarations
      //## begin FieldValue%405A532D009F.public preserve=yes
      //## end FieldValue%405A532D009F.public

  protected:
    // Additional Protected Declarations
      //## begin FieldValue%405A532D009F.protected preserve=yes
      //## end FieldValue%405A532D009F.protected

  private:
    // Additional Private Declarations
      //## begin FieldValue%405A532D009F.private preserve=yes
      //## end FieldValue%405A532D009F.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: m_pValue%405BD22E02CE
      //## begin FieldValue::m_pValue%405BD22E02CE.attr preserve=no  private: char* {U} 0
	//##ModelId=46B7B83F0333
      char* m_pValue;
      //## end FieldValue::m_pValue%405BD22E02CE.attr

      // 编辑/质检/作业状态 lishman@20170308
      unsigned m_dwStatus;

    // Additional Implementation Declarations
      //## begin FieldValue%405A532D009F.implementation preserve=yes
      //## end FieldValue%405A532D009F.implementation

};

//## begin FieldValue%405A532D009F.postscript preserve=yes
//## end FieldValue%405A532D009F.postscript

// Class FieldValue 

//## begin module%405A532D009F.epilog preserve=yes
//## end module%405A532D009F.epilog


#endif
