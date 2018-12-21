//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%40A1DA6803B9.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40A1DA6803B9.cm

//## begin module%40A1DA6803B9.cp preserve=no
//## end module%40A1DA6803B9.cp

//## Module: CGeometry%40A1DA6803B9; Pseudo Package specification

#ifndef CGeometry_h
#define CGeometry_h 1
class CFeature ;
//## begin module%40A1DA6803B9.additionalIncludes preserve=no
//## end module%40A1DA6803B9.additionalIncludes

//## begin module%40A1DA6803B9.includes preserve=yes
//## end module%40A1DA6803B9.includes

//## begin module%40A1DA6803B9.additionalDeclarations preserve=yes

//## begin CGeometry%40A1DA6803B9.preface preserve=yes
//## end CGeometry%40A1DA6803B9.preface

//## Class: CGeometry%40A1DA6803B9
//## Category: DataAccess::CGeoO%407001E50071
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//##ModelId=46B7B83F00FA
class __declspec(dllexport) CGeometry 
{
    //## begin CGeometry%40A1DA6803B9.initialDeclarations preserve=yes
    //## end CGeometry%40A1DA6803B9.initialDeclarations
    
public:
    
    CGeometry(CFeature*);
    
    virtual ~CGeometry();
    
public:    

       //## Other Operations (specified)
       //## Operation: GetGeoType%40A44EA1007D
       //##ModelId=46B7B83F00FC
       virtual int GetGeoType () = 0;
       
public:
    
    //##ModelId=46B7B83F00FB
	   CFeature *   GetOwnerFeaturePtr();

       ModifyStatus AppendModifyStatus(ModifyStatus status);

       // 获取编辑状态
       bool         QueryVerifyStatus();

       ModifyStatus QueryModifyStatus();
       
       // 清除编辑状态(加载数据/同步数据之后使用)
       void         ClearStatusFlags();
       
       CheckStatus  GetAutoCheck();
       
       void         SetAutoCheck(CheckStatus status);
       
       CheckStatus  GetManuCheck();
       
       void         SetManuCheck(CheckStatus status);
       
       OpType       GetOpType();
       
       void         SetOpType(OpType type);

	   Confirm		GetConfirm();

	   void			SetConfirm(Confirm confirm);
       
    // Additional Public Declarations
    //## begin CGeometry%40A1DA6803B9.public preserve=yes
    //## end CGeometry%40A1DA6803B9.public
    
protected:
    // Additional Protected Declarations
    //## begin CGeometry%40A1DA6803B9.protected preserve=yes
    //## end CGeometry%40A1DA6803B9.protected
    //##ModelId=46B7B83F010A
    CFeature* 	m_pOwnerFeature ;
    
    unsigned    m_dwStatus;
    
private:
    // Additional Private Declarations
    //## begin CGeometry%40A1DA6803B9.private preserve=yes
    //## end CGeometry%40A1DA6803B9.private
    
private: //## implementation
    // Additional Implementation Declarations
    //## begin CGeometry%40A1DA6803B9.implementation preserve=yes
    //## end CGeometry%40A1DA6803B9.implementation
    
};

//## begin CGeometry%40A1DA6803B9.postscript preserve=yes
//## end CGeometry%40A1DA6803B9.postscript

// Class CGeometry 

//## begin module%40A1DA6803B9.epilog preserve=yes
//## end module%40A1DA6803B9.epilog


#endif
