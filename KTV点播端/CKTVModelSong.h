//////////////////////////////////////////////////////////////////////////
//
//	KTV歌曲模型类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/25
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVMODELSONG_H
#define CKTVMODELSONG_H

#pragma once
#include "commonclass.h"
#include "cktvrowsong.h"

class CKTVModelSong : public XModelObject
{
public:
    CKTVModelSong(void);
    virtual ~CKTVModelSong(void);

    int                                 get_song_by_artistno(int artistno, CKTVRowSong row[], int page = 1, int pageSize = 10);
    int                                 get_song_by_pinyin(string pinyin, CKTVRowSong row[], int page = 1, int pageSize = 10);
    int                                 get_song_count_by_artistno(int artistno);
    int                                 get_song_count_by_pinyin(string pinyin);
    int                                 get_max_page_by_artistno(int artistno, int pageSize = 10);
    int                                 get_max_page_by_pinyin(string pinyin, int pageSize = 10);
};

#endif
