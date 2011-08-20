//////////////////////////////////////////////////////////////////////////
//
//	全局文件
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/20
//
//////////////////////////////////////////////////////////////////////////
#ifndef GLOBAL_H
#define GLOBAL_H
#include <windows.h>
#include <wtypes.h>

#include <assert.h>
#include <hge.h>
#include <commonclass.h>

#include "singleton.h"
#include "objectfactory.h"

namespace global
{
    /** 常量宏 */
#define KTV_TITLE                       "KTV点播系统"
#define CONFIG_FILE                     "ktv.ini"

    /** 简化宏 */
#define ENGINE                          (CKTVEngine::Instance())


extern HGE*                             g_pHGE;
};
#endif
