#include "global.h"

namespace global
{
    HGE*                        g_pHGE = NULL;
};

#include "cktvplaylist.h"
#include "../KTV播放端/commoncommand.h"
#include "cktvengine.h"
void global::ReceiveFunc(int MainID, int SubID, char* pData, size_t size)
{
    if(MainID == MAINID_REQUEST_SONG)
    {
        switch(SubID)
        {
        case SUBID_REQUEST_NEXT_SONG:
            {
                tagRequestNextSong next;
                CKTVRowSong rs = CKTVPlayList::Instance().GetNextSong();
                if(rs.SongName == "")
                {
                    printf("当前列表为空...\n");
                    next.path[0] = '\0';
                    ENGINE.Network()->SendMsg(MainID, SubID, (char*)&next, sizeof(tagRequestNextSong));
                    break;
                }
                else
                {
                    strcpy(next.path, rs.Download.c_str());
                    next.vol = CKTVPlayList::Instance().GetVolume();
                }

                printf("当前播放: %s\n", rs.SongName.c_str());
                CKTVPlayList::Instance().ShowList();
                ENGINE.Network()->SendMsg(MainID, SubID, (char*)&next, sizeof(tagRequestNextSong));

                break;
            }

        case SUBID_REQUEST_PAUSE:
            {
                tagRequestPause* pRP = (tagRequestPause*)pData;
                CKTVPlayList::Instance().SetPaused(pRP->paused);

                printf("当前状态: %s...\n", (pRP->paused) ? "暂停" : "播放");

                break;
            }

        case SUBID_REQUEST_CUTDOWN:
            {
                printf("切歌成功...\n");

                CKTVPlayList::Instance().SetPaused(false);
            }
        }
    }
}
