// CQCTask.cpp: implementation of the CQCTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskManager.h"
#include "CQCTask.h"

#include "CTaskLinkItemSet.h"
#include "CTaskBlock.h"
#include "CDB_Manager.h"

#include "task_definition.h"
#include <algorithm> 
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

CQCTask::CQCTask()
{
	m_sBound = _TSGEO::SGeoRect(0,0,0,0) ;
	m_vtLayerName.clear() ;
	m_iTaskID = -1 ;
	m_pLinkItemSet = NULL ;
	m_ilevel = -1 ;
}

CQCTask::~CQCTask()
{
	if ( m_pBlock != NULL )
	{
		m_pBlock->Release() ;
		m_pBlock = NULL ;
	}
	if ( m_pLinkItemSet != NULL )
	{
		m_pLinkItemSet->Release() ;
	}
	m_vtLayerName.clear() ;
}

void CQCTask::SetLinkItemSet(CTaskLinkItemSet *pItemset)
{
	m_pLinkItemSet = pItemset ;
}

CTaskLinkItemSet *CQCTask::GetLinkItemSet()
{
	return m_pLinkItemSet ;
}

void CQCTask::SetTaskBlock(CTaskBlock *pTaskBlock)
{
	m_pBlock = pTaskBlock ;
}

CTaskBlock *CQCTask::GetTaskBlock()
{
	return m_pBlock ;
}

