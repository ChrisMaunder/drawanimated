// DrawAnimatedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DrawAnimated.h"
#include "DrawAnimatedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


///////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	DrawWireRects
//
// DESCRIPTION:	Creates exploding wire rectanges
///
//  INPUTS: LPRECT lprcFrom      Source Rectangle
//	        LPRECT lprcTo        Destination Rectangle
//	        UINT nMilliSecSpeed  Speed in millisecs for animation
//
//	RETURN:	None
//	NOTES:	None
//
//	Maintenance Log
//	Author	    Date    Version     Notes
//	NT Almond   011199  1.0         Origin
//  CJ Maunder  010899  1.1         Modified rectangle transition code
//
////////////////////////////////////////////////////////////////////////////////
void WINAPI DrawWireRects(LPRECT lprcFrom, LPRECT lprcTo, UINT nMilliSecSpeed)
{
    const int nNumSteps = 10;

	GdiFlush();
    Sleep(50);  // Let the desktop window sort itself out

	// if hwnd is null - "you have the CON".
	HDC hDC = ::GetDC(NULL);

	// Pen size, urmmm not too thick
    HPEN hPen = ::CreatePen(PS_SOLID, 2, RGB(0,0,0));

	int nMode = ::SetROP2(hDC, R2_NOT);
	HPEN hOldPen = (HPEN) ::SelectObject(hDC, hPen);

	for (int i = 0; i < nNumSteps; i++)
	{
        double dFraction = (double) i / (double) nNumSteps;

        RECT transition;
        transition.left   = lprcFrom->left + (int)((lprcTo->left - lprcFrom->left) * dFraction);
        transition.right  = lprcFrom->right + (int)((lprcTo->right - lprcFrom->right) * dFraction);
        transition.top    = lprcFrom->top + (int)((lprcTo->top - lprcFrom->top) * dFraction);
        transition.bottom = lprcFrom->bottom + (int)((lprcTo->bottom - lprcFrom->bottom) * dFraction);

		POINT pt[5];
		pt[0] = CPoint(transition.left, transition.top);
		pt[1] = CPoint(transition.right,transition.top);
		pt[2] = CPoint(transition.right,transition.bottom);
		pt[3] = CPoint(transition.left, transition.bottom);
		pt[4] = CPoint(transition.left, transition.top);

		// We use Polyline because we can determine our own pen size
		// Draw Sides
		::Polyline(hDC,pt,5);

		GdiFlush();

		Sleep(nMilliSecSpeed);

		// UnDraw Sides
		::Polyline(hDC,pt,5);

		GdiFlush();
	}

	::SetROP2(hDC, nMode);
	::SelectObject(hDC, hOldPen);

	::ReleaseDC(NULL,hDC);
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	CRect m_rectFrom;
    BOOL  m_bWireFrame;

	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:

	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
    m_bWireFrame = FALSE;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawAnimatedDlg dialog

CDrawAnimatedDlg::CDrawAnimatedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawAnimatedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDrawAnimatedDlg)
	m_bWireFrame = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawAnimatedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawAnimatedDlg)
	DDX_Control(pDX, IDC_BUTTON1, m_ctlButton);
	DDX_Check(pDX, IDC_WIREFRAME, m_bWireFrame);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrawAnimatedDlg, CDialog)
	//{{AFX_MSG_MAP(CDrawAnimatedDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawAnimatedDlg message handlers

BOOL CDrawAnimatedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDrawAnimatedDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDrawAnimatedDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDrawAnimatedDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDrawAnimatedDlg::OnButton1() 
{
    UpdateData();

	CAboutDlg about;
	m_ctlButton.GetWindowRect(about.m_rectFrom);
    about.m_bWireFrame = m_bWireFrame;
	about.DoModal();
}

int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_rectFrom.IsRectEmpty())
	{
		CRect rectTo(lpCreateStruct->x,lpCreateStruct->y, 
			lpCreateStruct->x + lpCreateStruct->cx,
			lpCreateStruct->y + lpCreateStruct->cy);

        if (m_bWireFrame)
            DrawWireRects(m_rectFrom, rectTo, 20);
        else
		    DrawAnimatedRects(m_hWnd, IDANI_CAPTION, m_rectFrom, rectTo);
	}

	return 0;
}

void CAboutDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	if (!m_rectFrom.IsRectEmpty())
	{
		CRect rect;
		GetWindowRect(rect);

        if (m_bWireFrame)
        {
            rect.DeflateRect(2,2);
            DrawWireRects(rect, m_rectFrom, 20);
        }
        else
    		DrawAnimatedRects(m_hWnd,IDANI_CAPTION, rect, m_rectFrom);
	}
}
