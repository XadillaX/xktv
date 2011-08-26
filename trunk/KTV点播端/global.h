//////////////////////////////////////////////////////////////////////////
//
//	全局文件
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/20
//
//////////////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN

#ifndef GLOBAL_H
#define GLOBAL_H
#include <wtypes.h>

#include <string>
#include <algorithm>
#include <queue>
#include <list>
#include <map>
#include <stack>
using namespace std;

#include <assert.h>
#include <hge.h>
#include <hgesprite.h>
#include <hgeanim.h>
#include <commonclass.h>

#include "singleton.h"
#include "objectfactory.h"

typedef pair<HTEXTURE, hgeSprite*> SpritePair;
typedef pair<HTEXTURE, hgeAnimation*> AnimationPair;

namespace global
{
    /** 常量宏 */
#define KTV_TITLE                       "KTV点播系统"
#define CONFIG_FILE                     "ktv.ini"

    /** 简化宏 */
#define ENGINE                          (CKTVEngine::Instance())
#define TexWidth(a)                     (global::g_pHGE->Texture_GetWidth(a))
#define TexHeight(a)                    (global::g_pHGE->Texture_GetHeight(a))
#define TexWidthP(a)                    (global::g_pHGE->Texture_GetWidth(a.first))
#define TexHeightP(a)                   (global::g_pHGE->Texture_GetHeight(a.first))
#define Tex(a)                          (a.first)
#define Spr(a)                          (a.second)
#define Ani(a)                          (a.second)
#define TexRelease(a)                   { if(a.second != NULL) { delete a.second; a.second = NULL; global::g_pHGE->Texture_Free(a.first); } }

extern HGE*                             g_pHGE;
extern void                             ReceiveFunc(int, int, char*, size_t);
};

#endif
