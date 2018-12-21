// CTaskLinkItemSet.cpp: implementation of the CTaskLinkItemSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskManager.h"
#include "CTaskLinkItemSet.h"

#include "CDB_Manager.h"

#include "task_definition.h"
#include "Db_Definition.h"
#include "DB_ResultSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaskLinkItemSet *CreateLinkItemSet(__int64 iID)
{
	CTaskLinkItemSet *p = new CTaskLinkItemSet ;
	p->SetItemSetID(iID) ;
	p->LoadLinkInfo() ;
	return p ;
}

CTaskLinkItemSet::CTaskLinkItemSet()
{
	m_iID = -1 ;
	m_itype = -1 ;
	m_vtItemdetail.clear() ;
}

CTaskLinkItemSet::~CTaskLinkItemSet()
{
	for ( int i=0; i<GetItemCount(); i++ )
	{
		CDBFields *p = m_vtItemdetail.at(i) ;
		if ( p != NULL)
		{
			delete p ;
			p = NULL ;
		}
	}
	m_vtItemdetail.clear() ;
}

bool CTaskLinkItemSet::LoadLinkInfo()
{
	CString strSQL ;
	if ( m_iID <= 0 )
	{
		return false ;
	}
	if ( m_itype != -1 )
	{
		//mysql
// 		strSQL.Format("select d.*,i.oid,i.name,i.layername,i.enable,i.unit,i.`type`,"
// 			"i.systype,i.referdata,i.module,i.updatetime from tb_itemsetdetail d,tb_iteminfo i "
// 			"where d.itemid=i.id and d.itemsetid=%I64d and i.type=%d order by d.id asc ", m_iID,m_itype) ;
		//postgresql
		strSQL.Format("select d.*,i.oid,i.name,i.layername,i.enable,i.unit,i.\"type\","
			"i.systype,i.referdata,i.module,i.updatetime from tb_itemsetdetail d,tb_iteminfo i "
			"where d.itemid=i.id and d.itemsetid=%I64d and i.type=%d order by d.id asc ", m_iID,m_itype) ;
	}
	else
	{
		//mysql
// 		strSQL.Format("select d.*,i.oid,i.name,i.layername,i.enable,i.unit,i.`type`,"
// 			"i.systype,i.referdata,i.module,i.updatetime from tb_itemsetdetail d,tb_iteminfo i "
// 			"where d.itemid=i.id and d.itemsetid=%I64d order by d.id asc", m_iID) ;
		//postgresql
		strSQL.Format("select d.*,i.oid,i.name,i.layername,i.enable,i.unit,i.\"type\","
			"i.systype,i.referdata,i.module,i.updatetime from tb_itemsetdetail d,tb_iteminfo i "
			"where d.itemid=i.id and d.itemsetid=%I64d order by d.id asc", m_iID) ;
	}
	
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	CDB_ResultSet *pRes = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
	if ( pRes == NULL)
	{
		return false ;
	}
	int num_rows = pRes->GetResRowCount();
	int num_fields = pRes->GetResFieldCount();
	
	std::vector<Field_DB> vtFields ;
	
	MAP_RES mapres ;
	int icount = 0 ;
	for(int r = 0; r < num_rows; r++)
	{
		icount++ ;
		VT_RES vtRes ;
		for ( int i=0; i<num_fields; i++ )
		{
			int ftype = pRes->GetFieldType(i);
			if ( icount == 1 )
			{
				Field_DB field ;
				field.name = pRes->GetFieldName(i) ;
				field.table = "" ;
				field.type = ftype ;
				vtFields.push_back(field) ;	
			}
			
			CString strval;
			
			switch(ftype)
			{
			case DBFT_Int:
				{
					strval.Format("%d",pRes->GetResIntValue(r,i));
					break;
				}
			case DBFT_Double:
				{
					strval.Format("%f",pRes->GetResDoubleValue(r,i));
					break;
				}
			case DBFT_Bigint:
				{
					strval.Format("%I64d",pRes->GetResBigIntValue(r,i));
					break;
				}
			case DBFT_String:
				{
					strval.Format("%s",pRes->GetResStringValue(r,i));
					break;
				}
			}
			
			vtRes.push_back(strval.GetBuffer(0)) ;
		}
		mapres.insert(MAP_RES::value_type(icount,vtRes)) ;
	}
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes) ;

	if ( mapres.empty() )
	{
		return false ;
	}

	
	CDBFieldInfo *pFieldInfo = NULL ;
	CDBValue *pValue = NULL ;
	MAP_RES::iterator it ;

	for ( it=mapres.begin(); it!=mapres.end(); it++ )
	{
		CDBFields *pItemSetdetail = new CDBFields() ;
		VT_RES vtres = it->second ;
		for ( int i=0; i<num_fields; i++ )
		{
			int mysqltype = vtFields.at(i).type ;
			pFieldInfo = new CDBFieldInfo(vtFields[i].name,vtFields[i].table,mysqltype) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(mysqltype));//再单独设置一下
			pValue = new CDBValue ;
			pItemSetdetail->AddField(pFieldInfo, pValue) ;
			CString strval = vtres.at(i).c_str() ;
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pItemSetdetail->SetIntByIndex(i,atoi(strval) ) ;
				break;
			case DBFT_Bigint:
				pItemSetdetail->SetInt64ByIndex(i,_atoi64(strval) ) ;
				break;
			case DBFT_Double:
				pItemSetdetail->SetDoubleByIndex(i, atof(strval) ) ;
				break;
			case DBFT_String:
				pItemSetdetail->SetStringByIndex(i,strval) ;
				break;
			}
		}
		
		m_vtItemdetail.push_back(pItemSetdetail) ;
	}

	return true ;
}

void CTaskLinkItemSet::SetItemSetID(__int64 iId)
{
	m_iID = iId ;
}

__int64 CTaskLinkItemSet::GetItemSetID()
{
	return m_iID ;
}

int CTaskLinkItemSet::GetItemCount()
{
	return m_vtItemdetail.size() ;
}

CDBFields * CTaskLinkItemSet::GetFieldsByIndex(int iIndex)
{
	if ( iIndex <0 || iIndex>GetItemCount())
	{
		return NULL ;
	}
	return m_vtItemdetail.at(iIndex) ;
}

void CTaskLinkItemSet::SetType(int type)
{
	m_itype = type ;
}

int CTaskLinkItemSet::GetType()
{
	return m_itype ;
}