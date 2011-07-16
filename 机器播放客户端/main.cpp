#include "global.h"

/** ��Ⱦ���� */
bool RenderFunc()
{
    return false;
}

/** �߼����� */
bool FrameFunc()
{
    /** ������Ƶ���� */
    if(g_pTestPlayer == NULL)
    {
        g_pTestPlayer = new CXadillaXVideoPlayer();
        RECT rect;
        rect.left = rect.top = 0;
        rect.right = XSystemFunc::Window.GetScreenWidth(), rect.bottom = XSystemFunc::Window.GetScreenHeight();
        g_pTestPlayer->LoadFile("E:\\Games\\¹����\\LDJ\\Data\\Video\\yaoshiCG.wmv", rect, g_hWnd, false);
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
    /** ����HGE���� */
    g_pHGE = hgeCreate(HGE_VERSION);
    g_pHGE->System_SetState(HGE_WINDOWED, true);
    g_pHGE->System_SetState(HGE_RENDERFUNC, RenderFunc);
    g_pHGE->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    g_pHGE->System_SetState(HGE_SCREENHEIGHT, XSystemFunc::Window.GetScreenHeight());
    g_pHGE->System_SetState(HGE_SCREENWIDTH, XSystemFunc::Window.GetScreenWidth());
    g_pHGE->System_SetState(HGE_SHOWSPLASH, false);

    /** ��ʼ������ */
    if(g_pHGE->System_Initiate())
    {
        /** ��ȡ���ھ�� */
        g_hWnd = g_pHGE->System_GetState(HGE_HWND);

        /** ��ʼ�����庯���� */
        XSystemFunc::Window.SetWindow(g_hWnd);
        XSystemFunc::Window.SetBorder(false);

        /** ���濪ʼ */
        g_pHGE->System_Start();

        /** ... ѭ��ing ... */

        /** ������� */
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
        MessageBox(NULL, "KTVϵͳ��ʼ��ʧ�ܡ�", "ʧ��", MB_ICONERROR);
        return 0;
    }

    return 0;
}
