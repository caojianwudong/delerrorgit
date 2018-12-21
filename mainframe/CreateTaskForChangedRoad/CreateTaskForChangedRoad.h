// CreateTaskForChangedRoad.h : main header file for the CREATETASKFORCHANGEDROAD application
//

#if !defined(AFX_CREATETASKFORCHANGEDROAD_H__CF060BB7_E9EF_40C7_9030_B9AE7ADD9BDA__INCLUDED_)
#define AFX_CREATETASKFORCHANGEDROAD_H__CF060BB7_E9EF_40C7_9030_B9AE7ADD9BDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCreateTaskForChangedRoadApp:
// See CreateTaskForChangedRoad.cpp for the implementation of this class
//

class CCreateTaskForChangedRoadApp : public CWinApp
{
public:
	CCreateTaskForChangedRoadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateTaskForChangedRoadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCreateTaskForChangedRoadApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATETASKFORCHANGEDROAD_H__CF060BB7_E9EF_40C7_9030_B9AE7ADD9BDA__INCLUDED_)
