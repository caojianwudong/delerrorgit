// CreateTaskForChangedRoadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CreateTaskForChangedRoad.h"
#include "CreateTaskForChangedRoadDlg.h"
#include "CCreateTask.h"
#include "CWriteLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int	TIMER_UPDATE_BLOCK_STATE = 1 ;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateTaskForChangedRoadDlg dialog

CCreateTaskForChangedRoadDlg::CCreateTaskForChangedRoadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateTaskForChangedRoadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateTaskForChangedRoadDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	_CrtSetBreakAlloc(78); //1654为上面内存泄漏的块号。
}

void CCreateTaskForChangedRoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateTaskForChangedRoadDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCreateTaskForChangedRoadDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateTaskForChangedRoadDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_END, OnButtonEnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateTaskForChangedRoadDlg message handlers

BOOL CCreateTaskForChangedRoadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	char path[1024] ;
	::GetModuleFileName( NULL, path, 1024) ;
	CString strAppPath = path ;
	int ipos = strAppPath.ReverseFind('\\') ;
	if ( ipos != -1)
	{
		strAppPath = strAppPath.Left(ipos+1) ;
	}

	CTime time = CTime::GetCurrentTime() ;
	CString strtime = time.Format("_%Y-%m-%d") ;
	
	m_writelog = new CWriteLog() ;
	CString strLogPath = "" ;
	strLogPath.Format("%screatetask_log.txt",strAppPath) ;
	//m_writelog->SetLogPath( strLogPath ) ;
	m_writelog->SetLogPath(strAppPath);
	m_bRun = true ;
	m_bFirst = true ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCreateTaskForChangedRoadDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCreateTaskForChangedRoadDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCreateTaskForChangedRoadDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCreateTaskForChangedRoadDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here

	CCreateTask::GetCreateTaskPtr()->DeleteError() ;
	AfxMessageBox("完成") ;
}

void CCreateTaskForChangedRoadDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnTimer(nIDEvent);
}

void CCreateTaskForChangedRoadDlg::OnButtonEnd() 
{
	// TODO: Add your control notification handler code here
}

void CCreateTaskForChangedRoadDlg::ReadConfig()
{
	char path[1024] ;
	::GetModuleFileName( NULL, path, 1024) ;
	CString strAppPath = path ;
	int ipos = strAppPath.ReverseFind('\\') ;
	if ( ipos != -1)
	{
		strAppPath = strAppPath.Left(ipos+1) ;
	}

	CString strConfigPath = strAppPath + "config\\errortype.ini" ;
	CStdioFile stfile ;

	if ( !stfile.Open(strConfigPath, CFile::modeReadWrite))
	{
		AfxMessageBox(strConfigPath + " 打开失败") ;
		return ;
	}
	
	
	
	stfile.Close() ;

}


BOOL CCreateTaskForChangedRoadDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( m_writelog != NULL )
	{
		m_writelog->CloseLog() ;
		delete m_writelog ;
		m_writelog = NULL ;
	}

	CCreateTask::GetCreateTaskPtr()->Release() ;

	return CDialog::DestroyWindow();
}

bool CCreateTaskForChangedRoadDlg::CheckCurrentAndFrontFinishTime(long timespace )
{
	SYSTEMTIME currentTime ;
	GetLocalTime( &currentTime) ;

	time_t frontt = GetTime_TFromSystemTime(m_frontTime);
	time_t currentt = GetTime_TFromSystemTime( currentTime) ;
	if ( (currentt - frontt) > timespace || (currentt- frontt) >= 59)
	{
		return true ;
	}
	else
	{
		return false ;
	}
}

time_t CCreateTaskForChangedRoadDlg::GetTime_TFromSystemTime( SYSTEMTIME st )
{
	tm temptm = {st.wSecond, 
		st.wMinute, 
		st.wHour, 
		st.wDay, 
		st.wMonth - 1, 
		st.wYear - 1900, 
		st.wDayOfWeek, 
		0, 
		0};
    return mktime(&temptm);
}
