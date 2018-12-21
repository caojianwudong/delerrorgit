// CTaskBlock.cpp: implementation of the CTaskBlock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskManager.h"
#include "CTaskBlock.h"
#include "CTaskBlockDetail.h"
#include "CTaskManager.h"

#include "CDB_Manager.h"

#include "task_definition.h"
#include "DB_ResultSet.h"
#include "Db_Definition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaskBlock *CreateTaskBlock(__int64 iID,int ilevel)
{
	CTaskBlock *p = new CTaskBlock ;
	p->SetID(iID) ;
	p->SetReferLevel(ilevel) ;
	p->LoadLinkInfo() ;
	return p ;
}

CTaskBlock::CTaskBlock()
{
	m_id = 0 ;
	m_status = 0 ;
	m_type = 0 ;
	m_mapTaskBlockDetail = new TASKBLOCKDETAIL_MAP ;
	m_maxid = 0 ;
	m_ireferlevel = -1 ;
	m_roadnum = 0 ;
	m_errorCount = 0 ;
}

CTaskBlock::~CTaskBlock()
{
	if ( m_mapTaskBlockDetail != NULL)
	{
		TASKBLOCKDETAIL_MAP_ITERATOR detail_iterator ;
		int isize = m_mapTaskBlockDetail->size() ;
		for ( detail_iterator = m_mapTaskBlockDetail->begin(); detail_iterator != m_mapTaskBlockDetail->end(); detail_iterator++)
		{
			CTaskBlockDetail *p = detail_iterator->second ;
			if ( p != NULL)
			{
				delete detail_iterator->second ;
				p = NULL ;
				detail_iterator->second = NULL ;
			}
		}
		m_mapTaskBlockDetail->clear() ;
		delete m_mapTaskBlockDetail; 
		m_mapTaskBlockDetail = NULL ;
	}
}

bool CTaskBlock::LoadLinkInfo()
{
	CString strSQL ;
	m_id = GetID();
	if ( m_id <= 0 )
	{
		return false ;
	}
// 	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
	CTaskManager::GetTaskManager()->SetChoosingTask() ;
	// 获得block的类型，如果是数据集，加载blockdetail，如果是范围读取blockrefer
	strSQL.Format("select type,name from tb_task_block where id=%I64d",m_id) ;
	CDB_ResultSet *pRes1 = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
	if ( pRes1 == NULL)
	{
		return false ;
	}

	int iblocktype = -1 ;
	CString strName = "" ;
	
	//while ( (row1=mysql_fetch_row(pRes1)) != NULL )
	{
		iblocktype = pRes1->GetResIntValue(0,0) ;
		strName = pRes1->GetResStringValue(0,1) ;
	}
	SetName(strName) ;
	CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes1) ;
	m_type = iblocktype ;
	if ( iblocktype == 1 )
	{
		strSQL.Format("select * from tb_task_blockdetail where blockid=%I64d", m_id) ;
	}
	else if ( iblocktype == 0  )
	{
		strSQL.Format("select * from tb_task_blockrefer where blockid=%I64d ", m_id) ;
	}
	else
	{
		return false ;
	}
	m_type = iblocktype ;
	
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
		CTaskBlockDetail *pBlockdetail = new CTaskBlockDetail() ;
		VT_RES vtres = it->second ;
		for ( int i=0; i<num_fields; i++ )
		{
			int mysqltype = vtFields.at(i).type ;
			pFieldInfo = new CDBFieldInfo(vtFields[i].name,vtFields[i].table,mysqltype) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(mysqltype));//再单独设置一下
			pValue = new CDBValue ;
			pBlockdetail->AddField(pFieldInfo, pValue) ;
			CString strval = vtres.at(i).c_str() ;
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pBlockdetail->SetIntByIndex(i,atoi(strval) ) ;
				break;
			case DBFT_Bigint:
				pBlockdetail->SetInt64ByIndex(i,_atoi64(strval) ) ;
				break;
			case DBFT_Double:
				pBlockdetail->SetDoubleByIndex(i, atof(strval) ) ;
				break;
			case DBFT_String:
				pBlockdetail->SetStringByIndex(i,strval) ;
				break;
			}
		}
		int iIndex = pBlockdetail->GetIndex("id") ;
		__int64 id = pBlockdetail->GetInt64ByIndex(iIndex) ;
		m_mapTaskBlockDetail->insert(TASKBLOCKDETAIL_MAP::value_type(id,pBlockdetail)) ;
	}
	return true ;
}

