#include "global.h"
#include "commoncommand.h"

HGE* g_pHGE = NULL;
CXadillaXVideoPlayer* g_pPlayer = NULL;
HWND g_hWnd = 0;
CRITICAL_SECTION g_CriticalSection;
CKTVNetwork121* g_pNetwork = NULL;
bool g_bRequestingSong = false;
bool g_bPaused = false;

void NetworkReceive(int MainID, int SubID, char* pData, size_t size)
{
    if(MainID == MAINID_REQUEST_SONG)
    {
        switch(SubID)
        {
            /** ²¥·Å¸èÇú */
        case SUBID_REQUEST_NEXT_SONG:
            {
                tagRequestNextSong* pRNS = (tagRequestNextSong*)pData;
                if(strlen(pRNS->path) != 0)
                {
                    RECT rect;
                    rect.left = rect.top = 0;

#ifndef _DEBUG
                    rect.right = 800, rect.bottom = 600;
#else
                    rect.right = 320, rect.bottom = 240;
#endif

                    printf("ÊÕµ½¸èÇúÐÅÏ¢£º%s\n", pRNS->path);

                    //::EnterCriticalSection(&g_CriticalSection);
                    g_pPlayer->LoadFile(pRNS->path, rect, g_hWnd);
                    g_pPlayer->Play();
                    //::LeaveCriticalSection(&g_CriticalSection);
                }

                g_bRequestingSong = false;
                break;
            }

            /** ÔÝÍ£/²¥·Å */
        case SUBID_REQUEST_PAUSE:
            {
                tagRequestPause* pRP = (tagRequestPause*)pData;
                if(pRP->paused)
                {
                    ::EnterCriticalSection(&g_CriticalSection);
                    g_pPlayer->Pause();
                    g_bPaused = true;
                    ::LeaveCriticalSection(&g_CriticalSection);
                }
                else
                if(!pRP->paused)
                {
                    ::EnterCriticalSection(&g_CriticalSection);
                    g_pPlayer->Play();
                    g_bPaused = false;
                    ::LeaveCriticalSection(&g_CriticalSection);
                }

                /** ·´À¡×´Ì¬ */
                g_pNetwork->SendMsg(MainID, SubID, pData, size);
                printf("ÇëÇó %s...\n", (pRP->paused) ? ("ÔÝÍ£") : ("²¥·Å"));

                break;
            }

            /** ÇÐ¸è */
        case SUBID_REQUEST_CUTDOWN:
            {
                ::EnterCriticalSection(&g_CriticalSection);
                if(!g_bRequestingSong)
                {
                    g_pPlayer->Stop();
                    g_bPaused = false;

                    /** ·´À¡×´Ì¬ */
                    g_pNetwork->SendMsg(MainID, SubID, pData, size);
                }
                ::LeaveCriticalSection(&g_CriticalSection);

                break;
            }
        }
    }
}