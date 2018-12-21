#if !defined(AFX_CUSERLOGIN_H__33A4DB22_00D8_4078_9457_EDC274CCF974__INCLUDED_)
#define AFX_CUSERLOGIN_H__33A4DB22_00D8_4078_9457_EDC274CCF974__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CUserLogin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// UserLogin dialog

#include <openssl\md5.h>
#include <map>
#include <string>
#include <vector>

using namespace std;

class UserLogin : public CDialog
{
// Construction
public:
	void SetParentHwnd( HWND hwnd);
	UserLogin(CWnd* pParent = NULL);   // standard constructor
	~UserLogin();

	CString GetUserName();
	CString GetUserPass();
	CString GetUserPost();

// Dialog Data
	//{{AFX_DATA(UserLogin)
	enum { IDD = IDD_DIALOG_USER_LOGIN };
	CComboBox	m_combEdit;
	CComboBox	m_combPost;
	CString	m_csUserName;
	CString	m_csUserPass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(UserLogin)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(UserLogin)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void InitEditType();//初始化编辑类型
	char *get_md5(const char *ch_id, char *ch_md5);
	
	//恢复上次登录的用户信息
	void ResumeDir();
	
	//记录每次登录的用户信息
	void SaveAllDir();
	
	MD5_CTX *m_pMd5Ptr;

	HWND m_hwndParaent;

	//加载位图用的
	RECT rect;
    BITMAP bm;
    HBITMAP hBitmap;
    HDC hSrcDC;
    HDC hDesDC;
    CWnd *hwnd;

	std::map<std::string, int> m_mapEdit;
	std::vector< std::pair<int,std::string> > m_vecPost;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSERLOGIN_H__33A4DB22_00D8_4078_9457_EDC274CCF974__INCLUDED_)
