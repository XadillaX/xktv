#pragma warning(disable: 4995)

#include "global.h"
#include <queue>
#include <string>
std::queue<std::string> playq;

bool RenderFunc()
{
    return false;
}

void InitAfterStart()
{
    g_hWnd = g_pHGE->System_GetState(HGE_HWND);
    XSystemFunc::Window.SetWindow(g_hWnd);

    g_pTestPlayer = new CXadillaXVideoPlayer();
    g_pHGE->Input_SetMousePos(XSystemFunc::Window.GetScreenWidth(), XSystemFunc::Window.GetScreenHeight());
}

void PlayNext()
{
    string filename = playq.front();
    playq.pop();
    playq.push(filename);

    RECT rect;
    rect.left = rect.top = 0;
    rect.right = 800, rect.bottom = 600;

    g_pTestPlayer->LoadFile(filename.c_str(), rect, g_hWnd);
    g_pTestPlayer->Play();
}

bool FrameFunc()
{
    /** 开始之后的初始化 */
    static bool bInited = false;
    static bool bPaused = false;

    if(!bInited)
    {
        bInited = true;
        InitAfterStart();
    }

    /** 播放下一场 */
    if(!g_pTestPlayer->IsPlaying() && !bPaused)
    {
        PlayNext();
    }
    if(g_pHGE->Input_GetKeyState(HGEK_RIGHT))
    {
        PlayNext();
    }

    /** 暂停 */
    if(g_pHGE->Input_GetKeyState(HGEK_SPACE))
    {
        if(bPaused) g_pTestPlayer->Play();
        else g_pTestPlayer->Pause();

        bPaused ^= true;
    }

    /** 若未在播放 */
    //if(!bPaused && (g_pTestPlayer == NULL || !g_pTestPlayer->IsPlaying()))
    //{
    //    g_pHGE->Gfx_BeginScene();
    //    g_pHGE->Gfx_Clear(0xffff0000);
    //    g_pHGE->Gfx_EndScene();
    //}

    if(g_pHGE->Input_GetKeyState(HGEK_ESCAPE)) return true;

    return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    /** 配置HGE引擎 */
    g_pHGE = hgeCreate(HGE_VERSION);
    g_pHGE->System_SetState(HGE_WINDOWED, true);
    g_pHGE->System_SetState(HGE_RENDERFUNC, RenderFunc);
    g_pHGE->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    g_pHGE->System_SetState(HGE_SCREENHEIGHT, XSystemFunc::Window.GetScreenHeight());
    g_pHGE->System_SetState(HGE_SCREENWIDTH, XSystemFunc::Window.GetScreenWidth());

    g_pHGE->System_SetState(HGE_SCREENHEIGHT, 600);
    g_pHGE->System_SetState(HGE_SCREENWIDTH, 800);
    g_pHGE->System_SetState(HGE_WINDOWED, false);

    g_pHGE->System_SetState(HGE_SHOWSPLASH, false);

    /** 播放队列 */
    playq.push("E:\\Games\\鹿鼎记\\LDJ\\Data\\Video\\yaoshiCG.wmv");
    playq.push("E:\\Games\\鹿鼎记\\LDJ\\Data\\Video\\yinzheCG.wmv");
    playq.push("E:\\Games\\鹿鼎记\\LDJ\\Data\\Video\\xianshiCG.wmv");
    playq.push("E:\\Games\\鹿鼎记\\LDJ\\Data\\Video\\mengjiangCG.wmv");
    playq.push("E:\\Games\\鹿鼎记\\LDJ\\Data\\Video\\jiankeCG.wmv");
    playq.push("E:\\Games\\鹿鼎记\\LDJ\\Data\\Video\\huoqiangCG.wmv");

    /** 初始化引擎 */
    if(g_pHGE->System_Initiate())
    {
        /** 引擎开始 */
        g_pHGE->System_Start();

        /** ... 循环ing ... */

        /** 引擎结束 */
        g_pHGE->System_Shutdown();
        g_pHGE->Release();

        if(g_pTestPlayer != NULL)
        {
            delete g_pTestPlayer;
        }
    }
    else
    {
        g_pHGE->Release();
        MessageBox(NULL, "KTV系统初始化失败。", "失败", MB_ICONERROR);
        return 0;
    }

    return 0;
}
