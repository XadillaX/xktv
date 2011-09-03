#include "../公共库/Include/CXadillaXVideoPlayer/CXadillaXVideoPlayer.h"
#include <windows.h>
#include <wtypes.h>
#include <atlbase.h>
#include <vector>

#define WM_GRAPHNOTIFY              (WM_APP + 1)
#define SAFEDEL(p)                  { if(p != NULL) { delete p; p = NULL; } }

std::vector<CXadillaXVideoPlayer*>  _pPlayer;
CRITICAL_SECTION                    _cs;
bool                                _csinited = false;

struct _thread_param
{
    int PlayerID;
    int PlayID;
};

DWORD ListenPlayStateThread(LPVOID lpParam)
{
    _thread_param* tp = (_thread_param*)lpParam;
    int PlayerID = tp->PlayerID;
    int PlayID = tp->PlayID;
    delete tp;

    long evCode, param1, param2;
    HRESULT hr;

    /** 进入全局临界区 */
    ::EnterCriticalSection(&_cs);

    /** 若自己监听的播放器对象不存在 */
    if(_pPlayer[PlayerID] == NULL)
    {
        ::LeaveCriticalSection(&_cs);
        return 0;
    }

    //::EnterCriticalSection(&_pPlayer[PlayerID]->m_CS);
    HRESULT hRes = _pPlayer[PlayerID]->m_pMediaControl->Run();
    //::LeaveCriticalSection(&_pPlayer[PlayerID]->m_CS);

    //if(S_FALSE == hRes)
    //{
    //    _pPlayer[PlayerID]->__Release();

    //    ::LeaveCriticalSection(&_cs);
    //    return 0;
    //}

    ::LeaveCriticalSection(&_cs);

    while(true)
    {
        /** 进入全局临界区 */
        ::EnterCriticalSection(&_cs);

        /** 若自己监听的播放器对象不存在 */
        if(_pPlayer[PlayerID] == NULL)
        {
            ::LeaveCriticalSection(&_cs);
            return 0;
        }

        CXadillaXVideoPlayer* player = _pPlayer[PlayerID];
        ::EnterCriticalSection(&(player->m_CS));

        /** 若已经不再播放当前视频 */
        if(PlayID != player->m_nCurPlayID)
        {
            ::LeaveCriticalSection(&(player->m_CS));
            ::LeaveCriticalSection(&_cs);

            return 0;
        }

        /** 监听 */
        if(SUCCEEDED(player->m_pEvent->GetEvent(&evCode, &param1, &param2, 0)))
        {
            hr = player->m_pEvent->FreeEventParams(evCode, param1, param2);

            if(EC_COMPLETE == evCode)
            {
                player->m_bStopped = true;

                if(!player->m_bLoop)
                {
                    ::LeaveCriticalSection(&(player->m_CS));
                    player->__Release();
                    ::LeaveCriticalSection(&_cs);

                    return 0;
                }
                else
                {
                    ::LeaveCriticalSection(&(player->m_CS));
                    if(player->LoadFile(player->m_szFilename, player->m_tagRect, player->m_hWnd, player->m_bLoop))
                    {
                        player->Play();
                    }
                    ::LeaveCriticalSection(&_cs);

                    return 0;
                }
            }
        }

        ::LeaveCriticalSection(&(player->m_CS));
        ::LeaveCriticalSection(&_cs);

        Sleep(1);
    }

    return 0;
}

CXadillaXVideoPlayer::CXadillaXVideoPlayer() :
    m_bPlaying(false),
    m_bStopped(false),
    m_bLoop(false),
    m_bLoaded(false),
    m_nPlayID(0),
    m_nCurPlayID(-1),
    m_hThreadHandle(0),
    m_hWnd(0),
    m_pGraph(NULL),
    m_pVidWnd(NULL),
    m_pMediaControl(NULL),
    m_pEvent(NULL)
{
    ::InitializeCriticalSection(&m_CS);

    /** 播放器全局临界区 */
    if(!_csinited)
    {
        _csinited = true;
        ::InitializeCriticalSection(&_cs);
    }

    /** 播放器加入播放器列表 */
    ::EnterCriticalSection(&_cs);
    _pPlayer.push_back(this);
    m_nPlayerID = _pPlayer.size() - 1;
    ::LeaveCriticalSection(&_cs);
}

CXadillaXVideoPlayer::~CXadillaXVideoPlayer()
{
    /** 进入全局临界区 */
    ::EnterCriticalSection(&_cs);

    /** 从播放器列表中删除自己（线程中会用到） */
    _pPlayer[m_nPlayerID] = NULL;

    /** 释放资源 */
    __Release();

    /** 退出全局临界区 */
    ::LeaveCriticalSection(&_cs);
}

