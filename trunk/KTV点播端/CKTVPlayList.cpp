#include "CKTVPlayList.h"

CKTVPlayList::CKTVPlayList(void) :
    m_nCount(0),
    m_bPaused(false),
    m_nVolume(75)
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
    BakPlayList();

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
    BakPlayList();

#ifdef _DEBUG
    this->ShowList();
#endif

    return true;
}

void CKTVPlayList::ShowList()
{
    ::EnterCriticalSection(&m_CriticalSection);
    printf("歌单: \n");
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
    BakPlayList();

    return rs;
}

void CKTVPlayList::ChangePlayStatus()
{
    tagRequestPause rp;
    rp.paused = !this->IsPaused();

    /** 发送 暂停/播放 请求 */
    ENGINE.Network()->SendMsg(MAINID_REQUEST_SONG, SUBID_REQUEST_PAUSE, (char*)&rp, sizeof(tagRequestPause));
}

void CKTVPlayList::SendCutdownMsg()
{
    const char end = '\0';
    ENGINE.Network()->SendMsg(MAINID_REQUEST_SONG, SUBID_REQUEST_CUTDOWN, &end, 1);
}

void CKTVPlayList::SuffOrder()
{
    ::EnterCriticalSection(&m_CriticalSection);
    random_shuffle(m_PlayList.begin(), m_PlayList.begin() + m_nCount);
    ::LeaveCriticalSection(&m_CriticalSection);
    BakPlayList();

    ShowList();
}

void CKTVPlayList::GetList(CKTVRowSong row[])
{
    ::EnterCriticalSection(&m_CriticalSection);
    for(int i = 0; i < m_nCount; i++) row[i] = m_PlayList[i];
    ::LeaveCriticalSection(&m_CriticalSection);
}

int CKTVPlayList::GetCount()
{
    ::EnterCriticalSection(&m_CriticalSection);
    int cnt = m_nCount;
    ::LeaveCriticalSection(&m_CriticalSection);

    return cnt;
}

void CKTVPlayList::BakPlayList()
{
    ::EnterCriticalSection(&m_CriticalSection);
    CKTVRowSong* row = new CKTVRowSong[m_nCount + 5];
    ::LeaveCriticalSection(&m_CriticalSection);

    GetList(row);

    CKTVModelMachine* pMM = new CKTVModelMachine();
    pMM->back_machine_play_list(ENGINE.MachineInfo()->GetMachineInfo().MachineNo, row, GetCount());

    delete pMM;
    delete []row;
}

void CKTVPlayList::SetList(int row[], int count)
{
    ::EnterCriticalSection(&m_CriticalSection);
    m_PlayList.clear();
    CKTVRowSong* song = new CKTVRowSong[count];
    CKTVModelSong* pMS = new CKTVModelSong();
    count = pMS->get_song_group(row, count, song);
    m_nCount = count;
    for(int i = 0; i < count; i++)
    {
        m_PlayList.push_back(song[i]);
    }
    delete pMS;
    delete []song;
    ::LeaveCriticalSection(&m_CriticalSection);
}

void CKTVPlayList::SetVolume(int volume)
{
    if(volume < 0) volume = 0;
    if(volume > 100) volume = 100;

    ::EnterCriticalSection(&m_CriticalSection);
    if(volume == m_nVolume)
    {
        /** 2011-9-4 这个临界区忘了退出，结果导致一个BUG怎么也找不到！！！！！ */
        ::LeaveCriticalSection(&m_CriticalSection);
        return;
    }
    m_nVolume = volume;
    ::LeaveCriticalSection(&m_CriticalSection);

    /** 发送消息 */
    tagRequestValume RV;
    RV.volume = volume;
    ENGINE.Network()->SendMsg(MAINID_REQUEST_SONG, SUBID_REQUEST_SET_VALUME, (char*)&RV, sizeof(RV));
}
