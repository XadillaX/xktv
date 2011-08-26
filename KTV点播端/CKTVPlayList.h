//////////////////////////////////////////////////////////////////////////
//
//	KTV∏Ëµ•¿‡
//
//	Program by À¿‘¬(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/26
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVPLAYLIST_H
#define CKTVPLAYLIST_H

#pragma once
#include "global.h"
#include "singleton.h"
#include "cktvrowsong.h"

class CKTVPlayList : public Singleton<CKTVPlayList>
{
public:
    CKTVPlayList(void);
    virtual ~CKTVPlayList(void);

    bool                                AddSongToLast(CKTVRowSong song);
    bool                                AddSongToFirst(CKTVRowSong song);

    bool                                CheckRepeat(CKTVRowSong song);
    CKTVRowSong                         GetNextSong();

    void                                ShowList();

    CRITICAL_SECTION*                   GetCriticalSection() { return &m_CriticalSection; }

private:
    vector<CKTVRowSong>                 m_PlayList;

    int                                 m_nCount;
    CRITICAL_SECTION                    m_CriticalSection;
};

#endif
