// EMG_OperateExcel.h: interface for the EMG_OperateExcel class.
// 作者:彭江
// 完成日期:2011.12.20
// 版本号：1.0
// 1.0功能说明：Excel操作单例类
// 取代版本：无
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
	// 创建Excel文件
	void	CreateNewExcelFile(CString filePath, CString Password);
	// 打开Excel文件
	bool	OpenExcelFile(CString FilePath);
	// 关闭Excel文件
	void	CloseExcelFile();
	// 获取单元格内容
	CString GetRangeValue(CString RangePos);
	// 设置单元格内容
	void	SetRangeValue(CString RangePos, CString sValue);
	// 插入图片
	void	InsertOnePicture(CString PictureLocalPath, CString StartRangePos,CString EndRangepos);	
	// 设置行高
	void	SetRowHeight(CString RowPos, int height);
	// 获取行高
	int		GetRowHeight(CString RowPos);
	// 设置列宽
	void	SetClomnsWidth(CString ColmnsPos,int Width);
	// 获取列宽
	int		GetClomnsWidth(CString ColmnsPos);
	// 合并单元格
	void	CombineRanges(CString StartRange,CString EndRange);
	// 清除单元格内容
	void	ClearRangeContents(CString RangePos);
	// 获取行数
	UINT	GetRowsCount( );
	// 获取列数
	UINT	GetColumnsCount( );
	// 插入表格
	void	InsertChart(CString ChartTitleName, CString DataSource);
	// 插入线
	void	InsertLine( CString StartRangePos, CString EndRangePos, float weight,long color ,long style);
	// 插入函数
	void	InsertFormula(CString RangePos, CString Formula);
	// 设置字体
	void	SetRangeFont(CString RangePos,CString style, long size);
	// 设置字体颜色
	void	SetRangeWordsColor(CString RangePos, long color);
	// 设置背景颜色
	void	SetRangeBackGroundColor(CString RangePos, long ColorIndex);
	// 根据索引设置当前活动Sheet
	void	SetOperateSheetNumber( int number);
	// 获取当前活动Sheet的索引
	int		GetOperateSheetNumber();
	// 清除指定范围的内容
	void	ClearSomeArea(CString StartPos,CString EndPos);
	// 删除一行的内容
	void	ClearOneRowContents(int RowIndex);
	// 清除一列的内容
	void	ClearOneColumnsContents(CString ColIndex);
	// 设置当前活动Sheet名称
	void	SetOperateSheetName( CString strSheetName ) ;
	// 插入一个Sheet
	void	AddOneSheet( CString strSheetName ) ;
	// 根据Sheet名称设置当前活动Sheet
	void	SetOperateSheetByName( CString strSheetName ) ;
	// 获取活动Sheet名称
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
