// DB_ResultSet.cpp: implementation of the CDB_ResultSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DB_Manager.h"
#include "DB_ResultSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDB_ResultSet::CDB_ResultSet()
{

}

CDB_ResultSet::~CDB_ResultSet()
{

}

void CDB_ResultSet::SetResValue(std::vector<std::string> row_value)
{
	m_vtValue.push_back(row_value);
}

void CDB_ResultSet::SetFieldType(int type)
{
	m_vtFieldType.push_back(type);
}

void CDB_ResultSet::SetFieldName(const char* sName)
{
	m_vtFieldName.push_back(sName);
}

int CDB_ResultSet::GetResRowCount()
{
	return m_vtValue.size();
}

int CDB_ResultSet::GetResFieldCount()
{
	return m_vtFieldName.size();
}

const char* CDB_ResultSet::GetResStringValue(int inx_row, int inx_field)
{
	if(inx_row < 0 || inx_row >= GetResRowCount() || inx_field < 0 || inx_field >= GetResFieldCount())
		return "";

	return (m_vtValue[inx_row][inx_field]).c_str();
}

int CDB_ResultSet::GetFieldType(int inx_field)
{
	if(inx_field < 0 || inx_field >= GetResFieldCount())
		return -1;

	return m_vtFieldType[inx_field];
}

const char* CDB_ResultSet::GetFieldName(int inx_field)
{
	if(inx_field < 0 || inx_field >= GetResFieldCount())
		return "";

	return (m_vtFieldName[inx_field]).c_str();
}

int CDB_ResultSet::GetResIntValue(int inx_row, int inx_field)
{
	if(inx_row < 0 || inx_row >= GetResRowCount() || inx_field < 0 || inx_field >= GetResFieldCount())
		return -1;
	
	return atoi((m_vtValue[inx_row][inx_field]).c_str());
}

__int64 CDB_ResultSet::GetResBigIntValue(int inx_row, int inx_field)
{
	if(inx_row < 0 || inx_row >= GetResRowCount() || inx_field < 0 || inx_field >= GetResFieldCount())
		return -1;
	
	return _atoi64((m_vtValue[inx_row][inx_field]).c_str());
}

double CDB_ResultSet::GetResDoubleValue(int inx_row, int inx_field)
{
	if(inx_row < 0 || inx_row >= GetResRowCount() || inx_field < 0 || inx_field >= GetResFieldCount())
		return -1;
	
	return atof((m_vtValue[inx_row][inx_field]).c_str());
}
