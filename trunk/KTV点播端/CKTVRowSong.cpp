#include "CKTVRowSong.h"

CKTVRowSong::CKTVRowSong(void)
{
}

CKTVRowSong::~CKTVRowSong(void)
{
}

XModelStream& CKTVRowSong::operator << (XModelStream& s)
{
    for(int i = 0; i < 9; i++)
    {
        if(IsCol(i))
        {
            switch(i)
            {
            case 0: s >> SongNo; break;
            case 1: s >> SongName; break;
            case 2: s >> ArtistNo; break;
            case 3: s >> Lang; break;
            case 4: s >> Hit; break;
            case 5: s >> UpdateTime; break;
            case 6: s >> LastLong; break;
            case 7: s >> Download; break;
            case 8: s >> SongPinyin; break;

            default: break;
            }
        }
    }

    return s;
}
