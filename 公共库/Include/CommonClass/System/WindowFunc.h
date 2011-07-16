#ifndef WINDOWFUNC_H
#define WINDOWFUNC_H
#include <windows.h>
#include <wtypes.h>

class WindowFunc
{
public:
    WindowFunc();

public:
    void                        SetWindow(HWND hWnd);
    DWORD                       GetWindowWidth();
    DWORD                       GetWindowHeight();
    DWORD                       GetWindowLeft();
    DWORD                       GetWindowTop();

    static DWORD                GetScreenWidth();
    static DWORD                GetScreenHeight();

    void                        SetBorder(bool bBorder);

private:
    HWND                        m_hWnd;
};

#endif
