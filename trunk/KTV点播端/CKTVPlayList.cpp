#include "CKTVPlayList.h"

CKTVPlayList::CKTVPlayList(void) :
    m_nCount(0)
{
    ::InitializeCriticalSection(&m_CriticalSection);
}

CKTVPlayList::~CKTVPlayList(void)
{
}

bool CKTVPlayList::CheckRepeat(CKTVRowSong song, bool del)
{
    ::EnterCriticalSection(&m_CriticalSection);
    vector<CKTVRowSong>::iterator it = m_PlayList.begin();
    for(int i = 0; i < m_nCount; i++, it++)
    {
        if(song.SongNo == m_PlayList[i].SongNo)
        {
            if(del)
            {
                m_PlayList.erase(it);
                m_nCount--;
            }
            ::LeaveCriticalSection(&m_CriticalSection);
            return true;
        }
    }
    ::LeaveCriticalSection(&m_CriticalSection);

    return false;
}

bool CKTVPlayList::AddSongToLast(CKTVRowSong song)
{
    if(CheckRepeat(song)) return false;

    ::EnterCriticalSection(&m_CriticalSection);
    m_PlayList.push_back(song);
    m_nCount++;
    ::LeaveCriticalSection(&m_CriticalSection);

#ifdef _DEBUG
    this->ShowList();
#endif

    return true;
}

bool CKTVPlayList::AddSongToFirst(CKTVRowSong song)
{
    CheckRepeat(song, true);

    ::EnterCriticalSection(&m_CriticalSection);
    m_PlayList.insert(m_PlayList.begin(), song);
    m_nCount++;
    ::LeaveCriticalSection(&m_CriticalSection);

#ifdef _DEBUG
    this->ShowList();
#endif

    return true;
}

void CKTVPlayList::ShowList()
{
    ::EnterCriticalSection(&m_CriticalSection);
    printf("¸èµ¥: \n");
    for(int i = 0; i < m_nCount; i++)
    {
        printf(" %d. %s[%s]\n", i + 1, m_PlayList[i].SongName.c_str(), m_PlayList[i].ArtistName.c_str());
    }

    printf("\n");
    ::LeaveCriticalSection(&m_CriticalSection);
}

CKTVRowSong CKTVPlayList::GetNextSong()
{
    CKTVRowSong rs;
    if(m_nCount == 0)
    {
        rs.SongName = "";
        return rs;
    }

    ::EnterCriticalSection(&m_CriticalSection);
    rs = m_PlayList[0];
    m_PlayList.erase(m_PlayList.begin());
    m_nCount--;
    ::LeaveCriticalSection(&m_CriticalSection);

    return rs;
}