void CTaskBlock::SetID( __int64 id )
{
	int index = GetIndex("id");
	if( index != -1)
		SetInt64ByIndex(index , id );
	m_id = id ;
}

__int64 CTaskBlock::GetID()
{
	int index = GetIndex("id");
	if( index != -1)
		return GetInt64ByIndex(index);
	return m_id;
}

void CTaskBlock::SetType( int itype )
{
	m_type = itype ;
}

int CTaskBlock::GetType()
{
	return m_type ;
}

void CTaskBlock::SetStatus( int istatus )
{
	m_status = istatus ;
}

int CTaskBlock::GetStatus()
{
	return m_status ;
}

void CTaskBlock::SetBound( _TSGEO::SGeoRect rect )
{
	m_bound = rect ;
}

_TSGEO::SGeoRect CTaskBlock::GetBound()
{
	return m_bound ;
}

void CTaskBlock::SetUpdateTime( SYSTEMTIME time )
{
	m_updatetime = time ;
}

SYSTEMTIME CTaskBlock::GetUpdateTime()
{
	return m_updatetime ;
}

void CTaskBlock::AddTaskBlockDetail( CTaskBlockDetail *pTaskBlockDetail )
{
	if ( pTaskBlockDetail != NULL)
	{
		if ( pTaskBlockDetail->GetID() == 0)
		{
			m_maxid++ ;
			pTaskBlockDetail->SetID(m_maxid) ;
		}
		m_mapTaskBlockDetail->insert(TASKBLOCKDETAIL_MAP::value_type( pTaskBlockDetail->GetID(), pTaskBlockDetail)) ;
	}
}

int CTaskBlock::GetTaskBlockDetailCount()
{
	return m_mapTaskBlockDetail->size() ;
}

CTaskBlockDetail* CTaskBlock::GetFirstTaskBlockDetailPtr()
{
	if ( m_mapTaskBlockDetail == NULL)
	{
		return NULL ;
	}
	m_currentTaskBlockDetailPtr = m_mapTaskBlockDetail->begin() ;
	if ( m_currentTaskBlockDetailPtr == m_mapTaskBlockDetail->end())
	{
		return NULL ;
	}
	CTaskBlockDetail *pTaskBlockDetail = m_currentTaskBlockDetailPtr->second ;
	m_currentTaskBlockDetailPtr++ ;
	return pTaskBlockDetail ;
}

CTaskBlockDetail* CTaskBlock::GetNextTaskBlockDetailPtr()
{
	if ( m_mapTaskBlockDetail == NULL)
	{
		return NULL ;
	}
	if ( m_currentTaskBlockDetailPtr == m_mapTaskBlockDetail->end())
	{
		return NULL ;
	}
	CTaskBlockDetail *pTaskBlockDetail = m_currentTaskBlockDetailPtr->second ;
	m_currentTaskBlockDetailPtr++ ;
	return pTaskBlockDetail ;
}

CTaskBlockDetail* CTaskBlock::GetNextTaskBlockDetailPtr( CTaskBlockDetail* pTaskBlockDetail )
{
	if ( pTaskBlockDetail == NULL || m_mapTaskBlockDetail == NULL)
	{
		return NULL ;
	}
	TASKBLOCKDETAIL_MAP_ITERATOR detail_iterator ;
	detail_iterator = m_mapTaskBlockDetail->find( pTaskBlockDetail->GetID()) ;
	if ( detail_iterator == m_mapTaskBlockDetail->end())
	{
		return NULL ;
	}
	detail_iterator++ ;
	if ( detail_iterator == m_mapTaskBlockDetail->end())
	{
		return NULL ;
	}
	return detail_iterator->second ;
}

bool CTaskBlock::DeleteTaskBlockDetail( __int64 detailID )
{
	if ( m_mapTaskBlockDetail == NULL)
	{
		return false ;
	}
	TASKBLOCKDETAIL_MAP_ITERATOR detail_iterator ;
	detail_iterator = m_mapTaskBlockDetail->find( detailID) ;
	if ( detail_iterator == m_mapTaskBlockDetail->end())
	{
		return false ;
	}

	if (detail_iterator==m_currentTaskBlockDetailPtr)
	{
		m_currentTaskBlockDetailPtr++ ;
	}
	CTaskBlockDetail *pTaskBlockDetail = detail_iterator->second ;
	if ( pTaskBlockDetail != NULL)
	{
		delete pTaskBlockDetail ;
		pTaskBlockDetail = NULL ;
	}
	m_mapTaskBlockDetail->erase( detail_iterator) ;
	return true ;
}

