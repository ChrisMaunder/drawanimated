// ZoomRectDemoDlg.h : header file
//

#if !defined(AFX_ZOOMRECTDEMODLG_H__48D72269_D47A_11D3_A437_8D5F497A53B6__INCLUDED_)
#define AFX_ZOOMRECTDEMODLG_H__48D72269_D47A_11D3_A437_8D5F497A53B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CZoomRectDemoDlg dialog

class CZoomRectDemoDlg : public CDialog
{
// Construction
public:
	CZoomRectDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CZoomRectDemoDlg)
	enum { IDD = IDD_ZOOMRECTDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomRectDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CZoomRectDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMRECTDEMODLG_H__48D72269_D47A_11D3_A437_8D5F497A53B6__INCLUDED_)
