#include "global.h"
#include "commonclass.h"
#include "commoncommand.h"

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
    /** 初始化播放器 */
    static bool bInited = false;
    if(!bInited)
    {
        bInited = true;
        InitAfterStart();
    }

    ::EnterCriticalSection(&g_CriticalSection);
    if((g_pPlayer == NULL || (!g_pPlayer->IsPlaying() && !g_bPaused)) && !g_bRequestingSong)
    {
        /** 请求歌曲 */
        static int times = 0;
        printf("%d. 请求歌曲...\n", times++);
        char tmp[] = "\0";
        g_pNetwork->SendMsg(MAINID_REQUEST_SONG, SUBID_REQUEST_NEXT_SONG, tmp, 1);
        g_bRequestingSong = true;
    }
    ::LeaveCriticalSection(&g_CriticalSection);

    return false;
}

bool RenderFunc()
{

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
    g_pHGE->System_SetState(HGE_INIFILE, "config.ini");
    g_pHGE->System_SetState(HGE_DONTSUSPEND, true);

#ifdef _DEBUG
    g_pHGE->System_SetState(HGE_SCREENWIDTH, 320);
    g_pHGE->System_SetState(HGE_SCREENHEIGHT, 240);
#endif

    ::InitializeCriticalSection(&g_CriticalSection);

    if(g_pHGE->System_Initiate())
    {
        string szSrv = string("tcp://*:") + XStringFunc::IntToString(g_pHGE->Ini_GetInt("network", "localport", 5555));
        string szClt = string("tcp://") + g_pHGE->Ini_GetString("network", "serveraddress", "localhost") + string(":") + XStringFunc::IntToString(g_pHGE->Ini_GetInt("network", "serverport", 3456));
        g_pNetwork = new CKTVNetwork121(szSrv.c_str(), szClt.c_str(), NetworkReceive);

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

    delete g_pNetwork;

    return 0;
}
