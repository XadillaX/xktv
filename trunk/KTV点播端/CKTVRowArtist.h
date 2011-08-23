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
