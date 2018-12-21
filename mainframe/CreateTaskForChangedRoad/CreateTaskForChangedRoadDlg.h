// CreateTaskForChangedRoadDlg.h : header file
//

#if !defined(AFX_CREATETASKFORCHANGEDROADDLG_H__6934FEEE_C6A2_4D30_853F_F15DDC93C60F__INCLUDED_)
#define AFX_CREATETASKFORCHANGEDROADDLG_H__6934FEEE_C6A2_4D30_853F_F15DDC93C60F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCreateTaskForChangedRoadDlg dialog
#include "CWriteLog.h"

#include <vector>
#include <map>
using namespace std ;

typedef multimap<CString, CString> MUL_BATCH_ERRORTPE ;

class CWriteLog ;
class CCreateTaskForChangedRoadDlg : public CDialog
{
// Construction
public:
	CCreateTaskForChangedRoadDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateTaskForChangedRoadDlg)
	enum { IDD = IDD_CREATETASKFORCHANGEDROAD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateTaskForChangedRoadDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCreateTaskForChangedRoadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonStart();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonEnd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void				ReadConfig() ;

	// 检查当前时间距离上一次运行完成时间是否满足时间间隔
	bool				CheckCurrentAndFrontFinishTime(long timespace) ;

	// 时间格式转换
	time_t				GetTime_TFromSystemTime( SYSTEMTIME st ) ;

private:
	long				m_timespace ;// 自动运行的时间间隔，单位为毫秒
	CWriteLog			*m_writelog ;
	bool				m_bRun ;
	bool				m_bFirst ;

	SYSTEMTIME			m_frontTime ;

	MUL_BATCH_ERRORTPE	m_mulBatch_Errortype ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATETASKFORCHANGEDROADDLG_H__6934FEEE_C6A2_4D30_853F_F15DDC93C60F__INCLUDED_)
