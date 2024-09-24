// DrawAnimatedDlg.h : header file
//

#if !defined(AFX_DRAWANIMATEDDLG_H__DD01915A_BEE8_11D3_AB3A_0050BAD05CD9__INCLUDED_)
#define AFX_DRAWANIMATEDDLG_H__DD01915A_BEE8_11D3_AB3A_0050BAD05CD9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDrawAnimatedDlg dialog

class CDrawAnimatedDlg : public CDialog
{
// Construction
public:
	CDrawAnimatedDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDrawAnimatedDlg)
	enum { IDD = IDD_DRAWANIMATED_DIALOG };
	CButton	m_ctlButton;
	BOOL	m_bWireFrame;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawAnimatedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDrawAnimatedDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWANIMATEDDLG_H__DD01915A_BEE8_11D3_AB3A_0050BAD05CD9__INCLUDED_)
