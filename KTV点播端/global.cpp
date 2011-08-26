#include "global.h"

namespace global
{
    HGE*                        g_pHGE = NULL;
};

#include "cktvplaylist.h"
#include "../KTV���Ŷ�/commoncommand.h"
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
                    printf("��ǰ�б�Ϊ��...\n");
                    next.path[0] = '\0';
                    ENGINE.Network()->SendMsg(MainID, SubID, (char*)&next, sizeof(tagRequestNextSong));
                    break;
                }
                else strcpy(next.path, rs.Download.c_str());

                printf("��ǰ����: %s\n", rs.SongName.c_str());
                CKTVPlayList::Instance().ShowList();
                ENGINE.Network()->SendMsg(MainID, SubID, (char*)&next, sizeof(tagRequestNextSong));

                break;
            }
        }
    }
}
