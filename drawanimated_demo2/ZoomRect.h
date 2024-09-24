// ZoomRect.h: interface for the CZoomRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZOOMRECT_H__A0F8C7E4_73EF_4166_9BCB_5D68DEC1BE5D__INCLUDED_)
#define AFX_ZOOMRECT_H__A0F8C7E4_73EF_4166_9BCB_5D68DEC1BE5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <afxtempl.h>

class CZoomRect
{
public:
	CZoomRect()
	{
		// Make adding the points nice and quick
		m_points.SetSize(100,50);
	}

	~CZoomRect()
	{
		m_points.RemoveAll();
	}

	BOOL WINAPI Draw(HWND hWnd, CRect rcStart,CRect rcEnd, UINT nSleepTime);	


public:
	static void CALLBACK AddPointProc(int nX, int nY, LPARAM lpData);   
		
	CArray<CPoint, CPoint&> m_points;
	void AddPoint(CPoint& point) 
	{   
		m_points.Add(point); 
	}

protected:
	void Rectangle(HDC hDC,CRect rcWire, UINT nSleepTime);

};


#endif // !defined(AFX_ZOOMRECT_H__A0F8C7E4_73EF_4166_9BCB_5D68DEC1BE5D__INCLUDED_)
