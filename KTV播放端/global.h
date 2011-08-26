#ifndef GLOBAL_H
#define GLOBAL_H

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
using namespace std;

extern HWND                         g_hWnd;
extern HGE*                         g_pHGE;
extern CXadillaXVideoPlayer*        g_pPlayer;
extern CRITICAL_SECTION             g_CriticalSection;

#endif
