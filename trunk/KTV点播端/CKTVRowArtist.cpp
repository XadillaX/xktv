#include "CKTVRowArtist.h"

CKTVRowArtist::CKTVRowArtist(void)
{
}

CKTVRowArtist::~CKTVRowArtist(void)
{
}

XModelStream& CKTVRowArtist::operator << (XModelStream& s)
{
    for(int i = 0; i < 6; i++)
    {
        if(IsCol(i))
        {
            switch(i)
            {
            case 0: s >> ArtistNo; break;
            case 1: s >> ArtistName; break;
            case 2: s >> ArtistPro; break;
            case 3: s >> ArtistArea; break;
            case 4: s >> ArtistPhoto; break;
            case 5: s >> ArtistPinyin; break;

            default: break;
            }
        }
    }

    return s;
}
