// EMG_OperateExcel.h: interface for the EMG_OperateExcel class.
// ����:��
// �������:2011.12.20
// �汾�ţ�1.0
// 1.0����˵����Excel����������
// ȡ���汾����
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMG_OPERATEEXCEL_H__AC029FA9_CCAD_4EBE_85CE_FFD593CA7895__INCLUDED_)
#define AFX_EMG_OPERATEEXCEL_H__AC029FA9_CCAD_4EBE_85CE_FFD593CA7895__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

class EMG_PJ_EXCEL;

using namespace std;

class __declspec(dllexport) EMG_OperateExcel  
{
public:
	EMG_OperateExcel();

	EMG_PJ_EXCEL*	GetEMG_PJ_EXCELPtr();
	// ����Excel�ļ�
	void	CreateNewExcelFile(CString filePath, CString Password);
	// ��Excel�ļ�
	bool	OpenExcelFile(CString FilePath);
	// �ر�Excel�ļ�
	void	CloseExcelFile();
	// ��ȡ��Ԫ������
	CString GetRangeValue(CString RangePos);
	// ���õ�Ԫ������
	void	SetRangeValue(CString RangePos, CString sValue);
	// ����ͼƬ
	void	InsertOnePicture(CString PictureLocalPath, CString StartRangePos,CString EndRangepos);	
	// �����и�
	void	SetRowHeight(CString RowPos, int height);
	// ��ȡ�и�
	int		GetRowHeight(CString RowPos);
	// �����п�
	void	SetClomnsWidth(CString ColmnsPos,int Width);
	// ��ȡ�п�
	int		GetClomnsWidth(CString ColmnsPos);
	// �ϲ���Ԫ��
	void	CombineRanges(CString StartRange,CString EndRange);
	// �����Ԫ������
	void	ClearRangeContents(CString RangePos);
	// ��ȡ����
	UINT	GetRowsCount( );
	// ��ȡ����
	UINT	GetColumnsCount( );
	// ������
	void	InsertChart(CString ChartTitleName, CString DataSource);
	// ������
	void	InsertLine( CString StartRangePos, CString EndRangePos, float weight,long color ,long style);
	// ���뺯��
	void	InsertFormula(CString RangePos, CString Formula);
	// ��������
	void	SetRangeFont(CString RangePos,CString style, long size);
	// ����������ɫ
	void	SetRangeWordsColor(CString RangePos, long color);
	// ���ñ�����ɫ
	void	SetRangeBackGroundColor(CString RangePos, long ColorIndex);
	// �����������õ�ǰ�Sheet
	void	SetOperateSheetNumber( int number);
	// ��ȡ��ǰ�Sheet������
	int		GetOperateSheetNumber();
	// ���ָ����Χ������
	void	ClearSomeArea(CString StartPos,CString EndPos);
	// ɾ��һ�е�����
	void	ClearOneRowContents(int RowIndex);
	// ���һ�е�����
	void	ClearOneColumnsContents(CString ColIndex);
	// ���õ�ǰ�Sheet����
	void	SetOperateSheetName( CString strSheetName ) ;
	// ����һ��Sheet
	void	AddOneSheet( CString strSheetName ) ;
	// ����Sheet�������õ�ǰ�Sheet
	void	SetOperateSheetByName( CString strSheetName ) ;
	// ��ȡ�Sheet����
	CString GetOperateSheetName() ;

	void	InsertOneRow(int rowIndex) ;
	CString	FindValueInSheets(int sheetIndex, CString searchContent) ;
	int		GetSheetNumberByName(CString strName) ;
	int		GetSheetsNum() ;
	CString	GetSheetNameByNumber(int number) ;
	void	DeleteSheetByNumber(int number) ;
	virtual ~EMG_OperateExcel();

private:

	EMG_PJ_EXCEL*	m_EMG_PJ_EXCEL;
	

};

#endif // !defined(AFX_EMG_OPERATEEXCEL_H__AC029FA9_CCAD_4EBE_85CE_FFD593CA7895__INCLUDED_)
