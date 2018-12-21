// CWriteLog.h: interface for the CWriteLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CWRITELOG_H__DB0ED908_46F7_4947_824A_D34652DEE420__INCLUDED_)
#define AFX_CWRITELOG_H__DB0ED908_46F7_4947_824A_D34652DEE420__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWriteLog  
{
public:
	CWriteLog();
	virtual ~CWriteLog();

	bool WriteLog(CString msg) ;
	void SetLogPath( CString strLogPath) ;
	bool CreateLog() ;
	bool CloseLog() ;

private: 
	CString m_strLogPath ;

	CString	m_strLogFileName ;
	bool m_bCreateLog ;
	CStdioFile stfile ;

	CString m_strIp;

protected:
	const char* GetIp();
};

#endif // !defined(AFX_CWRITELOG_H__DB0ED908_46F7_4947_824A_D34652DEE420__INCLUDED_)
