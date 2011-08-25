//////////////////////////////////////////////////////////////////////////
//
//	KTV歌曲结果类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/25
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVROWSONG_H
#define CKTVROWSONG_H

#pragma once
#include "commonclass.h"

class CKTVRowSong : public XModelRowObject
{
public:
    CKTVRowSong(void);
    virtual ~CKTVRowSong(void);

    virtual XModelStream&               operator << (XModelStream& s);

public:
    int                                 SongNo;
    string                              SongName;
    int                                 ArtistNo;
    string                              Lang;
    int                                 Hit;
    XDataTime                           UpdateTime;
    int                                 LastLong;
    string                              Download;
    string                              SongPinyin;

    string                              ArtistName;
};

#endif