CTaskBlockDetail* CTaskBlock::GetTaskBlockDetailForFeatureIDPtr( __int64 featureID )
{
	TASKBLOCKDETAIL_MAP_ITERATOR detail_iterator ;
	for ( detail_iterator = m_mapTaskBlockDetail->begin(); detail_iterator != m_mapTaskBlockDetail->end(); detail_iterator++)
	{
		CTaskBlockDetail *pTaskBlockDetail = detail_iterator->second ;
		if ( pTaskBlockDetail == NULL)
		{
			continue; 
		}

		if ( pTaskBlockDetail->GetFeatureID() == featureID)
		{
			return pTaskBlockDetail ;
		}
	}
	return NULL ;
}

CTaskBlockDetail* CTaskBlock::GetTaskBlockDetailForDetailIDPtr( __int64 detailID )
{
	TASKBLOCKDETAIL_MAP_ITERATOR detail_iterator ;
	detail_iterator = m_mapTaskBlockDetail->find( detailID) ;
	if ( detail_iterator == m_mapTaskBlockDetail->end())
	{
		return NULL ;
	}
	return detail_iterator->second ;
}

__int64* CTaskBlock::GetFeatureIDs(int layerid, int &size)
{
	TASKBLOCKDETAIL_MAP_ITERATOR detail_iterator ;
	if ( m_mapTaskBlockDetail == NULL)
	{
		return NULL ;
	}
	int isize = m_mapTaskBlockDetail->size() ;
	if ( isize == 0)
	{
		return NULL ;
	}
	__int64 *pfeatureid = new __int64[isize] ;
	size = 0 ;
	for ( detail_iterator = m_mapTaskBlockDetail->begin(); detail_iterator != m_mapTaskBlockDetail->end(); detail_iterator++)
	{
		CTaskBlockDetail *pTaskBlockDetail = detail_iterator->second ;
		if ( pTaskBlockDetail == NULL)
		{
			continue;
		}

		int dx_layerid = pTaskBlockDetail->GetIndex("layerid") ;
		int dx_featureid = pTaskBlockDetail->GetIndex("featureid") ;
		if ( dx_featureid == -1 || dx_layerid == -1)
		{
			continue;
		}

		int detaillayerid = pTaskBlockDetail->GetIntByIndex(dx_layerid) ;

		if ( detaillayerid != layerid )
		{
			continue;
		}
		__int64 featureid = pTaskBlockDetail->GetInt64ByIndex(dx_featureid) ;
		pfeatureid[size] = featureid ;
		size++ ;

// 		if ( pTaskBlockDetail->GetLayerID() != layerid)
// 		{
// 			continue;
// 		}
// 		size++ ;
// 		pfeatureid[size-1] = pTaskBlockDetail->GetID() ;
	}
	return pfeatureid ;
}


