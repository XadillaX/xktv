#include "global.h"

/** 渲染函数 */
bool RenderFunc()
{
    return false;
}

/** 逻辑函数 */
bool FrameFunc()
{
    /** 测试视频播放 */
    if(g_pTestPlayer == NULL)
    {
        g_pTestPlayer = new CXadillaXVideoPlayer();
        RECT rect;
        rect.left = rect.top = 0;
        rect.right = XSystemFunc::Window.GetScreenWidth(), rect.bottom = XSystemFunc::Window.GetScreenHeight();
        g_pTestPlayer->LoadFile("E:\\Games\\鹿鼎记\\LDJ\\Data\\Video\\yaoshiCG.wmv", rect, g_hWnd, false);
        g_pTestPlayer->Play();
        g_pHGE->Input_SetMousePos(XSystemFunc::Window.GetScreenWidth(), XSystemFunc::Window.GetScreenHeight());
    }

    if(g_pTestPlayer == NULL || !g_pTestPlayer->IsPlaying())
    {
        g_pHGE->Gfx_BeginScene();
        g_pHGE->Gfx_Clear(0xffff0000);
        g_pHGE->Gfx_EndScene();
    }

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
    g_pHGE->System_SetState(HGE_SHOWSPLASH, false);

    /** 初始化引擎 */
    if(g_pHGE->System_Initiate())
    {
        /** 获取窗口句柄 */
        g_hWnd = g_pHGE->System_GetState(HGE_HWND);

        /** 初始化窗体函数类 */
        XSystemFunc::Window.SetWindow(g_hWnd);
        XSystemFunc::Window.SetBorder(false);

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
