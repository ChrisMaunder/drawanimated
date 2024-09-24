// DrawAnimated.h : main header file for the DRAWANIMATED application
//

#if !defined(AFX_DRAWANIMATED_H__DD019158_BEE8_11D3_AB3A_0050BAD05CD9__INCLUDED_)
#define AFX_DRAWANIMATED_H__DD019158_BEE8_11D3_AB3A_0050BAD05CD9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDrawAnimatedApp:
// See DrawAnimated.cpp for the implementation of this class
//

class CDrawAnimatedApp : public CWinApp
{
public:
	CDrawAnimatedApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawAnimatedApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDrawAnimatedApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWANIMATED_H__DD019158_BEE8_11D3_AB3A_0050BAD05CD9__INCLUDED_)
