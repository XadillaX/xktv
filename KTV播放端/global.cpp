#include "global.h"
#include "commoncommand.h"

HGE* g_pHGE = NULL;
CXadillaXVideoPlayer* g_pPlayer = NULL;
HWND g_hWnd = 0;
CRITICAL_SECTION g_CriticalSection;
CKTVNetwork121* g_pNetwork = NULL;
bool g_bRequestingSong = false;

void NetworkReceive(int MainID, int SubID, char* pData, size_t size)
{
    if(MainID == MAINID_REQUEST_SONG)
    {
        switch(SubID)
        {
            /** 播放歌曲 */
        case SUBID_REQUEST_NEXT_SONG:
            {
                tagRequestNextSong* pRNS = (tagRequestNextSong*)pData;
                if(strlen(pRNS->path) != 0)
                {
                    RECT rect;
                    rect.left = rect.top = 0;
                    rect.right = 800, rect.bottom = 600;

                    printf("收到歌曲信息：%s\n", pRNS->path);
                    g_pPlayer->LoadFile(pRNS->path, rect, g_hWnd);
                    g_pPlayer->Play();
                }

                g_bRequestingSong = false;
            }
        }
    }
}