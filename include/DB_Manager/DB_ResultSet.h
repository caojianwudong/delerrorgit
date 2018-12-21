// DB_ResultSet.h: interface for the CDB_ResultSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB_RESULTSET_H__50EDBBDF_22F8_4F5E_8035_C8629894614A__INCLUDED_)
#define AFX_DB_RESULTSET_H__50EDBBDF_22F8_4F5E_8035_C8629894614A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <VECTOR>

using namespace std;

enum DBFIELDTYPE
{
	DBFT_Unkown = 0,
	DBFT_Int = 1,
	DBFT_Double = 2,
	DBFT_String = 3,
	DBFT_Bigint = 4
};



class __declspec(dllexport)CDB_ResultSet  
{
public:
	CDB_ResultSet();
	virtual ~CDB_ResultSet();

	//��ȡ��ǰ�����������
	int GetResRowCount();

	//��ȡ��ǰ����������Ը���
	int GetResFieldCount();

	//��ȡ��ǰ�����ָ��λ�õ�����
	//inx_row:������
	//inx_field:������
	const char* GetResStringValue(int inx_row, int inx_field);
	int GetResIntValue(int inx_row, int inx_field);
	__int64 GetResBigIntValue(int inx_row, int inx_field);
	double GetResDoubleValue(int inx_row, int inx_field);

	//��ȡָ����������������
	int GetFieldType(int inx_field);

	//��ȡָ����������������
	const char* GetFieldName(int inx_field);


};

#endif // !defined(AFX_DB_RESULTSET_H__50EDBBDF_22F8_4F5E_8035_C8629894614A__INCLUDED_)
