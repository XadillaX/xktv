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
            /** ���Ÿ��� */
        case SUBID_REQUEST_NEXT_SONG:
            {
                tagRequestNextSong* pRNS = (tagRequestNextSong*)pData;
                if(strlen(pRNS->path) != 0)
                {
                    RECT rect;
                    rect.left = rect.top = 0;

                    /** ������1~100 */
                    DWORD vol = ((float)pRNS->vol / (float)100) * 0xFFFF;
                    
                    /** ����Ϊ0~0xFFFFFFFF�����и�λΪ����������λΪ������ */
                    vol = (vol << 16) + vol;
                    ::waveOutSetVolume(0, vol);

#ifdef _DEBUG
                    rect.right = 800, rect.bottom = 600;
#else
                    rect.right = 320, rect.bottom = 240;
#endif

                    printf("�յ�������Ϣ��%s\n", pRNS->path);

                    ::EnterCriticalSection(&g_CriticalSection);
                    if(g_pPlayer->LoadFile(pRNS->path, rect, g_hWnd))
                    {
                        
                        if(!g_pPlayer->Play())
                        {
                            printf("%s ���Ŵ���...\n", pRNS->path);
                            g_pPlayer->Stop();

                            g_bRequestingSong = false;
                        }
                    }
                    else
                    {
                        printf("%s �򿪴���...\n", pRNS->path);
                        g_bRequestingSong = false;
                    }
                    
                    ::LeaveCriticalSection(&g_CriticalSection);
                }

                ::EnterCriticalSection(&g_CriticalSection);
                g_bRequestingSong = false;
                ::LeaveCriticalSection(&g_CriticalSection);

                break;
            }

            /** ��ͣ/���� */
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

                /** ����״̬ */
                g_pNetwork->SendMsg(MainID, SubID, pData, size);
                printf("���� %s...\n", (pRP->paused) ? ("��ͣ") : ("����"));

                break;
            }

            /** �и� */
        case SUBID_REQUEST_CUTDOWN:
            {
                ::EnterCriticalSection(&g_CriticalSection);
                if(!g_bRequestingSong)
                {
                    g_pPlayer->Stop();
                    g_bPaused = false;

                    /** ����״̬ */
                    g_pNetwork->SendMsg(MainID, SubID, pData, size);
                }
                ::LeaveCriticalSection(&g_CriticalSection);

                break;
            }

            /** ���� */
        case SUBID_REQUEST_SET_VALUME:
            {
                tagRequestValume* pRV = (tagRequestValume*)pData;

                /** ������1~100 */
                DWORD vol = ((float)pRV->volume / 100) * 0xFFFF;
                
                /** ����Ϊ0~0xFFFFFFFF�����и�λΪ����������λΪ������ */
                vol = (vol << 16) + vol;
                ::waveOutSetVolume(0, vol);

                printf("����: 0x%.8X...\n", vol);

                break;
            }
        }
    }
}