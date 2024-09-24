// ZoomRect.cpp: implementation of the CZoomRect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZoomRect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	DrawWireRects
//
// DESCRIPTION:	Creates exploding wire rectanges
///
// INPUTS:		CRect rcSrc				Source Rectangle
//				CRect rcDest			Destination Rectangle
//				UINT nMilliSecSpeed		Speed in millisecs for animation
//
//	RETURN:		None
//	NOTES:		None
//
//	Maintenance Log
//	Author		Date	Version		Notes
//	NT Almond	011199	1.0			Origin
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	AddPointProc
//
// DESCRIPTION:	LineDDAs required callback function to add points to Array
///
// INPUTS:		int nX			- x coordinate
//				int nY			- y coordinate
//				LPARAM lpData	- User Defined Data 
//
//	RETURN:		None
//	NOTES:		None
//
//	Maintenance Log
//	Author		Date	Version		Notes
//	NT Almond	190100	1.0			Origin
//
////////////////////////////////////////////////////////////////////////////////
void CALLBACK CZoomRect::AddPointProc(int nX, int nY, LPARAM lpData)
{
	CZoomRect* pThis = (CZoomRect*)lpData;

	ASSERT(pThis); 

	pThis->AddPoint(CPoint(nX,nY));
}

///////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	Draw
//
// DESCRIPTION:	Creates zooming rectangle effects
///
// INPUTS:		CRect rcSrc				Source Rectangle
//				CRect rcDest			Destination Rectangle
//				UINT nMilliSecSpeed		Speed in millisecs for animation
//
//	RETURN:		None
//	NOTES:		None
//
//	Maintenance Log
//	Author		Date	Version		Notes
//	NT Almond	190100	1.0			Origin
//
////////////////////////////////////////////////////////////////////////////////
BOOL WINAPI CZoomRect::Draw(HWND hWnd, CRect rcStart, CRect rcEnd, UINT nSleepTime)
{

	CPoint ptStart = rcStart.CenterPoint();
	CPoint ptEnd = rcEnd.CenterPoint();


	m_points.RemoveAll();

	LineDDA(ptStart.x, ptStart.y, ptEnd.x, ptEnd.y,CZoomRect::AddPointProc, (LPARAM) this);

	// Are the centre points of the source and destination rectangles the same?
	// if so no points will be drawn, so add some dummy points
	if (m_points.GetSize() == 0)
	{
		for (int i=0;i < 100;i++)
			m_points.Add(ptStart);
	}			
		

	HDC hDC = GetDC(hWnd);

	SetROP2 (hDC,R2_NOT) ;

	HPEN hPen = ::CreatePen(PS_SOLID, 2, RGB(0,0,0));

	SelectObject (hDC,hPen) ;

	int nWidth = 0;
	int nHeight = 0;

	int nAreaFrom = rcStart.Width() * rcStart.Height();
	int nAreaTo = rcEnd.Width() * rcEnd.Height();

	BOOL bExplode = nAreaTo > nAreaFrom;

	if (bExplode)
	{
		nWidth =  rcStart.Width() - rcEnd.Width();
		nHeight = rcStart.Height() - rcEnd.Height();
	}
	else
	{
		nWidth =  rcEnd.Width() - rcStart.Width();
		nHeight = rcEnd.Height() - rcStart.Height();
	}

	int nPercent = (m_points.GetSize()) / 10;

	int nXFlate = (int) ((double) nWidth  / (double) nPercent);
	int nYFlate = (int) ((double) nHeight / (double) nPercent);
	double nXStep = 0;
	double nYStep = 0;

	CRect rcWire;
	CPoint pt;


	for (int n=0;n < m_points.GetSize(); n+=10)
	{
		pt = m_points.GetAt(n);
		rcWire.SetRect(pt.x, pt.y,pt.x, pt.y);
		if (!bExplode)
			rcWire.InflateRect(rcStart.Width() / 2, rcStart.Height() / 2);

		rcWire.InflateRect((int) (nXStep/2.0),(int)(nYStep/2.0));

		Rectangle(hDC, rcWire, nSleepTime);

		nXStep += nXFlate;
		nYStep += nYFlate;
	}

	Rectangle(hDC, rcEnd, nSleepTime);

	SelectObject (hDC, (HPEN) NULL);

	DeleteObject(hPen);

	ReleaseDC(NULL, hDC);

	return TRUE;
}


void CZoomRect::Rectangle(HDC hDC,CRect rcWire, UINT nSleepTime)
{

    CPoint pt[5];
    pt[0] = CPoint(rcWire.left, rcWire.top);
    pt[1] = CPoint(rcWire.right, rcWire.top);
    pt[2] = CPoint(rcWire.right, rcWire.bottom);
    pt[3] = CPoint(rcWire.left, rcWire.bottom);
    pt[4] = CPoint(rcWire.left, rcWire.top);

    // Draw Sides
    Polyline(hDC,pt,5);
    GdiFlush();

    Sleep(nSleepTime);

		// UnDraw Sides
    Polyline(hDC,pt,5);
		GdiFlush();

    TRACE("Result: %d,%d %d,%d\n",rcWire.left,rcWire.top, rcWire.right, rcWire.bottom);


}
