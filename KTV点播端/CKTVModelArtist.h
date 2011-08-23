#ifndef CKTVMODELARTIST_H
#define CKTVMODELARTIST_H

#pragma once
#include "commonclass.h"
#include "cktvrowartist.h"

class CKTVModelArtist : public XModelObject
{
public:
    CKTVModelArtist(void);
    virtual ~CKTVModelArtist(void);

    bool                            get_artist_info(int ArtistNo, CKTVRowArtist* out);
    
    int                             get_artist_info_by_pinyin(string pinyin, CKTVRowArtist row[], int page = 1, int pageSize = 10);
    int                             get_artist_count_by_pinyin(string pinyin);
    int                             get_max_page_by_pinyin(string pinyin, int pageSize = 10);
};

#endif