bool CTaskBlock::UpdateBlockDetail( CTaskBlockDetail *pTaskBlockDetail,const char *szFieldNames )
{
	if ( pTaskBlockDetail == NULL )
	{
		return false ;
	}
	CString strFieldNames = szFieldNames ;
	__int64 id = pTaskBlockDetail->GetInt64ByIndex(pTaskBlockDetail->GetIndex("id")) ;
	CString strHead = "update tb_task_blockdetail set ";
	CString strtail = "" ;
	strtail.Format(" where id=%I64d",id) ;
	CString strUpdate = "" ;
	if ( strFieldNames == "" )
	{// 更新全部字段
		int icount = pTaskBlockDetail->Size() ;
		for ( int i=0; i<icount; i++ )
		{
			CString strName = pTaskBlockDetail->GetFieldInfoByIndex(i)->GetFieldName() ;
			CString strValue = "" ;
			DB_FIELDTYPE etype = pTaskBlockDetail->GetFieldTypeByIndex(i) ;
			switch ( etype)
			{
			case DBFT_Int:
				strValue.Format("%d", pTaskBlockDetail->GetIntByIndex(i) ) ;
				break;
			case DBFT_Bigint:
				strValue.Format("%I64d", pTaskBlockDetail->GetInt64ByIndex(i ) );
				break;
			case DBFT_Double:
				strValue.Format("%f", pTaskBlockDetail->GetDoubleByIndex(i) );
				break;
			case DBFT_String:
				strValue.Format("'%s'", pTaskBlockDetail->GetStringByIndex(i) ) ;
				break;
			}
			if ( strUpdate != "")
			{
				strUpdate += "," ;
			}
			strUpdate += strName ;
			strUpdate += "=" ;
			strUpdate += strValue ;
		}
	}
	else
	{// 更新部分字段（szFieldNames中指定）
		int ipos = strFieldNames.Find(",") ;
		CString strName ;
		while ( ipos != -1 )
		{
			strName = strFieldNames.Left(ipos) ;
			int iIndex = pTaskBlockDetail->GetIndex(strName) ;
			if ( iIndex != -1 )
			{
				CString strValue = "" ;
				DB_FIELDTYPE etype = pTaskBlockDetail->GetFieldTypeByIndex(iIndex) ;
				switch ( etype)
				{
				case DBFT_Int:
					strValue.Format("%d", pTaskBlockDetail->GetIntByIndex(iIndex) ) ;
					break;
				case DBFT_Bigint:
					strValue.Format("%I64d", pTaskBlockDetail->GetInt64ByIndex(iIndex ) );
					break;
				case DBFT_Double:
					strValue.Format("%f", pTaskBlockDetail->GetDoubleByIndex(iIndex) );
					break;
				case DBFT_String:
					strValue.Format("'%s'", pTaskBlockDetail->GetStringByIndex(iIndex) ) ;
					break;
				}
				if ( strUpdate != "")
				{
					strUpdate += "," ;
				}
				strUpdate += strName ;
				strUpdate += "=" ;
				strUpdate += strValue ;
			}

			
			strFieldNames = strFieldNames.Right(strFieldNames.GetLength()-ipos-1) ;
			ipos = strFieldNames.Find(",") ;
		}
		int iIndex = pTaskBlockDetail->GetIndex(strFieldNames) ;
		if ( iIndex != -1 )
		{
			CString strValue = "" ;
			DB_FIELDTYPE etype = pTaskBlockDetail->GetFieldTypeByIndex(iIndex) ;
			switch ( etype)
			{
			case DBFT_Int:
				strValue.Format("%d", pTaskBlockDetail->GetIntByIndex(iIndex) ) ;
				break;
			case DBFT_Bigint:
				strValue.Format("%I64d", pTaskBlockDetail->GetInt64ByIndex(iIndex ) );
				break;
			case DBFT_Double:
				strValue.Format("%f", pTaskBlockDetail->GetDoubleByIndex(iIndex) );
				break;
			case DBFT_String:
				strValue.Format("'%s'", pTaskBlockDetail->GetStringByIndex(iIndex) ) ;
				break;
			}
			if ( strUpdate != "")
			{
				strUpdate += "," ;
			}
			strUpdate += strFieldNames ;
			strUpdate += "=" ;
			strUpdate += strValue ;
		}
	}
	if ( strUpdate != "" )
	{
		CString strSql ;
		strSql = strHead + strUpdate + strtail ;
		CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL);
		int iaffact = 0;
		return CDB_Manager::GetDBManagerPtr()->ExcuteSql(strSql,iaffact) ;
	}
	return false ;
}

int	CTaskBlock::GetReferLevel() 
{
	return m_ireferlevel ;
}
void CTaskBlock::SetReferLevel(int ilevel)
{
	m_ireferlevel = ilevel ;
}

const char *CTaskBlock::GetName()
{
	return m_strname.c_str() ;
}

void CTaskBlock::SetName(const char *szName)
{
	m_strname = szName ;
}


void CTaskBlock::SetRoadNum( int roadnum )
{
	m_roadnum = roadnum ;
}

int CTaskBlock::GetRoadNum()
{
	return m_roadnum ;
}

void CTaskBlock::SetErrorCount( int errorcount )
{
	m_errorCount = errorcount ;
}

int CTaskBlock::GetErrorCount()
{
	return m_errorCount ;
}