// ZoomRectDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZoomRectDemo.h"
#include "ZoomRectDemoDlg.h"

#include "ZoomRect.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomRectDemoDlg dialog

CZoomRectDemoDlg::CZoomRectDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomRectDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZoomRectDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZoomRectDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomRectDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CZoomRectDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CZoomRectDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomRectDemoDlg message handlers

BOOL CZoomRectDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CZoomRectDemoDlg::OnPaint() 
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

HCURSOR CZoomRectDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CZoomRectDemoDlg::OnButton1() 
{
    int n = rand() % 6;

    CRect rcStart, rcEnd;
    int   nDelay;

    switch (n)
    {
        case 0:
            rcStart.SetRect(0,0,20,20);
            rcEnd.SetRect(200,200,600,600);
            nDelay = 10;
            break;

        case 1:
            rcStart.SetRect(200,200,600,600);
            rcEnd.SetRect(0,0,20,20);
            nDelay = 10;
            break;

        case 2:
            rcStart.SetRect(400,400,400,400);
            rcEnd.SetRect(100,100,700,700);
            nDelay = 50;
            break;

        case 3:
            rcStart.SetRect(100,100,700,700);
            rcEnd.SetRect(400,400,400,400);
            nDelay = 50;
            break;

        case 4:
            rcStart.SetRect(700,20,700,20);
            rcEnd.SetRect(10,500,200,610);
            nDelay = 10;
            break;

        case 5:
        default:
            rcStart.SetRect(10,600,10,600);
            rcEnd.SetRect(600,0,800,200);
            nDelay = 10;
            break;
    }

	CZoomRect m_ZoomRect;
    m_ZoomRect.Draw(NULL, rcStart, rcEnd, nDelay);
}
