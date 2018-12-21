// DB_Manager.h : main header file for the DB_MANAGER DLL
//

#if !defined(AFX_DB_MANAGER_H__EC3A6BE0_9C47_4196_9E9A_09A54EE3CFD6__INCLUDED_)
#define AFX_DB_MANAGER_H__EC3A6BE0_9C47_4196_9E9A_09A54EE3CFD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDB_ManagerApp
// See DB_Manager.cpp for the implementation of this class
//

class CDB_ManagerApp : public CWinApp
{
public:
	CDB_ManagerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDB_ManagerApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDB_ManagerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB_MANAGER_H__EC3A6BE0_9C47_4196_9E9A_09A54EE3CFD6__INCLUDED_)
