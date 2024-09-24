// ZoomRectDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ZoomRectDemo.h"
#include "ZoomRectDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomRectDemoApp

BEGIN_MESSAGE_MAP(CZoomRectDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CZoomRectDemoApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomRectDemoApp construction

CZoomRectDemoApp::CZoomRectDemoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CZoomRectDemoApp object

CZoomRectDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CZoomRectDemoApp initialization

BOOL CZoomRectDemoApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CZoomRectDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
