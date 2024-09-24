# Using the DrawAnimatedRects() function

Shows how to use the DrawAnimatedRects function to improve the look of your apps.

## Introduction

If you look at MS Word and invoke the find dialog, you can see a neat animation. I wished to mimic this and came across the `DrawAnimatedRects()` function. The `DrawAnimatedRects()` function draws a wire-frame rectangle and animates it to indicate the opening of an icon, or the minimizing or maximizing of a window. The syntax is as follows:

```cpp
BOOL WINAPI DrawAnimatedRects(
  HWND hwnd,            // handle to clipping window
  int idAni,            // type of animation
  CONST RECT *lprcFrom, // rectangle coordinates (minimized)
  CONST RECT *lprcTo    // rectangle coordinates (restored)
);
```

The `lprcFrom` parameter sets where the animation will start, and the `lprcTo` value where the animation will end. For instance, if you wish to make a window appear to expand from a button to a window, you would set `lprcFrom` as the dimensions of the button, and `lprcTo` as the dimensions of the final window position. The effect is not as good as MS Word, but if any GUI experts can provide a MS Word Sample, it will be of great help.

## Using the function

The [sample application](https://raw.githubusercontent.com/ChrisMaunder/drawanimated/master/docs/assets/DrawAnimated_demo1.zip) demonstrates a nice use of the function. In the demo, the About Box is animated so it appears to expand and collapse from a button inside a dialog.

To achieve this, you simply override the `OnCreate` and `OnDestroy` functions in your About Box dialog class, and add calls to `DrawAnimatedRects()` at the appropriate places.

To make things simple, we first store the dimensions of the button where the About Box will expand from. We add a member variable `m_rectFrom` to the About Box class and to make the About Box appear, we use the following.

```cpp
    CAboutDlg about;
    m_ctlButton.GetWindowRect(about.m_rectFrom);
    about.DoModal();
```

where `m_ctlButton` is the button control the About Box is appearing to expand from.

Next, you need to add overrides to `OnCreate` and `OnDestroy` inside your About Box class:

```cpp
int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CDialog::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_rectFrom.IsRectEmpty())
    {
        CRect rectTo(lpCreateStruct->x,lpCreateStruct->y, 
            lpCreateStruct->x + lpCreateStruct->cx,
            lpCreateStruct->y + lpCreateStruct->cy);

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
        DrawAnimatedRects(m_hWnd, IDANI_CAPTION, rect, m_rectFrom);
    }
}
```

This effectively draws the Windows animation sequence either before the window itself appears, or after the window has disappeared.

That's it! A simple method but an effective one.

* * *

**Updated:** Norm Almond has supplied some code that produces the window exploding/imploding effect using a wire frame. The syntax for his function is as follows:

```cpp
void WINAPI DrawWireRects(LPRECT lprcFrom, LPRECT lprcTo, UINT nMilliSecSpeed)
```

The `lprcFrom` parameter sets where the animation will start, and the `lprcTo` value where the animation will end. `nMilliSecSpeed` is the delay in milliseconds between each wire frame being displayed (a value of 20 milliseconds works nicely).

```cpp
////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:    DrawWireRects
//
// DESCRIPTION: Creates exploding wire rectanges
//
// INPUTS:  LPRECT lprcFrom      Source Rectangle
//          LPRECT lprcTo        Destination Rectangle
//          UINT nMilliSecSpeed  Speed in millisecs for animation
//
// RETURN:    None
// NOTES:    None
//
//  Maintenance Log
//  Author      Date    Version     Notes
//  NT Almond   011199  1.0         Origin
//  CJ Maunder  010899  1.1         Modified rectangle transition code
//
/////////////////////////////////////////////////////////////////////////
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
        transition.left   = lprcFrom->left + 
            (int)((lprcTo->left - lprcFrom->left) * dFraction);
        transition.right  = lprcFrom->right + 
            (int)((lprcTo->right - lprcFrom->right) * dFraction);
        transition.top    = lprcFrom->top + 
            (int)((lprcTo->top - lprcFrom->top) * dFraction);
        transition.bottom = lprcFrom->bottom + 
            (int)((lprcTo->bottom - lprcFrom->bottom) * dFraction);

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
```

Demo project number 1 includes this new code. Norm has also produced a class that is part of Demo project number that demonstrates a class `CZoomRect` that can be used to implement his updated Zoom Rect code.

To use his class, include the *ZoomRect.h* header file, create a `CZoomRect` object and call its `Draw()` method:

```cpp
CRect rcStart(10,600,10,600);
CRect rcEnd(600,0,800,200);
int   nDelay = 10;

CZoomRect ZoomRect;
ZoomRect.Draw(NULL, rcStart, rcEnd, nDelay);
```

The first parameter is a handle to the window that should be used for drawing (or `NULL` for the desktop window), the second and third are the start and destination rectangles, and the last is the delay in milliseconds between frames.

* * *

[Michael Dunn](mailto:mdunn@inreach.com) wrote that, in regards to the zooming-outline effect from Word 97, he remembers hearing a co-worker mention a long time ago that really early builds of Win 95 (builds from 1994) used the same effect. It may have been similar to what CE 2.0 does when opening/closing apps.

If you look in *winuser.h*, you'll find two legacy constants, `IDANI_OPEN` and `IDANI_CLOSE`. A first thought was that passing them to `DrawAnimatedRects()` would make the zooming-outline effect, but unfortunately that isn't the case. `DrawAnimatedRects()` only works if you pass `IDANI_CAPTION`.

This has turned more into a history lesson than a solution :), but I just wanted to pass along this tidbit, in case you were wondering about those other two `IDANI_*` constants.
