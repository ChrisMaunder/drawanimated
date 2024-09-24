// ZoomRectDemo.h : main header file for the ZOOMRECTDEMO application
//

#if !defined(AFX_ZOOMRECTDEMO_H__48D72267_D47A_11D3_A437_8D5F497A53B6__INCLUDED_)
#define AFX_ZOOMRECTDEMO_H__48D72267_D47A_11D3_A437_8D5F497A53B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CZoomRectDemoApp:
// See ZoomRectDemo.cpp for the implementation of this class
//

class CZoomRectDemoApp : public CWinApp
{
public:
	CZoomRectDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomRectDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZoomRectDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMRECTDEMO_H__48D72267_D47A_11D3_A437_8D5F497A53B6__INCLUDED_)
