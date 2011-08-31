//////////////////////////////////////////////////////////////////////////
//
//	KTV歌单类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/26
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVPLAYLIST_H
#define CKTVPLAYLIST_H

#pragma once
#include "global.h"
#include "singleton.h"
#include "cktvmodelsong.h"
#include "../KTV播放端/commoncommand.h"
#include "cktvengine.h"

class CKTVPlayList : public Singleton<CKTVPlayList>
{
public:
    CKTVPlayList(void);
    virtual ~CKTVPlayList(void);

    bool                                AddSongToLast(CKTVRowSong song);
    bool                                AddSongToFirst(CKTVRowSong song);

    bool                                CheckRepeat(CKTVRowSong song, bool del = false);
    CKTVRowSong                         GetNextSong();
    void                                GetList(CKTVRowSong row[]);
    void                                SetList(int row[], int count);
    int                                 GetCount();

    void                                ShowList();
    bool                                IsPaused()
    {
        ::EnterCriticalSection(&m_CriticalSection);
        bool paused = m_bPaused;
        ::LeaveCriticalSection(&m_CriticalSection);
        return paused;
    }
    void                                SetPaused(bool paused)
    {
        ::EnterCriticalSection(&m_CriticalSection);
        m_bPaused = paused;
        ::LeaveCriticalSection(&m_CriticalSection);
    }
    void                                ChangePlayStatus();
    void                                SendCutdownMsg();
    void                                SuffOrder();
    void                                BakPlayList();

    CRITICAL_SECTION*                   GetCriticalSection() { return &m_CriticalSection; }

private:
    vector<CKTVRowSong>                 m_PlayList;

    int                                 m_nCount;
    CRITICAL_SECTION                    m_CriticalSection;

    bool                                m_bPaused;
};

#endif
