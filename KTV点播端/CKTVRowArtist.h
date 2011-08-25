//////////////////////////////////////////////////////////////////////////
//
//	KTV歌手结果类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/24
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVROWARTIST_H
#define CKTVROWARTIST_H

#pragma once
#include "commonclass.h"

class CKTVRowArtist : public XModelRowObject
{
public:
    CKTVRowArtist(void);
    virtual ~CKTVRowArtist(void);

    virtual XModelStream&       operator << (XModelStream& s);

public:
    int                         ArtistNo;
    string                      ArtistName;
    string                      ArtistPro;
    string                      ArtistArea;
    string                      ArtistPhoto;
    string                      ArtistPinyin;
};

#endif
