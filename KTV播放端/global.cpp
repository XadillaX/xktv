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
            /** 播放歌曲 */
        case SUBID_REQUEST_NEXT_SONG:
            {
                tagRequestNextSong* pRNS = (tagRequestNextSong*)pData;
                if(strlen(pRNS->path) != 0)
                {
                    RECT rect;
                    rect.left = rect.top = 0;

                    /** 音量从1~100 */
                    DWORD vol = ((float)pRNS->vol / (float)100) * 0xFFFF;
                    
                    /** 音量为0~0xFFFFFFFF，其中高位为左声道，低位为右声道 */
                    vol = (vol << 16) + vol;
                    ::waveOutSetVolume(0, vol);

#ifdef _DEBUG
                    rect.right = 800, rect.bottom = 600;
#else
                    rect.right = 320, rect.bottom = 240;
#endif

                    printf("收到歌曲信息：%s\n", pRNS->path);

                    ::EnterCriticalSection(&g_CriticalSection);
                    if(g_pPlayer->LoadFile(pRNS->path, rect, g_hWnd))
                    {
                        
                        if(!g_pPlayer->Play())
                        {
                            printf("%s 播放错误...\n", pRNS->path);
                            g_pPlayer->Stop();

                            g_bRequestingSong = false;
                        }
                    }
                    else
                    {
                        printf("%s 打开错误...\n", pRNS->path);
                        g_bRequestingSong = false;
                    }
                    
                    ::LeaveCriticalSection(&g_CriticalSection);
                }

                ::EnterCriticalSection(&g_CriticalSection);
                g_bRequestingSong = false;
                ::LeaveCriticalSection(&g_CriticalSection);

                break;
            }

            /** 暂停/播放 */
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

                /** 反馈状态 */
                g_pNetwork->SendMsg(MainID, SubID, pData, size);
                printf("请求 %s...\n", (pRP->paused) ? ("暂停") : ("播放"));

                break;
            }

            /** 切歌 */
        case SUBID_REQUEST_CUTDOWN:
            {
                ::EnterCriticalSection(&g_CriticalSection);
                if(!g_bRequestingSong)
                {
                    g_pPlayer->Stop();
                    g_bPaused = false;

                    /** 反馈状态 */
                    g_pNetwork->SendMsg(MainID, SubID, pData, size);
                }
                ::LeaveCriticalSection(&g_CriticalSection);

                break;
            }

            /** 音量 */
        case SUBID_REQUEST_SET_VALUME:
            {
                tagRequestValume* pRV = (tagRequestValume*)pData;

                /** 音量从1~100 */
                DWORD vol = ((float)pRV->volume / 100) * 0xFFFF;
                
                /** 音量为0~0xFFFFFFFF，其中高位为左声道，低位为右声道 */
                vol = (vol << 16) + vol;
                ::waveOutSetVolume(0, vol);

                printf("音量: 0x%.8X...\n", vol);

                break;
            }
        }
    }
}