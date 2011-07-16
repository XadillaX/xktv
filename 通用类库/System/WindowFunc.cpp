#include "System/WindowFunc.h"

WindowFunc::WindowFunc() :
    m_hWnd(0)
{
}

void WindowFunc::SetWindow(HWND hWnd)
{
    m_hWnd = hWnd;
}

DWORD WindowFunc::GetWindowWidth()
{
    if(m_hWnd == 0) return 0;

    RECT rect;
    GetWindowRect(m_hWnd, &rect);
    return rect.right - rect.left;
}

DWORD WindowFunc::GetWindowHeight()
{
    if(m_hWnd == 0) return 0;

    RECT rect;
    GetWindowRect(m_hWnd, &rect);
    return rect.bottom - rect.top;
}

DWORD WindowFunc::GetWindowLeft()
{
    if(m_hWnd == 0) return 0;

    RECT rect;
    GetWindowRect(m_hWnd, &rect);
    return rect.left;
}

DWORD WindowFunc::GetWindowTop()
{
    if(m_hWnd == 0) return 0;

    RECT rect;
    GetWindowRect(m_hWnd, &rect);
    return rect.top;
}

DWORD WindowFunc::GetScreenWidth()
{
    return GetSystemMetrics(SM_CXSCREEN);
}

DWORD WindowFunc::GetScreenHeight()
{
    return GetSystemMetrics(SM_CYSCREEN);
}

void WindowFunc::SetBorder(bool bBorder)
{
    if(0 == m_hWnd) return;

    DWORD l = GetWindowLong(m_hWnd, GWL_STYLE);
    DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE| WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;   
    if(bBorder)
    {
        l |= dwNewStyle;
    }
    else
    {
        l &= dwNewStyle;
    }

    ::SetWindowLong(m_hWnd, GWL_STYLE, l);
}