void CXadillaXVideoPlayer::__Release()
{
    ::EnterCriticalSection(&m_CS);

    if(m_pVidWnd != NULL)
    {
        m_pVidWnd->put_Visible(OAFALSE);
    }

    if(m_pGraph != NULL)
    {
        m_pGraph->Release();
    }

    if(m_pMediaControl != NULL)
    {
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
    m_nCurPlayID = -1;

    //::CloseHandle(m_hThreadHandle);

    ::LeaveCriticalSection(&m_CS);
}

bool CXadillaXVideoPlayer::Stop()
{
    ::EnterCriticalSection(&m_CS);

    /** 若未载入 */
    if(!m_bLoaded)
    {
        ::LeaveCriticalSection(&m_CS);
        return false;
    }

    /** 若已暂停 */
    if(m_bStopped)
    {
        ::LeaveCriticalSection(&m_CS);
        return true;
    }

    if(m_pMediaControl != NULL)
    {
        m_nCurPlayID = -1;
        ::LeaveCriticalSection(&m_CS);

        __Release();
        return true;
    }

    ::LeaveCriticalSection(&m_CS);
    return true;
}

bool CXadillaXVideoPlayer::Pause()
{
    ::EnterCriticalSection(&m_CS);

    /** 若未载入 */
    if(!m_bLoaded)
    {
        ::LeaveCriticalSection(&m_CS);
        return false;
    }

    if(m_pMediaControl != NULL)
    {
        m_bPlaying = false;
        m_pMediaControl->Pause();
    }
    ::LeaveCriticalSection(&m_CS);

    return true;
}

bool CXadillaXVideoPlayer::Play()
{
    ::EnterCriticalSection(&m_CS);

    /** 若未载入 */
    if(!m_bLoaded)
    {
        ::LeaveCriticalSection(&m_CS);
        return false;
    }

    if(m_pMediaControl != NULL)
    {
        m_bPlaying = true;
        //if(S_FALSE == hRes)
        //{
        //    ::LeaveCriticalSection(&m_CS);
        //    return false;
        //}

        /** 创建监听线程 */
        m_nPlayID++;
        m_nCurPlayID = m_nPlayID;

        _thread_param* tp = new _thread_param();
        tp->PlayerID = m_nPlayerID;
        tp->PlayID = m_nPlayID;

        DWORD dwThreadID;
        m_hThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ListenPlayStateThread,
            (LPVOID)tp, 0, &dwThreadID);

        ::LeaveCriticalSection(&m_CS);
        return true;
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

    /** 创建Graph */
    CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
        IID_IGraphBuilder, (void**)&m_pGraph);

    /** 初始化m_pGraph */
    m_pGraph->QueryInterface(IID_IVideoWindow, (void**)&m_pVidWnd);
    m_pGraph->QueryInterface(IID_IMediaEventEx, (void**)&m_pEvent);
    m_pEvent->SetNotifyWindow((OAHWND)hWnd, WM_GRAPHNOTIFY, 0);
    m_pGraph->QueryInterface(IID_IMediaControl, (void**)&m_pMediaControl);

    /** 载入文件 */
    m_hWnd = hWnd;
    WCHAR szFilename[1024];
    memcpy(szFilename, CA2WEX<1024>(filename), sizeof(szFilename));
    HRESULT hRes = m_pGraph->RenderFile(szFilename, NULL);

    /** 载入失败 */
    if(hRes != S_OK && hRes != VFW_S_AUDIO_NOT_RENDERED && hRes != VFW_S_DUPLICATE_NAME &&
        hRes != VFW_S_PARTIAL_RENDER && hRes != VFW_S_VIDEO_NOT_RENDERED)
    {
        m_bLoaded = false;
        
        m_pVidWnd->put_Visible(OAFALSE);
        m_pGraph->Release();
        m_pMediaControl->Release();
        m_pVidWnd->Release();
        m_pEvent->Release();

        m_pVidWnd = NULL;
        m_pGraph = NULL;
        m_pMediaControl = NULL;
        m_pEvent = NULL;

        ::LeaveCriticalSection(&m_CS);
        return false;
    }

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
    m_nCurPlayID = -1;

    ::LeaveCriticalSection(&m_CS);

    return true;
}

bool CXadillaXVideoPlayer::IsLoaded()
{
    ::EnterCriticalSection(&m_CS);
    bool rst = m_bLoaded;
    ::LeaveCriticalSection(&m_CS);

    return rst;
}

bool CXadillaXVideoPlayer::IsPlaying()
{
    ::EnterCriticalSection(&m_CS);
    bool rst = m_bPlaying;
    ::LeaveCriticalSection(&m_CS);

    return rst;
}
