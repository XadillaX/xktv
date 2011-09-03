//////////////////////////////////////////////////////////////////////////
//
//	视频播放类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//
//////////////////////////////////////////////////////////////////////////
#include "../公共库/Include/CXadillaXVideoPlayer/CXadillaXVideoPlayer.h"
#include <windows.h>
#include <wtypes.h>
#include <atlbase.h>

#define WM_GRAPHNOTIFY  (WM_APP + 1)
#define SAFEDEL(p) { if(p != NULL) { delete p; p = NULL; } }

DWORD ListenPlayStateThread(LPVOID lpParam)
{
    CXadillaXVideoPlayer* pXVP = (CXadillaXVideoPlayer*)lpParam;
    long evCode, param1, param2;
    HRESULT hr;
    CRITICAL_SECTION m_CS = pXVP->m_CS;

    while(true)
    {
        ::EnterCriticalSection(&m_CS);
        bool flag = SUCCEEDED(pXVP->m_pEvent->GetEvent(&evCode, &param1, &param2, 0));
        ::LeaveCriticalSection(&m_CS);

        if(flag)
        {
            ::EnterCriticalSection(&m_CS);
            hr = pXVP->m_pEvent->FreeEventParams(evCode, param1, param2);
            ::LeaveCriticalSection(&m_CS);

            if((EC_COMPLETE == evCode))
            {
                ::EnterCriticalSection(&m_CS);
                pXVP->m_bStopped = true;
                bool bLoop = pXVP->m_bLoop;
                ::LeaveCriticalSection(&m_CS);

                if(!bLoop)
                {
                    ::EnterCriticalSection(&m_CS);
                    pXVP->m_bPlaying = false;
                    ::LeaveCriticalSection(&m_CS);

                    /** 关闭线程 */
                    pXVP->__Release();

                    /** 退出线程 */
                    return 0;
                }
                else
                {
                    ::EnterCriticalSection(&m_CS);
                    pXVP->m_bKillThread = false;
                    ::LeaveCriticalSection(&m_CS);

                    if(pXVP->LoadFile(pXVP->m_szFilename, pXVP->m_tagRect, pXVP->m_hWnd, pXVP->m_bLoop))
                    {
                        ::EnterCriticalSection(&m_CS);
                        pXVP->m_pMediaControl->Run();
                        ::LeaveCriticalSection(&m_CS);
                    }

                    ::EnterCriticalSection(&m_CS);
                    pXVP->m_bKillThread = true;
                    ::LeaveCriticalSection(&m_CS);
                }
            }
        }

        Sleep(1);
    }

    return 0;
}

CXadillaXVideoPlayer::CXadillaXVideoPlayer(void) :
    m_bPlaying(false),
    m_pGraph(NULL),
    m_pMediaControl(NULL),
    m_pEvent(NULL),
    m_pVidWnd(NULL),
    m_bLoop(false),
    m_bLoaded(false),
    m_hThreadHandle(0),
    m_bKillThread(true),
    m_bStopped(true)
    //m_nVolume(10000),
    //m_pAudio(NULL)
{
    ::InitializeCriticalSection(&m_CS);
}

CXadillaXVideoPlayer::~CXadillaXVideoPlayer(void)
{
    __Release();
}

void CXadillaXVideoPlayer::__Release()
{
    ::EnterCriticalSection(&m_CS);

    if(m_hThreadHandle != 0 && m_bKillThread)
    {
        /** 中断监听线程 */
        TerminateThread(m_hThreadHandle, 0);

        CloseHandle(m_hThreadHandle);
        m_hThreadHandle = 0;
    }

    if(m_pVidWnd)
    {
        m_pVidWnd->put_Visible(OAFALSE);
        //m_pVidWnd->put_Owner(NULL);
    }

    if(m_pGraph)
    {
        m_pGraph->Release();
    }

    if(m_pMediaControl)
    {
        //if(m_bPlaying) m_pMediaControl->Stop();
        m_pMediaControl->Release();
        m_bPlaying = false;
    }

    if(m_pVidWnd)
    {
        m_pVidWnd->Release();
    }

    if(m_pEvent)
    {
        m_pEvent->Release();
    }

    m_pGraph = NULL;
    m_pVidWnd = NULL;
    m_pMediaControl = NULL;
    m_pEvent = NULL;

    m_bPlaying = false;
    m_bStopped = true;
    m_bLoaded = false;

    ::LeaveCriticalSection(&m_CS);
}

bool CXadillaXVideoPlayer::Stop()
{
    if(!m_bLoaded) return false;
    if(m_bStopped) return true;

    if(m_pMediaControl)
    {
        //TerminateThread(m_hThreadHandle, 0);
        //m_hThreadHandle = 0;
        
        __Release();
    }
}

bool CXadillaXVideoPlayer::Pause()
{
    if(!m_bLoaded) return false;

    ::EnterCriticalSection(&m_CS);
    if(m_pMediaControl)
    {
        m_bPlaying = false;
        m_pMediaControl->Pause();
    }
    ::LeaveCriticalSection(&m_CS);

    return true;
}

bool CXadillaXVideoPlayer::Play()
{
    if(!m_bLoaded) return false;

    ::EnterCriticalSection(&m_CS);
    if(m_pMediaControl)
    {
        m_bPlaying = true;
        HRESULT hRes = m_pMediaControl->Run();
        if(!hRes)
        {
            ::LeaveCriticalSection(&m_CS);
            return false;
        }

        /** 创建监听线程 */
        if(!m_hThreadHandle)
        {
            DWORD dwThreadID;
            m_hThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ListenPlayStateThread,
                (LPVOID)this, 0, &dwThreadID);
        }
    }
    else
    {
        ::LeaveCriticalSection(&m_CS);
        return false;
    }
    ::LeaveCriticalSection(&m_CS);

    return true;
}

bool CXadillaXVideoPlayer::LoadFile(const char* filename, RECT rect, HWND hWnd, bool bLoop)
{
    /** 释放上一次资源 */
    __Release();

    ::EnterCriticalSection(&m_CS);
    /** 创建m_pGraph */
    CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
        IID_IGraphBuilder, (void**)&m_pGraph);

    /** 初始化m_pGraph */
    m_pGraph->QueryInterface(IID_IVideoWindow, (void**)&m_pVidWnd);
    m_pGraph->QueryInterface(IID_IMediaEventEx, (void**)&m_pEvent);
    m_pEvent->SetNotifyWindow((OAHWND)hWnd, WM_GRAPHNOTIFY, 0);
    m_pGraph->QueryInterface(IID_IMediaControl, (void**)&m_pMediaControl);
    //m_pGraph->QueryInterface(IID_IBasicAudio, (void**)m_pAudio);
    //m_pAudio->put_Volume(m_nVolume + VOLUME_TRUE_ZERO);

    /** 载入文件 */
    m_hWnd = hWnd;
    WCHAR szFilename[1024];
    memcpy(szFilename, CA2WEX<1024>(filename), sizeof(szFilename));
    m_pGraph->RenderFile(szFilename, NULL);

    /** 播放窗口位置 */
    m_pVidWnd->SetWindowPosition(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
    m_pVidWnd->put_Owner((OAHWND)hWnd);
    m_pVidWnd->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);

    m_bPlaying = false;
    m_bStopped = false;
    m_bLoop = bLoop;
    m_tagRect = rect;
    strcpy(m_szFilename, filename);
    m_bLoaded = true;
    ::LeaveCriticalSection(&m_CS);

    return true;
}
