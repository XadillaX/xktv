//////////////////////////////////////////////////////////////////////////
//
//	视频播放类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//
//////////////////////////////////////////////////////////////////////////
#ifndef CXADILLAXVIDEOPLAYER_H
#define CXADILLAXVIDEOPLAYER_H

#include <tchar.h>
#include <DShow.h>
#pragma comment(lib, "Strmiids.lib")
#pragma comment(lib, "Quartz.lib")

#define VOLUME_TRUE_ZERO                -10000

#pragma once
class CXadillaXVideoPlayer
{
    friend DWORD ListenPlayStateThread(LPVOID lpParam);

public:
    CXadillaXVideoPlayer(void);
    virtual ~CXadillaXVideoPlayer(void);

    bool                                LoadFile(const char* filename, RECT rect, HWND hWnd, bool bLoop = false);
    bool                                Play();
    bool                                Pause();
    bool                                Stop();

    bool                                IsLoaded() { return m_bLoaded; }
    bool                                IsPlaying() { return m_bPlaying; }
    void                                SetVolume(long vol) { m_nVolume = vol; }

private:
    void                                __Release();

private:
    IGraphBuilder*                      m_pGraph;
    IVideoWindow*                       m_pVidWnd;
    IMediaControl*                      m_pMediaControl;
    IMediaEventEx*                      m_pEvent;
    IBasicAudio*                        m_pAudio;

    char                                m_szFilename[512];
    RECT                                m_tagRect;

    HANDLE                              m_hThreadHandle;
    HWND                                m_hWnd;
    bool                                m_bPlaying;
    bool                                m_bLoaded;
    bool                                m_bLoop;
    bool                                m_bKillThread;
    bool                                m_bStopped;

    long                                m_nVolume;
};

#endif