bool CQCTask::LoadLinkInfo()
{
	int iIndex = GetIndex("id") ;
	__int64 iid = GetInt64ByIndex(iIndex) ;
	CString strSQL = ""; 
	/// 先获得task的referdata中的图层信息及bound
	CDB_Manager::GetDBManagerPtr()->ChooseDB(DB_TASK_PGSQL) ;
	iIndex = GetIndex("tasktype") ;
	int itype = GetIntByIndex(iIndex) ;
	iIndex = GetIndex("process") ;
	int process = GetIntByIndex(iIndex) ;
	iIndex = GetIndex("state") ;
	int istate = GetIntByIndex(iIndex) ;
	CString strrefertype = "qc" ;
	if ( itype == 2002 || process == 5  )// 由于获取任务时并没有修改process状态，所以批处理获得到的为process=5
	{
		strrefertype = "tool" ;
	}
	else if ( itype == 2001 || process == 51 )
	{
		strrefertype = "qc" ;
	}
	if ( process == 51 )
	{
		strrefertype = "tool" ;
	}
	if ( process == 52 )
	{
		strrefertype = "qc" ;
	}
	int iNum = 0 ;
	CString strLayernames = "" ;
	CDB_ResultSet *pRes1 = NULL ;
	int num_rows1 = 0 ;
	if ( m_pBlock->GetType() == 1 || m_pBlock->GetType() == 2 )
	{
		/* mysql
		strSQL.Format("SELECT json_extract(t.qc,'$.layer') as 'qclayer',"
			"json_extract(t.qc,'$.bound[0]') as 'xmin',"
			"json_extract(t.qc,'$.bound[2]') as 'xmax',"
			"json_extract(t.qc,'$.bound[1]') as 'ymin',"
			"json_extract(t.qc,'$.bound[3]') as 'ymax',"
			"json_length(t.qc->'$.layer') as 'num'"
			"FROM (select json_extract(referdata,'$.%s') AS 'qc' from tb_task where id=%I64d ) as t ", strrefertype,iid) ;
			*/
		//postgresql
		strSQL.Format("select qc::json->'layer' as \"qclayer\","
			"qc::json->'bound'->0 as \"xmin\","
			"qc::json->'bound'->2 as \"xmax\","
			"qc::json->'bound'->1 as \"ymin\","
			"qc::json->'bound'->3 as \"ymax\","
			"json_array_length(qc::json->'layer') as \"num\" "
			"from (select referdata::json->'%s' as \"qc\" from tb_task where id=%I64d) as t", strrefertype,iid);

		pRes1 = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
		if ( pRes1 != NULL)
		{
			int rowcount = pRes1->GetResRowCount();
		
			for(int i = 0; i < rowcount; i++)
			{
				strLayernames.Format("%s",pRes1->GetResStringValue(i,0));
		
				m_sBound.x_min = atof(pRes1->GetResStringValue(i,1)) ;
				m_sBound.x_max = atof(pRes1->GetResStringValue(i,2)) ;
				m_sBound.y_min = atof(pRes1->GetResStringValue(i,3)) ;
				m_sBound.y_max = atof(pRes1->GetResStringValue(i,4)) ;

				int type5 = pRes1->GetFieldType(5);
				if(type5 == DBFT_Int) iNum = pRes1->GetResIntValue(i,5);
				else 
					iNum = atoi(pRes1->GetResStringValue(i,5)) ;
			}
			
		
			CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes1) ;
		
		}
	}
	else
	{
		/* mysql
		strSQL.Format("SELECT json_extract(t.qc,'$.layer') as 'qclayer',"
			"json_extract(t.qc,'$.bound[0]') as 'level',"
			"json_length(t.qc->'$.layer') as 'num'"
			"FROM (select json_extract(referdata,'$.%s') AS 'qc' from tb_task where id=%I64d ) as t ", strrefertype,iid) ;
			*/

		//postgresql
		strSQL.Format("select qc::json->'layer' as \"qclayer\","
			"qc::json->'bound'->0 as \"level\","
			"json_array_length(qc::json->'layer') as \"num\" "
			"from (select referdata::json->'%s' as \"qc\" from tb_task where id=%I64d) as t", strrefertype,iid);

		pRes1 = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
		if ( pRes1 != NULL)
		{
			int rowcount = pRes1->GetResRowCount();
			
			for(int i = 0; i < rowcount; i++)
			{
				strLayernames.Format("%s",pRes1->GetResStringValue(i,0));
				m_ilevel = atoi(pRes1->GetResStringValue(i,1)) ;
				int type2 = pRes1->GetFieldType(2);
				if(type2 == DBFT_Int) iNum = pRes1->GetResIntValue(i,2);
				else 
					iNum = atoi(pRes1->GetResStringValue(i,2)) ;
			}
			
		
			CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes1) ;
			
		}
	}
	
	if ( iNum > 0 )
	{
		strSQL = "" ;
		CString strmid = "" ;
		while ( iNum >= 0)
		{
			iNum-- ;
			if ( iNum < 0)
			{
				break ;
			}
			CString strtem ;
			/*mysql
			strtem.Format("json_extract('%s','$[%d]') as 'qclayer%d'",strLayernames,iNum,iNum) ;
			*/
			//postgresql
			strtem.Format("'%s'::json->%d as \"qclayer%d\" ",strLayernames,iNum,iNum) ;

			if (strmid != "" )
			{
				strmid += "," ;
			}
			strmid += strtem ;
		}
		strSQL.Format("SELECT %s ", strmid) ;
		pRes1 = CDB_Manager::GetDBManagerPtr()->ExcuteQuerySql(strSQL) ;
		CString strname = "" ;
		
		int rowcount = pRes1->GetResRowCount();
		int num_rows1 = pRes1->GetResFieldCount();

		for(int r = 0; r < rowcount; r++)
		{
			while ( num_rows1 > 0 )
			{
				num_rows1-- ;
				strname = pRes1->GetResStringValue(r,num_rows1) ;
				strname.Replace("\"","");
				m_vtLayerName.push_back(strname.GetBuffer(0)) ;
			}
		}
		CDB_Manager::GetDBManagerPtr()->ReleaseRes(&pRes1) ;
	}
	
	strSQL.Format("select t.*,s.layername from tb_task_link_itemset t, tb_itemset s where t.taskid=%I64d and t.itemsetid=s.id", iid) ;
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
	CTaskLinkItemSet *pTask = new CTaskLinkItemSet() ;
	if ( strrefertype == "qc")
	{
		pTask->SetType(0) ;
	}
	if ( strrefertype == "tool")
	{
		pTask->SetType(1) ;
	}
	
	CDBFieldInfo *pFieldInfo = NULL ;
	CDBValue *pValue = NULL ;
	MAP_RES::iterator it ;
	
	for ( it=mapres.begin(); it!=mapres.end(); it++ )
	{
		VT_RES vtres = it->second ;
		for ( int i=0; i<num_fields; i++ )
		{
			int mysqltype = vtFields.at(i).type ;
			pFieldInfo = new CDBFieldInfo(vtFields[i].name,vtFields[i].table,mysqltype) ;
			pFieldInfo->SetFieldType(DB_FIELDTYPE(mysqltype));//再单独设置一下
			pValue = new CDBValue ;
			pTask->AddField(pFieldInfo, pValue) ;
			CString strval = vtres.at(i).c_str() ;
			DB_FIELDTYPE etype = pFieldInfo->GetFieldType() ;
			switch ( etype)
			{
			case DBFT_Int:
				pTask->SetIntByIndex(i,atoi(strval) ) ;
				break;
			case DBFT_Bigint:
				pTask->SetInt64ByIndex(i,_atoi64(strval) ) ;
				break;
			case DBFT_Double:
				pTask->SetDoubleByIndex(i, atof(strval) ) ;
				break;
			case DBFT_String:
				pTask->SetStringByIndex(i,strval) ;
				break;
			}
		}
		iIndex = pTask->GetIndex("itemsetid") ;
		__int64 iSetID = pTask->GetInt64ByIndex(iIndex) ;
		pTask->SetItemSetID(iSetID) ;
		pTask->LoadLinkInfo() ;
		m_pLinkItemSet = pTask ;
	}
	return true;
}

// 参考的区域
_TSGEO::SGeoRect CQCTask::GetBound() 
{
	return m_sBound ;
}
// 获得参考图层的个数
int CQCTask::GetReferLayerCount() 
{
	return m_vtLayerName.size() ;
}
// 获取参考图层名
const char* CQCTask::GetLayerNameByIndex(int iIndex) 
{
	if ( iIndex < 0 || iIndex>m_vtLayerName.size() )
	{
		return "" ;
	}
	string strlayername = m_vtLayerName.at(iIndex) ;
	return strlayername.c_str() ;
}

void CQCTask::SetBound(_TSGEO::SGeoRect bound)
{
	m_sBound = bound ;
}

void CQCTask::SetLayerName(const char *szLayername)
{
	if ( !m_vtLayerName.empty() )
	{
		if ( find(m_vtLayerName.begin(),m_vtLayerName.end(),szLayername) != m_vtLayerName.end() )
		{
			return ;
		}
	}
	m_vtLayerName.push_back(szLayername) ;
}

int CQCTask::GetReferLevel()
{
	return m_ilevel ;
}

