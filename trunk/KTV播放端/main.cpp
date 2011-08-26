#include "global.h"
#include "commonclass.h"

void InitAfterStart()
{
    ::EnterCriticalSection(&g_CriticalSection);
    g_hWnd = g_pHGE->System_GetState(HGE_HWND);
    XSystemFunc::Window.SetWindow(g_hWnd);

    g_pPlayer = new CXadillaXVideoPlayer();
    g_pHGE->Input_SetMousePos(XSystemFunc::Window.GetScreenWidth(), XSystemFunc::Window.GetScreenHeight());
    ::LeaveCriticalSection(&g_CriticalSection);
}

bool FrameFunc()
{

    return false;
}

bool RenderFunc()
{
    /** 初始化播放器 */
    static bool bInited = false;
    if(!bInited)
    {
        bInited = true;
        InitAfterStart();
    }

    return false;
}

#ifdef _DEBUG
int main(int argv, char* argc[])
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
    g_pHGE = hgeCreate(HGE_VERSION);

    g_pHGE->System_SetState(HGE_TITLE, "KTV点播端");
    g_pHGE->System_SetState(HGE_FPS, 100);
    g_pHGE->System_SetState(HGE_WINDOWED, true);
    g_pHGE->System_SetState(HGE_RENDERFUNC, RenderFunc);
    g_pHGE->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    g_pHGE->System_SetState(HGE_SHOWSPLASH, false);

    ::InitializeCriticalSection(&g_CriticalSection);

    if(g_pHGE->System_Initiate())
    {
        g_pHGE->System_Start();
        g_pHGE->System_Shutdown();
        g_pHGE->Release();

        if(g_pPlayer != NULL) delete g_pPlayer;
    }
    else
    {
        g_pHGE->Release();
        MessageBox(NULL, "KTV系统初始化失败。", "失败", MB_ICONERROR);
        return 0;
    }

    return 0;
}
