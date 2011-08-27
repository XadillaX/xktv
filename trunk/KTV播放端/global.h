#ifndef GLOBAL_H
#define GLOBAL_H

#include "cktvnetwork121.h"
#include <cxadillaxvideoplayer.h>
#include <hge.h>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "../KTVµã²¥¶Ë/cktverror.h"
using namespace std;

extern HWND                         g_hWnd;
extern HGE*                         g_pHGE;
extern CXadillaXVideoPlayer*        g_pPlayer;
extern CRITICAL_SECTION             g_CriticalSection;
extern CKTVNetwork121*              g_pNetwork;

extern bool                         g_bRequestingSong;

extern void                         NetworkReceive(int, int, char*, size_t);
extern void                         InitAfterStart();

#endif
