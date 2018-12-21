// TaskManager.h : main header file for the TASKMANAGER DLL
//

#if !defined(AFX_TASKMANAGER_H__07C317A5_A780_4F0B_B8F7_09FDB14B3B47__INCLUDED_)
#define AFX_TASKMANAGER_H__07C317A5_A780_4F0B_B8F7_09FDB14B3B47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTaskManagerApp
// See TaskManager.cpp for the implementation of this class
//

class CTaskManagerApp : public CWinApp
{
public:
	CTaskManagerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTaskManagerApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTaskManagerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKMANAGER_H__07C317A5_A780_4F0B_B8F7_09FDB14B3B47__INCLUDED_)
